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
    setNom( "Station"+std::to_string(idNoeud));
    adressePasserelle = DEFAULT_IP;
    type = STATION;
    controleur = new Congestion();
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
    if(id_src < 0 || id_dest < 0){
        //std::cout <<"Lecture @mac probleme "<<id_src<<" "<<id_dest<< std::endl;
        //PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers ")+QString::number(ext->noeud->getNom()));

        return;
    }

    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    this->lastpath = path;
    int size_p = path.size();

    if(!size_p){
        //std::cout << "Je connais pas le chemin vers "<<id_dest<<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Je connais pas le chemin vers "+ Graphe::getSommets()[id_dest]->getNom()));

        return;
    }

    this->mutexcabl->lock();
    //Une fois que le paquet est envoyé on met à jour le rtt
    controleur->setBaseRtt(CalculRTT(controleur));
    //On calcule la latence de l'envoi dans le contrôleur
    //controleur->setlatence(CalculLatenceDynamique(Graphe::get(), controleur, dest.data, id_src, id_dest));
    //Et on diminue la bande passante du cable à l'envoi pour chaque cable du chemin
     for (int i = 0; i < path.size(); ++i){   
            float tmpcableBP = path[i]->getDebitAcc();
            path[i]->setDebitAcc(tmpcableBP - (float)dest.data->getOriginialStringSize()*8);
    }    
    this->mutexcabl->unlock();
    // prochaine destination
    extremite * extNext = path[size_p -1]->getInverseExt(this);
/* std::cout << dest.data->getOriginialStringSize()*8 << std::endl;
    std::cout << Graphe::getMatrice()[id_src][id_dest]->getDebitAcc() << std::endl;
*/

	if ( this->checkSimulationStat( dest)) return; 

    std::this_thread::sleep_for(Graphe::getWaitTime());
    PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Enovyé donnée vers ")+QString::fromStdString(extNext->noeud->getNom()));
    extNext->noeud->recevoirMessage(key, extNext->interface, dest);

}

void Station::recevoirMessage(int key, int dest_i, destination dest){
	if ( this->checkSimulationStat( dest)) return;
     //Libèration de la bande passante dans les cas particuliers de reception
    this->mutexcabl->lock();
    for (int i = 0; i < lastpath.size(); ++i){   
        float tmpcableBP = lastpath[i]->getDebitAcc();
        lastpath[i]->setDebitAcc(tmpcableBP + (float)dest.data->getOriginialStringSize()*8);
    }    
    this->mutexcabl->unlock();
    //std::cout <<"Je suis une station "<< idNoeud<<std::endl;
    // std::cout <<"TYPE DATA = "<< dest.data->getType() << std::endl;
    if(dest.data->getType() < 3){
        std::cout <<"Data non encapsuler"<<std::endl;

        return;
    }

    int mac_dest = lireAdresseMac(dest.data, 1);
    int mac_src = lireAdresseMac(dest.data, 0);

    if(mac_dest < 0 || mac_src < 0){
        std::cout << "Lecture @mac probleme "<<mac_src<<" "<<mac_dest<< std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Erreur de lecture de l'adresse mac"));

        return;
    }
    if(idNoeud == mac_dest){
        desencapsule_trame(dest.data);
        string ipSrc = getInterface(dest_i)->getAdresseIP();
        string ipDest= lireAdresseIp(dest.data, 1);
        if(ipSrc == DEFAULT_IP || ipDest == DEFAULT_IP){
            //std::cout<< "Probleme lecture @ip" <<std::endl;
           PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Erreur de lecture de l'adresse IP"));

            return;
        }

        if(ipSrc == ipDest){
            std::cout <<"Cest moi la destination" <<std::endl;
           PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Arrivé à destination"));

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
               PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Reassemblage de paquets"));

                dest.data = reassemblagepaquet(res);

                }


            PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Desencapsulation de paquet"));
            desencapsule_paquet(dest.data);

            // lire ack et syn
            int flags = lireFlagSegment(dest.data);
            if(flags == 2 || flags == 18){
                // syn = 1, doit repondre ack
                if(flags == 18){

                    std::cout <<"J'ai bien recu un ack"<<std::endl;
                    int nAck = lire_bits ( *(dest.data)->getSeq(), 64, 32).to_ulong();
                    PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Ack recu ")+QString::number(nAck));

                    if(nAck < 0) return;
                    // supprimer de la file d'attente
                    controleur->verifieNumAck(this, nAck);
                }
                Noeud * n2 = Graphe::getSommets()[mac_src];
                // retourner un ACK
                int nSeq = lire_bits ( *(dest.data)->getSeq(), 32, 32).to_ulong();
                if(nSeq < 0) return;

                PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Desencapsulation de segment"));
                desencapsule_segment(dest.data);
                PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Message recu :")+QString::fromStdString(showMessage(dest.data)));

                std::cout <<"Jai recu le message :"<<std::endl<<showMessage(dest.data) <<std::endl;
                delete dest.data;
			    this->mutexcabl->lock();
                //Libèration de la bande passante 
                for (int i = 0; i < lastpath.size(); ++i){   
                    float tmpcableBP = lastpath[i]->getDebitAcc();
                    lastpath[i]->setDebitAcc(tmpcableBP + (float)dest.data->getOriginialStringSize()*8);
                }    
			    this->mutexcabl->unlock();
                // envoi nouveau ack
                PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Envoie d'Ack ")+QString::number(nSeq+1)+" vers "+QString::fromStdString(n2->getNom()));

                controleur->verifieNumSegment(this, n2, nSeq+1);

            }
            else if(flags == 16){
                // ack = 1, accusé ack
                std::cout <<"J'ai bien recu un ack"<<std::endl;

                int nAck = lire_bits ( *(dest.data)->getSeq(), 64, 32).to_ulong();
                PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Ack recu  ")+QString::number(nAck));

                if(nAck < 0) return;

                desencapsule_segment(dest.data);
                std::cout <<"Jai recu le message :"<<std::endl<<showMessage(dest.data) <<std::endl;
          PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Message recu  ")+QString::fromStdString(showMessage(dest.data)));

                delete dest.data;

                // supprimer de la file d'attente
                controleur->verifieNumAck(this, nAck);
            }else {

                desencapsule_segment(dest.data);

                std::cout <<"Jai recu le message :"<<std::endl<<showMessage(dest.data) <<std::endl;
                PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Message recu  ")+QString::fromStdString(showMessage(dest.data)));

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

            else
                std::cout <<"Je ne suis pas une passerelle"<<std::endl;


            return;
        }
    }
    else {
       // std::cout <<"Mauvaise destination" <<std::endl;
        PanneauEvents::addCh(parent->getTreeItem(),QString::fromStdString("Mauvaise destination"));

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
        
        std::cout << "Fonction principale du thread" << std::endl;
        std::chrono::seconds sec(1);
		bool deb = true;
        while (run){
			if(g->getEtat() == DEMARRER){
				deb = false;
			   meo->lock();
			   bool bok = this->getControleur()->getok();
			   meo->unlock();
			   if(bok){
					std::cout <<  getIdNoeud() << std::endl;
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


