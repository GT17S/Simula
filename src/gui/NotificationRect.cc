#include "NotificationRect.hh"
#include <QDebug>


NotificationRect::NotificationRect(QGraphicsItem *_parent):
    QGraphicsRectItem(_parent)

{
    text = new QGraphicsTextItem(this);

}
NotificationRect::NotificationRect(const QString _notification,QColor _color, QGraphicsItem *_parent) :
    QGraphicsRectItem(_parent)
{
    initNotification(_notification, _color);

}

NotificationRect::~NotificationRect(){

}


void NotificationRect::clearNotification(){
    color = QColor();
    text->setPlainText("");
    setRect(QRect());
    setBrush(color);

}

void NotificationRect::initNotification(const QString _notification, QColor _color){

    color = _color;
    text->setPlainText(_notification);
    setRect(text->boundingRect());
    setBrush(_color);
}

void NotificationRect::mousePressEvent(QGraphicsSceneMouseEvent *event){
    clearNotification();
}
/*
void NotificationRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    qDebug()<<"Hello";
  painter->setBrush(color);
  painter->drawRoundedRect(this->rect(),10,10);
}*/
