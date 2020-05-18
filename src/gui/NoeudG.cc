#include <NoeudG.hh>
#include <QMessageBox>

NoeudG::NoeudG(EspaceTravail * _espaceTravail, QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    espaceTravail = _espaceTravail;
    child = nullptr;
    this->setFlag(QGraphicsItem::ItemIsMovable);
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
    case CABLE_MODE:   { break;}
    default: return;
    }
}


