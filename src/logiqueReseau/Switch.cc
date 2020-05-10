#include "Switch.hh"
#include <iostream>
#include "DataOutils.hh"


Switch::Switch(string  _nom,int _idNoeud,int _nbPort) :
    Hub(_nom, _idNoeud, _nbPort)
{
    type = SWITCH;
}

Switch::Switch() : Hub() {
    // ID automatique
    // nb port =1
    // filedattente vide
    nom = "Switch"+std::to_string(idNoeud);
    type = SWITCH;

}

Switch::~Switch(){

}
void Switch::envoyerMessage(Data * data){

    int id_src  = lireAdresseMac(data, 0);
    int id_dest = lireAdresseMac(data, 1);


    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p){
        std::cout<<"Je connais pas le chemin vers "<<id_dest<<std::endl;
        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);
    //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    extNext->noeud->recevoirMessage(extNext->interface, data);
}

void Switch::recevoirMessage(int interface, Data * data){
    std::cout <<"Je suis un switch"<< idNoeud<<std::endl;

    //int id_dest = lireAdresseMac(data, 1);
    envoyerMessage(data);

}
