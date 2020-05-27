#ifndef NOTIFICATION_RECT_H
#define NOTIFICATION_RECT_H

#include <QGraphicsItem>
#include <QPainter>


class NotificationRect : public QGraphicsTextItem{
    friend class NoeudG;
private :
    QColor color;
public:
    NotificationRect(QGraphicsItem * parent);
    NotificationRect(QString notification, QColor color, QGraphicsItem * parent = nullptr);
    ~NotificationRect();

    void clearNotification();
    void initNotification(QString _notification, QColor _color);
    void notificationToHtml(QString &message, QColor _color);

    static QColor RED_NOTIFICATION_COLOR,
                  GREEN_NOTIFICATION_COLOR,
                  BLUE_NOTIFICATION_COLOR;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};


#endif
