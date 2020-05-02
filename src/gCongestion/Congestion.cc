#include "Congestion.hh"

    Congestion::Congestion(){
    cwnd=1;
    ssthresh=32;
    cpt=0;
    numAckRecu=0;
    nbrAcksRecu=0;
    nbrAcksDuplique=0;
    dernierNumSegment=0;
}
    Congestion::Congestion(Congestion &c){
        cwnd=c.cwnd;
        ssthresh=c.ssthresh;
        cpt=c.cpt;
        numAckRecu=c.numAckRecu;
        nbrAcksRecu=c.nbrAcksRecu;
        nbrAcksDuplique=c.nbrAcksDuplique;
        dernierNumSegment=c.dernierNumSegment;

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
            Congestion::congestionAvoidance();
        }

    }
    void Congestion::fastRecovery(){
        ssthresh=ssthresh/2;
        cwnd= ssthresh+3;
        cpt++;
    }

    void Congestion::congestionAvoidance(){

        cwnd =cwnd+(1/cwnd);
        cpt++;
    }

    void Congestion::verifieNumAck(std::string *ack,std::vector<int> num_seq){
        nbrAcksRecu++;
       // numAckRecu=ack->num;
        if(numAckRecu==num_seq[0]){
           num_seq.erase (num_seq.begin());
            if(cwnd==nbrAcksRecu){
                nbrAcksRecu=0;
                slowStart();
            }
        }else{//en cas de perte difficle a ce cas
             nbrAcksDuplique++;
             if(nbrAcksDuplique==3){
                 fastRecovery();
                 dernierNumSegment++;
                 nbrAcksRecu=0;
                 nbrAcksDuplique=0;
                 //fast ret comme paramter tous les message deja encoyer , num semg a envoyer
                 //elle va parcour et le trouve et apple la focbtion envoyer de station
             }
        }
    }
    void Congestion::verifieNumSegment(std::string *segment){
        //int j=segment.datatotal;
        //int i comptur
        //dernierNumSegment=segment->num
        if(dernierNumSegment==dernierNumSegment+1){
            dernierNumSegment++;
            //ack avec dernierNumSegment mais coment savoir adress ip et encapsuler
             //i++;
            //if(i==j){
            //set dernierNumSegment 0
        //}
        }else{
            //ack avec dernierNumSegment

        }

    }


