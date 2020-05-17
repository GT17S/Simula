#ifndef __H_HUBG_
#define __H_HUBG_

/*!
 * \file HubG.h
 * \brief HubG
 * \author GT17S
 * \version 0.1
 */

#include <NoeudG.hh>

class NoeudG;

/*!
 * \class HubG
 * \brief La classe HubG représentant un Hub sur l'interface graphique
 * lors de la simulation du protocole TCP/IP.
 */
class HubG :  public virtual NoeudG
{

    private:

    public:


        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe HubG
             *  Initialise un HubG par une scene ou le HubG vas etre afficher et une icon.
             * \param pixmap : voir #QPixmap
             * \param parent : voir #QGraphicsScene
        */
        HubG(EspaceTravail *parent=nullptr,QPixmap pixmap = QPixmap("../../ressources/hub.png"));

        /*!
             * \brief desctructeur
             *  Desctructeur de la classe HubG
        */

        ~HubG();

};

#endif
