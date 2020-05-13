#ifndef __H_TOOLBAREQUIPEMENT__
#define __H_TOOLBAREQUIPEMENT__


#include <QToolBar>
#include <QWidget>
#include <QPixmap>
#include <QAction>
#include <QSignalMapper>
#include <iostream>

#include "Noeud.hh"
#include "Cable.hh"
#include "Hub.hh"
#include "CableG.hh"
#include "DataG.hh"
#include "Station.hh"
#include "Routeur.hh"
#include "Switch.hh"
#include "simulaGui.hh"

class QToolBar;
class simulaGui;

class ToolBarEquipement : public QToolBar {
    Q_OBJECT
public:
    ToolBarEquipement(QWidget*);
    virtual ~ToolBarEquipement(){};


    
public slots:
    void selectionnerEquipement(){};
    void ajouterNoeud(int n){ std::cout << n << std::endl;};
    void ajouterCable();
    void supprimerEquipement(){std::cout << "Winiw" << std::endl;};

};


#endif