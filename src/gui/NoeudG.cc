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
    //PanneauEvents::addRoot(parent,"Noeud");
    //PanneauEvents::addRoot(parent,QString::fromStdString());

}
void NoeudG::setChild(Noeud * _child){child = _child; configuration=new Dialog (_child);}

NoeudG::~NoeudG()
{

    delete parent;
   // qDebug()<<"My size before destruction"<<extremiteG.size();
    for(cableG_extremite c : extremiteG){
        c.cable->~CableG();
        //delete c.cable;
        //c.cable = 0;
    }
    extremiteG.clear();

   //qDebug()<<"My size after destruction"<< extremiteG.size();

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

        if(ret == QMessageBox::Yes){
            if(child)
                child->~Noeud();
            else
                this->~NoeudG();
        }
        //event->ignore();
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
            espaceTravail->currentCable = cg;
            showInterfacesMenu();
            if(!espaceTravail->currentExtremite){
                delete cg;
                cg = nullptr;
                extremiteG.pop_back();
                espaceTravail->currentCable = nullptr;
                event->ignore();
                break;
            }

            qDebug() << "first click";
            event->ignore();
            break;
        }else {
            // select interface
            extremite * ext1 = espaceTravail->currentExtremite;
            espaceTravail->currentExtremite = nullptr;
            CableG * cg = espaceTravail->currentCable;
            espaceTravail->currentCable = nullptr;
            cg->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            addLine(cg, false);
            //qDebug()<<event->scenePos();
            moveCable(event->scenePos() - boundingRect().center());
            showInterfacesMenu();
            if(!espaceTravail->currentExtremite){
                delete cg;
                cg = nullptr;
                extremiteG.pop_back();
                espaceTravail->currentCable = nullptr;
                event->ignore();
                break;
            }
            cg->setZValue(-1);
            espaceTravail->getScene()->addItem(cg);
            qDebug() << "second click"<< cg->line();
            event->ignore();
            break;
        }

        break;
    }
    default: break;
    }
}
void NoeudG::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(espaceTravail->getMode()==SELECT_MODE){
        configuration->showConfig(child);
        configuration->show();}
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
{
    QMenu interfacesMenu;

    QObject::connect(&interfacesMenu, SIGNAL(triggered(QAction*)), this, SLOT(interfaceAction(QAction*)));

    for(int i = 0; i < child->getInterfaces().size(); i++){
        QAction * ia = interfacesMenu.addAction("Interface "+QString::number(i));
        ia->setToolTip(QString(i));
    }

    interfacesMenu.exec(QCursor::pos());
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
    if(isPoint1)
        e.cable->extG1 = this;
    else
        e.cable->extG2 = this;

    extremiteG.push_back(e);
}

void NoeudG::moveCable(QPointF newPos){

    //qDebug()<< extremiteG.size();

    for(cableG_extremite e : extremiteG){
        if(!e.cable) return;
      //  qDebug() <<"MOVE CABLE "<< e.cable->line() <<" "<<child->getIdNoeud();
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


