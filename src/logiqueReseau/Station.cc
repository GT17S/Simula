#include "simulaGui.hh"
#include "gSimulation.hh"
#include "Station.hh"
#include "DataOutils.hh"
#include "QString"

bool Station::getRun() const
{
    return run;
}

void Station::setRun(bool value)
{
    run = value;
}

Station::Station(StationG * parent) : Noeud(parent){
    // ID automatique
    // nb port =1
    // filedattente vide
    controleur = new Congestion();

    setNom( "Station"+std::to_string(idNoeud));
    adressePasserelle = DEFAULT_IP;
    type = STATION;
    numSeq = 1;
    isPasserelle = false;
    run = true;
    setParent(parent);

}

Station::Station(string _nom, int _idNoeud, int _nbPort, string _adressePasserelle, bool _isPasserelle, StationG *parent):
    Noeud(_nom, _idNoeud, _nbPort, parent){
    // file dattente vide
    setPasserelle(_adressePasserelle);
    type = STATION;
    isPasserelle = _isPasserelle;
    setParent(parent);

}


void Station::setPasserelle(string _adresse){
    adressePasserelle = InterfaceFE::checkAdresse(_adresse, IP_REGEX, DEFAULT_IP);

}


void Station::setControleur(Congestion *_controleur){
    controleur = _controleur;
}

// Section critique ? 
int Station::getNextNumSeq()
{
    numSeq++;
    return numSeq-1;
}

void Station::setNumSeq(int _numSeq)
{
    numSeq = _numSeq;
}

void Station::setIsPasserelle(bool _isPasserelle){
    isPasserelle = _isPasserelle;
}



int Station::checkFragment(Data* data){
    if(data->getType() != DATA_PAQUET) return -1;
    unsigned int mf = (unsigned int) lire_bits ( *(data->getSeq()), 50, 1).to_ulong();
    //unsigned int df = (unsigned int) lire_bits ( p, 49, 1).to_ulong();
    unsigned int offset = (unsigned int)lire_bits (*(data->getSeq()) , 51, 13).to_ulong();
    int ipid = lireIdIp(data);

    if(!mf && !offset) return 0;  // non fragmenté
    else if(mf){ // encore des fragments
        fragments.insert({ipid ,data});
        return -1;
    }
    else if(!mf && offset){ // dernier fragment
        fragments.insert({ipid ,data});
        return ipid;
    }
    //mf = 0 et offset = 0 : paquet non fragmenté
    //mf = 0 et offset != 0 : dernier fragment
    //mf = 1 et offset = 0 : premier fragment
    //mf = 1 et offset != 0 : fragments
}

void Station::envoyerMessage(int key, destination dest){
    // passerelle
    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);

    std::cout << "STATION ENVOYER"<<id_src<<" "<<id_dest<<std::endl;

    if(id_src < 0 || id_dest < 0){
        emit parent->notificationSignal("Probleme lecture adresses MAC", NotificationRect::RED_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());
        return;
    }

    vector<Cable*> path;
    vector<Cable*> pathcomplet;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    Graphe::genererChemin(id_src, idNoeud, id_dest, pathcomplet, true);

    this->lastpath = path;
    int size_p = path.size();
    int size_pc = pathcomplet.size();
    if(!size_p){
        QString error = "Pas de chemin vers "+ QString::fromStdString(Graphe::getSommets()[id_dest]->getNom());
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),error);
        // alert
        emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
        return;
    }

    this->mutexcabl->lock();
    //Une fois que le paquet est envoyé on met à jour le rtt
    controleur->setBaseRtt(CalculRTT(controleur));
    //Et on diminue la bande passante du cable à l'envoi pour chaque cable du chemin
    for (int i = 0; i < size_pc; ++i){
        float tmpcableBP = pathcomplet[i]->getDebitMax();
        if((float)dest.data->getOriginialStringSize()*8 > pathcomplet[i]->getMTU())
            pathcomplet[i]->setDebitAcc(tmpcableBP -  pathcomplet[i]->getMTU());
        pathcomplet[i]->setDebitAcc(tmpcableBP - (float)dest.data->getOriginialStringSize()*8);
        pathcomplet[i]->setLatence((float)dest.data->getOriginialStringSize()*8 /  tmpcableBP);
    }
    this->mutexcabl->unlock();
    // prochaine destination
    extremite * extNext = path[size_p -1]->getInverseExt(this);

    /*
    std::cout << dest.data->getOriginialStringSize()*8 << std::endl;
    std::cout << Graphe::getMatrice()[id_src][id_dest]->getDebitAcc() << std::endl;
*/

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
        extNext->noeud->recevoirMessage(key, extNext->interface, dest);
    }else{
        QString error = "Verifier le type de cable vers "+QString::fromStdString(extNext->noeud->getNom());;
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),error);
        // alert
        emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
    }

}

