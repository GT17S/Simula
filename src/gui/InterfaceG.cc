#include "InterfaceG.hh"


InterfaceG::~InterfaceG()
{
    delete gridLayoutinterface ;
    delete AdresseIP	;
    delete AdresseMac	;
    delete AdresseRes	;
    delete mask ;
    delete interfaceName ;
    delete liaison ;
    delete appliquer;
    delete supprimer;

}

void InterfaceG::deleteInterfaceG()
{
    this->~InterfaceG();
}
InterfaceG::InterfaceG(QString _AdresseIP,QString _AdresseMac,QString _AdresseRes,
           QString _mask,QString _interfaceName,bool _liaison){
    createInputs( _AdresseIP, _AdresseMac, _AdresseRes,
                  _mask, _interfaceName, _liaison);
    createLabels();




}
void InterfaceG::createInputs(QString _AdresseIP, QString _AdresseMac, QString _AdresseRes, QString _mask,
                              QString _interfaceName, bool _liaison){

    AdresseIP	 = new QLineEdit (_AdresseIP);
    AdresseMac	 = new QLineEdit (_AdresseMac);
    AdresseRes	 = new QLineEdit (_AdresseRes);
    mask = new QLineEdit (_mask);
    interfaceName = new QLineEdit (_interfaceName);
    liaison = new QCheckBox("liaison", this);
    if(_liaison){
        liaison->setChecked(true);
    }else{
        liaison->setChecked(false);
    }
}
void InterfaceG::createLabels(){
    gridLayoutinterface = new QGridLayout();

    supprimer = new QPushButton("Supprimer");
    appliquer = new QPushButton("Appliquer");

    QGroupBox *portGroupBox = new QGroupBox("Form Port");
    QFormLayout *layout = new QFormLayout;

    layout->addRow(new QLabel("Nom interface:"), interfaceName);
    layout->addRow(new QLabel("Adresse machine:"), AdresseMac);
    layout->addRow(new QLabel("Adresse IP:"), AdresseIP);
    layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
    layout->addRow(new QLabel("Masque:"), mask);
    layout->addRow(new QLabel("Liaison:"), liaison);

    portGroupBox->setLayout(layout);
    gridLayoutinterface->addWidget(portGroupBox);
    gridLayoutinterface->addWidget(appliquer);
    gridLayoutinterface->addWidget(supprimer);

    this->setLayout(gridLayoutinterface);

}
