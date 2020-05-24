#include "PanneauData.hh"

PanneauData::PanneauData( QWidget *parent) : QTabWidget(parent) {
	this->setMinimumHeight(80);
	this->setMaximumHeight(100);
	this->setTabsClosable(true);
	compt = 0;

    connect( this, SIGNAL(tabCloseRequested(int)), this, SLOT(askRemoveTab(int)));

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
}

void PanneauData::askRemoveTab( int index)	{
   std::cout << "Index : " << index << std::endl;

   delete widget(index);
}

void PanneauData::clearPanneauData()	{
    //QMap<Data *, DataG *>::iterator i;
    onglets.clear();

    int size_tabs = this->count();
    if(!size_tabs)
        return;
    for (int i = size_tabs-1; i > -1 ; i--)	{
        delete widget(i);

	}
/*	for (i = onglets.begin(); i != onglets.end(); ++i)	{
		delete this->onglets.take ( i.key());
	}*/		
}
