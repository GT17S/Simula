#include <RouteurG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

RouteurG::RouteurG(){}
RouteurG::RouteurG(QGraphicsScene *parent, QPixmap pixmap ): NoeudG(parent,pixmap){}
RouteurG::RouteurG(QPixmap pixmap): NoeudG(pixmap){}
RouteurG::~RouteurG(){}

void RouteurG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        QMessageBox::information(NULL, "Information!", "Mouse right Detected!");

}

void RouteurG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        this->~RouteurG();
}
