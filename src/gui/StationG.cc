#include <StationG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

StationG::StationG(){}
StationG::StationG(QGraphicsScene *parent, QPixmap pixmap ): NoeudG(parent,pixmap){}
StationG::StationG(QPixmap pixmap): NoeudG(pixmap){}

StationG::~StationG(){}

void StationG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        QMessageBox::information(NULL, "Information!", "Mouse right Detected!");

}

void StationG::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"afffa";
    if(event->button()== Qt::RightButton)
        getTabWidget()->show();
}
