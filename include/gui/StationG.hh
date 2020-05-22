#ifndef __H_STATIONG_
#define __H_STATIONG_

/*!
 * \file StationG.hh
 * \brief StationG
 * \author GT17S & Medish & Khalimoh
 * \version 0.1
 */

#include "Station.hh"
#include "NoeudG.hh"

class NoeudG;
class Station;

/*!
 * \class StationG
 * \brief La classe StationG représentant une Station sur l'interface graphique
 * lors de la simulation du protocole TCP/IP.
 */
class StationG  :  public  NoeudG
{

    private:

    public:
        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe StationG
             *  Initialise un StationG par une scene ou la StationG vas etre afficher et une icon.
             * \param pixmap : voir #QPixmap
             * \param parent : voir #QGraphicsScene
        */
        StationG(EspaceTravail *parent);

        /*!
             * \brief desctructeur
             *  Desctructeur de la classe StationG
        */
        ~StationG();

};

#endif
