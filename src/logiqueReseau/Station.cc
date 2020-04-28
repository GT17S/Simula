#include "../../include/logiqueReseau/Station.hh"


Station::Station() : Noeud(), numSegmentsEnvoye(){
    // ID automatique
    // nb port =1
    // filedattente vide
    nom = "Station"+std::to_string(idNoeud);
    adressePasserelle = DEFAULT_IP;

}

Station::Station(string _nom, int _idNoeud, int _nbPort, string _adressePasserelle):
                 Noeud(_nom, _idNoeud, _nbPort), numSegmentsEnvoye(){
    // file dattente vide
    setPasserelle(_adressePasserelle);

}


void Station::setPasserelle(string _adresseIP){
    if(InterfaceFE::regexValide(_adresseIP, DEFAULT_IP))
        adressePasserelle = _adresseIP;
    else
        adressePasserelle = DEFAULT_IP;

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

void Station::envoyerMessage(Noeud * _Nrecepteur, string _message){

}
