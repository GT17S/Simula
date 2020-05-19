#include <NoeudG.hh>
#include <QMessageBox>
#include "PanneauEvents.hh"


NoeudG::NoeudG(EspaceTravail * _espaceTravail, QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    espaceTravail = _espaceTravail;
    this->setFlag(QGraphicsItem::ItemIsMovable);
    //espaceTravail->addItem(this);

    this->setTabWidget(new QTabWidget);
    //tabWidget->addTab("GENERAL");
    parent=new QTreeWidgetItem(PanneauEvents::getTreeview());
    PanneauEvents::addRoot(parent,"Noeud");
}
void NoeudG::setparent(QTreeWidgetItem *value)
{
    parent = value;
}

/*
NoeudG::NoeudG(QGraphicsScene *espaceTravail, QPixmap pixmap): QGraphicsPixmapItem(pixmap)
{

    //this = espaceTravail->addPixmap(new QPixmap("../../ressources/station.png"));

    QPixmap *pix=new QPixmap("../../ressources/routeur.png");
    setPixmap(pix);
    //QGraphicsPixmapItem* item3 = espaceTravail->addPixmap(pixmap3);
    //this =espaceTravail->addPixmap(pix);


    this->moveBy(qrand()%200-100, qrand()%200-100);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    //espaceTravail->addItem(this);


    this->setTabWidget(new QTabWidget) ;
    //this->getTabWidget()->addTab(this,"GENERAL");
}
*/
NoeudG::~NoeudG()
{
    //delete tabWidget;
    //delete buttonBox;
    //delete item;
    //delete pixmap; Sert à rien de delete c'est passé statiquement au super constructeur
    delete parent;
}

QGraphicsPixmapItem *NoeudG::getItem() const
{
    return item;
}

void NoeudG::setItem(QGraphicsPixmapItem *value)
{
    item = value;
}

QTabWidget *NoeudG::getTabWidget() const
{
    return tabWidget;
}

void NoeudG::setTabWidget(QTabWidget *value)
{
    tabWidget = value;
}

QDialogButtonBox *NoeudG::getButtonBox() const
{
    return buttonBox;
}

void NoeudG::setButtonBox(QDialogButtonBox *value)
{
    buttonBox = value;
}

QPixmap *NoeudG::getPixmap() const
{
    return pixmap;
}

void NoeudG::setPixmap(QPixmap *value)
{
    pixmap = value;
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
        if(ret == QMessageBox::Yes)
            this->~NoeudG();
        break;
    }
    case ROUTEUR_MODE: { break;}
    case STATION_MODE: { break;}
    case SWITCH_MODE:  {break;}
    case HUB_MODE:     {break;}
    case CABLE_MODE:   { break;}
    default: return;
    }
}


