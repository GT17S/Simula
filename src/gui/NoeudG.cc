#include <NoeudG.hh>
#include <QMessageBox>
#include "PanneauEvents.hh"

NoeudG::NoeudG(EspaceTravail * _espaceTravail) : QGraphicsPixmapItem()
{
    espaceTravail = _espaceTravail;
    child = nullptr;
    configuration = new Dialog(child);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    toolTipShow();
    parent=new QTreeWidgetItem(PanneauEvents::getTreeview());
    PanneauEvents::addRoot(parent,"Noeud");
}


NoeudG::~NoeudG()
{

    //delete tabWidget;
    //delete buttonBox;
    //delete item;
    //delete pixmap; Sert à rien de delete c'est passé statiquement au super constructeur

    delete parent;
}

void NoeudG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() <<"mouse pressed NoeudG";
    PanneauEvents::addCh(parent,"Clic ok");
    switch(espaceTravail->getMode()){
    case SELECT_MODE:  { break;}
    case DELETE_MODE:  {

        const QMessageBox::StandardButton ret
                = QMessageBox::question(espaceTravail, "Supprimer equipement",
                                        "Voulez-vous vraiment supprimer l'éuipement ?",
                                        QMessageBox::Yes | QMessageBox::No);

        if(ret == QMessageBox::Yes){
            if(child)
                child->~Noeud();
            else
                this->~NoeudG();
        }
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
void NoeudG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    configuration->show();



}

void NoeudG::toolTipShow(){
    setToolTip(
                "<h2><b><font color='red'>MyList</font></b></h2>"
                "<ol>"
                "<li>First</li>"
                "<li>Second</li>"
                "<li>Third</li>"
                "</ol>"
                );
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

