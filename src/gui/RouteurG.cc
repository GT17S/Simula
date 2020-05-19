#include <RouteurG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

RouteurG::RouteurG(EspaceTravail *parent, QPixmap pixmap ): NoeudG(parent,pixmap){}
RouteurG::~RouteurG(){
}
/*
void RouteurG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        QMessageBox::information(NULL, "Information!", "Mouse right Detected!");

}*/
