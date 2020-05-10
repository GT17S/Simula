
#include "../include/logiqueReseau/Graphe.hh"

#include "Congestion.hh"


#include "string"
using namespace std;



int Congestion::getDataTotal() const
{
    return dataTotal;
}

void Congestion::setDataTotal(int value)
{
    dataTotal = value;
}

int Congestion::getCountSegment() const
{
    return countSegment;
}

void Congestion::setCountSegment(int value)
{
    countSegment = value;
}


void Congestion::setSegRecu(const std::vector<Data *> value)
{
    segRecu = value;
}



void Congestion::setSegAE(const std::vector<Data *> &value)
{
    segAE = value;
}



Congestion::Congestion(){
    cwnd=1;
    ssthresh=32;
    cpt=0;
    numAckRecu=0;
    nbrAcksRecu=0;
    nbrAcksDuplique=0;
    dernierNumSegment=0;
    //segRecu=NULL;
    countSegment=0;
    dataTotal=0;

}
Congestion::Congestion(Congestion &c){
        cwnd=c.cwnd;
        ssthresh=c.ssthresh;
        cpt=c.cpt;
        numAckRecu=c.numAckRecu;
        nbrAcksRecu=c.nbrAcksRecu;
        nbrAcksDuplique=c.nbrAcksDuplique;
        dernierNumSegment=c.dernierNumSegment;
        segRecu=c.segRecu;
        countSegment=c.countSegment;
        dataTotal=c.dataTotal;

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


    void Congestion::setDernierNumSegment(int _dernierNumSegment ){
        if(_dernierNumSegment >0)
        dernierNumSegment = _dernierNumSegment ;
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

    void Congestion::setNumAckRecu(int _numAckRecu){
        if(_numAckRecu >0)
        numAckRecu = _numAckRecu ;
        else return;
    }


    void Congestion::setBaseRtt(int _baseRtt){
        if(_baseRtt >0)
        baseRtt = _baseRtt ;
        else return;
    }

    void Congestion::slowStart(){
        if(cwnd > ssthresh){
            cwnd=cwnd*2;
            cpt++;
        }else{
          congestionAvoidance();
        }

    }
    void Congestion::fastRecovery(){
        ssthresh=ssthresh/2;
        cwnd= ssthresh+3;
        cpt++;
    }

    void Congestion::congestionAvoidance(){

        cwnd =cwnd+1;
        cpt++;
    }

    void Congestion::verifieNbrSegment(Station * src){

        if(mapFileEnvoyer.empty()){
            cout<<"fin de l'envoie"<<endl;
            //resamblahe(segRecu());
                   return;
        }

        for(int i = 0; i< cwnd; i++){

            if(i > mapFileEnvoyer.size()){
                cout<<"fin de l'envoie"<<endl;
                return;
            }

         auto it=mapFileEnvoyer.begin();
         std::advance(it,i);
         int key=(*it).first;
         destination ds;
         ds=(*it).second;
          src->envoyerMessage(ds.des,ds.d);
            dynamic_bitset<> numSeq;
            numSeq=lire_bits(*ds.d->getSeq(),32,32);//numsq
            if(numSeq.to_ulong()==1){
                mapFileACK.insert ({key,ds});

            }
           mapFileEnvoyer.erase (it);


        }
    }
    void Congestion::retrnasmission(int key){

        mapFileEnvoyer.insert (mapFileEnvoyer.begin(), mapFileACK.find(key));
        mapFileACK.erase(mapFileACK.find(key));
    }


    void Congestion::verifieNumSegment(Station *stThis,Station *src,Data *data){//pc recepteur
        Data ack("");
        dynamic_bitset<> dF;
        dF=lire_bits(*data->getSeq(),54,4);//fraglent ou nn
        if(dF.to_ulong()==1){
         segRecu.push_back(data);

        }else{
        segRecu.push_back(data);
        dynamic_bitset<> numSeq;
        numSeq=lire_bits(*data->getSeq(),32,32);//numsq
        int numeroSeqOld=numSeq.to_ulong();
        numeroSeqOld=numeroSeqOld+1;
        boost::dynamic_bitset<> newNum (32,numeroSeqOld);
        boost::dynamic_bitset<> syn (32,numeroSeqOld);
        ecrire_bits(ack.getSeq(),(32,newNum),64,32);//ack num
        ecrire_bits(ack.getSeq(),(0,syn),64,0);//syn=1
        /*encapsuler on a les tous les infos ici
         * envoyer
         * en attend medish
         * /
*/
  }  }

    void Congestion::verifieNumAck(Station *stThis,int numAck,int key){
        nbrAcksRecu++;
        map<int, destination>::iterator it = mapFileACK.find(key);
        destination ds;
        ds=it->second;
        Data *dat=ds.d;
        dynamic_bitset<> numAc;
        numAc=lire_bits(*dat->getSeq(),62,32);//numsq7
        if(numAc.to_ulong()==numAck-1){
         mapFileACK.erase(mapFileACK.find(key));
        }
        if(cwnd==nbrAcksRecu){
            nbrAcksRecu=0;
            slowStart();
            verifieNbrSegment(stThis);
        }
    }