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
#include <iostream>

/*!
 * \class EspaceTravail
 * \brief La classe EspaceTravail représentant l'Espace de Travail de l'utilisateur sur le protocole TCP/IP.
 */

class EspaceTravail : public QWidget
{

    Q_OBJECT
private:
    QGraphicsScene* scene;/*!< Scene d'affichage de l'espace de travail*/
    QGraphicsView* vue;/*!< Vue qui va afficher la scene */
    //QVector<Equipement*> Equipement;/*!< Vecteur d'Equipements se trouvant sur l'espace de travail*/

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
    ~EspaceTravail();

    /*!
         * \brief getScene
         * getter qui recupere la Scene.
         * \return voir #scene
    */
    QGraphicsScene *getScene() const {return scene;}

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
    QGraphicsView *getVue() const {return vue;}

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
    QPoint offset;

protected:
    void mouseDoubleClickEvent( QMouseEvent * e );
    void mousePressEvent(QMouseEvent  *event);
    void mouseMoveEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );
};

#endif
