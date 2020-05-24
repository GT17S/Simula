#include "PanneauData.hh"

PanneauData::PanneauData( QWidget *parent) : QTabWidget(parent) {
	this->setMinimumHeight(80);
	this->setMaximumHeight(100);
	this->setTabsClosable(true);
	compt = 0;
//	PanneauData::setPanneauData (this);
//	this->setStyleSheet("background-color: blue");
//	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


PanneauData::~PanneauData(){}

void PanneauData::addData ( Data * d)	{

	DataG * od = new DataG( d, onglets.size()+1, this);
//	od->setTabsClosable (true);
	this->addTab( od,QString("Envoie n°%1").arg( onglets.size()));
	onglets.insert ( d,od);
	connect( this, SIGNAL(tabCloseRequested(int)), this, SLOT(askRemoveTab(int)));
//	connect( od, SIGNAL( closedTab(DataG*)), this, SLOT( askRemoveTab(DataG*)));
}

void PanneauData::askRemoveTab( int index)	{
	//DataG * cu = currentWidget( index);
//	std::cout << "Index : " << index << " " << this->count() << std::endl;
	DataG * cu = dynamic_cast<DataG *> (this->widget(index));
	if ( cu && (compt == 0))	{
		std::cout << "Compt S: " << compt << std::endl;
		this->removeTab ( index);
		compt++;
	}
	else if ( cu && compt != 0)	{
		std::cout << "Compt NS: " << compt << std::endl;
		compt++;
	//	delete cu;
	}
}

void PanneauData::clearPanneauData()	{
	QMap<Data *, DataG *>::iterator i;
	for (int i = this->onglets.count(); i > -1 ; i--)	{
		this->removeTab ( i);		
	}
/*	for (i = onglets.begin(); i != onglets.end(); ++i)	{
		delete this->onglets.take ( i.key());
	}*/		
	onglets.clear();
}
