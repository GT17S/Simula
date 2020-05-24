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


public:
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

    /*!
        * \brief getChild
        * recuperer l'enfant de NoeudG qui est Un Noeud
   */
    Noeud * getChild(){return child;}


    /*!
        * \brief setChild
        * affecter un noeud fils à NoeudG.
        * \param _child: voir #Noeud
   */
    void setChild(Noeud * _child);


    /*!
        * \brief getCablesG
        * recuperer les CableG de NoeudG.
   */
    vector<cableG_extremite> getCablesG(){return extremiteG;}


    /*!
        * \brief setCableG
        * Affecte un vecteur de cableG.
        * \param _extrimiteG: voir #cableG_extremite
   */
    void setCableG(vector<cableG_extremite> _extremiteG){ extremiteG = _extremiteG;}


    /*!
        * \brief getTreeItem
        * recuperer le parent de NoeudG .
   */
    QTreeWidgetItem * getTreeItem(){return parent;}


    /*!
        * \brief setTreeItem
        * Initialise le parent de NoeudG.
        * \param *_parent: voir #QTreeWidgetItem
   */
    void setTreeItem(QTreeWidgetItem *_parent){ parent = _parent;}

    void addLine(CableG * cable, bool isPoint1);
    void moveCable(QPointF newPos);


    /*!
        * \brief ToolTipShow
        * Affichage en hover souris des donnees d'un equipement.
   */
    void toolTipShow();
	//Ajouté par Massi
	EspaceTravail * getEspaceTravail ()	{ return espaceTravail;};

protected:
    vector<cableG_extremite> extremiteG;/*!< Vecteur stockant les cablesG d'un NoeudG*/
    //fenetre en clickant sur l'un des noeuds
    EspaceTravail *espaceTravail;/*!< Objet permettant de contenir les equipements et de realiser leurs differrentes interactions sur l'interface graphique*/
    Noeud * child;/*!< Fils de NoeudG permettant d'affichage et la gestion des données sur l'interface graphique*/
    QTreeWidgetItem *parent;/*!< la section ou tous les traitement d'une station seront affiche dans PanneauEvent */
    Dialog * configuration;/*!< fenetre de configuration du NoeudG sur l'interface graphique*/

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
