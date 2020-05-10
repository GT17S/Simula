#ifndef __H_TOOLBAREQUIPEMENT__
#define __H_TOOLBAREQUIPEMENT__

#include "Noeud.hh"
#include "Cable.hh"
#include "Hub.hh"
#include "CableG.hh"
#include "DataG.hh"
#include "Station.hh"
#include "Routeur.hh"
#include "Switch.hh"

#include <QToolBar>
#include <QWidget>
#include <QPixmap>
#include <QAction>
#include <iostream>

class QToolBar;

class ToolBarEquipement : public QToolBar {
    Q_OBJECT
public:
    ToolBarEquipement();
	virtual ~ToolBarEquipement(){};

public slots:
    void selectionnerEquipement(){};
    void ajouterNoeud(Noeud * n){ std::cout << n << std::endl;};
    void ajouterCable(Cable *){ };
    void supprimerEquipement(){std::cout << "Winiw" << std::endl;};

};


#endif
