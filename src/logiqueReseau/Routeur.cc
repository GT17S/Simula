#include "../include/logiqueReseau/Routeur.hh"

Routeur::Routeur() : Noeud(){
    // ID automatique
    // nb port = 1
    // filedattente vide
    nom = "Routeur"+std::to_string(idNoeud);

}

Routeur::Routeur(string _nom, int _idNoeud, int _nbPort) :
           Noeud(_nom, _idNoeud, _nbPort){

}

Routeur::~Routeur(){

}

void Routeur::envoyerMessage(Noeud *Nrecepteur, std::string message){

}
