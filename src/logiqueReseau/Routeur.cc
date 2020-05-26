#include "simulaGui.hh"
#include "gSimulation.hh"
#include "Routeur.hh"
#include "DataOutils.hh"


Routeur::Routeur(RouteurG * parent) : Noeud(parent){
    // ID automatique
    // nb port = 1
    // filedattente vide
    setNom("Routeur"+std::to_string(idNoeud));
    type = ROUTEUR;
    setParent(parent);
}

Routeur::Routeur(string _nom, int _idNoeud, int _nbPort, RouteurG *parent) :
    Noeud(_nom, _idNoeud, _nbPort, parent){
    type = ROUTEUR;
    setParent(parent);

}

Routeur::~Routeur(){

}

void Routeur::envoyerMessage(int key, destination dest){
    int id_dest = lireAdresseMac(dest.data, 1);
    int id_src  = lireAdresseMac(dest.data, 0);


    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, true);
    int size_p = path.size();

    if(!size_p){
       // std::cout << "Je connais pas le chemin vers "<<id_dest<<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers ")+QString::fromStdString(Graphe::getSommets()[id_dest]->getNom()));

        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);

	if ( this->checkSimulationStat( dest)) return;

	//if ( true) return;
    //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    //_message = std::to_string(id_next)+"_"+std::to_string(id_dest);
    std::this_thread::sleep_for(Graphe::getWaitTime());
    PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Envoyer donnée vers :s")+QString::fromStdString(extNext->noeud->getNom()));

    extNext->noeud->recevoirMessage(key, extNext->interface,  dest);
}

void Routeur::recevoirMessage(int key, int dest_i, destination dest){
	if ( this->checkSimulationStat( dest)) return;
    std::cout <<"Je suis un routeur"<< idNoeud<<std::endl;

    if(dest.data->getType() < 3){
        std::cout <<"Data non encapsuler"<<std::endl;
        return;
    }

    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);

    if(idNoeud == id_dest){
        std::cout <<"Cest moi la passerelle" <<std::endl;

        desencapsule_trame(dest.data);
        string ipSrc = getInterface(dest_i)->getAdresseIP();
        if(ipSrc == lireAdresseIp(dest.data, 1)){
           // std::cout <<"Cest moi la destination" <<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Arrivé à destination "));

            desencapsule_paquet(dest.data);
            desencapsule_segment(dest.data);
            std::cout <<showMessage(dest.data) <<std::endl;
            delete dest.data;
        }
        else {

            // generer chemin complet, jusqua la destination
            vector<Cable *> path;
            string ip_dest_string = lireAdresseIp(dest.data, 1);
            int ip_dest = Graphe::noeudFromIp(ip_dest_string);
            if(ip_dest < 0)
                return;

            Graphe::genererChemin(id_src, idNoeud, ip_dest, path, false);
            int size_p = path.size();
            // pas de chemin
            if(!size_p){
                std::cout << "Je connais pas le chemin vers " <<ip_dest<<std::endl;
                PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers "+ Graphe::getSommets()[id_dest]->getNom()));

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
            srcExt->noeud = Graphe::getSommets()[id_src];
            srcExt->interface = dest.interface_src;

            // fragmentation
            Cable * next_cable = path[size_p -1];
            //Cable * prec_cable = getInterface(dest_i)->getCable(); // cable precedent
            int mtu = next_cable->getMTU() / 8;
            int tp_initial = (int) lire_bits ( *(dest.data->getSeq()), 16, 16).to_ulong()-20;
            //std::cout << dest.data->getSeq()->size() << std::endl;

            //std::cout <<"MTU = "<< mtu<<" TP  "<<tp_initial<< std::endl;
            if(mtu < tp_initial){
                //fragmenter
               PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Fragmentation de paquet"));

                unsigned int df = (unsigned int) lire_bits ( *(dest.data->getSeq()), 49, 1).to_ulong();
                if(df) { delete dest.data; return;}
                vector<Data*> fragments = fragmentationPaquet(*(dest.data), mtu);

                for(Data * d : fragments){
                    encapsule_paquet ( srcExt, destExt, d);
                    destination t_dest;
                    t_dest.data = d;
                    t_dest.interface_src = dest.interface_src;
                    envoyerMessage(key, t_dest);
                }

                delete dest.data;
            }else {
                encapsule_paquet ( srcExt, destExt, dest.data);
                envoyerMessage(key, dest);
            }

        }
    }
    else {
        //std::cout <<"Mauvaise destination" <<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Mauvaise destination"));

        return;
    }
}



