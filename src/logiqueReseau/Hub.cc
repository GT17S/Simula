#include "Hub.hh"
#include "DataOutils.hh"

Hub::Hub(string _nom,int _idNoeud,int _nbPort)
    : Noeud(_nom, _idNoeud, _nbPort){

    type = HUB;
}

Hub::Hub() : Noeud(){
	nom = "Hub"+std::to_string(idNoeud);	
    type = HUB;
}

Hub::~Hub(){
}

void Hub::envoyerBroadCast(string message){
    //a implimenter
}
void Hub::envoyerMessage(int key,destination dest){

    int id_src  = lireAdresseMac(dest.data, 0);

    std::cout <<"J'envoie le message à tous les membres"<< std::endl;
    for(InterfaceFE * ie: interfaces){
        extremite * ext = ie->getCable()->getInverseExt(this);
        if(ext && ext->noeud->getIdNoeud() != id_src){
            //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
            ext->noeud->recevoirMessage(key, ext->interface, dest);
        }
    }
}

void Hub::recevoirMessage(int key, int dest_i, destination dest){
    std::cout <<"Je suis un hub"<< idNoeud<<std::endl;

    //int id_dest = lireAdresseMac(data, 1);
    envoyerMessage(key, dest);

}




