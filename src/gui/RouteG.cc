#include "RouteG.hh"
#include <QDebug>
#include "Dialog.hh"


RouteG::~RouteG()
{
    delete gridLayoutinterface ;
    delete nextHope;
    delete AdresseRes;
    delete mask ;
    delete resName ;
    delete supprimer;
    delete appliquer;
    delete portGroupBox ;
    //delete layout ;

}

void RouteG::deleteroute()
{
    qDebug()<<"kaka";
    this->~RouteG();
}
RouteG::RouteG(QString _nextHope, QString _AdresseRes, QString _mask){
    createInputs( _nextHope, _AdresseRes, _mask );

    createLabels();

}
void RouteG::createLabels(){
    gridLayoutinterface = new QGridLayout();

    supprimer = new QPushButton("Supprimer");
    appliquer = new QPushButton("Appliquer");

    portGroupBox = new QGroupBox("Form Routage");
    layout = new QFormLayout;

   layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
   layout->addRow(new QLabel("Masque:"), mask);
   layout->addRow(new QLabel("Next hope:"), nextHope);

   portGroupBox->setLayout(layout);
   gridLayoutinterface->addWidget(portGroupBox);
   gridLayoutinterface->addWidget(appliquer);
   gridLayoutinterface->addWidget(supprimer);

   setLayout(gridLayoutinterface);

}
void RouteG::createInputs(QString _nextHope,QString _AdresseRes,QString _mask){
    nextHope	 = new QLineEdit (_nextHope);
    AdresseRes	 = new QLineEdit (_AdresseRes);
    mask	 = new QLineEdit (_mask);
}
