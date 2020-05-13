#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QRadialGradient>
#include <QPropertyAnimation>
#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QStyle>
#include <iostream>
#include <qdebug.h>


#include "EspaceTravail.hh"
#include "NoeudG.hh"
#include "CableG.hh"

EspaceTravail::EspaceTravail(){
    clickedonce = false;
    scene = new QGraphicsScene();
    vue = new QGraphicsView(scene,this);
    vue->setStyleSheet("background-color:#f2f0f0");
    vue->setGeometry(0,0,900,520);
    vue->setMinimumSize(450,430);

    vue->setAcceptDrops(true);
   
    setMouseTracking(true);
    auto test = new CableG(10,10,80,90);
    
    scene->addItem(test);
    vue->show();
    scene->update();
}

EspaceTravail::~EspaceTravail()
{
    delete scene;
    delete vue;
}

void EspaceTravail::deleteScene()
{
    this->scene->~QGraphicsScene();
}


void EspaceTravail::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        emit deleteButton();
    }
}

void EspaceTravail::mousePressEvent(QMouseEvent *event)
{
    nbclic++;

   
   

    if(event->button()==Qt::LeftButton)
    {
        offset.rx()=event->pos().rx();
        offset.ry()=event->pos().ry();
        std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<std::endl;
        qDebug()<<"position X= "<<offset.rx();
        qDebug()<<"position Y= "<<offset.ry();
        mousePressed=true;
       // qDebug()<<mousePressed;
        if(nbclic % 2 == 0){ //dans le cas de deux clics successifs
            offset2 = offset;
            std::cout << "double clic" << std::endl;
            addCatPos();
        }
    }



}

void EspaceTravail::mouseMoveEvent(QMouseEvent *e)
{

    if ((e->buttons() & Qt::LeftButton) && mousePressed)
    {
        qDebug()<<"debut de move event";

    }


    /*QPoint pnt;
            pnt.rx()=e->pos().rx();
            pnt.ry()=e->pos().ry();

            pnt.setX(e->pos().rx());
            pnt.setX(e->pos().ry());

            qDebug()<<"pos X= "<<pnt.x();
            qDebug()<<"pos Y= "<<pnt.y();
            o->setGeometry( pnt.x(),pnt.y(), 100,50  );

            pb->setGeometry( pnt.x(),pnt.y(), 100,50  );
    update();*/
}

void EspaceTravail::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"release mouse event";
    if ( e->button() == Qt::LeftButton && mousePressed)
    {      mousePressed = false;
        update();
    }
    qDebug()<<mousePressed;

}

/*
    void mouseMoveEvent(QMouseEvent *event)
    {
        qDebug()<<"-_-Je suis dans la deuxieme-_-";


        if (event->buttons() & Qt::LeftButton)
        {

            QPoint newpos_min = mapToParent(event->pos()- offset);
            QPoint newpos_max = QPoint(newpos_min.x() + this->width(), newpos_min.y() + this->height());

            if(newpos_min.x() > 0 &&
               newpos_min.y() > 0 &&
               newpos_max.x() < this->parentWidget()->width() &&
               newpos_max.y() < this->parentWidget()->height()){

               move(mapToParent(event->pos() - offset));
            }
        }
           update();
    }*/

//EspaceTravail::EspaceTravail(QVector<Equipement *> Equipement){}

void EspaceTravail::addCatPos(){
    if(!offset.isNull()){
        if(!offset2.isNull())
        scene->addItem(new CableG(offset2.rx(),offset2.ry(), offset.rx(), offset.ry()));
    }
}