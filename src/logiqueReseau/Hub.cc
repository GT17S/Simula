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

    for(InterfaceFE * ie: interfaces){
        Cable * cable = ie->getCable();
        if(!cable) return; // pas liaison
        extremite * ext = cable->getInverseExt(this);
        if(ext && ext->noeud->getIdNoeud() != id_src){
        if(cable->estBienConnecte()){
            std::this_thread::sleep_for(Graphe::getWaitTime());
            QString alert = QString::fromStdString("Envoyer message vers ")+QString::fromStdString(ext->noeud->getNom());
            // panneau events
            PanneauEvents::addCh(parent->getTreeItem(),alert);
            //alert
            emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
            std::this_thread::sleep_for(Graphe::getAlertTime());
            emit parent->notificationSignal("", QColor());

            ext->noeud->recevoirMessage(key, ext->interface, dest);
        }else {
            QString error = "Verifier le type de cable vers "+QString::fromStdString(ext->noeud->getNom());;
            // panneau events
            PanneauEvents::addCh(parent->getTreeItem(),error);
            // alert
            emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);

        }
        }
    }
}

void Hub::recevoirMessage(int key, int dest_i, destination dest){
    QString error = "Recevoir le message";
    // panneau events
    PanneauEvents::addCh(parent->getTreeItem(),error);
    // alert
    emit parent->notificationSignal(error, NotificationRect::GREEN_NOTIFICATION_COLOR);
   // std::this_thread::sleep_for(Graphe::getAlertTime());

	if ( this->checkSimulationStat( dest)) return;
    if(dest.data->getType() < 3){
        emit parent->notificationSignal("Probleme lecture message", NotificationRect::RED_NOTIFICATION_COLOR);
        //std::this_thread::sleep_for(Graphe::getAlertTime());
        //emit parent->notificationSignal("", QColor());

        return;
    }
    envoyerMessage(key, dest);

}




