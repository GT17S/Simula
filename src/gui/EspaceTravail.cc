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
    p1.setX(0);
    p1.setY(0);
    p2.setX(0);
    p2.setY(0);
    scene = new QGraphicsScene();

    vue= new QGraphicsView(scene,this);
    vue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //scroll avec  souris (HandDrag)
    vue->setDragMode(QGraphicsView::ScrollHandDrag);

    vue->setRenderHints( QPainter::SmoothPixmapTransform );
    vue->setStyleSheet("background-color:#f2f0f0");
    //this->setGeometry(0,0,900,520);
    this->setMinimumSize(450,430);
    vue->setAcceptDrops(true);
    scene->setSceneRect(0,0,1600,1000);

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
    
}

void EspaceTravail::mousePressEvent(QMouseEvent *event)
{   
    if(event->button()==Qt::LeftButton){
        if (p1.x() == 0 && p1.y() == 0) {
            p1 = event->pos();
            return;
        }else {
            p2 = event->pos();
            std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<std::endl;
            qDebug()<<"position X1= "<<p1.rx();
            qDebug()<<"position Y1= "<<p1.ry();
            std::cout<<"________________________________________________"<<std::endl;
            qDebug()<<"position X2= "<<p2.rx();
            qDebug()<<"position Y2= "<<p2.ry();
            std::cout<<"-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<std::endl;
            //afficher
            p1.setX(0);
            p1.setY(0); 
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
    if(!p1.isNull()){
        if(!p2.isNull())
        std::cout << "Je suis là" << std::endl;
        scene->addItem(new CableG(p1.rx(),p1.ry(), p2.rx(), p2.ry()));
    }
}

void EspaceTravail::addNoeud(NoeudG* noeud){
    assert(noeud && "Pointeur null");
    scene->addItem(noeud);
}
