#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>
#include <QWidget>
#include <QAction>
#include <iostream>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include "EspaceTravail.hh"
#include "gSimulation.hh"
class PanneauOutils : public QToolBar{
	Q_OBJECT
public:

    PanneauOutils();
	virtual ~PanneauOutils(){};

public slots:
    void timer();
    void nouveauFichier();
    void ouvrirFichier();
    void sauvegarderFichier();
    void exporterFichier();
    void exporterImage(){std::cout<< "Exporter"<<std::endl;};
    void demarrerSimulation();
    void pauseSimulation();
    void arreterSimulation();
    void resetSimulation();
    void changeMode(){std::cout<< "changeMode"<<std::endl;};
    void envoieD(){std::cout<< "envoieD"<<std::endl;};

private :
    QString curFile;
    gSimulation gestSimulation;
};

#endif
