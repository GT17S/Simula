#ifndef __H_NOEUDG_
#define __H_NOEUDG_

/*!
 * \file NoeudG.h
 * \brief NoeudG
 * \author GT17S & Medish & Khalimoh
 * \version 0.1
 */

#include <Noeud.hh>
#include "EspaceTravail.hh"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "QTreeWidgetItem"
#include <vector>
#include <Dialog.hh>

class Noeud;
class EspaceTravail;
class CableG;


#ifndef CABLEG_EXTREMITE_H
#define CABLEG_EXTREMITE_H
struct cableG_extremite{
    CableG * cable;
    bool isP1;
};
#endif

using std::vector;
/*!
 * \class NoeudG
 * \brief La classe NoeudG représentant un noeud (equipement) sur l'interface graphique
 * pendant la simulation de protocole TCP/IP.
 */
class Dialog;
class NoeudG  :  public QGraphicsPixmapItem
{
private:
    //pour les icons afficher les differents noeuds
    QPixmap *pixmap;
    QGraphicsPixmapItem* item;
    vector<cableG_extremite> extremiteG;
    //fenetre en clickant sur l'un des noeuds
    EspaceTravail *espaceTravail;
    Noeud * child;
    QTreeWidgetItem *parent;/*!< la section ou tous les traitement d'une station seront affiche dans PanneauEvent */
    Dialog * configuration;
    void addLine(CableG * cable, bool isPoint1);
    void moveCable(QPointF newPos);


public:

    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe NoeudG
         *  Initialise un NoeudG par une scene ou le noeudG va t'etre afficher et une icon.
         * \param pixmap : voir #QPixmap
         * \param espaceTravail : voir #QGraphicsScene
    */
    NoeudG(EspaceTravail *_espaceTravail, QPixmap pixmap= QPixmap("../../ressources/hub.png"));

    /*!
         * \brief Destructeur
         * Destructeur de la classe NoeudG
     */
    ~NoeudG();

    QPixmap *getPixmap() const;
    void setPixmap(QPixmap *value);

    QGraphicsPixmapItem *getItem() const;
    void setItem(QGraphicsPixmapItem *value);

    Noeud * getChild(){return child;}
    void setChild(Noeud * child);

protected:
    //void mouseDoubleClickEvent( QMouseEvent * e );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    //void mouseMoveEvent( QMouseEvent *e );
    //void mouseReleaseEvent( QMouseEvent *e );
};

#endif
