#ifndef __H_TOOLBAREQUIPEMENT__
#define __H_TOOLBAREQUIPEMENT__


#include <QToolBar>
#include <QWidget>
#include <QSignalMapper>
#include <iostream>
#include "simulaGui.hh"


/*!
 * \class ToolBarEquipement
 * \brief La classe ToolBarEquipement représentant une bare d'équipements sur l'interface graphique lors de la simulation du protocole TCP/IP.
 */
class ToolBarEquipement : public QToolBar {
    Q_OBJECT
private:
    QPushButton *selectAction,/*!< Bouton de selection d'un équipement ou cable*/
                *supprAction,/*!< Bouton de supprission d'un équipement ou cable*/
                *cableAction,/*!< Bouton de d'ajout d'un cable*/
                *stationAction,/*!< Bouton de d'ajout d'une station*/
                *routeurAction,/*!< Bouton de d'ajout d'un routeur*/
                *hubAction,/*!< Bouton de d'ajout d'un hub*/
                *switchAction;/*!< Bouton de d'ajout d'un Switch*/
    QAction     *cableCAction,
                *cableDAction;
    EspaceTravail * espaceTravail;/*!< Objet permettant de contenir les equipements et de realiser leurs differrentes interactions sur l'interface graphique*/

    /*!
        * \brief createButtons
        * Construction et Initialisation  des differentes buttons de ToolBarEquipement
   */
   void createButtons();

   /*!
       * \brief createSignals
       * Construction et Initialisation  des differentes signaux de ToolBarEquipement
   */
   void createSignals();

   /*!
       * \brief createShortcuts
       * Initialisation  des differentes raccourcis de ToolBarEquipement
   */
   void createShortcuts();


public:
   /*!
       * \brief Constructeur paramétré
       * Constructeur qui prends un espace de travail
       * \param *: voir #EspaceTravail

   */
    ToolBarEquipement(EspaceTravail *);

    /*!
        * \brief Destructeur
        * Destructeur de la classe ToolBarEquipement
    */

    virtual ~ToolBarEquipement(){}


    
public slots:
  	//void selectionnerEquipement(){};
    /*!
        * \brief selectItem
        * selectionner un item sur la ToolBarEquipement
    */
    void selectItem();

    /*!
        * \brief ajouterNoeud
        * Slot d'ajout d'un noeud
        *\param n: voir #int
*/
    void ajouterNoeud(int n);

    /*!
        * \brief ajouterCable
        * Slot d'ajout d'un cable

*/
    void ajouterCable();

    /*!
        * \brief supprimerEquipement
        * Slot permettant la suppression d'un element de l'espace de travail
    */
    void supprimerEquipement();

};


#endif
