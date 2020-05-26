#ifndef NOTIFICATION_RECT_H
#define NOTIFICATION_RECT_H

#include <QGraphicsItem>
#include <QPainter>

class NotificationRect : public QGraphicsRectItem{
    friend class NoeudG;
private :
    QGraphicsTextItem * text;
    QColor color;
public:
    NotificationRect(QGraphicsItem * parent);
    NotificationRect(const QString notification, QColor color, QGraphicsItem * parent = nullptr);
    ~NotificationRect();

    void clearNotification();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};


#endif
