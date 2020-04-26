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
void Hub::setTableNoeuds(Noeud* noeud){
    /*unsigned int i;
    i= tableNoeuds.size();
    tableNoeuds[i+1]=noeud;*/
    tableNoeuds.push_back(noeud);
}
void Hub::setTableNoeuds(vector<Noeud*> noeuds){
    tableNoeuds=noeuds;

}
void Hub::envoyerBroadCast(string message){
    //a implimenter
}
void Hub::envoyerMessage(Noeud *nRecepteur, std::string message){
       //vide
}



