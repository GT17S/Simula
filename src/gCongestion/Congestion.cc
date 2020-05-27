#include "Congestion.hh"


#include "string"
using namespace std;






Congestion::Congestion() :  mapFileEnvoyer(), mapFileACK(){
    cwnd=1;
    ssthresh=32;
    cpt=0;
    nbrAcksRecu=0;
    nbrAcksDuplique=0;
    envoiok = false;
}
Congestion::Congestion(Congestion &c){
    cwnd=c.cwnd;
    ssthresh=c.ssthresh;
    cpt=c.cpt;
    nbrAcksRecu=c.nbrAcksRecu;
    nbrAcksDuplique=c.nbrAcksDuplique;

}

Congestion::~Congestion()	{
	this->clearFiles();
}

void Congestion::setCwnd(int _cwnd){
    if(_cwnd >0)
        cwnd = _cwnd ;
    else return;
}

void Congestion:: setSsthresh(float _ssthresh){
    if(_ssthresh >0)
        ssthresh = _ssthresh ;

    else return;
}


void Congestion::setCpt(int _cpt){
    if(_cpt >0)
        cpt = _cpt ;
    else return;
}




void Congestion::setNbrAcksDuplique(int _nbrAcksDuplique){
    if(_nbrAcksDuplique >0)
        nbrAcksRecu = _nbrAcksDuplique ;
    else return;
}

void Congestion::setNbrAcksRecu(int _nbrAcksRecu){
    if(_nbrAcksRecu >0)
        nbrAcksRecu = _nbrAcksRecu ;
    else return;
}



void Congestion::setBaseRtt(int _baseRtt){
    if(_baseRtt >0)
        baseRtt = _baseRtt ;
    else return;
}


void Congestion::setMapFileEnvoyer(const std::map<int, destination> _map)
{
    mapFileEnvoyer = _map;
}



void Congestion::setMapFileACK(std::map<int, destination> _map)
{
    mapFileACK =  _map;
}

void Congestion::slowStart(Noeud *src){
    if(cwnd < ssthresh){
        cwnd=cwnd*2;
        cpt++;
    }else{
        congestionAvoidance(src);
    }
    //PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("slowStart: CWND = ")+QString::number(cwnd));
    QString alert = QString("slowStart : Augmentation CWND ="+QString::number(cwnd));
    // panneau events
    PanneauEvents::addCh(src->getParent()->getTreeItem(),alert);
    emit src->getParent()->notificationSignal(src->getParent()->getNotification()->toHtml()+alert, NotificationRect::BLUE_NOTIFICATION_COLOR);
    std::this_thread::sleep_for(Graphe::getAlertTime());



}
void Congestion::fastRecovery(Noeud *src){
    ssthresh=ssthresh/2;
    cwnd= ssthresh+3;
    cpt++;
    //PanneauEvents::affichage("fastRecovery est lance");
    //PanneauEvents::addCh(src->getParent()->getTreeItem(),);
    QString alert = QString("fastRecovery: CWND = ")+QString::number(cwnd);
    // panneau events
    PanneauEvents::addCh(src->getParent()->getTreeItem(),alert);
    emit src->getParent()->notificationSignal(src->getParent()->getNotification()->toHtml()+alert, NotificationRect::BLUE_NOTIFICATION_COLOR);
    std::this_thread::sleep_for(Graphe::getAlertTime());


    //PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("fastRecovery:le ssthresh :  ")+QString::number(ssthresh));
    alert = QString("fastRecovery: ssthres = ")+QString::number(ssthresh);
    // panneau events
    PanneauEvents::addCh(src->getParent()->getTreeItem(),alert);
    emit src->getParent()->notificationSignal(src->getParent()->getNotification()->toHtml()+alert, NotificationRect::BLUE_NOTIFICATION_COLOR);
    std::this_thread::sleep_for(Graphe::getAlertTime());


}

void Congestion::congestionAvoidance(Noeud *src){
cwnd=cwnd+1;
    cpt++;
    PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("congestionAvoidance: CWND = ")+QString::number(cwnd));


}

void Congestion::verifieNbrSegment(Noeud * src){
    PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("Vérification de la file d'attente"));
    std::cout << "Je suis parralélisé " << std::endl;
