#include "../include/logiqueReseau/Cable.hh"
#include "typeinfo"


int Cable::nbCables = 0;
int Cable::i = 0;


Cable::Cable(cableT _type, int _debitMax, int _MTU){
    type = _type;
    debitMax = _debitMax;
    MTU = _MTU;

    // ID cable
    nbCables = nbCables+1;
    id = i;
    i++;
}

Cable::~Cable(){

    nbCables = nbCables-1;
}


Noeud * Cable::getExt(Noeud * ext){
    if(ext == ext1)
            return ext2;

    else if(ext == ext2)
            return ext1;

    else
            return nullptr;
}

void Cable::setId(int _idCable){ id = _idCable;}

void Cable::setDebitMax(int _debitMax){debitMax = _debitMax;}

void Cable::setDebitAcc(float _debitAcc){debitAcc = _debitAcc;}

void Cable::setLatence(float _latence){latence = _latence;}

void Cable::setMTU(int _MTU){ MTU = _MTU;}

void Cable::setType(const cableT & _type){type = _type;}

void Cable::setExt1(Noeud * _noeud1){ext1 = _noeud1;}

void Cable::setExt2(Noeud * _noeud2){ext2 = _noeud2;}

bool  Cable::estBienConnecte(){

    string typeNoeud1;
    string typeNoeud2;

    typeNoeud1 = typeid(ext1).name();
    typeNoeud2 = typeid(ext2).name();

    // Meme type, cable croisé
    if(typeNoeud1 == typeNoeud2){
        if(type == 1)
            return true;
        else
            return false;
    // Switch & Hub, cable croisé
    }else if ((typeNoeud1 == "3Hub" ||typeNoeud2 == "3Hub") && (typeNoeud1 == "6Switch" ||typeNoeud2 == "6Switch")){
        if(type == 1)
            return true;
        else
            return false;

    // Sinon cable droit
    }else if(type == 0)
        return true;
    else
        return false;
}

bool Cable::connexionNoeuds(Noeud * N1, int interface1, Noeud * N2, int interface2){
    if(N1->acceptCable(this, interface1) && N2->acceptCable(this, interface2)){
        setExt1(N1);
        setExt2(N2);
        return true;
    }

    // Sinon destruction du cable!
    delete this;
    return false;

}


