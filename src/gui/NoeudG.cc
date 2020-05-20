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
//    toolTipShow();

    parent=new QTreeWidgetItem(PanneauEvents::getTreeview());
    PanneauEvents::addRoot(parent,"Noeud");
}


NoeudG::~NoeudG()
{
    delete parent;
}

void NoeudG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() <<"mouse pressed NoeudG";
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
            // select interface
            // stock current extremite

            CableG * cg = new CableG();
            addLine(cg, true);
            moveCable(event->scenePos() - boundingRect().center());
            qDebug()<<event->scenePos();
            espaceTravail->currentCable = cg;
            /*showInterfacesMenu();
            if(!espaceTravail->currentExtremite){
                cg = nullptr;
                extremiteG.pop_back();
                espaceTravail->currentCable = nullptr;
                return;
            }*/
            qDebug() << "first click";
            return;
        }else {
            // select interface
            //extremite * ext1 = espaceTravail->currentExtremite;
            //espaceTravail->currentExtremite = nullptr;
            CableG * cg = espaceTravail->currentCable;
            espaceTravail->currentCable = nullptr;
            cg->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            addLine(cg, false);
            qDebug()<<event->scenePos();
            moveCable(event->scenePos() - boundingRect().center());
            /*showInterfacesMenu();
            if(!espaceTravail->currentExtremite){
                extremiteG.pop_back();
                espaceTravail->currentCable = nullptr;
                cg = nullptr;
                return;
            }*/
            cg->setZValue(-1);
            espaceTravail->getScene()->addItem(cg);

            qDebug() << "second click"<< cg->line();
            return;
        }

        break;
    }
    default: return;
    }
}
void NoeudG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
   if(espaceTravail->getMode() == SELECT_MODE)
        configuration->show();

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

void NoeudG::showInterfacesMenu()
{   qDebug()<<"menu open";
    interfacesMenu = new QMenu();

    QObject::connect(interfacesMenu, SIGNAL(triggered(QAction*)), this, SLOT(interfaceAction(QAction*)));
    QObject::connect(interfacesMenu, SIGNAL(aboutToHide()), this, SLOT(onCloseMenu()));

    for(int i = 0; i < child->getInterfaces().size(); i++){
        QAction * ia = interfacesMenu->addAction("Interface");
        ia->setToolTip(QString(i));
    }

    interfacesMenu->popup(QCursor::pos());
    return;

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
        qDebug() <<"MOVE CABLE "<< e.cable->line() <<" "<<child->getIdNoeud();
        if(e.isP1)
            e.cable->setLine(QLineF(newPos+boundingRect().center(), e.cable->line().p2()));
        else
            e.cable->setLine(QLineF(e.cable->line().p1(), newPos+boundingRect().center()));
    }
}

void NoeudG::interfaceAction(QAction* action){
    extremite * ext = new extremite;
    ext->noeud = child;
    ext->interface = action->toolTip().toInt();
    espaceTravail->currentExtremite = ext;
}

void NoeudG::onCloseMenu(){
    qDebug()<<"menu closed";
    interfacesMenu = nullptr;
}




