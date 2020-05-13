#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QtGlobal>
#include <sstream>
#include <string>
#include <QPen>
#include "Cable.hh"


/*!
 * \file CableG.hh
 * \brief Representation graphique du cable
 * \author GT17 & Khalimouh
 * \version 0.1
 */
class CableG: public  Cable, public QGraphicsLineItem
{
private:
	std::stringstream tooltipstr; /*!< Chaine qui va servir à construire la tooltip*/
	QPen pen; /*!< Style de la fleche en fonction du cable*/
public:
	 /*!
         * \brief Constructeur par défaut
         * Constructeur par défaut de la classe CableG.
    */
	CableG();
	 /*!
         * \brief Constructeur paramétré
         * Constructeur qui prends deux points et initialise le cable a cette position
         * \param qreal positions des points en 2D
    */
	CableG(qreal x1, qreal x2, qreal x3, qreal x4);
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
};