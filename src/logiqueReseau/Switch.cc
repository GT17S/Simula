#include "Switch.hh"
#include <iostream>

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
void Switch::envoyerMessage(string _message){
    std::cout << _message << std::endl;
    std::cout <<"Je suis un switch"<< idNoeud<<std::endl;
    // id_next _ id_dest
    int id_next = std::stoi(_message.substr(0, _message.find("_")));
    //_message.erase(0, _message.find("_") + 1);
    //int id_dest = std::stoi(d);
    vector<Cable*> path;
    Graphe::genererChemin(idNoeud, idNoeud, id_next, path, false);
    int size_p = path.size();

    if(!size_p){
        std::cout<<"Je connais pas la distination"<<std::endl;
        return;
    }
    extremite * ext = path[size_p -1]->getInverseExt(this);
    std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    ext->noeud->envoyerMessage(_message);

}