/**		May be here */
//    this->mutexEnvoiOk->lock();
	this->mutexFileEnvoyer->lock();
    if(mapFileEnvoyer.empty()){

      //  cout<<"fin de l'envoie " <<endl;
    //PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("File d'attente vide"));

    QString alert = QString("File d'attente vide");
    // panneau events
    PanneauEvents::addCh(src->getParent()->getTreeItem(),alert);
    emit src->getParent()->notificationSignal(src->getParent()->getNotification()->toHtml()+alert, NotificationRect::BLUE_NOTIFICATION_COLOR);
    std::this_thread::sleep_for(Graphe::getAlertTime());
    //emit src->getParent()->notificationSignal("", QColor());

        //PanneauEvents::affichage("fin de l'envoie 1 ");
/**		May be not here */
        this->mutexEnvoiOk->lock();
        envoiok = false;
        this->mutexEnvoiOk->unlock();
        //resamblahe(segRecu());
		this->mutexFileEnvoyer->unlock();

        return;
    }

    for(int i = 0; i< cwnd; i++){
        if(i > (int)mapFileEnvoyer.size()){
           // cout<<"fin de l'envoie 2"<<endl;
            PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("Fin de l'envoie  "));

            this->mutexEnvoiOk->lock();
            envoiok = false;
            this->mutexEnvoiOk->unlock();
            this->mutexFileEnvoyer->unlock();

            return;
        }

        auto it=mapFileEnvoyer.begin();
        int key=(*it).first;
        destination ds;
        ds=(*it).second;
        //
        // si syn = 1 alors doit attendre!
        int flags = lireFlagSegment(ds.data);
        if(flags == 2 || flags == 18){
            mapFileACK.insert ({key,ds});

        }

        mapFileEnvoyer.erase (it);

        src->envoyerMessage(key, ds);

    }
/**		May be not here */
    this->mutexEnvoiOk->lock();
    envoiok = false;
    this->mutexEnvoiOk->unlock();
    this->mutexFileEnvoyer->unlock();
}
void Congestion::retrnasmission(int key){
	bool locked = this->mutexFileACK->try_lock();
    mapFileEnvoyer.insert (mapFileEnvoyer.begin(), mapFileACK.find(key));
    mapFileACK.erase(mapFileACK.find(key));
    if (locked) this->mutexFileACK->unlock();
}


void Congestion::verifieNumSegment(Noeud * src,Noeud * dest, int nAck){//pc recepteur
    Data* ndata = new Data("ACK");
    Station * st = dynamic_cast<Station*>(src);
    if(!st ) return;

    int nSeq = st->getNextNumSeq(),
        ipId = nSeq+100;
    PanneauEvents::addCh(src->getParent()->getTreeItem(),QString::fromStdString("Envoyer ack vers ")+QString::fromStdString(dest->getNom()));

    envoyer(src, dest, 0, 0,false, true, nSeq, nAck,ipId,false, ndata);
    //verifieNbrSegment(st);
    //remplacer verifieNbrSegment(st) par var == true
	this->mutexEnvoiOk->lock();
    envoiok = true;
	this->mutexEnvoiOk->unlock();
}

void Congestion::verifieNumAck(Noeud * n, int nAck){
    PanneauEvents::addCh(n->getParent()->getTreeItem(),QString::fromStdString("Verfication d'ack recu  "));

    Station * st = dynamic_cast<Station*>(n);
    if(!st ) return;

    int oldNseq = nAck - 1;
    this->mutexFileACK->lock();
    map<int, destination>::iterator it = mapFileACK.find(oldNseq);
    if(it == mapFileACK.end())	{
		this->mutexFileACK->unlock();
		return;
	}
    mapFileACK.erase(it);
    this->mutexFileACK->unlock();
    nbrAcksRecu++;

    if(cwnd==nbrAcksRecu){
    PanneauEvents::addCh(n->getParent()->getTreeItem(),QString::fromStdString("CWND = NombreAckRecu "));


        nbrAcksRecu=0;
        slowStart( n);
       // verifieNbrSegment(st);
    	this->mutexEnvoiOk->lock();
        envoiok = true;
    	this->mutexEnvoiOk->unlock();
    }
}

void Congestion::clearFiles()	{
	this->mapFileACK.clear();
	this->mapFileEnvoyer.clear();
}
