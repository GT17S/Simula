#include "../include/logiqueReseau/Hub.hh"
using namespace std;

Hub::Hub(string nom,int idNoeud,int nbPort)
{
    this->nom="Hub"+idNoeud;
    this->idNoeud=idNoeud;
    this->nbPort=nbPort;
}
Hub::Hub(){

}
Hub::~Hub(){

}

void Hub::envoyerBroadCast(string message){
    //a implimenter
}
void Hub::envoyerMessage(Noeud * _nRecepteur, string message){
       //vide
}



