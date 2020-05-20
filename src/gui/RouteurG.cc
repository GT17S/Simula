#include <RouteurG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

RouteurG::RouteurG(EspaceTravail *parent): NoeudG(parent){
    setPixmap(QPixmap(":/ressources/equipements/routeur.png"));

}
RouteurG::~RouteurG(){
}
/*
void RouteurG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        QMessageBox::information(NULL, "Information!", "Mouse right Detected!");

}*/
