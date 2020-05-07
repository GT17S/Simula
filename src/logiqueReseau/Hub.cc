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
void Hub::envoyerMessage(Noeud * _nRecepteur, string message){
       //vide
}




