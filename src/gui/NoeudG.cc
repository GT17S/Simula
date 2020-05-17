#include <NoeudG.hh>

NoeudG::NoeudG(EspaceTravail *_parent, QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    parent = _parent;
    this->setFlag(QGraphicsItem::ItemIsMovable);
    //parent->addItem(this);

    this->setTabWidget(new QTabWidget);
    //tabWidget->addTab("GENERAL");
}

/*
NoeudG::NoeudG(QGraphicsScene *parent, QPixmap pixmap): QGraphicsPixmapItem(pixmap)
{

    //this = parent->addPixmap(new QPixmap("../../ressources/station.png"));

    QPixmap *pix=new QPixmap("../../ressources/routeur.png");
    setPixmap(pix);
    //QGraphicsPixmapItem* item3 = parent->addPixmap(pixmap3);
    //this =parent->addPixmap(pix);


    this->moveBy(qrand()%200-100, qrand()%200-100);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    //parent->addItem(this);


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
    switch(parent->getMode()){
    case SELECT_MODE:  { break;}
    case DELETE_MODE:  { this->~NoeudG(); break;}
    case ROUTEUR_MODE: { break;}
    case STATION_MODE: { break;}
    case SWITCH_MODE:  { break;}
    case HUB_MODE:     { break;}
    case CABLE_MODE:   { break;}
    default: return;
    }
}
