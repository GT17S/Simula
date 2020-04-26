#include "../include/logiqueReseau/Routeur.hh"

Routeur::Routeur() : Noeud(){
    // ID automatique
    // nb port = 1
    // filedattente vide
    nom = "Routeur"+std::to_string(idNoeud);

}

Routeur::Routeur(String nom, int idNoeud, int nbPort, vector<InterfaceFE *>){

}

void Routeur::setTableNoeuds(Noeud *){

}

void Routeur::setTableNoeuds(vector<Noeud *>){

}

void Routeur::setTableRoutage(Route *){

}

void Routeur::setTableRoutage(vector<Route *>){

}

void Routeur::setTableInterface(InterfaceFE *){

}

void Routeur::setTableInterface(vector<InterfaceFE *>){

}

void Routeur::envoyerMessage(Noeud *Nrecepteur, std::string message){

}
