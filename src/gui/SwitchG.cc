#include <SwitchG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>


SwitchG::SwitchG(QGraphicsScene *parent, QPixmap pixmap ): NoeudG(parent,pixmap){}
SwitchG::SwitchG(QPixmap pixmap): NoeudG(pixmap){}
SwitchG::~SwitchG(){}

void SwitchG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        QMessageBox::information(NULL, "Information!", "I'm a Switcher!");
}

void SwitchG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        this->~SwitchG();
}
