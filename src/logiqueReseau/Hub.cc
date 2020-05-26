#include "Hub.hh"
#include "DataOutils.hh"

Hub::Hub(string _nom, int _idNoeud, int _nbPort, HubG *parent)
    : Noeud(_nom, _idNoeud, _nbPort, parent){

    type = HUB;
    setParent(parent);

}

Hub::Hub(HubG *parent) : Noeud(parent){

    setNom( "Hub"+std::to_string(idNoeud));
    type = HUB;
    setParent(parent);
}

Hub::~Hub(){
}

void Hub::envoyerBroadCast(string message){
    //a implimenter
}
void Hub::envoyerMessage(int key,destination dest){

	if ( this->checkSimulationStat( dest)) return;
    int id_src  = lireAdresseMac(dest.data, 0);

    std::cout <<"J'envoie le message à tous les membres"<< std::endl;
    for(InterfaceFE * ie: interfaces){
        Cable * cable = ie->getCable();
        if(!cable) return; // pas liaison
        extremite * ext = cable->getInverseExt(this);
        if(ext && ext->noeud->getIdNoeud() != id_src){
            //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Envoie de message vers  ")+QString::fromStdString(ext->noeud->getNom()));

            ext->noeud->recevoirMessage(key, ext->interface, dest);
        }
    }
}

void Hub::recevoirMessage(int key, int dest_i, destination dest){
	if ( this->checkSimulationStat( dest)) return;
    std::cout <<"Je suis un hub"<< idNoeud<<std::endl;
    if(dest.data->getType() < 3){
        std::cout <<"Data non encapsuler"<<std::endl;
        return;
    }
    //int id_dest = lireAdresseMac(data, 1);
    envoyerMessage(key, dest);

}




