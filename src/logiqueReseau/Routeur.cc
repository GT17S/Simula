#include "../include/logiqueReseau/Routeur.hh"

Routeur::Routeur() : Noeud(){
    // ID automatique
    // nb port = 1
    // filedattente vide
    nom = "Routeur"+std::to_string(idNoeud);

}

Routeur::Routeur(string _nom, int _idNoeud, int _nbPort){

}

Routeur::~Routeur(){

}

void Routeur::setTableRoutage(Route *){

}

void Routeur::setTableRoutage(vector<Route *>){

}

void Routeur::envoyerMessage(Noeud *Nrecepteur, std::string message){

}
