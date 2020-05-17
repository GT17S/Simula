#include "simulaGui.hh"

simulaGui::simulaGui(){

    //Initialisation de la fenetre principale
	this->setWindowTitle("Simula");
	this->setWindowIcon(QIcon("../../ressources/logo.png"));
    this->setStyleSheet("background-color: #f5f2f2;");
    this->setMinimumSize(900,600);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(1000,600);
    mainlayout = new QGridLayout();
    this->setLayout(mainlayout);
/*
    for(int i = 0; i <5; ++i){
        widgets.append(new QLabel());
   }
*/
    EspaceTravail * e = new EspaceTravail;
    widgets.append(new PanneauOutils(e)); //0
    widgets.append(e);
    widgets.append(new PanneauData());
    widgets.append(new ToolBarEquipement());
    widgets.append(new PanneauEvents());
 	

    //Modifier les tailles de chaque widget
    mainlayout->addWidget(widgets[0], 0, 0, 1, 4); //Barre menu (0)
    mainlayout->addWidget(widgets[1], 1, 1, 3, 2); //Espace de travail (1)
    mainlayout->addWidget(widgets[2], 4, 0, 1, 4); //Barre d'etat (2)
    mainlayout->addWidget(widgets[3], 1, 0, 3, 1); //Barre d'équipements (3)
    mainlayout->addWidget(widgets[4], 1, 3, 3, 1); //Panneau evenements (4)

    //Stretch

    mainlayout->setColumnStretch(0,1);
    mainlayout->setColumnStretch(1,2);
    mainlayout->setColumnStretch(2,2);
    mainlayout->setColumnStretch(3,2);

    mainlayout->setRowStretch(0,1);
    mainlayout->setRowStretch(1,2);
    mainlayout->setRowStretch(2,2);
    mainlayout->setRowStretch(3,1);
    mainlayout->setRowStretch(4,2);

    
    //widgets[1]->setMinimumSize(450,410);
//    widgets[2]->setMinimumHeight(80);
//    widgets[2]->setMaximumHeight(100);
    widgets[4]->setMinimumSize(100,410);
    widgets[4]->setMaximumWidth(350);

    for(int i = 0; i < 5; i++){
        widgets[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        widgets[i]->setParent(this);
    }

    //Signaux


 }

simulaGui::~simulaGui(){

}
