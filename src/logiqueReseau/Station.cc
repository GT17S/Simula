#include "Station.hh"
#include "DataOutils.hh"


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

void Station::envoyerMessage(Data * data){


    // station , j'ai preparer la distination , j'envoie

    /*if(id_next != idNoeud){
        std::cout<<"Mauvaise destination"<<std::endl;
        return;
    }*/
    // passerelle
    int id_src  = lireAdresseMac(data, 0);
    int id_dest = lireAdresseMac(data, 1);
    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p){
        std::cout << "Je connais pas le chemin vers "<<id_dest<<std::endl;
        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);

    //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    //_message = std::to_string(id_next)+"_"+std::to_string(id_dest);
    extNext->noeud->recevoirMessage(extNext->interface, data);

}

void Station::recevoirMessage(int interface, Data * data){
    std::cout <<"Je suis une station "<< idNoeud<<std::endl;
    int mac_dest = lireAdresseMac(data, 1);
    std::cout << mac_dest <<std::endl;

    if(idNoeud == mac_dest){
           std::cout <<"Cest moi la passerelle" <<std::endl;
           desencapsule_trame(data);
           string ipSrc = getInterface(interface)->getAdresseIP();
           if(ipSrc == lireAdresseIp(data, 1)){
               std::cout <<"Cest moi la destination" <<std::endl;
               desencapsule_paquet(data);
               desencapsule_segment(data);
               std::cout <<showMessage(data) <<std::endl;
           }
           else {
               // generer chemin jusqua cette IP
               // encapsule paquet , avec la nouvelle @mac dest
               // envoyer message
           }
    }
    else {
        std::cout <<"Mauvaise destination" <<std::endl;
        return;
    }
    /*
    -station recoit le message,
    -elle lit la trame (@mac dest)
    -si @macdest = this->@macdest
        - desencapsule la trame => paquet
        - elle lit le paquet (@ip dest)
        - si @ipdest = this->@ip je suis le destinataire
            - desencapsulation jusqua lire le message
        - sinon, generer chemin jusqua cette distination
                - envoyer(message)
    -sinon, mauvaise destination

    */
}

















