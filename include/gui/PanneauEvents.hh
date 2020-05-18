#ifndef __H_PANNEAUEVENTS__
#define __H_PANNEAUEVENTS__

/*!
 * \file PanneauEvents.hh
 * \brief Panneau des événements
 * \author Nadjibian
 * \version 0.1
 */

#include "QTextEdit"
#include "QLabel"
#include "QLCDNumber"
#include "gSimulation.hh"
#include "QString"
#include "QVBoxLayout"
#include "QTreeWidgetItem"
#include "QStandardItemModel"
/*!
 * \class PanneauEvents
 * \brief La classe PanneauEvents pour afficher les traces de la simulation  .
 */
class gSimulation;
class PanneauEvents : public QWidget
{
    Q_OBJECT
private:
  QLabel *evenements;/*!< Titre a afficher sur le panneau d'événements */
 // static QTextEdit *txt;/*!< espace d'affichage des événements */
  static QLCDNumber *timerSimulation;/*!< affichage de timer*/
  QVBoxLayout layout;/*!< alignment attributes de widget*/
  static QTreeWidget *treeview;/*!<affichage des tous les équipements */

public:
  /*!
       * \brief Constructeur par défaut
       * Constructeur par défaut de la classe PanneauEvents.
  */
    PanneauEvents();
    /*!
         * \brief Destructeur  par défaut
         * Constructeur par défaut de la classe PanneauEvents.
    */
    ~PanneauEvents();
    /*!
         * \brief affichage
         * afficher un text sur le panneau d'événements
         * \param  text : text a afficher
    */
   //static void affichage(QString text);
    /*!
         * \brief addRoot
         * l'ajout d'un parent treeview
         * \param  parent : parent a ajouter
         * \param nom: le nom de parent
    */
  static  void addRoot(QTreeWidgetItem *parent,QString nom);
  /*!
       * \brief addCh
       * l'ajout d'un fils sur le treeview
       * \param  parent : le parent ou le fils sera ajouté
       * \param nom: le nom de fils
  */
  static void addCh(QTreeWidgetItem *parent,QString nom);
  /*!
       * \brief getTreeview
       * return treeview
  */
 static QTreeWidget *getTreeview(){return treeview;};
  /*!
       * \brief setTreeview
       * \param treeview:le nouveau treeview
  */
  void setTreeview(QTreeWidget *treeview);

public slots:
   /*!
        * \brief afftime
        * afficher le timer sur un qcld number
   */
  static void afftime();

};
#endif

