#include "Hub.hh"
using namespace std;

Hub::Hub(string _nom,int _idNoeud,int _nbPort)
    : Noeud(_nom, _idNoeud, _nbPort){}

Hub::Hub() : Noeud(){
	nom = "Hub"+std::to_string(idNoeud);	
}

Hub::~Hub(){
}

void Hub::envoyerBroadCast(string message){
    //a implimenter
}
void Hub::envoyerMessage(Noeud * _nRecepteur, string message){
       //vide
}




