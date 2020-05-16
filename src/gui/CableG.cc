#include "CableG.hh"

CableG::CableG(){

}

CableG::CableG(qreal x1, qreal x2, qreal x3, qreal x4) 
	:Cable(),QGraphicsLineItem(x1,x2,x3,x4)
{
	updateaff();

	if(getType() == DROIT){
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(4);
		pen.setBrush(Qt::black);
		pen.setCapStyle(Qt::FlatCap);
		pen.setJoinStyle(Qt::RoundJoin);
		setPen(pen);
	}else{
		pen.setStyle(Qt::DashDotLine);
		pen.setWidth(3);
		pen.setBrush(Qt::red);
		pen.setCapStyle(Qt::RoundCap);
		pen.setJoinStyle(Qt::RoundJoin);
		setPen(pen);
	}

}

CableG::~CableG(){

}

void CableG::updateaff(){
	tooltipstr << "Cable: " << this->getId() << std::endl << "Bande Passante:"<< this->getDebitAcc() << std::endl \
			   << "MTU :" <<  this->getMTU() << std::endl << "Type de cable: " << this->getType() << std::endl \
			   << "Extremité 1 :" << this->getExt1()->interface << std::endl << "Extremité 2 :" << this->getExt1()->interface;
	
	std::string s = tooltipstr.str();
	setToolTip(QString(s.c_str()));
}