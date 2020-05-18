#ifndef __H_ROUTEURG_
#define __H_ROUTEURG_

/*!
 * \file RouteurG.h
 * \brief RouteurG
 * \author GT17S & Medish & Khalimoh
 * \version 0.1
 */

#include <Routeur.hh>
#include <NoeudG.hh>


/*!
 * \class RouteurG
 * \brief La classe RouteurG représentant un Routeur sur l'interface graphique
 * lors de la simulation du protocole TCP/IP.
 */

class RouteurG  : public virtual NoeudG
{
    private:

    public:
    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe RouteurG
         *  Initialise un RouteurG par une scene ou la StationG vas etre afficher et une icon.
         * \param pixmap : voir #QPixmap
         * \param parent : voir #QGraphicsScene
    */
    RouteurG(EspaceTravail *parent, QPixmap pixmap = QPixmap(":/ressources/equipements/routeur.png"));

    /*!
         * \brief desctructeur
         *  Desctructeur de la classe RouteurG
    */
    ~RouteurG();

};

#endif
