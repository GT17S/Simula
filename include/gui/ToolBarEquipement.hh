#ifndef __H_TOOLBAREQUIPEMENT__
#define __H_TOOLBAREQUIPEMENT__


#include <QToolBar>
#include <QWidget>
#include <QPixmap>
#include <QAction>
#include <QSignalMapper>
#include <iostream>

#include "Noeud.hh"
#include "NoeudG.hh"
#include "CableG.hh"
#include "Cable.hh"
#include "Hub.hh"
#include "HubG.hh"
#include "Switch.hh"
#include "SwitchG.hh"
#include "DataG.hh"
#include "Station.hh"
#include "StationG.hh"
#include "simulaGui.hh"
#include "Routeur.hh"
#include "RouteurG.hh"

class QToolBar;
class simulaGui;
class NoeudG;
class RouteurG;
class StationG;	

class ToolBarEquipement : public QToolBar {
    Q_OBJECT
public:
    ToolBarEquipement(QWidget*);
    virtual ~ToolBarEquipement(){};


    
public slots:
    void selectionnerEquipement(){};
    void ajouterNoeud(int n);
    void ajouterCable();
    void supprimerEquipement(){std::cout << "Winiw" << std::endl;};

};


#endif