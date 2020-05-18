#include "Congestion.hh"


#include "string"
using namespace std;






void Congestion::setMapFileEnvoyer(const std::map<int, destination> _map)
{
    mapFileEnvoyer = _map;
}



void Congestion::setMapFileACK(std::map<int, destination> _map)
{
    mapFileACK =  _map;
}

Congestion::Congestion() :  mapFileEnvoyer(), mapFileACK(){
    cwnd=1;
    ssthresh=32;
    cpt=0;
    nbrAcksRecu=0;
    nbrAcksDuplique=0;

}
Congestion::Congestion(Congestion &c){
    cwnd=c.cwnd;
    ssthresh=c.ssthresh;
    cpt=c.cpt;
    nbrAcksRecu=c.nbrAcksRecu;
    nbrAcksDuplique=c.nbrAcksDuplique;

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

void Congestion::slowStart(){
    if(cwnd < ssthresh){
        cwnd=cwnd*2;
        cpt++;
    }else{
        congestionAvoidance();
    }
    std::cout<<"CWND = "<<cwnd<<std::endl;
    //PanneauEvents::affichage("CWND est a :"+ QString::number(cwnd););

}
void Congestion::fastRecovery(){
    ssthresh=ssthresh/2;
    cwnd= ssthresh+3;
    cpt++;
    //PanneauEvents::affichage("fastRecovery est lance");

}

void Congestion::congestionAvoidance(){

    cwnd =cwnd+1;
    cpt++;
    //PanneauEvents::affichage("congestionAvoidance est lance");

}

void Congestion::verifieNbrSegment(Noeud * src){
    std::cout << "Je suis parralélisé " << std::endl;
    if(mapFileEnvoyer.empty()){
        cout<<"fin de l'envoie " <<endl;
        //PanneauEvents::affichage("fin de l'envoie 1 ");

        //resamblahe(segRecu());
        return;
    }

    for(int i = 0; i< cwnd; i++){
        //lock mutex mapfile
        if(i > mapFileEnvoyer.size()){
            cout<<"fin de l'envoie 2"<<endl;
            //PanneauEvents::affichage("fin de l'envoie de pc : "+src.getNom());

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
        //std::mutex unlock
        //std::thread emetteur(src::envoyerMessage(int, destination), key,ds);
        
       src->envoyerMessage(key, ds);
    }

    //var = false
}
void Congestion::retrnasmission(int key){

    mapFileEnvoyer.insert (mapFileEnvoyer.begin(), mapFileACK.find(key));
    mapFileACK.erase(mapFileACK.find(key));
}


void Congestion::verifieNumSegment(Noeud * src,Noeud * dest, int nAck){//pc recepteur
    Data* ndata = new Data("");
    Station * st = dynamic_cast<Station*>(src);
    if(!st ) return;

    int nSeq = st->getNextNumSeq(),
        ipId = 100;
    envoyer(src, dest, 0, 0,false, true, nSeq, nAck,ipId,false, ndata);
    verifieNbrSegment(st);
    //remplacer verifieNbrSegment(st) par var == true
}

void Congestion::verifieNumAck(Noeud * n, int nAck){
    Station * st = dynamic_cast<Station*>(n);
    if(!st ) return;

    int oldNseq = nAck - 1;
    map<int, destination>::iterator it = mapFileACK.find(oldNseq);
    if(it == mapFileACK.end()) return;
    mapFileACK.erase(it);

    nbrAcksRecu++;

    if(cwnd==nbrAcksRecu){
        nbrAcksRecu=0;
        slowStart();
        verifieNbrSegment(st);
    }
}
