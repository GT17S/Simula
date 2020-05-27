#include "CableG.hh"
#include <bits/stdc++.h>
#include <iomanip>
QPen CableG::DROIT_TYPE,
CableG::CROISE_TYPE,
CableG::DROIT_ERREUR_TYPE,
CableG::CROISE_ERREUR_TYPE;


CableG::CableG(EspaceTravail * _espaceTravail,qreal x1, qreal x2, qreal x3, qreal x4)
    :   QGraphicsLineItem(x1,x2,x3,x4)
{
    espaceTravail = _espaceTravail;
    child = nullptr;
    extG1 = nullptr;
    extG2 = nullptr;
    createPen();
}
void CableG::setChild(Cable * _child){
    child=_child;
    configurationCable=new DialogCable(nullptr,0,0,0,child);
    updateaff();
}


CableG::~CableG(){
    if(extG1){
        vector<cableG_extremite> v1 = extG1->getCablesG();
        for(auto i = v1.begin(); i != v1.end(); i++){
            if( (*i).cable == this){
                (*i).cable = nullptr;
                v1.erase(i);
                break;
            }
        }extG1->setCableG(v1);
     }
    if(extG2){
        vector<cableG_extremite> v2 = extG2->getCablesG();
        for(auto i = v2.begin(); i != v2.end(); i++){
            if( (*i).cable == this){
                (*i).cable = nullptr;
                v2.erase(i);
                break;
            }
        }extG2->setCableG(v2);
    }

}

void CableG::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(espaceTravail->getMode() == DELETE_MODE){
        const QMessageBox::StandardButton ret
                = QMessageBox::question(espaceTravail, "Supprimer cable",
                                        "Voulez-vous vraiment supprimer le cable ?",
                                        QMessageBox::Yes | QMessageBox::No);

        if(ret == QMessageBox::Yes){
            if(child)
                child->~Cable();
            else
                this->~CableG();
        }
    }

}

void CableG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(espaceTravail->getMode()==SELECT_MODE){

    configurationCable->showConfig(child);
    configurationCable->show();}
}
void CableG::updateaff(){
    QString s,equipementName;
    QTextStream stream(&s);

    stream <<"Debit Max = "<<child->getDebitMax()<<"<br>"
          <<"MTU = "<<child->getMTU()<<"<br>"
           <<"Bande passante = "<<fixed <<  qSetRealNumberPrecision(0)<<child->getDebitAcc()
          <<"<br>Latence = "<<fixed <<  qSetRealNumberPrecision(0)<<child->getLatence();


    setToolTip(s);


}
void CableG::createPen(){
    DROIT_TYPE=QPen (Qt::black,3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    CROISE_TYPE=QPen (Qt::black,3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    DROIT_ERREUR_TYPE=QPen (Qt::red,3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    CROISE_ERREUR_TYPE=QPen (Qt::red,3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
}




