#include <NoeudG.hh>
#include <QMessageBox>

NoeudG::NoeudG(EspaceTravail * _espaceTravail, QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    espaceTravail = _espaceTravail;
    child = nullptr;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);


}
NoeudG::~NoeudG()
{
    //delete tabWidget;
    //delete buttonBox;
    //delete item;
    //delete pixmap; Sert à rien de delete c'est passé statiquement au super constructeur
}

QGraphicsPixmapItem *NoeudG::getItem() const
{
    return item;
}

void NoeudG::setItem(QGraphicsPixmapItem *value)
{
    item = value;
}

QPixmap *NoeudG::getPixmap() const
{
    return pixmap;
}

void NoeudG::setPixmap(QPixmap *value)
{
    pixmap = value;
}

void NoeudG::setChild(Noeud * _child){
    child = _child;
}


void NoeudG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() <<"mouse pressed NoeudG";
    switch(espaceTravail->getMode()){
    case SELECT_MODE:  { break;}
    case DELETE_MODE:  {

        const QMessageBox::StandardButton ret
                = QMessageBox::question(espaceTravail, "Supprimer equipement",
                                        "Voulez-vous vraiment supprimer l'éuipement ?",
                                        QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes)
            this->~NoeudG();
        break;
    }
    case ROUTEUR_MODE: { break;}
    case STATION_MODE: { break;}
    case SWITCH_MODE:  { break;}
    case HUB_MODE:     { break;}
    case CABLE_MODE:   {
        if(!espaceTravail->currentCable){
            CableG * i = new CableG();
            addLine(i, true);
            moveCable(event->scenePos() - boundingRect().center());
            espaceTravail->currentCable = i;
            qDebug() << "first click";
        }else{
            CableG * i = espaceTravail->currentCable;
           // *i = * (espaceTravail->currentCable);
            qDebug() << "second click";
            //i->setLine(QLineF(espaceTravail->origPoint, event->scenePos()-boundingRect().center()));
            i->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            addLine(i, false);
            moveCable(event->scenePos() - boundingRect().center());
            i->setZValue(-1);
            espaceTravail->getScene()->addItem(i);

            espaceTravail->currentCable = nullptr;
        }

        break;
    }
    default: return;
    }
}

void NoeudG::addLine(CableG * _cable, bool isPoint1) {
    cableG_extremite e;
    e.cable = _cable;
    e.isP1 = isPoint1;

    extremiteG.push_back(e);
}

void NoeudG::moveCable(QPointF newPos){
    for(cableG_extremite e : extremiteG){
    if(e.isP1)
        e.cable->setLine(QLineF(newPos+boundingRect().center(), e.cable->line().p2()));
    else
        e.cable->setLine(QLineF(e.cable->line().p1(), newPos+boundingRect().center()));
    }
}

QVariant NoeudG::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        moveCable(newPos);
    }
    return QGraphicsItem::itemChange(change, value);
}


