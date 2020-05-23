#ifndef CABLEG_H
#define CABLEG_H

#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QtGlobal>
#include <sstream>
#include <string>
#include <QPen>
#include "Cable.hh"
#include "NoeudG.hh"

class Cable;
class NoeudG;
/*!
 * \file CableG.hh
 * \brief Representation graphique du cable
 * \author GT17 & Khalimouh
 * \version 0.1
 */
class CableG: public QGraphicsLineItem
{
    friend class NoeudG;
private:
    Cable * child;
    NoeudG * extG1;
    NoeudG * extG2;
public:
	 /*!
         * \brief Constructeur paramétré
         * Constructeur qui prends deux points et initialise le cable a cette position
         * \param qreal positions des points en 2D
    */
    CableG(qreal x1 = 0, qreal x2 = 0, qreal x3 =0, qreal x4=0);
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

    Cable * getChild(){return child;}
    void setChild(Cable * _child){ child = _child;}
};

#endif
