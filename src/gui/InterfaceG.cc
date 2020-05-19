#include "InterfaceG.hh"

InterfaceG::InterfaceG()
{

    gridLayoutinterface = new QGridLayout();
    AdresseIP	 = new QLineEdit ();
    AdresseMac	 = new QLineEdit ();
    AdresseRes	 = new QLineEdit ();
    mask = new QLineEdit ();
    interfaceName = new QLineEdit ();
    liaison = new QCheckBox("liaison", this);

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

    connect(supprimer,SIGNAL(clicked()),this,SLOT(deleteInterfaceG()));
}

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
