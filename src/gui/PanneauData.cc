#include "PanneauData.hh"

PanneauData::PanneauData( QWidget *parent) : QTabWidget(parent) {
	this->setMinimumHeight(80);
	this->setMaximumHeight(100);
	this->setTabsClosable(true);
//	PanneauData::setPanneauData (this);
//	this->setStyleSheet("background-color: blue");
//	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


PanneauData::~PanneauData(){}

void PanneauData::addData ( Data * d)	{

	DataG * od = new DataG( d, this);
//	od->setTabsClosable (true);
	this->addTab( od,QString("Envoie n°%1").arg( onglets.size()+1));
	onglets.insert ( d,od);
}

