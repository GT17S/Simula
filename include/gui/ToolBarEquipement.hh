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
    QAction     *cableCAction,
                *cableDAction;
    void createButtons();
    void createSignals();
    void createShortcuts();
    EspaceTravail * espaceTravail;
public:
    ToolBarEquipement(EspaceTravail *);
    virtual ~ToolBarEquipement(){}


    
public slots:
  	//void selectionnerEquipement(){};
    void selectItem();
    void ajouterNoeud(int n);
    void ajouterCable();
    void supprimerEquipement();

};


#endif
