#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>
#include <QWidget>
#include <QDebug>
#include <QMenu>
#include <QPushButton>
#include <QAction>

#include <QFormLayout>
#include <QInputDialog>
#include <QTextEdit>
#include <QCheckBox>

#include <stdio.h>
#include <string.h>

#include "EspaceTravail.hh"
#include "gSimulation.hh"
#include "PanneauEvents.hh"
class PanneauOutils : public QToolBar{
	Q_OBJECT
private :
    QString curFile;
    gSimulation *gestSimulation;
    QPushButton *nouveau,
                *ouvrir,
                *sauvegarder,
                *simDemPause,
                *arreter,
                *relancer,
                *changerMode,
                *envoyer,
                *zoomIn,
                *zoomOut,
                *exportButton;
    QAction     *exporterDot,
                *exporterPng;

void createButtons();
void createSignals();
void createShortCuts();

public:

    PanneauOutils( gSimulation * g);
    virtual ~PanneauOutils();
	gSimulation* getGestionnaire(){ return gestSimulation;};
	void setGestionnaire ( gSimulation * g){gestSimulation = g;};

public slots:
    void timer();
    void nouveauFichier();
    void ouvrirFichier();
    void sauvegarderFichier();
    void exportDot();
    void exportPng();
    void demarrerPauseSimulation();
    void arreterSimulation();
    void resetSimulation();
    void changeMode();
    void envoieD();
    /*!
         * \brief toPng
         * slot qui permet d'exporter l'espace de travail en image png
    */
    void toPng();

};

#endif