void Station::recevoirMessage(int key, int dest_i, destination dest){
    QString error = "Recevoir le message";
    // panneau events
    PanneauEvents::addCh(parent->getTreeItem(),error);
    // alert
    emit parent->notificationSignal(error, NotificationRect::GREEN_NOTIFICATION_COLOR);
    //std::this_thread::sleep_for(Graphe::getAlertTime());



    int id_src  = lireAdresseMac(dest.data, 0);
    int id_dest = lireAdresseMac(dest.data, 1);

    std::cout << "STATION "<<id_src<<" "<<id_dest<<std::endl;
    vector<Cable*> path;
    vector<Cable*> pathcomplet;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    Graphe::genererChemin(id_src, idNoeud, id_dest, pathcomplet, true);

    this->lastpath = path;
    int size_p = path.size();
    int size_pc = pathcomplet.size();

    //Libèration de la bande passante dans les cas particuliers de reception

    if ( this->checkSimulationStat( dest)) return;
    //Libèration de la bande passante dans les cas particuliers de reception

    this->mutexcabl->lock();
    for (int i = 0; i < size_pc; ++i){
        float tmpcableBP = pathcomplet[i]->getDebitMax();
        if((float)dest.data->getOriginialStringSize()*8 > pathcomplet[i]->getMTU())
            pathcomplet[i]->setDebitAcc(tmpcableBP -  pathcomplet[i]->getMTU());
        pathcomplet[i]->setDebitAcc(tmpcableBP - (float)dest.data->getOriginialStringSize()*8);
        //pathcomplet[i]->setLatence((float)dest.data->getOriginialStringSize()*8 /  tmpcableBP);
    }
    this->mutexcabl->unlock();
    //std::cout <<"Je suis une station "<< idNoeud<<std::endl;
    // std::cout <<"TYPE DATA = "<< dest.data->getType() << std::endl;
    if(dest.data->getType() < 3){
        emit parent->notificationSignal("Probleme lecture message", NotificationRect::RED_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());
        return;
    }

    int mac_dest = lireAdresseMac(dest.data, 1);
    int mac_src = lireAdresseMac(dest.data, 0);

    if(mac_dest < 0 || mac_src < 0){
        emit parent->notificationSignal("Probleme lecture adresses MAC", NotificationRect::RED_NOTIFICATION_COLOR);
        std::this_thread::sleep_for(Graphe::getAlertTime());
        emit parent->notificationSignal("", QColor());

        return;
    }
    if(idNoeud == mac_dest){
        desencapsule_trame(dest.data);
        string ipSrc = getInterface(dest_i)->getAdresseIP();
        string ipDest= lireAdresseIp(dest.data, 1);
        if(ipSrc == DEFAULT_IP || ipDest == DEFAULT_IP){
            emit parent->notificationSignal("Probleme lecture adresse IP", NotificationRect::RED_NOTIFICATION_COLOR);
            std::this_thread::sleep_for(Graphe::getAlertTime());
            emit parent->notificationSignal("", QColor());
            return;
        }

        if(ipSrc == ipDest){
            std::this_thread::sleep_for(Graphe::getWaitTime());
            QString alert = QString("Arrivé à destination");
            // panneau events
            PanneauEvents::addCh(parent->getTreeItem(),alert);
            //alert
            emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
            std::this_thread::sleep_for(Graphe::getAlertTime());
            emit parent->notificationSignal("", QColor());

            // verifier fragmentation ?
            int ipid = checkFragment(dest.data);
            if(ipid < 0) return; // nextfragment
            if(ipid > 0){  // reassemblage
                vector<Data*> res;
                for(auto it = fragments.begin(); it != fragments.end();){
                    if(it->first == ipid){
                        res.push_back(it->second);
                        it = fragments.erase(it);
                    }else it++;
                }
                // reassemblage
                QString alert = QString("Reassemblage de paquets...");
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),alert);
                emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
                std::this_thread::sleep_for(Graphe::getWaitTime()+Graphe::getAlertTime());
                dest.data = reassemblagepaquet(res);

            }


            PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Desencapsulation de paquet"));
            desencapsule_paquet(dest.data);

            // lire ack et syn
            int flags = lireFlagSegment(dest.data);
            if(flags == 2 || flags == 18){
                // syn = 1, doit repondre ack
                if(flags == 18){

                    int nAck = lire_bits ( *(dest.data)->getSeq(), 64, 32).to_ulong();
                    QString alert = QString("ACK numero : "+QString::number(nAck)+" bien recu");
                    // panneau events
                    PanneauEvents::addCh(parent->getTreeItem(),alert);
                    emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
                    std::this_thread::sleep_for(Graphe::getAlertTime());

                    if(nAck < 0){
                        return;
                    }
                    // supprimer de la file d'attente
                    controleur->verifieNumAck(this, nAck);
                }
                Noeud * n2 = Graphe::getSommets()[mac_src];
                // retourner un ACK
                int nSeq = lire_bits ( *(dest.data)->getSeq(), 32, 32).to_ulong();
                if(nSeq < 0) return;

                desencapsule_segment(dest.data);
                //std::cout <<showMessage(dest.data) <<std::endl;
                alert = QString("Message recu : "+QString::fromStdString(showMessage(dest.data)));
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),alert);
                //alert
                emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);

                delete dest.data;
                this->mutexcabl->lock();
                //Libèration de la bande passante
                for (int i = 0; i < lastpath.size(); ++i){
                    float tmpcableBP = lastpath[i]->getDebitAcc();
                    lastpath[i]->setDebitAcc(tmpcableBP + (float)dest.data->getOriginialStringSize()*8);
                }
                this->mutexcabl->unlock();
                // envoi nouveau ack
                std::this_thread::sleep_for(Graphe::getAlertTime());
                alert = QString("Envoyer ACK numero  ")+QString::number(nSeq+1)+" vers "+QString::fromStdString(n2->getNom());
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),alert);
                //alert
                emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);

                controleur->verifieNumSegment(this, n2, nSeq+1);

            }
            else if(flags == 16){
                // ack = 1, accusé ack

                int nAck = lire_bits ( *(dest.data)->getSeq(), 64, 32).to_ulong();
                //PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Ack recu  ")+QString::number(nAck));

                if(nAck < 0) return;

                QString alert = QString("ACK numero : "+QString::number(nAck)+" bien recu");
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),alert);
                emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);
                desencapsule_segment(dest.data);

                delete dest.data;

                // supprimer de la file d'attente
                controleur->verifieNumAck(this, nAck);
            }else {

                desencapsule_segment(dest.data);

                QString alert = QString("Message recu : "+QString::fromStdString(showMessage(dest.data)));
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),alert);
                //alert
                emit parent->notificationSignal(alert, NotificationRect::GREEN_NOTIFICATION_COLOR);

                delete dest.data;
                return;
            }
        }
        else {
            /// Station est une passerelle
            if(isPasserelle){
                std::cout <<"Je suis une passerelle"<<std::endl;

                // generer chemin complet, jusqua la destination
                vector<Cable *> path;
                string ip_dest_string = lireAdresseIp(dest.data, 1);
                int ip_dest = Graphe::noeudFromIp(ip_dest_string);
                if(ip_dest < 0)
                    return;

                Graphe::genererChemin(mac_src, idNoeud, ip_dest, path, false);
                int size_p = path.size();
                // pas de chemin
                if(!size_p){
                    // std::cout << "Je connais pas le chemin vers " <<Graphe::getSommets()[ip_dest]->getNom()<<std::endl;
                    PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers "+ Graphe::getSommets()[ip_dest]->getNom()));

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
                srcExt->noeud = Graphe::getSommets()[mac_src];
                srcExt->interface = dest.interface_src;
                std::this_thread::sleep_for(Graphe::getWaitTime());
                encapsule_paquet ( srcExt, destExt, dest.data);
                envoyerMessage(key, dest);

            }

            else{
                QString error = "Je ne suis pas un Routeur, Vérifier la passerelle";
                // panneau events
                PanneauEvents::addCh(parent->getTreeItem(),error);
                // alert
                emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
            }



            return;
        }
    }
    else {
        // std::cout <<"Mauvaise destination" <<std::endl;
        QString error = "Mauvaise destination";
        // panneau events
        PanneauEvents::addCh(parent->getTreeItem(),error);
        // alert
        emit parent->notificationSignal(error, NotificationRect::RED_NOTIFICATION_COLOR);
        return;
    }

}





