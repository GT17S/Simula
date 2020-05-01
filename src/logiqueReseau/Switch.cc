#include "../include/logiqueReseau/Switch.hh"

Switch::Switch(std::string  _nom,int _idNoeud,int _nbPort) :
    Hub(_nom, _idNoeud, _nbPort)
{

}

Switch::Switch() : Hub() {
    // ID automatique
    // nb port =1
    // filedattente vide
    nom = "Switch"+std::to_string(idNoeud);

}

Switch::~Switch(){

}
void Switch::envoyerMessage(Noeud *nRecepteur, std::string message){
// a implimenter
}
