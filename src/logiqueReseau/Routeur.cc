#include "simulaGui.hh"
#include "gSimulation.hh"
#include "Routeur.hh"
#include "DataOutils.hh"


Routeur::Routeur(RouteurG * parent) : Noeud(parent){

    setNom("Routeur"+std::to_string(idNoeud));
    type = ROUTEUR;
    setParent(parent);
}

Routeur::Routeur(string _nom, int _idNoeud, int _nbPort, RouteurG *parent) :
    Noeud(_nom, _idNoeud, _nbPort, parent){
    type = ROUTEUR;
    setParent(parent);

}

Routeur::~Routeur(){

}

void Routeur::envoyerMessage(int key, destination dest){
    int id_dest = lireAdresseMac(dest.data, 1);
    int id_src  = lireAdresseMac(dest.data, 0);


    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, true);
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


    if(path[size_p-1]->estBienConnecte()){
        std::this_thread::sleep_for(Graphe::getWaitTime());
        QString alert = QString::fromStdString("Envoyer message vers ")+QString::fromStdString(extNext->noeud->getNom());
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),alert);
        //alert
        emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());

        extNext->noeud->recevoirMessage(key, extNext->interface,  dest);
    }else {
        QString error = "Verifier le type de cable vers "+QString::fromStdString(extNext->noeud->getNom());;
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),error);
        // alert
        emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
        //std::this_thread::sleep_for(Graphe::getAlertTime());
        //emit parent->notificationSignal("", QColor());


    }
}

void Routeur::recevoirMessage(int key, int dest_i, destination dest){
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

    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);

    if(idNoeud == id_dest){
        /*
        QString alert = QString::fromStdString("Arrivé à la passerelle");
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),alert);
        //alert
        emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());
        */

        //std::cout <<"Cest moi la passerelle" <<std::endl;
        std::cout <<" IP DEST ="<<lireAdresseIp(dest.data, 1)<<std::endl;
        desencapsule_trame(dest.data);
        string ipSrc = getInterface(dest_i)->getAdresseIP();
        std::cout <<"IP SOURCE ="<<ipSrc<<" IP DEST ="<<lireAdresseIp(dest.data, 1)<<std::endl;
        if(ipSrc == lireAdresseIp(dest.data, 1)){
            // std::cout <<"Cest moi la destination" <<std::endl;
            std::this_thread::sleep_for(Graphe::getWaitTime());
            QString alert = QString("Arrivé à destination");
            // panneau events
            PanneauEvents::addCh(parent->getTreeItem(),alert);
            //alert
            emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
            std::this_thread::sleep_for(Graphe::getAlertTime());
            emit parent->notificationSignal("", QColor());

            desencapsule_paquet(dest.data);
            desencapsule_segment(dest.data);

            //std::cout <<showMessage(dest.data) <<std::endl;
            alert = QString("Message recu : "+QString::fromStdString(showMessage(dest.data)));
            // panneau events
            PanneauEvents::addCh(parent->getTreeItem(),alert);
            //alert
            emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
            delete dest.data;
        }
        else {

            // generer chemin complet, jusqua la destination
            vector<Cable *> path;
            string ip_dest_string = lireAdresseIp(dest.data, 1);
            int ip_dest = Graphe::noeudFromIp(ip_dest_string);
            if(ip_dest < 0){
                QString error = "Verifier l'adresse IP "+QString::fromStdString(ip_dest_string);
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),error);
                // alert
                emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);

                return;
            }

            Graphe::genererChemin(id_src, idNoeud, ip_dest, path, false);
            int size_p = path.size();
            // pas de chemin
            if(!size_p){
                QString error = "Pas de chemin vers "+ QString::fromStdString(Graphe::getSommets()[id_dest]->getNom());
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),error);
                // alert
                emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);

                return;
            }

            // get next
            extremite * destExt; // destination finale
            Cable * cable;
            Noeud * n = this;
            for(int i = size_p - 1; i > -1; i--){
                cable = path[i];
                destExt = cable->getInverseExt(n);

                n = destExt->noeud;
            }
            // encapsuler paquet avec la prochaine @mac
            extremite* srcExt = new extremite;
            srcExt->noeud = Graphe::getSommets()[id_src];
            srcExt->interface = dest.interface_src;

            // fragmentation
            Cable * next_cable = path[size_p -1];
            //Cable * prec_cable = getInterface(dest_i)->getCable(); // cable precedent
            int mtu = next_cable->getMTU() / 8;
            int tp_initial = (int) lire_bits ( *(dest.data->getSeq()), 16, 16).to_ulong()-20;

            if(mtu < tp_initial){
                //fragmenter
                QString error = "Fragmentation de paquet...";
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),error);
                // alert
                emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
                std::this_thread::sleep_for(Graphe::getAlertTime());
                emit parent->notificationSignal("", QColor());


                unsigned int df = (unsigned int) lire_bits ( *(dest.data->getSeq()), 49, 1).to_ulong();
                if(df) {
                    QString error = "Fragmentation non autorisée";
                    // panneau events
                    PanneauEvents::addCh(parent->getTreeItem(),error);
                    // alert
                    emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
                    delete dest.data;
                    return;
                }
                vector<Data*> fragments = fragmentationPaquet(*(dest.data), mtu);

                for(Data * d : fragments){
                    encapsule_paquet ( srcExt, destExt, d);
                    destination t_dest;
                    t_dest.data = d;
                    t_dest.interface_src = dest.interface_src;

                    envoyerMessage(key, t_dest);
                }

                delete dest.data;
            }else {
                encapsule_paquet ( srcExt, destExt, dest.data);
                envoyerMessage(key, dest);
            }

        }
    }
    else {
        //std::cout <<"Mauvaise destination" <<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Mauvaise destination"));

        return;
    }
}



