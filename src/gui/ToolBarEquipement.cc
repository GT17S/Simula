#include "ToolBarEquipement.hh"




ToolBarEquipement::ToolBarEquipement(QWidget* par): QToolBar(par){

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

    //Mapper le 4 triggered vers 
    QSignalMapper* mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(ajouterNoeud(int)));

    connect(Addcable, SIGNAL(triggered()), this, SLOT(ajouterCable()));
    connect(DelEq, SIGNAL(triggered()), this, SLOT(supprimerEquipement()));
    mapper->setMapping(NRouteur, 1);
    mapper->setMapping(NHub, 2);
    mapper->setMapping(NStation, 3);
    mapper->setMapping(NSw, 4);

  	connect(NRouteur, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(NHub, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(NStation, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(NSw, SIGNAL(triggered()), mapper, SLOT(map()));

}	


void ToolBarEquipement::ajouterCable(){
   auto s  = this->parent();
   simulaGui* ss = dynamic_cast<simulaGui*>(s);
   auto ss2 = dynamic_cast<EspaceTravail*>(ss->getMainlayout()->itemAtPosition(1,1)->widget());
   assert(ss && ss2);  
   ss2->addCatPos();
}