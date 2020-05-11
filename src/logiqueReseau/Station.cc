#include "Station.hh"
#include "DataOutils.hh"


int Station::getNumSeq()
{
    return numSeq;
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

Station::Station() : Noeud(){
    // ID automatique
    // nb port =1
    // filedattente vide
    nom = "Station"+std::to_string(idNoeud);
    adressePasserelle = DEFAULT_IP;
    type = STATION;
    controleur = new Congestion();
    numSeq = 1;

}

Station::Station(string _nom, int _idNoeud, int _nbPort, string _adressePasserelle):
                 Noeud(_nom, _idNoeud, _nbPort){
    // file dattente vide
    setPasserelle(_adressePasserelle);
    type = STATION;
}


void Station::setPasserelle(string _adresse){
     adressePasserelle = InterfaceFE::checkAdresse(_adresse, IP_REGEX, DEFAULT_IP);

}


void Station::setControleur(Congestion *_controleur){
    controleur = _controleur;
}

void Station::envoyerMessage(int key, destination dest){

    // passerelle
    std::cout << dest.data->getType() <<std::endl;
    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);
    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);


    int size_p = path.size();

    if(!size_p){
        std::cout << "Je connais pas le chemin vers "<<id_dest<<std::endl;
        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);

    //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    //_message = std::to_string(id_next)+"_"+std::to_string(id_dest);
    extNext->noeud->recevoirMessage(key, extNext->interface, dest);

}

void Station::recevoirMessage(int key, int dest_i, destination dest){
    std::cout <<"Je suis une station "<< idNoeud<<std::endl;
    int mac_dest = lireAdresseMac(dest.data, 1);
    int mac_src = lireAdresseMac(dest.data, 0);

    if(idNoeud == mac_dest){
           std::cout <<"Cest moi la passerelle" <<std::endl;
           desencapsule_trame(dest.data);
           string ipSrc = getInterface(dest_i)->getAdresseIP();
           if(ipSrc == lireAdresseIp(dest.data, 1)){
               std::cout <<"Cest moi la destination" <<std::endl;
               desencapsule_paquet(dest.data);
               // lire ack et syn
               int flags = lireFlagSegment(dest.data);
               std::cout<<"Flags = "<<flags<<std::endl;
               if(flags == 2 || flags == 18){
                   // syn = 1, doit repondre ack
                   if(flags == 18){
                       std::cout <<"J'ai bien recu un ack"<<std::endl;
                       controleur->verifieNumAck(this, dest.data);

                   }
                   //Data * ndata = new Data("");
                   Noeud * n2 = Graphe::getSommets()[mac_src];
                   controleur->verifieNumSegment(this, n2, dest.data);

                  // return;

               }
               else if(flags == 16){
                   // ack = 1, accusé ack

                   std::cout <<"J'ai bien recu un ack"<<std::endl;

                   controleur->verifieNumAck(this, dest.data);
               }else {
                   std::cout <<"Probleme lecture data"<<std::endl;
                   return;
               }


               desencapsule_segment(dest.data);

               std::cout <<showMessage(dest.data) <<std::endl;
               std::cout <<"FILE ACK "<<controleur->mapFileACK.size()<<std::endl;
               std::cout <<"FILE EN "<<controleur->mapFileEnvoyer.size()<<std::endl;
           }
           else {
               // generer chemin jusqua cette IP
               // encapsule paquet , avec la nouvelle @mac dest
               // envoyer message
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















