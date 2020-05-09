#include "Station.hh"


Station::Station() : Noeud(){
    // ID automatique
    // nb port =1
    // filedattente vide
    nom = "Station"+std::to_string(idNoeud);
    adressePasserelle = DEFAULT_IP;
    type = STATION;

}

Station::Station(string _nom, int _idNoeud, int _nbPort, string _adressePasserelle):
                 Noeud(_nom, _idNoeud, _nbPort){
    // file dattente vide
    setPasserelle(_adressePasserelle);
    type = STATION;

}


void Station::setPasserelle(string _adresse){
     adressePasserelle = InterfaceFE::checkAdresse(_adresse, IP_REGEX, DEFAULT_IP);

}

void Station::setNumSegmentsEnvoye(int _nSegment){
    for(int ns : numSegmentsEnvoye){
        // Existe déja
        if(ns == _nSegment)
            return;
    }

    numSegmentsEnvoye.push_back(_nSegment);

}

void Station::setNumSegmentsEnvoye(vector<int> _numSegmentsEnvoye){
    numSegmentsEnvoye = _numSegmentsEnvoye;
}

void Station::envoyerMessage(string _message){
    std::cout << _message << std::endl;
    std::cout <<"Je suis une station "<< idNoeud<<std::endl;
    // id_next _ id_dest
    int id_next = std::stoi(_message.substr(0, _message.find("_")));
    _message.erase(0, _message.find("_") + 1);
    int id_dest = std::stoi(_message);

    if(id_dest == idNoeud){
        std::cout<<"c'est moi la distination"<<std::endl;
        return;
    }
    /*if(id_next != idNoeud){
        std::cout<<"Mauvaise destination"<<std::endl;
        return;
    }*/
    // passerelle
    vector<Cable*> path;
    Graphe::genererChemin(idNoeud, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p)
        return;

    extremite * ext = path[size_p -1]->getInverseExt(this);

    std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    _message = std::to_string(id_next)+"_"+std::to_string(id_dest);
    ext->noeud->envoyerMessage(_message);

}



