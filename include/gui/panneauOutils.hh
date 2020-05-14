#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>
#include <QWidget>
#include <QAction>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QMenu>
#include <QToolButton>
#include <QPushButton>
#include "EspaceTravail.hh"
#include "gSimulation.hh"
class PanneauOutils : public QToolBar{
	Q_OBJECT
private :
    QString curFile;
    gSimulation gestSimulation;
    QAction *nouveau,
            *ouvrir,
            *sauvegarder,
            *exporterDot,
            *exporterPng,
            *demarrer,
            *pause,
            *arreter,
            *relancer,
            *changerMode,
            *envoyer;
    QToolButton * exportButton;

void createButtons();
void createSignals();
void createShortCuts();

public:

    PanneauOutils();
    virtual ~PanneauOutils();

public slots:
    void timer();
    void nouveauFichier();
    void ouvrirFichier();
    void sauvegarderFichier();
    void exportDot();
    void exportPng();
    void demarrerSimulation();
    void pauseSimulation();
    void arreterSimulation();
    void resetSimulation();
    void changeMode(){std::cout<< "changeMode"<<std::endl;}
    void envoieD(){std::cout<< "envoieD"<<std::endl;}

};

#endif
