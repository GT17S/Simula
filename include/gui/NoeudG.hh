#ifndef __H_NOEUDG_
#define __H_NOEUDG_

/*!
 * \file NoeudG.hh
 * \brief NoeudG
 * \author GT17S & Medish & Khalimoh
 * \version 0.1
 */

#include "Noeud.hh"
#include "CableG.hh"
#include "EspaceTravail.hh"
#include "Dialog.hh"
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

class Noeud;
class EspaceTravail;


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
class NoeudG  :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    //pour les icons afficher les differents noeuds
    void addLine(CableG * cable, bool isPoint1);
    void moveCable(QPointF newPos);


public:
    void toolTipShow();
    //NoeudG(){ qDebug("hello switch!");}
    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe NoeudG
         *  Initialise un NoeudG par une scene ou le noeudG va t'etre afficher et une icon.
         * \param pixmap : voir #QPixmap
         * \param espaceTravail : voir #QGraphicsScene
    */
    NoeudG(EspaceTravail *_espaceTravail);

    /*!
         * \brief Destructeur
         * Destructeur de la classe NoeudG
     */
    ~NoeudG();

    Noeud * getChild(){return child;}
    void setChild(Noeud * _child);

    vector<cableG_extremite> getCablesG(){return extremiteG;}
    void setCableG(vector<cableG_extremite> _extremiteG){ extremiteG = _extremiteG;}

    QTreeWidgetItem * getTreeItem(){return parent;}
    void setTreeItem(QTreeWidgetItem *_parent){ parent = _parent;}

protected:
    vector<cableG_extremite> extremiteG;
    //fenetre en clickant sur l'un des noeuds
    EspaceTravail *espaceTravail;
    Noeud * child;
    QTreeWidgetItem *parent;/*!< la section ou tous les traitement d'une station seront affiche dans PanneauEvent */
    Dialog * configuration;

    //void mouseDoubleClickEvent( QMouseEvent * e );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void showInterfacesMenu();
    //void mouseMoveEvent( QMouseEvent *e );
    //void mouseReleaseEvent( QMouseEvent *e );

 public slots :
    void interfaceAction(int i);
};

#endif
