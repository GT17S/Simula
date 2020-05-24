#include "RouteG.hh"
#include <QDebug>
#include "Dialog.hh"


RouteG::~RouteG()

{
}

void RouteG::deleteroute()
{
    this->~RouteG();
}
RouteG::RouteG(QString _nextHope, QString _AdresseRes, QString _mask){
    createInputs( _nextHope, _AdresseRes, _mask );

    createLabels();

}
void RouteG::createLabels(){

    gridLayoutinterface = new QGridLayout();

    supprimer = new QPushButton("Supprimer la route");
    appliquer = new QPushButton("Appliquer modifications");

    portGroupBox = new QGroupBox("Routage");
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
QLineEdit *RouteG::getNextHope() const
{
    return nextHope;
}

void RouteG::setNextHope(QLineEdit *value)
{
    nextHope = value;
}

QLineEdit *RouteG::getAdresseRes() const
{
    return AdresseRes;
}

void RouteG::setAdresseRes(QLineEdit *value)
{
    AdresseRes = value;
}

QLineEdit *RouteG::getMask() const
{
    return mask;
}

void RouteG::setMask(QLineEdit *value)
{
    mask = value;
}

void RouteG::createInputs(QString _nextHope,QString _AdresseRes,QString _mask){
    QRegExp rxIp(QString::fromStdString(IP_REGEX));
    QValidator *ipValidator= new QRegExpValidator(rxIp,this);
    nextHope	 = new QLineEdit (_nextHope);
    nextHope->setValidator(ipValidator);
    AdresseRes	 = new QLineEdit (_AdresseRes);
    AdresseRes->setValidator(ipValidator);
    mask	 = new QLineEdit (_mask);
    mask->setValidator(ipValidator);

}
