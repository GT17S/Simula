#include "simulaGui.hh"

simulaGui::simulaGui(){

    //Initialisation de la fenetre principale
	this->setWindowTitle("Simula");
	this->setWindowIcon(QIcon("../../ressources/logo.png"));
	this->setStyleSheet("background-color: lightgray;");
	//Donner une taille	
	resize(1000,600);


    mainlayout = new QGridLayout();
    this->setLayout(mainlayout);


	for (int i = 0; i < 5; ++i)
	{
        widgets.append(new QTextEdit());
    }

    //Modifier les tailles de chaque widget
    //QWidget *widget, int fromRow, int fromColumn, int rowSpan, int columnSpan
    mainlayout->addWidget(widgets[0], 0, 0, 1, 4); //Barre menu
    mainlayout->addWidget(widgets[1], 2, 2, 2, 2); //Espace de travail
    mainlayout->addWidget(widgets[2], 4, 0, 1, 4); //Barre d'etat
    mainlayout->addWidget(widgets[3], 1, 0, 2, 1); //Barre d'équipements
    mainlayout->addWidget(widgets[4], 2, 3, 2, 1); //Panneau evenements

    //Signaux


 }

simulaGui::~simulaGui(){

}
