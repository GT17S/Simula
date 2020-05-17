#ifndef __H_ESPACETRAVAIL__
#define __H_ESPACETRAVAIL__


/*!
 * \file EspaceTravail.h
 * \brief EspaceTravail
 * \author GT17S & Medish
 * \version 0.1
 */

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QtWidgets>
#include <QPoint>
#include <QMainWindow>
#include <iostream>

#include "NoeudG.hh"

/*!
 * \class EspaceTravail
 * \brief La classe EspaceTravail représentant l'Espace de Travail de l'utilisateur sur le protocole TCP/IP.
 */

class EspaceTravail : public QMainWindow
{

    Q_OBJECT
private:
    QGraphicsScene* scene;/*!< Scene d'affichage de l'espace de travail*/
    QGraphicsView* vue;/*!< Vue qui va afficher la scene */
    //QVector<Equipement*> Equipement;/*!< Vecteur d'Equipements se trouvant sur l'espace de travail*/

    /*!< Booléen qui vérifie si deux clics on été faits */
    QPoint p1,p2;
    QPushButton *pb;
    QLabel *o;

public:

    /*!
         * \brief Constructeur par défaut
         * Constructeur par défaut de la classe EspaceTravail.
    */
    EspaceTravail();

    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe EspaceTravail
         *  Initialise un EspaceTravail par un vecteur d'Equipements.
         * \param Equipement : voir #EspaceTravail
    */
    // EspaceTravail(QVector<Equipement*> Equipement);

    /*!
         * \brief Destructeur
         * Destructeur de la classe EspaceTravail
     */
    virtual ~EspaceTravail();

    /*!
         * \brief getScene
         * getter qui recupere la Scene.
         * \return voir #scene
    */
    QGraphicsScene *getScene()  {return scene;}

    /*!
         * \brief setScene
         * setter qui insere une _scene à la scene de l'EspaceTravail.
         * \param  _scene : voir #scene
    */
    void setScene(QGraphicsScene *_scene){scene=_scene;}

    /*!
         * \brief getVue
         * getter qui recupere la Vue.
         * \return voir #vue
    */
    QGraphicsView *getVue()  {return vue;}

    /*!
         * \brief setVue
         * setter qui insere une _vue à la vue de l'EspaceTravail.
         * \param  _vue : voir #vue
    */
    void setVue(QGraphicsView *_vue){vue=_vue;}

    void deleteScene();
    void deleteButton(){
        if(pb->isActiveWindow()){ qDebug()<<"endless speech";pb->~QPushButton();}}
    bool mousePressed = false;
    
    QPoint offset; /*!< Coordonnées du premier point*/
    QPoint offset2; /*!< Coordonnées du deuxieme point*/
    /*!
         * \brief AddCatPos
         * Dessine une cable entre deux points entrés par l'utilisateur
         * \param  _vue : voir #vue
    */
    void addCatPos();
    void addNoeud(NoeudG* noeud);


protected:
    void mouseDoubleClickEvent( QMouseEvent * e );
    void mousePressEvent(QMouseEvent  *event);
    void mouseMoveEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );


};

#endif
