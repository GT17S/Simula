#ifndef CABLEG_H
#define CABLEG_H

/*!
 * \file CableG.hh
 * \brief Representation graphique du cable
 * \author GT17S & Khalimouh
 * \version 0.1
 */

#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QtGlobal>
#include <sstream>
#include <string>
#include <QPen>
#include "Cable.hh"
#include "NoeudG.hh"
#include "DialogCable.hh"

class Cable;
class NoeudG;
class DialogCable;
class EspaceTravail;


/*!
 * \class CableG
 * \brief La classe CableG représentant un cable loqigue sur l'interface graphique lors de la simulation du protocole TCP/IP.
 */

class CableG: public QGraphicsLineItem
{
    friend class NoeudG;
private:
    Cable * child;/*!< Fils de cableG permettant d'affichage et la gestion des données sur l'interface graphique*/
    NoeudG * extG1;/*!< Extrimite de cableG sur l'interface graphique*/
    NoeudG * extG2;/*!< Extrimite de cableG sur l'interface graphique*/
    EspaceTravail *espaceTravail;/*!< Objet permettant de contenir les equipements et de realiser leurs differrentes interactions sur l'interface graphique*/
    DialogCable *configurationCable;/*!< fenetre de configuration du cableG sur l'interface graphique*/

    /*!
        * \brief createPen
        * Constructeur et Initialisation  des differentes cableG possibles
   */
    static void createPen();

public:

    /*!
        * Initialisateur de type de CableG pendant la siumlation
   */
    static  QPen DROIT_TYPE,
                    CROISE_TYPE,
                    DROIT_ERREUR_TYPE,
                    CROISE_ERREUR_TYPE;

	 /*!
         * \brief Constructeur paramétré
         * Constructeur qui prends deux points et initialise le cable a cette position
         * \param qreal positions des points en 2D
    */
    CableG(EspaceTravail * _espaceTravail,qreal x1 = 0, qreal x2 = 0, qreal x3 =0, qreal x4=0);
	 /*!
         * \brief Destructeur
         * Destructeur de la classe CableG
     */
	~CableG();
	 /*!
         * \brief Mise à jour de l'affichage
         * Fonction qui met à jours l'affichage de la tooltip
    */
	void updateaff();

    /*!
        * \brief getChild
        * recuperer l'enfant de CableG qui est Un Cable
   */
    Cable * getChild(){return child;}

    /*!
        * \brief setChild
        * Initialise le cable fils de CableG par une entre cable
        * \param _child: voir #Cable
   */
    void setChild(Cable * _child);
protected:
    /*!
        * \brief mouseDoubleClickEvent
        * \param *event: voir #QGraphicsSceneMouseEvent
   */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif
