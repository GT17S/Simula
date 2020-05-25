#include "InterfaceG.hh"
#include "QDebug"
#include "InterfaceFE.hh"

InterfaceG::~InterfaceG()
{
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

    QRegExp rxIp(QString::fromStdString(IP_REGEX));
    QValidator *ipValidator= new QRegExpValidator(rxIp,this);
    AdresseIP	 = new QLineEdit (_AdresseIP);
    AdresseIP->setValidator(ipValidator);
    AdresseMac	 = new QLineEdit (_AdresseMac);
    AdresseRes	 = new QLineEdit (_AdresseRes);
    AdresseRes->setValidator(ipValidator);

    mask = new QLineEdit (_mask);
    mask->setValidator(ipValidator);

    interfaceName = new QLineEdit (_interfaceName);
    liaison = new QCheckBox("liaison", this);
    liaison->setEnabled(false);
    if(_liaison){
        liaison->setChecked(true);
    }else{
        liaison->setChecked(false);
    }
}
void InterfaceG::createLabels(){
    gridLayoutinterface = new QGridLayout();

    //supprimer = new QPushButton("Supprimer");
    appliquer = new QPushButton("Appliquer modifications ");

    QGroupBox *portGroupBox = new QGroupBox(" Port");
    QFormLayout *layout = new QFormLayout;

    layout->addRow(new QLabel("Nom interface:"), interfaceName);
    layout->addRow(new QLabel("Adresse machine:"), AdresseMac);
    AdresseMac->setEnabled(false);
    layout->addRow(new QLabel("Adresse IP:"), AdresseIP);
    layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
    layout->addRow(new QLabel("Masque:"), mask);
    layout->addRow(new QLabel("Liaison:"), liaison);

    portGroupBox->setLayout(layout);
    gridLayoutinterface->addWidget(portGroupBox);
    gridLayoutinterface->addWidget(appliquer);
   // gridLayoutinterface->addWidget(supprimer);

    this->setLayout(gridLayoutinterface);

}
