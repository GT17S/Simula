#include "../include/logiqueReseau/Switch.hh"

Switch::Switch(std::string  nom,int idNoeud,int nbPort)
{
    this->nom="Switch"+idNoeud;
    this->idNoeud=idNoeud;
    this->nbPort=nbPort;
}
Switch::~Switch(){

}

void Switch::envoyerMessage(Noeud *nRecepteur, std::string message){
// a implimenter
}