void Station::mainlocal(std::mutex *m, gSimulation* g){
    this->mutexcabl = m;
    controleur->setMutex(m);
    std::mutex * mfe = new std::mutex();
    std::mutex * mfa = new std::mutex();
    std::mutex * meo = new std::mutex();


    this->mutexEnvoiOk = meo;
    this->mutexFileEnvoyer = mfe;
    controleur->setMutexFileEnvoyer ( mfe);
    controleur->setMutexFileACK ( mfa);
    controleur->setMutexEnvoiOk ( meo);

    //std::cout << "Fonction principale du thread" << std::endl;
    std::chrono::seconds sec(1);
    bool deb = true;
    while (run){
        if(g->getEtat() == DEMARRER){
            deb = false;
            meo->lock();
            bool bok = this->getControleur()->getok();
            meo->unlock();
            if(bok){
                //std::cout <<  getIdNoeud() << std::endl;
                this->getControleur()->verifieNbrSegment(this);

            }
        }
        if(g->getEtat() == PAUSE)
            std::this_thread::sleep_for(sec);
        if (g->getEtat() == ARRET && !deb)	{
            this->getControleur()->clearFiles();
            this->getControleur()->setCwnd(1);
            this->getControleur()->setSsthresh(32);
            this->getControleur()->setCpt(0);
            this->getControleur()->setNbrAcksDuplique(0);
            this->getControleur()->setNbrAcksRecu(0);
            this->getControleur()->setok( false);
            deb = true;
        }
    }
}


