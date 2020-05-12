#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>
#include <QWidget>
#include <QAction>
#include <iostream>
#include "EspaceTravail.hh"
class PanneauOutils : public QToolBar{
	Q_OBJECT
public:

    PanneauOutils();
	virtual ~PanneauOutils(){};

public slots:
    void nouveauFichier();
    void ouvrirFichier();
    void sauvegarderFichier();
    void exporterFichier();
    void exporterImage(){std::cout<< "Exporter"<<std::endl;};
    void demarrerSimulation(){std::cout<< "demarrer"<<std::endl;};
    void arreterSimulation(){std::cout<< "arreter"<<std::endl;};
    void resetSimulation(){std::cout<< "reset"<<std::endl;};
    void changeMode(){std::cout<< "changeMode"<<std::endl;};
    void envoieD(){std::cout<< "envoieD"<<std::endl;};

private :
    QString curFile;

    bool maybeSave();
};

#endif
