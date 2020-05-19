#include "Route.hh"
#include <QDebug>
#include "Dialog.hh"

Route::Route()
{
     gridLayoutinterface = new QGridLayout();
     nextHope	 = new QLineEdit ();
     AdresseRes	 = new QLineEdit ();
     mask = new QLineEdit ();
     resName = new QLineEdit ();

     supprimer = new QPushButton("Supprimer");
     appliquer = new QPushButton("Appliquer");

     portGroupBox = new QGroupBox("Form Routage");
     layout = new QFormLayout;

    layout->addRow(new QLabel("Nom de reseau:"), resName);
    layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
    layout->addRow(new QLabel("Masque:"), mask);
    layout->addRow(new QLabel("Next hope:"), nextHope);

    portGroupBox->setLayout(layout);
    gridLayoutinterface->addWidget(portGroupBox);
    gridLayoutinterface->addWidget(appliquer);
    gridLayoutinterface->addWidget(supprimer);

    setLayout(gridLayoutinterface);
    connect(supprimer,SIGNAL(clicked()),SLOT(deleteroute()));
}

Route::~Route()
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

void Route::deleteroute()
{
    qDebug()<<"kaka";
    this->~Route();
}
