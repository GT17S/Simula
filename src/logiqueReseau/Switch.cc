#include "Switch.hh"
#include <iostream>
#include "DataOutils.hh"


Switch::Switch(string  _nom,int _idNoeud,int _nbPort, SwitchG * parent) :
    Hub(_nom, _idNoeud, _nbPort, parent)
{
    type = SWITCH;
    setParent(parent);

}

Switch::Switch(SwitchG * parent) : Hub(parent) {
    // ID automatique
    // nb port =1
    // filedattente vide
    setNom("Switch"+std::to_string(idNoeud));
    type = SWITCH;
    setParent(parent);

}

Switch::~Switch(){

}
void Switch::envoyerMessage(int key, destination dest){

    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);


    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p){
        std::cout<<"Je connais pas le chemin vers "<<id_dest<<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers "+ Graphe::getSommets()[id_dest]->getNom()));

        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);
    //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers ")+QString::fromStdString(extNext->noeud->getNom()));

    extNext->noeud->recevoirMessage(key, extNext->interface, dest);
}

void Switch::recevoirMessage(int key, int dest_i, destination dest){
    std::cout <<"Je suis un switch"<< idNoeud<<std::endl;
    if(dest.data->getType() < 3){
        std::cout <<"Data non encapsulée"<<std::endl;
        return;
    }

    //int id_dest = lireAdresseMac(data, 1);
    envoyerMessage(key, dest);
}
