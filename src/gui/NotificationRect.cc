#include "NotificationRect.hh"
#include <QDebug>
#include <QTextDocument>

QColor NotificationRect::RED_NOTIFICATION_COLOR = QColor(Qt::red),
       NotificationRect::GREEN_NOTIFICATION_COLOR = QColor(Qt::green);

NotificationRect::NotificationRect(QGraphicsItem *_parent):
    QGraphicsTextItem(_parent)
{
    document()->setTextWidth(60);
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
    setHtml("");
    //setBrush(color);

}

void NotificationRect::initNotification(QString _notification, QColor _color){

    color = _color;
    notificationToHtml(_notification, _color);
    setHtml(_notification);
    //setRect(text->boundingRect());
    //setBrush(_color);
}

void NotificationRect::notificationToHtml(QString &message, QColor _color){
    QString html;
    QTextStream stream(&html);
    stream<<"<html>"
            "<head></head><body>"
            "<div style = 'padding: 40px;background-color:"+_color.name()+";color: white;border-radius: 10px;'>"
              "<strong>"+message+"aaaaaaaaaaaaaaaaaaaaaaaaaaa</strong></div>"
            "</body></html>";
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
