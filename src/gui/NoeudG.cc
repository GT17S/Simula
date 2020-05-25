#include <NoeudG.hh>
#include <QMessageBox>
#include "PanneauEvents.hh"
#include "DialogEnvoi.hh"


NoeudG::NoeudG(EspaceTravail * _espaceTravail) : QGraphicsPixmapItem()
{
    espaceTravail = _espaceTravail;
    child = nullptr;
    configuration = new Dialog(child);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    parent=new QTreeWidgetItem(PanneauEvents::getTreeview());


}
    void NoeudG::setChild(Noeud * _child){
      child = _child;
      configuration=new Dialog (_child);
      toolTipShow();
      }


NoeudG::~NoeudG()
{

    delete parent;

    extremiteG.clear();


}

void NoeudG::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() <<"mouse pressed NoeudG";
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
        emit espaceTravail->removeStation(this);
        break;
    }
    case ROUTEUR_MODE: { break;}
    case STATION_MODE: { break;}
    case SWITCH_MODE : { break;}
    case HUB_MODE    : { break;}
    case CABLE_MODE  : {
        if(!espaceTravail->currentCable){
            // select interface
            showInterfacesMenu();
            if(!espaceTravail->currentExtremite){
                // aucune interface n'est choisie

                event->ignore(); // ignorer l'event
                break;
            }

            CableG * cg = new CableG(espaceTravail);
            addLine(cg, true);
            moveCable(event->scenePos() - boundingRect().center());
            espaceTravail->currentCable = cg;
            //qDebug() << "first click";
            event->ignore();
            break;
        }else {
            //qDebug() << "second click 0";
            // select interface
            extremite * ext1 = espaceTravail->currentExtremite;
            if(ext1->noeud == child) break;
            espaceTravail->currentExtremite = nullptr;
            showInterfacesMenu();
            if(!espaceTravail->currentExtremite){
                //delete cg;
                //cg = nullptr;
                //extremiteG.pop_back();
                espaceTravail->currentCable = nullptr;
                event->ignore();
                break;
            }
            CableG * cg = espaceTravail->currentCable;
            espaceTravail->currentCable = nullptr;
            addLine(cg, false);
            moveCable(event->scenePos() - boundingRect().center());
            // Creation du cable logique!
            Cable * cable = new Cable(cg);
            extremite * ext2 = espaceTravail->currentExtremite;
            espaceTravail->currentExtremite = nullptr;
            if(!cable->connexionNoeuds(ext1->noeud, ext1->interface, ext2->noeud, ext2->interface)){
                //qDebug() << "second click 1";
                event->ignore();
                break;
            }
            cg->setZValue(-1);
            espaceTravail->getScene()->addItem(cg);
            //qDebug() << "second click 2";
            espaceTravail->setMode(SELECT_MODE);
            event->ignore();
            break;
        }

        break;
    }
    case MESSAGE_MODE  : {
        if(child->getTypeNoeud() != STATION) break;
        if(!espaceTravail->currentExtremite){
            //qDebug() << "first click message";
            extremite * x = new extremite;
            x->noeud = child;
            espaceTravail->currentExtremite = x;
            event->ignore();
            break;
        }else {
            extremite *x = espaceTravail->currentExtremite;
            // meme cable!
            if(x->noeud == child) break;
            //qDebug() << "second click message";
            extremite *x2 = new extremite;
            x2->noeud = child;
            espaceTravail->currentExtremite= nullptr;
            DialogEnvoi * dEnvoi= new DialogEnvoi(x->noeud, x2->noeud, this); // Modifié par Massi
            dEnvoi->show();
            espaceTravail->setMode(SELECT_MODE);
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


    for(int i = 0; i < child->getInterfaces().size(); i++){
        QAction * ia = interfacesMenu.addAction("Interface "+QString::number(i), [this, i](bool) {this->interfaceAction(i);});
        if(child->getInterface(i)->getCable())
            ia->setEnabled(false);
        ia->setToolTip(QString(i));
    }
   // QObject::connect(&interfacesMenu, SIGNAL(triggered(QAction*)), this, SLOT(interfaceAction(QAction*)));

    interfacesMenu.exec(QCursor::pos());
    return;

}
void NoeudG::toolTipShow(){
  QString s,equipementName;
  QTextStream stream(&s);

  stream << "<html><head><style> td{border: 1px solid #ffffff; padding: 0.1em 0.1em;}</style></head><body><h6> <b> <font color='red'>" << "Nom equipement: " <<QString::fromStdString(this->getChild()->getNom())<<" </font></b></h6>";

  switch(child->getTypeNoeud()){
  case SWITCH: {
       equipementName="Switch";
       stream<<"<b>Interfaces voisines connectes: </b>";

       if(!child->getInterface(0)->getCable())
           stream<<"<br>Pas d'interfaces voisines encore";
       else
       {
           stream<<"<table>";

       for(int i=0;i<child->getInterfaces().size();i++)
       {
           Cable *c=child->getInterface(i)->getCable();
           if(c)
           {
               extremite *x=c->getInverseExt(child);
               if(x)
               {   InterfaceFE *f;
                   f = x->noeud->getInterface(x->interface);
                           stream<<
                                   //"<tr><td> "<<QString::fromStdString(f->getNomInterface())<<
                                   "<tr><td> "<<QString::fromStdString(f->getAdresseIP())<<"</td>"<<
                                   //"<td> "<<QString::fromStdString(f->getAdresseMac())<<"</td>"<<
                                   "<td> "<<QString::fromStdString(f->getAdresseRes())<<"</td>"<<
                                   "<td> "<<QString::fromStdString(f->getMasque())<<"</td></tr>";

               }

           }
       }
        stream<<"</table>";
       }
       stream<<"</body></html>";
      break;
  }
  case STATION: {
      equipementName="Station";

      stream<<"<b>Interfaces:</b><table>";
      for (int i=0;i<child->getInterfaces().size();i++ ) {
              stream<<
                      //"<tr><td> "<<QString::fromStdString(child->getInterfaces().at(i)->getNomInterface())<<"</td>"<<" "<<
                      "<tr><td> "<<QString::fromStdString(child->getInterfaces().at(i)->getAdresseIP())<<"</td>"<<" "<<
                      //"<td> "<<QString::fromStdString(child->getInterfaces().at(i)->getAdresseMac())<<"</td>"<<" "<<
                      "<td> "<<QString::fromStdString(child->getInterfaces().at(i)->getAdresseRes())<<"</td>"<<" "<<
                      "<td> "<<QString::fromStdString(child->getInterfaces().at(i)->getMasque())<<"</td>"<<"</tr>";
      }
      stream<<"</table><br><b>Routes: </b>";
      if(child->getTableRoutage().empty())
          stream<<"<br>Pas de routes encore";
      else
      {
          stream<<"<table>";
      for (int i=0;i<child->getTableRoutage().size();i++ ) {
              stream<<
                      "<tr><td> "<<QString::fromStdString(child->getTableRoutage().at(i)->adresseReseau)<<"</td>"<<" "<<
                      "<td> "<<QString::fromStdString(child->getTableRoutage().at(i)->masque)<<"</td>"<< " "<<
                      "<td> "<<QString::fromStdString(child->getTableRoutage().at(i)->passerelle)<<"</td>"<< "</tr>";
      }
           stream<<"</table>";
      }

      Station *st=dynamic_cast<Station *>(child);
      if(st)
      {
          int cwnd=st->getControleur()->getCwnd();
          stream<<"<br><br> Taille de la fenetre de congestion = "<<cwnd;
      }

      stream<<"</body></html>";
      break;
  }
  case HUB:  {
      equipementName="Hub";

      stream<<"<b>Interfaces voisines connectes: </b>";

      if(!child->getInterface(0)->getCable())
          stream<<"<br>Pas d'interfaces voisines encore";
      else
      {
          stream<<"<table>";

      for(int i=0;i<child->getInterfaces().size();i++)
      {
          Cable *c=child->getInterface(i)->getCable();
          if(c)
          {
              extremite *x=c->getInverseExt(child);
              if(x)
              {   InterfaceFE *f;
                  f = x->noeud->getInterface(x->interface);
                          stream<<
                                  //"<tr><td> "<<QString::fromStdString(f->getNomInterface())<<
                                  "<tr><td> "<<QString::fromStdString(f->getAdresseIP())<<"</td>"<<
                                  //"<td> "<<QString::fromStdString(f->getAdresseMac())<<"</td>"<<
                                  "<td> "<<QString::fromStdString(f->getAdresseRes())<<"</td>"<<
                                  "<td> "<<QString::fromStdString(f->getMasque())<<"</td></tr>";

              }

          }
      }
       stream<<"</table>";
      }
      stream<<"</body></html>";
      break;
  }
  case ROUTEUR: {
      equipementName="Routeur";
      stream<<"<b>Interfaces:</b><table>";
      for (int i=0;i<child->getInterfaces().size();i++ ) {
              stream<<
                      //"<tr><td> "<<QString::fromStdString(child->getInterfaces().at(i)->getNomInterface())<<"</td>"<<" "<<
                      "<tr><td> "<<QString::fromStdString(child->getInterfaces().at(i)->getAdresseIP())<<"</td>"<<" "<<
                      //"<td> "<<QString::fromStdString(child->getInterfaces().at(i)->getAdresseMac())<<"</td>"<<" "<<
                      "<td> "<<QString::fromStdString(child->getInterfaces().at(i)->getAdresseRes())<<"</td>"<<" "<<
                      "<td> "<<QString::fromStdString(child->getInterfaces().at(i)->getMasque())<<"</td>"<<"</tr>";
      }
      stream<<"</table><br><b>Routes: </b>";
      if(child->getTableRoutage().empty())
          stream<<"<br>Pas de routes encore";
      else
      {
          stream<<"<table>";
      for (int i=0;i<child->getTableRoutage().size();i++ ) {
              stream<<
                      "<tr><td> "<<QString::fromStdString(child->getTableRoutage().at(i)->adresseReseau)<<"</td>"<<" "<<
                      "<td> "<<QString::fromStdString(child->getTableRoutage().at(i)->masque)<<"</td>"<< " "<<
                      "<td> "<<QString::fromStdString(child->getTableRoutage().at(i)->passerelle)<<"</td>"<< "</tr>";
      }
           stream<<"</table>";
      }
      stream<<"</body></html>";
      break;
  }
  default: return;
  }

          setToolTip(s);

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

void NoeudG::interfaceAction(int i){
    extremite * ext = new extremite;
    ext->noeud = child;
    ext->interface = i;
    //qDebug() << " Interface "<<ext->interface;
    espaceTravail->currentExtremite = ext;
}
