#ifndef __H_STATIONG_
#define __H_STATIONG_

/*!
 * \file StationG.h
 * \brief StationG
 * \author GT17S & Medish & Khalimoh
 * \version 0.1
 */

#include <Station.hh>
#include <NoeudG.hh>

class NoeudG;
class Station;

/*!
 * \class StationG
 * \brief La classe StationG représentant une Station sur l'interface graphique
 * lors de la simulation du protocole TCP/IP.
 */
class StationG  :  public virtual NoeudG
{

    private:

    public:
        StationG();

        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe StationG
             *  Initialise une StationG par une icon.
             * \param pixmap : voir #QPixmap
        */
        StationG(QPixmap pixmap);

        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe StationG
             *  Initialise un StationG par une scene ou la StationG vas etre afficher et une icon.
             * \param pixmap : voir #QPixmap
             * \param parent : voir #QGraphicsScene
        */
        StationG(QGraphicsScene *parent=nullptr,QPixmap pixmap = QPixmap("../../ressources/computer.png"));

        /*!
             * \brief desctructeur
             *  Desctructeur de la classe StationG
        */
        ~StationG();
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseDoubleClickEvent( QMouseEvent * event );

};

#endif
