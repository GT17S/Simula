#include "simulaGui.hh"
#include "gSimulation.hh"
#include "Switch.hh"
#include <iostream>
#include "DataOutils.hh"


Switch::Switch(string  _nom,int _idNoeud,int _nbPort, SwitchG * parent) :
    Hub(_nom, _idNoeud, _nbPort, parent)
{
    type = SWITCH;
    setParent(parent);

}

Switch::Switch(SwitchG * parent) : Hub(parent) {
    // ID automatique
    // nb port =1
    // filedattente vide
    setNom("Switch"+std::to_string(idNoeud));
    type = SWITCH;
    setParent(parent);

}

Switch::~Switch(){

}
void Switch::envoyerMessage(int key, destination dest){

    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);


    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p){
        QString error = "Pas de chemin vers "+ QString::fromStdString(Graphe::getSommets()[id_dest]->getNom());
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),error);
        // alert
        emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
        //std::this_thread::sleep_for(Graphe::getAlertTime());
        //emit parent->notificationSignal("", QColor());
        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);

    if ( this->checkSimulationStat( dest)) return;

    if(path[size_p -1]->estBienConnecte()){
        std::this_thread::sleep_for(Graphe::getWaitTime());
        QString alert = QString::fromStdString("Envoyer message vers ")+QString::fromStdString(extNext->noeud->getNom());
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),alert);
        //alert
        emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());
        extNext->noeud->recevoirMessage(key, extNext->interface, dest);
    }
    else {
        QString error = "Verifier le type de cable vers "+QString::fromStdString(extNext->noeud->getNom());;
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),error);
        // alert
        emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
        //std::this_thread::sleep_for(Graphe::getAlertTime());
        //emit parent->notificationSignal("", QColor());

    }
}

void Switch::recevoirMessage(int key, int dest_i, destination dest){
    QString error = "Recevoir le message";
    // panneau events
    PanneauEvents::addCh(parent->getTreeItem(),error);
    // alert
    emit parent->notificationSignal(error, NotificationRect::GREEN_NOTIFICATION_COLOR);
    //std::this_thread::sleep_for(Graphe::getAlertTime());

    if ( this->checkSimulationStat( dest)) return;
    if(dest.data->getType() < 3){
        emit parent->notificationSignal("Probleme lecture message", NotificationRect::RED_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());
        return;
    }

    envoyerMessage(key, dest);
}
