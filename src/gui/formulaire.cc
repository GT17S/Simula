#include "formulaire.hh"

formulaire::formulaire(): QWidget(){
	setWindowTitle(QString("Paramètres d'envoi"));
    setMinimumSize(50,100);
    resize(300,600);
    setLayout(new QVBoxLayout());




    show();
}