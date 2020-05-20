#include "CableG.hh"

CableG::CableG(qreal x1, qreal x2, qreal x3, qreal x4) 
    :   QGraphicsLineItem(x1,x2,x3,x4)
{

}

CableG::~CableG(){

}

void CableG::updateaff(){
/*	tooltipstr << "Cable: " << this->getId() << std::endl << "Bande Passante:"<< this->getDebitAcc() << std::endl \
			   << "MTU :" <<  this->getMTU() << std::endl << "Type de cable: " << this->getType() << std::endl \
			   << "Extremité 1 :" << this->getExt1()->interface << std::endl << "Extremité 2 :" << this->getExt1()->interface;
	
	std::string s = tooltipstr.str();
	setToolTip(QString(s.c_str()));
*/
}
