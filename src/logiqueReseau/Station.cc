#include "../include/logiqueReseau/Station.hh"


Station::Station() : Noeud(){

}

Station::Station(string nom, int idNoeud, int nbPort, string adressePasserelle, InterfaceFE interfacePc):
                 Noeud(nom, idNoeud, nbPort){

}

void Station::setInterfacePc(InterfaceFE interfacePc){

}

void Station::setPasserelle(string adressePasserelle){

}

void Station::setNumSegmentsEnvoye(int nSegment){

}

void Station::setNumSegmentsEnvoye(vector<int> numSegmentsEnvoye){

}

void Station::envoyerMessage(Noeud *Nrecepteur, string message){

}
