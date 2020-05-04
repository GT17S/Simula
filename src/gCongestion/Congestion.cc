#include "Congestion.hh"

#include "string"
using namespace std;

int Congestion::getIndiceEnv() const
{
    return indiceEnv;
}

void Congestion::setIndiceEnv(int value)
{
    indiceEnv = value;
}

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
    indiceEnv=0;
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
        indiceEnv=c.indiceEnv;
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

    void Congestion::verifieNumAck(Data *ack , std::vector<int> num_seq,Station *stSrc){//la station qui va verfie d'aqq(emet)
        nbrAcksRecu++;
        boost::dynamic_bitset<> test;
        test= lire_bits (*ack->getSeq(),64,32);
        numAckRecu=test.to_ulong();
        numAckRecu=int(numAckRecu);
        if(numAckRecu==num_seq[0]){
           num_seq.erase (num_seq.begin());
            if(cwnd==nbrAcksRecu){
                nbrAcksRecu=0;
                slowStart();
               if(num_seq.empty()){
                verifieNbrSegment(stSrc);}
            }
        }else{//en cas de perte difficle a ce cas
             nbrAcksDuplique++;
             if(nbrAcksDuplique==3){
                 fastRecovery();
                 dernierNumSegment++;
                 nbrAcksRecu=0;
                 nbrAcksDuplique=0;
                 //fastRetransmission(Station::getDataEnv(),numAckRecu);
             }
        }
    }
    void Congestion::verifieNumSegment(Data *segment,Station *stDes){//la station qui va verfie le num segment(recpt)
        string ip,ip2,numSeg;
        boost::dynamic_bitset<>test,test1,test2,unBit;
        test= lire_bits (*segment->getSeq(),32,32);//num seg
        dernierNumSegment=test.to_ulong();
        dernierNumSegment=int(dernierNumSegment);
        test1=lire_bits (*segment->getSeq(),96,32);//ip src orgin pc  a
        boost::to_string(test1,ip);
        test2=lire_bits (*segment->getSeq(),128,32);//ip2 des origin pc b
        boost::to_string(test2,ip2);
        string dernierNumSegmentss;
        string un="1";
        if(dernierNumSegment==dernierNumSegment+1){
            segRecu.push_back(segment);
            dernierNumSegment++;
            dernierNumSegmentss=to_string(dernierNumSegment);//vers string numseg

            numSeg=segment->strtobinary(dernierNumSegmentss);//to binary
            boost::dynamic_bitset<>segToBin(std::begin(numSeg), std::end(numSeg));//to bistest

            un=segment->strtobinary(un);//to binary 1
            boost::dynamic_bitset<>unBit(std::begin(un), std::end(un));//to bistest 1

            //ack en parcournt somment de noed et trouve le sommet qui a meme addrrss ip
                    Noeud *stSrc;
                   // stSrc=Graphe::noeudFromIp(ip2);
                    ecrire_bits(segment->getSeq(),test2,96,32);//pos addres ip src
                    ecrire_bits(segment->getSeq(),test1,128,32);//ip des
                    ecrire_bits(segment->getSeq(),segToBin,64,32);//num acqt
                    ecrire_bits(segment->getSeq(),unBit,106,6);//flag

                    stDes->envoyerMessage(stSrc,segment);
                }

           countSegment++;
            if(countSegment==dataTotal){
            setDernierNumSegment(0);
            //resaomblage(segRecu)

        }else{
            //ack avec dernierNumSegment
                dernierNumSegmentss=to_string(dernierNumSegment);
                numSeg=segment->strtobinary(dernierNumSegmentss);
                boost::dynamic_bitset<>segToBin(std::begin(numSeg), std::end(numSeg));
                un=segment->strtobinary(un);//to binary 1
                boost::dynamic_bitset<>unBit(std::begin(un), std::end(un));//to bistest 1


                        Noeud *stSrc;
                       stSrc=Graphe::noeudFromIp(ip2);
                       ecrire_bits(segment->getSeq(),test2,96,32);//pos addres ip src
                       ecrire_bits(segment->getSeq(),test1,128,32);//ip des
                       ecrire_bits(segment->getSeq(),segToBin,64,32);//num acqt
                       ecrire_bits(segment->getSeq(),unBit,106,6);//flag
                        stDes->envoyerMessage(stSrc,segment);

    }}

    void  Congestion::verifieNbrSegment(Station *stSrc){

        int i,j;
      i=0;j=0;
        for (i;i<cwnd;i++){
            Data *segment;
            string ipSrc,ipDes;
            j=i+indiceEnv;
            if(j>=dataTotal){
                break ; //fin
            }else {
            segment=segAE[j];
            boost::dynamic_bitset<>test1;;
            test1=lire_bits (*segment->getSeq(),16,8);//ip des
            boost::to_string(test1,ipDes);
            Noeud *des;
            des=Graphe::noeudFromIp(ipDes);

        stSrc->envoyerMessage(des,segment);
          // segAEnv.erase(segAEnv.begin()+i);
                }
        indiceEnv =j+1;

    }}

    void Congestion::fastRetransmission(std::vector<Data> messages, int num){
       //parcourir segAEnv et verf le numero avec num si == alors envoyerMessage
    }

