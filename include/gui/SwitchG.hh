#ifndef __H_SWITCHG_
#define __H_SWITCHG_

/*!
 * \file SwitchG.h
 * \brief SwitchG
 * \author GT17S
 * \version 0.1
 */

#include "HubG.hh"

class EspaceTravail;
class HubG;

/*!
 * \class SwitchG
 * \brief La classe SwitchG représentant un Switch sur l'interface graphique
 * lors de la simulation du protocole TCP/IP.
 */
class SwitchG  :  public  HubG
{

    private:

    public:
        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe SwitchG
             *  Initialise un SwitchG par une scene ou le SwitchG vas etre afficher et une icon.
             * \param pixmap : voir #QPixmap
             * \param parent : voir #QGraphicsScene
        */
        SwitchG(EspaceTravail * parent=nullptr);

        /*!
             * \brief desctructeur
             *  Desctructeur de la classe SwitchG
        */

        ~SwitchG();

};

#endif
