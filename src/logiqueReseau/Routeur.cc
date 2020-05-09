#include "Routeur.hh"

Routeur::Routeur() : Noeud(){
    // ID automatique
    // nb port = 1
    // filedattente vide
    nom = "Routeur"+std::to_string(idNoeud);
    type = ROUTEUR;
}

Routeur::Routeur(string _nom, int _idNoeud, int _nbPort) :
           Noeud(_nom, _idNoeud, _nbPort){
    type = ROUTEUR;

}

Routeur::~Routeur(){

}

void Routeur::envoyerMessage(string _message){
    std::cout <<"Je suis un routeur"<< idNoeud<<std::endl;

    int id_next = std::stoi(_message.substr(0, _message.find("_")));
    _message.erase(0, _message.find("_") + 1);
    int id_dest = std::stoi(_message);

    if(id_dest == idNoeud){
        std::cout<<"c'est moi la distination"<<std::endl;
        return;
    }
    if(id_next != idNoeud){
        std::cout<<"Mauvaise destination"<<std::endl;
        return;
    }
    // passerelle
    vector<Cable*> path;
    Graphe::genererChemin(idNoeud, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p)
        return;

    extremite * ext_next = path[size_p -1]->getInverseExt(this);

    // get next
    extremite * nextDest;
    Cable * cable;
    Noeud * nextNoeud = this;

    for(int i = size_p - 1; i > -1; i--){
        cable = path[i];
        nextDest = cable->getInverseExt(nextNoeud); // 6
        nextNoeud = nextDest->noeud;
    }


    std::cout <<"J'envoie le message à "<<ext_next->noeud->getIdNoeud()<< std::endl;
    _message = std::to_string(nextNoeud->getIdNoeud())+"_"+std::to_string(id_dest);
    ext_next->noeud->envoyerMessage(_message);

}
