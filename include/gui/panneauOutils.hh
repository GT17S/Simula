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
#include "PanneauEvents.hh"
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
    void demarrerSimulation();
    void pauseSimulation();
    void arreterSimulation();
    void resetSimulation();
    /*!
         * \brief toPng
         * slot qui permet d'exporter l'espace de travail en image png
    */
    void toPng();
    void changeMode(){std::cout<< "changeMode"<<std::endl;};
    void envoieD(){std::cout<< "envoieD"<<std::endl;};

private :
    QString curFile;
    gSimulation gestSimulation;
};

#endif
