
#ifndef __H_SIMULAGUI__
#define __H_SIMULAGUI__ 

#include <QtWidgets>
#include <QIcon>
#include <QVector>
#include <QGridLayout>
#include <QTextEdit>
#include <QWidget>
#include <QLabel>


#include "EspaceTravail.hh"
#include "panneauOutils.hh"
#include "ToolBarEquipement.hh"
#include "PanneauData.hh"
#include "PanneauEvents.hh"

class ToolBarEquipement;

class simulaGui: public QWidget {
private:
	//Grid
    QGridLayout* mainlayout;
	//Va contenir les 5 widgets
    QVector<QWidget *> widgets;

public:
	simulaGui();
	~simulaGui();
	

    QGridLayout* getMainlayout(void) const {return mainlayout;};

};


#endif
