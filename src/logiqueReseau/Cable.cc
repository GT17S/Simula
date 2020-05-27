#include "Cable.hh"
#include "Graphe.hh"
#include "typeinfo"
#include <iostream>

int Cable::nbCables = 0;
int Cable::i = 1;

Cable::Cable(CableG * _parent, cableT _type, int _debitMax, int _MTU){
    debitMax = _debitMax;
    debitAcc = _debitMax;
    MTU = _MTU;

    // ID cable
    nbCables = nbCables+1;
    id = i;
    i++;

    ext1 = new extremite();
    ext2 = new extremite();

    setParent(_parent);
    setType(_type);
}

Cable::~Cable(){
   // //std::cout << "Desutruction cable "<<id <<std::endl;
    if(ext1->noeud&& ext2->noeud){
        Graphe::supprimerCableMatrice(this);

    ext1->noeud->getInterface(ext1->interface)->setCable(nullptr);
    ext2->noeud->getInterface(ext2->interface)->setCable(nullptr);

    }
    ////std::cout << "Desutruction ext1 "<<id <<std::endl;
    delete ext1;
    ////std::cout << "Desutruction ext2 "<<id <<std::endl;
    delete ext2;
    nbCables = nbCables-1;

    delete parent;
}


void Cable::setId(int _idCable){ id = _idCable;}

void Cable::setDebitMax(int _debitMax){debitMax = _debitMax;parent->updateaff();}

void Cable::setDebitAcc(float _debitAcc){debitAcc = _debitAcc;parent->updateaff();}

void Cable::setLatence(float _latence){latence = _latence;parent->updateaff();}

void Cable::setMTU(int _MTU){ MTU = _MTU;parent->updateaff();}

void Cable::setType(const cableT & _type){
    type = _type;
    if(type==0){
        parent->setPen(CableG::DROIT_TYPE);
    }else{
        parent->setPen(CableG::CROISE_TYPE);
    }
parent->updateaff();

}

void Cable::setExt1(extremite * _noeud1){ext1 = _noeud1;}

void Cable::setExt2(extremite * _noeud2){ext2 = _noeud2;}

void Cable::setEstBienConnecteCable(bool value){estBienConnecteCable = value;}


void Cable::setParent(CableG * _parent){
    parent = _parent;
    if(_parent)
        parent->setChild(this);
}


bool  Cable::estBienConnecte(){

    typeNoeud typeNoeud1, typeNoeud2;

    typeNoeud1 = ext1->noeud->getTypeNoeud();
    typeNoeud2 = ext2->noeud->getTypeNoeud();

    // Meme type, cable croisé
    if(typeNoeud1 == typeNoeud2){
        if(type==1){
            parent->setPen(CableG::CROISE_TYPE);

        }else  parent->setPen(CableG::CROISE_ERREUR_TYPE);
        return type;
    // Switch & Hub, cable croisé
    }else if ((typeNoeud1 == HUB ||typeNoeud2 == HUB) && (typeNoeud1 == SWITCH ||typeNoeud2 == SWITCH)){
        if(type==1){
            parent->setPen(CableG::CROISE_TYPE);

        }else  parent->setPen(CableG::CROISE_ERREUR_TYPE);
        return type;

    // Sinon cable droit
    }else {
        if(type==1){
            parent->setPen(CableG::DROIT_ERREUR_TYPE);

        }else  parent->setPen(CableG::DROIT_TYPE);

        return 1 - type;}
}

bool Cable::connexionNoeuds(Noeud * N1, int interface1, Noeud * N2, int interface2){

    if(N1 != N2 && N1->acceptCable(this, interface1) && N2->acceptCable(this, interface2)){

        ext1->noeud = N1;
        ext1->interface = interface1;

        ext2->noeud = N2;
        ext2->interface = interface2;

        Graphe::ajoutCableMatrice(this);
        estBienConnecte();
        N1->getParent()->toolTipShow();
        N2->getParent()->toolTipShow();
        return true;

    }

    // Sinon destruction du cable!
    delete this;
    //this = NULL;
    return false;
}

