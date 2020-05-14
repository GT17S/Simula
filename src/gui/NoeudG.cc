#include <NoeudG.hh>

NoeudG::NoeudG(QGraphicsScene *parent, QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    //parent->addItem(this);

    this->setTabWidget(new QTabWidget);
    //tabWidget->addTab("GENERAL");
}

NoeudG::NoeudG(QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->moveBy(qrand()%200-100, qrand()%200-100);
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
    delete tabWidget;
    delete buttonBox;
    delete item;
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

/////////////////***********///////////////////
void NoeudG::mousePressEvent(QMouseEvent *event)
{
    if(event->button()== Qt::RightButton)
        tabWidget->show();
}
