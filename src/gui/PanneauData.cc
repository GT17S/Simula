#include "PanneauData.hh"

PanneauData::PanneauData( QWidget *parent) : QTabWidget(parent) {
	this->setMinimumHeight(80);
	this->setMaximumHeight(100);
	this->setTabsClosable(true);
//	this->setStyleSheet("background-color: blue");
//	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    parentt=new QTreeWidgetItem(PanneauEvents::getTreeview());
    PanneauEvents::addRoot(parentt,"Panneau DATA");
}


PanneauData::~PanneauData(){}

void PanneauData::addData ( Data * d)	{

	DataG * od = new DataG( d, this);
//	od->setTabsClosable (true);
	this->addTab( od,QString("Envoie n°%1").arg( onglets.size()+1));
	onglets.insert ( d,od);
}

QTreeWidgetItem *PanneauData::getParentt() const
{
    return parentt;
}

void PanneauData::setParentt(QTreeWidgetItem *value)
{
    parentt = value;
}

