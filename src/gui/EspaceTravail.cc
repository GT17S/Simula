#include <QGraphicsWidget>
#include <iostream>
#include <qdebug.h>

#include "EspaceTravail.hh"
#include "RouteurG.hh"
#include "StationG.hh"
#include "HubG.hh"
#include "SwitchG.hh"
#include "CableG.hh"

QCursor EspaceTravail::SELECT_CURSOR,
EspaceTravail::DELETE_CURSOR,
EspaceTravail::ROUTEUR_CURSOR,
EspaceTravail::STATION_CURSOR,
EspaceTravail::SWITCH_CURSOR,
EspaceTravail::HUB_CURSOR,
EspaceTravail::CABLE_CURSOR;

EspaceTravail::EspaceTravail(){

    this->setMinimumSize(450,430);
    createCursors();
    scene = new QGraphicsScene(this);

    vue= new QGraphicsView(scene,this);
    vue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    vue->setRenderHints( QPainter::SmoothPixmapTransform );
    vue->setStyleSheet("background-color:white;");
    vue->setAcceptDrops(true);
    scene->setSceneRect(0, 0, 2000, 1000);
    setCentralWidget(vue);
    vue->show();
    //scene->update();
}
EspaceTravail::~EspaceTravail()
{
    delete scene;
    delete vue;
}
void EspaceTravail::setMode(cursor_mode _mode){
    mode = _mode;

    switch(_mode){
    case SELECT_MODE:  {
        setCursor(SELECT_CURSOR);
        vue->setDragMode(QGraphicsView::RubberBandDrag);

        return;
    }
    case DELETE_MODE:  {setCursor(DELETE_CURSOR); break;}
    case ROUTEUR_MODE: {setCursor(ROUTEUR_CURSOR); break;}
    case STATION_MODE: {setCursor(STATION_CURSOR); break;}
    case SWITCH_MODE:  {setCursor(SWITCH_CURSOR); break;}
    case HUB_MODE:     {setCursor(HUB_CURSOR); break;}
    case CABLE_MODE:   {setCursor(CABLE_CURSOR); break;}
    }
    vue->setDragMode(QGraphicsView::NoDrag);
}

void EspaceTravail::createCursors(){
    SELECT_CURSOR  = QCursor(Qt::ArrowCursor);
    DELETE_CURSOR  = QCursor(QPixmap(":/ressources/cursors/deleteCursor.png")),
    ROUTEUR_CURSOR = QCursor(QPixmap(":/ressources/cursors/routeurCursor.png")),
    STATION_CURSOR = QCursor(QPixmap(":/ressources/cursors/stationCursor.png")),
    SWITCH_CURSOR  = QCursor(QPixmap(":/ressources/cursors/switchCursor.png")),
    HUB_CURSOR     = QCursor(QPixmap(":/ressources/cursors/hubCursor.png")),
    CABLE_CURSOR   = QCursor(QPixmap(":/ressources/cursors/cableCursor.png"));
}

void EspaceTravail::deleteScene()
{
    this->scene->~QGraphicsScene();
}


void EspaceTravail::mouseDoubleClickEvent(QMouseEvent *event)
{
    
}

void EspaceTravail::mousePressEvent(QMouseEvent *event)
{   qDebug() <<"mouse pressed";
    QPoint origin = vue->mapFromGlobal(QCursor::pos());
    QPointF p = vue->mapToScene(origin);
    switch(mode){
    case SELECT_MODE:  { break;}
    case DELETE_MODE:  { break;}
    case ROUTEUR_MODE: {
        RouteurG * r = new RouteurG(this);
        addNoeud(r, p);
        break;
    }
    case STATION_MODE: {
        StationG * r = new StationG(this);
        addNoeud(r, p);
        break;
    }
    case SWITCH_MODE:  {
        SwitchG * r = new SwitchG(this);
        addNoeud(r, p);
        break;
    }
    case HUB_MODE:     {
        HubG * r = new HubG(this);
        addNoeud(r, p);
        break;
    }
    case CABLE_MODE:   {
        break;
    }
    default: return;
    }

}

void EspaceTravail::mouseMoveEvent(QMouseEvent *event)
{

}

void EspaceTravail::mouseReleaseEvent(QMouseEvent *event)
{

}

void EspaceTravail::addNoeud(NoeudG* noeud, QPointF p){
    assert(noeud && "Pointeur null");
    noeud->setPos(p);
    scene->addItem(noeud);
}

