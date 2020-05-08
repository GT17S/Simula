#ifndef __H_TOOLBAREQUIPEMENT__
#define __H_TOOLBAREQUIPEMENT__

#include "Noeud.hh"
#include "Cable.hh"

#include <QToolBar>
#include <MyQWidget.hh>
class ToolBarEquipement : public QToolBar, public MyQWidget
{
    Q_OBJECT
public:

    ToolBarEquipement();
	virtual ~ToolBarEquipement(){};
public slots:
	void selectionnerEquipement();
	void ajouterNoeud(Noeud *);
	void ajouterCable(Cable *);
    void supprimerEquipement();

    void showInfos() override;
};

#endif
