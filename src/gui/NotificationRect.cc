#include "NotificationRect.hh"
#include <QDebug>
#include <QTextDocument>

QColor NotificationRect::RED_NOTIFICATION_COLOR = QColor(Qt::red),
       NotificationRect::GREEN_NOTIFICATION_COLOR = QColor(Qt::green);

NotificationRect::NotificationRect(QGraphicsItem *_parent):
    QGraphicsTextItem(_parent)
{
    //document()->setTextWidth(60);
    //document()->setDefaultStyleSheet("body {color: white;}");
}
NotificationRect::NotificationRect(QString _notification,QColor _color, QGraphicsItem *_parent) :
    QGraphicsTextItem(_parent)
{
    initNotification(_notification, _color);

}

NotificationRect::~NotificationRect(){

}


void NotificationRect::clearNotification(){
    color = QColor();
    this->setHtml("");
    //setBrush(color);

}

void NotificationRect::initNotification(QString _notification, QColor _color){

    color = _color;
    notificationToHtml(_notification, _color);
    this->setHtml(_notification);
    //setRect(text->boundingRect());
    //setBrush(_color);
}

void NotificationRect::notificationToHtml(QString &message, QColor _color){
    QString html;
    QTextStream stream(&html);
    stream<<"<body style='background-color:"+_color.name()+";'>"
            "<strong>"+message+"</strong>"
            "</body>";
    message = html;
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
