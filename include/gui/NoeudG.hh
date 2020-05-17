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

class EspaceTravail;
/*!
 * \class NoeudG
 * \brief La classe NoeudG représentant un noeud (equipement) sur l'interface graphique
 * pendant la simulation de protocole TCP/IP.
 */
class NoeudG  :  public QGraphicsPixmapItem
{
private:
    //pour les icons afficher les differents noeuds
    QPixmap *pixmap;
    QGraphicsPixmapItem* item;

    //fenetre en clickant sur l'un des noeuds
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    EspaceTravail *parent;

public:

    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe NoeudG
         *  Initialise un NoeudG par une scene ou le noeudG va t'etre afficher et une icon.
         * \param pixmap : voir #QPixmap
         * \param parent : voir #QGraphicsScene
    */
    NoeudG(EspaceTravail *parent, QPixmap pixmap= QPixmap("../../ressources/hub.png"));


    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe NoeudG
         *  Initialise un NoeudG par une icon.
         * \param pixmap : voir #QPixmap
    */
    NoeudG(QPixmap pixmap);

    /*!
         * \brief Destructeur
         * Destructeur de la classe NoeudG
     */
    ~NoeudG();

    QPixmap *getPixmap() const;
    void setPixmap(QPixmap *value);

    QGraphicsPixmapItem *getItem() const;
    void setItem(QGraphicsPixmapItem *value);

    QTabWidget *getTabWidget() const;
    void setTabWidget(QTabWidget *value);

    QDialogButtonBox *getButtonBox() const;
    void setButtonBox(QDialogButtonBox *value);

protected:
    //void mouseDoubleClickEvent( QMouseEvent * e );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent( QMouseEvent *e );
    //void mouseReleaseEvent( QMouseEvent *e );
};

#endif
