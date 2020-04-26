#include "../include/logiqueReseau/Cable.hh"

#include "typeinfo"
using namespace std;


Cable::Cable(){
    this->id=i;
    this->nbCables=nbCables+1;
    i++;
}

Cable::Cable(cableT type,int debitMax,Noeud* ext1, Noeud* ext2){
    this->type=type;
    this->debitMax=debitMax;
    this->ext1=ext1;
    this->ext2=ext2;
    this->nbCables=nbCables+1;
    this->id=i;
    i++;
}

Cable::Cable(Cable& c){
    this->type=c.type;
    this->debitMax=c.debitMax;
    this->ext1=c.ext1;
    this->ext2=c.ext2;
    this->nbCables=nbCables+1;
    this->id=i;
    i++;
}

Cable::~Cable(){this->nbCables=nbCables-1;}



void Cable::setId(int idCable){ this->id = idCable;}



void Cable::setDebitMax(int debitMax){this->debitMax = debitMax;}



void Cable::setDebitAcc(float debitAcc){this->debitAcc = debitAcc;}



void Cable::setLatence(float latence){this->latence = latence;}


void Cable::setType(const cableT &type){this->type = type;}


void Cable::setNbCables(int nbCable){nbCables = nbCable;}

void Cable::setExt1(Noeud *noeud1){this->ext1 = noeud1;}


void Cable::setExt2(Noeud *noeud2){this->ext2 = noeud2;}
bool  Cable::estBienConnecte() const{
    string classType1;
    string classType2;
    classType1=typeid(ext1).name();
    classType2=typeid(ext2).name();
    if(classType1==classType2){
        if(type==1){
            return true;
        }else return false;
    }else if ((classType1=="3hub" ||classType2=="3hub") && (classType1=="6Switch" ||classType2=="6Switch")){
        if(type==1){
            return true;
        }else return false;
    }else{
        if(type==0) return true;
        else return false;
    }
}
int Cable::nbCables=0;
int Cable::i=0;
