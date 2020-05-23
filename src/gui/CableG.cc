#include "CableG.hh"
QPen CableG::DROIT_TYPE,
CableG::CROISE_TYPE,
CableG::DROIT_ERREUR_TYPE,
CableG::CROISE_ERREUR_TYPE;


CableG::CableG(qreal x1, qreal x2, qreal x3, qreal x4) 
    :   QGraphicsLineItem(x1,x2,x3,x4)
{
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
void CableG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    configurationCable->showConfig(child);
    configurationCable->show();
}
void CableG::updateaff(){
    QString s,equipementName;
    QTextStream stream(&s);
    qreal bandPass= child->getDebitAcc();
    QString::number(bandPass,'f', 3);

    stream <<"Debit Max = "<<child->getDebitMax()<<"<br>"
          <<"MTU = "<<child->getMTU()<<"<br>";
          /*  if(bandPass){
        stream <<"Bande passente = "<<QString::number(bandPass,'f', 3)<<"<br>";
            }else{
              stream<<"Bande passente N/A "<<"<br>";
            }*/

    setToolTip(s);


}
void CableG::createPen(){
    DROIT_TYPE=QPen (Qt::black,3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    CROISE_TYPE=QPen (Qt::black,3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    DROIT_ERREUR_TYPE=QPen (Qt::red,3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    CROISE_ERREUR_TYPE=QPen (Qt::red,3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
}




