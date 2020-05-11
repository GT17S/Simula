#include "Station.hh"
#include "DataOutils.hh"




Station::Station() : Noeud(){
    // ID automatique
    // nb port =1
    // filedattente vide
    nom = "Station"+std::to_string(idNoeud);
    adressePasserelle = DEFAULT_IP;
    type = STATION;
    controleur = new Congestion();
    numSeq = 1;
    isPasserelle = false;

}

Station::Station(string _nom, int _idNoeud, int _nbPort, string _adressePasserelle, bool _isPasserelle):
    Noeud(_nom, _idNoeud, _nbPort){
    // file dattente vide
    setPasserelle(_adressePasserelle);
    type = STATION;
    isPasserelle = _isPasserelle;
}


void Station::setPasserelle(string _adresse){
    adressePasserelle = InterfaceFE::checkAdresse(_adresse, IP_REGEX, DEFAULT_IP);

}


void Station::setControleur(Congestion *_controleur){
    controleur = _controleur;
}
int Station::getNextNumSeq()
{
    numSeq++;
    return numSeq-1;
}

void Station::setNumSeq(int _numSeq)
{
    numSeq = _numSeq;
}

void Station::setIsPasserelle(bool _isPasserelle){
    isPasserelle = _isPasserelle;
}


void Station::envoyerMessage(int key, destination dest){

    // passerelle
    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);
    if(id_src < 0 || id_dest < 0){
        std::cout <<"Lecture @mac probleme "<<id_src<<" "<<id_dest<< std::endl;
        return;
    }

    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p){
        std::cout << "Je connais pas le chemin vers "<<id_dest<<std::endl;
        return;
    }

    // prochaine destination
    extremite * extNext = path[size_p -1]->getInverseExt(this);
    extNext->noeud->recevoirMessage(key, extNext->interface, dest);

}

void Station::recevoirMessage(int key, int dest_i, destination dest){
    std::cout <<"Je suis une station "<< idNoeud<<std::endl;
   // std::cout <<"TYPE DATA = "<< dest.data->getType() << std::endl;
    if(dest.data->getType() < 3){
        std::cout <<"Data non encapsuler"<<std::endl;
        return;
    }

    int mac_dest = lireAdresseMac(dest.data, 1);
    int mac_src = lireAdresseMac(dest.data, 0);

    if(mac_dest < 0 || mac_src < 0){
        std::cout << "Lecture @mac probleme "<<mac_src<<" "<<mac_dest<< std::endl;
        return;
    }
    if(idNoeud == mac_dest){
        desencapsule_trame(dest.data);
        string ipSrc = getInterface(dest_i)->getAdresseIP();
        string ipDest= lireAdresseIp(dest.data, 1);
        if(ipSrc == DEFAULT_IP || ipDest == DEFAULT_IP){
            std::cout<< "Probleme lecture @ip" <<std::endl;
            return;
        }

        if(ipSrc == ipDest){
            std::cout <<"Cest moi la destination" <<std::endl;
            desencapsule_paquet(dest.data);
            // lire ack et syn
            int flags = lireFlagSegment(dest.data);
            if(flags == 2 || flags == 18){
                // syn = 1, doit repondre ack
                if(flags == 18){
                    std::cout <<"J'ai bien recu un ack"<<std::endl;
                    int nAck = lire_bits ( *(dest.data)->getSeq(), 64, 32).to_ulong();
                    if(nAck < 0) return;
                    // supprimer de la file d'attente
                    controleur->verifieNumAck(this, nAck);
                }
                Noeud * n2 = Graphe::getSommets()[mac_src];
                // retourner un ACK
                int nSeq = lire_bits ( *(dest.data)->getSeq(), 32, 32).to_ulong();
                if(nSeq < 0) return;

                desencapsule_segment(dest.data);
                std::cout <<"Jai recu le message :"<<std::endl<<showMessage(dest.data) <<std::endl;

                // envoi nouveau ack
                controleur->verifieNumSegment(this, n2, nSeq+1);
            }
            else if(flags == 16){
                // ack = 1, accusé ack
                std::cout <<"J'ai bien recu un ack"<<std::endl;
                int nAck = lire_bits ( *(dest.data)->getSeq(), 64, 32).to_ulong();
                if(nAck < 0) return;

                desencapsule_segment(dest.data);
                std::cout <<"Jai recu le message :"<<std::endl<<showMessage(dest.data) <<std::endl;
                // supprimer de la file d'attente
                controleur->verifieNumAck(this, nAck);
            }else {

                desencapsule_segment(dest.data);
                std::cout <<"Jai recu le message :"<<std::endl<<showMessage(dest.data) <<std::endl;
                return;
            }
        }
        else {
            /// Station est une passerelle
            if(isPasserelle){
                std::cout <<"Je suis une passerelle"<<std::endl;
                // generer chemin complet, jusqua la destination
                vector<Cable *> path;
                string ip_dest_string = lireAdresseIp(dest.data, 1);
                int ip_dest = Graphe::noeudFromIp(ip_dest_string);
                if(ip_dest < 0)
                    return;

                Graphe::genererChemin(mac_src, idNoeud, ip_dest, path, false);
                int size_p = path.size();
                // pas de chemin
                if(!size_p){
                    std::cout << "Je connais pas le chemin vers " <<ip_dest<<std::endl;
                    return;
                }

                // get next
                extremite * destExt; // destination finale
                Cable * cable;
                Noeud * n = this;
                for(int i = size_p - 1; i > -1; i--){
                    cable = path[i];
                    destExt = cable->getInverseExt(n);

                    n = destExt->noeud;
                }
                // encapsuler paquet avec la prochaine @mac
                extremite* srcExt = new extremite;
                srcExt->noeud = Graphe::getSommets()[mac_src];
                srcExt->interface = dest.interface_src;

                encapsule_paquet ( srcExt, destExt, dest.data);
                envoyerMessage(key, dest);

            }

            else
                std::cout <<"Je ne suis pas une passerelle"<<std::endl;

            return;
        }
    }
    else {
        std::cout <<"Mauvaise destination" <<std::endl;
        return;
    }

}

/* TABLE DE VERITE ACK SYN FIN :
    0	0	0	0	0	0   = 0
    0	0	0	0	0	FIN = 1
    0	0	0	0	SYN 0   = 2
    0	0	0	0	SYN FIN = 3
    0	ACK 0	0	0   0   = 16
    0	ACK 0	0	0   FIN = 17
    0	ACK 0	0	SYN 0   = 18
    0	ACK 0	0	SYN FIN = 19
*/

/*
//  unsigned int mf = (unsigned int) lire_bits ( p, 50, 1).to_ulong();
//  unsigned int df = (unsigned int) lire_bits ( p, 49, 1).to_ulong();
//    unsigned int offset = (unsigned int)lire_bits ( p, 51, 13).to_ulong();
mf = 0 et offset = 0 : paquet non fragmenté
mf = 0 et offset != 0 : dernier fragment
mf = 1 et offset = 0 : premier fragment
mf = 1 et offset != 0 : fragments


*/










