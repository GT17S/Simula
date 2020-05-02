#include "Hub.hh"
using namespace std;

Hub::Hub(string _nom,int _idNoeud,int _nbPort)
    : Noeud(_nom, _idNoeud, _nbPort){}

Hub::Hub() : Noeud(){}

Hub::~Hub(){
     nom = "Hub"+std::to_string(idNoeud);
}

void Hub::envoyerBroadCast(string message){
    //a implimenter
}
void Hub::envoyerMessage(Noeud * _nRecepteur, string message){
       //vide
}




