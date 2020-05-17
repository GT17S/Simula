#ifndef __H_TOOLBAREQUIPEMENT__
#define __H_TOOLBAREQUIPEMENT__


#include <QToolBar>
#include <QWidget>
#include <QSignalMapper>
#include <iostream>
#include "simulaGui.hh"


class ToolBarEquipement : public QToolBar {
    Q_OBJECT
private:
    QPushButton *selectAction,
                *supprAction,
                *cableAction,
                *stationAction,
                *routeurAction,
                *hubAction,
                *switchAction;
    void createButtons();
    void createSignals();
    EspaceTravail * espaceTravail;
public:
    ToolBarEquipement(EspaceTravail *);
    virtual ~ToolBarEquipement(){}


    
public slots:
  	//void selectionnerEquipement(){};
    void ajouterNoeud(int n);
    void ajouterCable();
    void supprimerEquipement();

};


#endif
