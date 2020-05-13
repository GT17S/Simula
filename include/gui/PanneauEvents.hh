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


/*!
 * \class PanneauEvents
 * \brief La classe PanneauEvents pour afficher les traces des algorithmes de congestions  .
 */

class PanneauEvents : public QWidget
{
    Q_OBJECT
private:
  QLabel *evenements;/*!< Titre a afficher sur le panneau d'événements */
  static QTextEdit *txt;/*!< espace d'affichage des événements */
  static QLCDNumber *timerSimulation;/*!< affichage de timer*/

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
   static void affichage(QString text);

public slots:
   /*!
        * \brief afftime
        * afficher le timer sur un qcld number
   */
  static void afftime();
};
#endif

