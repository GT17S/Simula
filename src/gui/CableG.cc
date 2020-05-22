#include "CableG.hh"

CableG::CableG(qreal x1, qreal x2, qreal x3, qreal x4) 
    :   QGraphicsLineItem(x1,x2,x3,x4)
{

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

void CableG::updateaff(){
/*	tooltipstr << "Cable: " << this->getId() << std::endl << "Bande Passante:"<< this->getDebitAcc() << std::endl \
			   << "MTU :" <<  this->getMTU() << std::endl << "Type de cable: " << this->getType() << std::endl \
			   << "Extremité 1 :" << this->getExt1()->interface << std::endl << "Extremité 2 :" << this->getExt1()->interface;
	
	std::string s = tooltipstr.str();
	setToolTip(QString(s.c_str()));
*/
}
