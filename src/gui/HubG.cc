#include <HubG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

HubG::HubG(){}
HubG::HubG(QGraphicsScene *parent, QPixmap pixmap ): NoeudG(parent,pixmap){}
HubG::HubG(QPixmap pixmap): NoeudG(pixmap){}
HubG::~HubG(){}

void HubG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        QMessageBox::information(NULL, "Information!", "I'm a Hub!");

}

void HubG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        this->~HubG();
}
