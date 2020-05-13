
#ifndef __H_SIMULAGUI__
#define __H_SIMULAGUI__ 

#include <QtWidgets>
#include <QIcon>
#include <QVector>
#include <QGridLayout>
#include <QTextEdit>
#include <QWidget>
#include <QLabel>
#include <assert.h>

#include "EspaceTravail.hh"
#include "panneauOutils.hh"
#include "ToolBarEquipement.hh"
#include "PanneauData.hh"
#include "PanneauEvents.hh"

class ToolBarEquipement;
/*!
 * \file simulaGui.hh
 * \brief Fenetre principale de l'application
 * \author Khalimouh
 * \version 0.1
 */
class simulaGui: public QWidget {
private:
	//Grid
    QGridLayout* mainlayout; /*!< Grille de Layout pour le 5 Widgets*/
	
    QVector<QWidget *> widgets;/*!< Tableau pour contenir les 5 widgets*/

public:
	 /*!
         * \brief Constructeur par défaut
         * Constructeur par défaut de la classe simulaGui.
    */
	simulaGui();
	/*!
         * \brief Destructeur
         * Destructeur de la classe simulaGui
     */
	~simulaGui();
	
	
    QGridLayout* getMainlayout(void) const {return mainlayout;};

};


#endif
