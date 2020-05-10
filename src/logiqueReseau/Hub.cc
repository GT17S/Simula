#include "Hub.hh"

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
void Hub::envoyerMessage(string _message){
    std::cout <<"Je suis un hub"<< std::endl;

    std::cout <<"J'envoie le message à tous les membres"<< std::endl;
    for(InterfaceFE * ie: interfaces){
        extremite * ext = ie->getCable()->getInverseExt(this);
        if(ext){
            std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
            ext->noeud->envoyerMessage(_message);
        }
    }
}




