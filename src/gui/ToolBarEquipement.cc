#include "ToolBarEquipement.hh"

ToolBarEquipement::ToolBarEquipement(): QToolBar(){

    //this->setStyleSheet("background-color: pink");
	this->setMinimumSize(50,430);
    this->setMaximumWidth(100);
    this->setOrientation(Qt::Vertical);
    //Creer les boutons
    QPixmap cable("../../ressources/logo.png");
    QPixmap suppr("../../ressources/logo.png");
    QPixmap routeur("../../ressources/logo.png");
    QPixmap hub("../../ressources/logo.png");
    QPixmap station("../../ressources/logo.png");
    QPixmap sw("../../ressources/logo.png");

    QAction* Addcable =  this->addAction(QIcon(cable),"Ajouter Cable");
    QAction* DelEq = this->addAction(QIcon(suppr),"Supprimer Equipement");
    this->addSeparator();
    QAction* NRouteur =  this->addAction(QIcon(routeur),"Nouveau Routeur");
    QAction* NHub = this->addAction(QIcon(hub),"Nouveau Hub");
    QAction* NStation =this->addAction(QIcon(station),"Nouvelle Station");
    QAction* NSw =this->addAction(QIcon(sw),"Nouveau Swtich");


    connect(Addcable, SIGNAL(triggered()), this, SLOT(ajouterCable()));
    connect(DelEq, SIGNAL(triggered()), this, SLOT(supprimerEquipement()));
    connect(NRouteur, SIGNAL(triggered()), this, SLOT(ajouterNoeud(Noeud*)));
    connect(NHub, SIGNAL(triggered()), this, SLOT(ajouterNoeud(Noeud*)));
    connect(NStation, SIGNAL(triggered()), this, SLOT(ajouterNoeud(Noeud*)));
    connect(NSw, SIGNAL(triggered()), this, SLOT(ajouterNoeud(Noeud*)));


}	




