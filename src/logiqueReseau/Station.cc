#include "../include/logiqueReseau/Station.hh"


Station::Station(){

}

Station::Station(std::string nom, int idNoeud, int nbPort, std::string adressePasserelle, InterfaceFE interfacePc){

}

void Station::setInterfacePc(InterfaceFE interfacePc){

}

void Station::setPasserelle(std::string adressePasserelle){

}

void Station::setNumSegmentsEnvoye(int nSegment){

}

void Station::setNumSegmentsEnvoye(std::vector<int> numSegmentsEnvoye){

}

void Station::envoyerMessage(Noeud *Nrecepteur, Data message){

}
