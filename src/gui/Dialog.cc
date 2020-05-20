#include "Dialog.hh"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QDebug>
#include <QPushButton>
#include <QToolBox>
#include <QCheckBox>
#include <QMainWindow>
#include "RouteG.hh"
#include "InterfaceG.hh"


Dialog::Dialog(Noeud *parent)
{
    //TABWWDGET
        tabWidget = new QTabWidget;
        toolRoutage = new QToolBox();
        toolInterface = new QToolBox();
        ajouterRoute = new QPushButton("Ajout");
        supprimerRoute = new QPushButton("Suppression");
        ajouterInterface = new QPushButton("Ajout");
        supprimerInterface = new QPushButton("Suppression");

        routeWidget = new QWidget();
        intWidget = new QWidget();


        routeLayout = new QGridLayout;
              routeLayout->addWidget(ajouterRoute);

        routeWidget->setLayout(routeLayout);
        connect(ajouterRoute,SIGNAL(clicked()),this,SLOT(addRoute()));

        //QPushButton* button = toolRoutage->currentWidget()->findChild<QPushButton*>("supprimer");

        interfaceLayout = new QGridLayout;
              interfaceLayout->addWidget(ajouterInterface);


        intWidget->setLayout(interfaceLayout);
        connect(ajouterInterface,SIGNAL(clicked()),this,SLOT(addInterface()));

          generalWidget();

          interfaceLayout->addWidget(toolInterface);

          intWidget->setLayout(interfaceLayout);
          tabWidget->addTab(intWidget,"Interface");


          routeLayout->addWidget(toolRoutage);

          routeWidget->setLayout(routeLayout);
          tabWidget->addTab(routeWidget,"Routage");



        tabWidget->setMovable(true);
        tabWidget->setDocumentMode(true);


        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
           connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
           connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

           QVBoxLayout *mainLayout = new QVBoxLayout;
               mainLayout->addWidget(tabWidget);
               mainLayout->addWidget(buttonBox);

        setLayout(mainLayout);
        setWindowTitle(tr("Configuration Tab"));

        update();
}

Dialog::~Dialog(){}

void Dialog::interfaceWidget(int nbPorts)
{
    //INTERFACE
    for(int i=0;i<nbPorts;i++)
    {
        QGridLayout *gridLayoutinterface = new QGridLayout();
        QLineEdit 	*AdresseIP	 = new QLineEdit ();
        QLineEdit 	*AdresseMac	 = new QLineEdit ();
        QLineEdit 	*AdresseRes	 = new QLineEdit ();
        QLineEdit   *mask = new QLineEdit ();
        QLineEdit   *interfaceName = new QLineEdit ();
        QCheckBox   *liaison = new QCheckBox("liaison", this);

        QGroupBox *portGroupBox = new QGroupBox("Form Port");
        QFormLayout *layout = new QFormLayout;

        layout->addRow(new QLabel("Nom interface:"), interfaceName);
        layout->addRow(new QLabel("Adresse machine:"), AdresseMac);
        layout->addRow(new QLabel("Adresse IP:"), AdresseIP);
        layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
        layout->addRow(new QLabel("Masque:"), mask);
        layout->addRow(new QLabel("Liaison:"), liaison);

        portGroupBox->setLayout(layout);
        gridLayoutinterface->addWidget(portGroupBox);

        QWidget *p= new QWidget();
        p->setLayout(gridLayoutinterface);

        QString o=QString::number(i);
        toolInterface->insertItem(i,p,"Interface "+o);
    }
    tabWidget->addTab(toolInterface,"interface");
}

//UNUSED
void Dialog::portsWidget()
{
    QWidget *interfaceWidget = new QWidget();
    QGridLayout *gridLayoutinterface = new QGridLayout();

    QLineEdit 	*AdresseIP	 = new QLineEdit ();
    QLineEdit 	*AdresseMac	 = new QLineEdit ();
    QLineEdit 	*AdresseRes	 = new QLineEdit ();
    QLineEdit   *mask = new QLineEdit ();
    QLineEdit   *interfaceName = new QLineEdit ();

    gridLayoutinterface->setVerticalSpacing (0);
    interfaceWidget->setFixedSize( 400, 450);

    QGroupBox *portGroupBox = new QGroupBox(tr("Form Port"));
    QFormLayout *layout = new QFormLayout;

    layout->addRow(new QLabel(tr("Nom interface:")), interfaceName);
    layout->addRow(new QLabel(tr("Adresse machine:")), AdresseMac);
    layout->addRow(new QLabel(tr("Adresse IP:")), AdresseIP);
    layout->addRow(new QLabel(tr("Adresse reseau:")), AdresseRes);
    layout->addRow(new QLabel(tr("Masque:")), mask);

    portGroupBox->setLayout(layout);
    gridLayoutinterface->addWidget(portGroupBox);

    interfaceWidget->setLayout(gridLayoutinterface);
    interfaceWidget->show();
    //tabWidget->addTab(interfaceWidget,tr("Interface"));
}

//UNUSED
void Dialog::routageWidget(int nbres)
{
    //Routage
    for(int i=0;i<nbres;i++)
    {
        QGridLayout *gridLayoutinterface = new QGridLayout();
        QLineEdit 	*nextHope	 = new QLineEdit ();
        QLineEdit 	*AdresseRes	 = new QLineEdit ();
        QLineEdit   *mask = new QLineEdit ();
        QLineEdit   *resName = new QLineEdit ();

        QGroupBox *portGroupBox = new QGroupBox("Form Routage");
        QFormLayout *layout = new QFormLayout;

        layout->addRow(new QLabel("Nom de reseau:"), resName);
        layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
        layout->addRow(new QLabel("Masque:"), mask);
        layout->addRow(new QLabel("Next hope:"), nextHope);

        portGroupBox->setLayout(layout);
        gridLayoutinterface->addWidget(portGroupBox);

        QWidget *p= new QWidget();
        p->setLayout(gridLayoutinterface);

        QString o=QString::number(i);
        toolRoutage->insertItem(i,p,"Table Routage "+o);
    }
    QGridLayout *lay=new  QGridLayout;
    lay->addWidget(toolRoutage);

    routeWidget->setLayout(lay);
    tabWidget->addTab(routeWidget,"Routage");
}

//UNUSED
std::vector<QWidget *> Dialog::getPorts() const
{
    return ports;
}
//UNUSED
void Dialog::setPorts(const std::vector<QWidget *> &value)
{
    ports = value;
}
//UNUSED
void Dialog::ked(int i)
{
    this->getPorts().at(i)->show();
}

void Dialog::addRoute()
{
    /*
        QGridLayout *gridLayoutinterface = new QGridLayout();
        QLineEdit 	*nextHope	 = new QLineEdit ();
        QLineEdit 	*AdresseRes	 = new QLineEdit ();
        QLineEdit     *mask = new QLineEdit ();
        QLineEdit     *resName = new QLineEdit ();

        QPushButton *supprimer = new QPushButton("Supprimer");
        QPushButton *appliquer = new QPushButton("Appliquer");

        QGroupBox *portGroupBox = new QGroupBox("Form Routage");
        QFormLayout *layout = new QFormLayout;

        layout->addRow(new QLabel("Nom de reseau:"), resName);
        layout->addRow(new QLabel("Adresse reseau:"), AdresseRes);
        layout->addRow(new QLabel("Masque:"), mask);
        layout->addRow(new QLabel("Next hope:"), nextHope);

        portGroupBox->setLayout(layout);
        gridLayoutinterface->addWidget(portGroupBox);
        gridLayoutinterface->addWidget(appliquer);
        gridLayoutinterface->addWidget(supprimer);

        QWidget *p= new QWidget();
        p->setLayout(gridLayoutinterface);

        QString o=QString::number(toolRoutage->count());
        toolRoutage->insertItem(toolRoutage->count(),p,"Route"+o);


    //mainly changes
    routeLayout->addWidget(toolRoutage);
    routeWidget->setLayout(routeLayout);
    update();

    */

    RouteG *road=new RouteG();
    QString Num=QString::number(toolRoutage->count());
    toolRoutage->insertItem(toolRoutage->count(),road, "Route"+Num);
    //mainly changes
    routeLayout->addWidget(toolRoutage);
    routeWidget->setLayout(routeLayout);

    update();
/*
    //recuperer le bouton supprimer:
    QLayoutItem* item = toolRoutage->currentWidget()->layout()->itemAt(2);
    QWidget* widget = item->widget();
    QPushButton* button5 = dynamic_cast<QPushButton*>(widget);
    connect(button5,SIGNAL(clicked()),this,SLOT(deleteRoute(toolRoutage->count())));
*/
}

void Dialog::addInterface()
{
    InterfaceG *inter=new InterfaceG();
    QString Num=QString::number(toolInterface->count());
    toolInterface->insertItem(toolInterface->count(),inter, "Interface"+Num);
    //mainly changes
    interfaceLayout->addWidget(toolInterface);
    intWidget->setLayout(interfaceLayout);

    update();
}

//USED BUT NOT WORKING INSTEAD SUPPRESSION IN ROUTE deleteroute SLOT.
void Dialog::deleteRoute(int s)
{
    //toolRoutage->removeItem(s);
    toolRoutage->currentWidget()->~QWidget();
     update();
}

void Dialog::configurationWidget()
{
    //CONFIGURATION
    QWidget *confWidget = new QWidget();
    QGridLayout *gridLayoutconf = new QGridLayout();
    QLineEdit 	*AdressePasserelle	 = new QLineEdit ();
    QLineEdit   *AdresseMAC = new QLineEdit ();
    QLineEdit   *nbPort = new QLineEdit ();

    gridLayoutconf->setVerticalSpacing (0);
    confWidget->setFixedSize( 400, 450);

    QGroupBox *confGroupBox = new QGroupBox(tr("Form Configuration"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Adresse MAC:")), AdresseMAC);
    layout->addRow(new QLabel(tr("Passerelle:")), AdressePasserelle);
    layout->addRow(new QLabel(tr("Nombres de ports:")), nbPort);

    confGroupBox->setLayout(layout);
    gridLayoutconf->addWidget(confGroupBox);
    confWidget->setLayout(gridLayoutconf);

    tabWidget->addTab(confWidget,tr("Configuration"));
}

void Dialog::generalWidget()
{
    //GENERAL
    //GENERALWIDGET
    QWidget *generalWidget = new QWidget();
    //GENERALLAYOUT
    QGridLayout *gridLayoutGeneral = new QGridLayout();
    //GENERALEDITLINES
    QLineEdit 	*NomStation	 = new QLineEdit ();


    gridLayoutGeneral->setVerticalSpacing (0);
    generalWidget->setFixedSize( 400, 450);

    QGroupBox *generalGroupBox = new QGroupBox(tr("Form General"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Nom station:")), NomStation);

    generalGroupBox->setLayout(layout);
    gridLayoutGeneral->addWidget(generalGroupBox);
    generalWidget->setLayout(gridLayoutGeneral);

    tabWidget->addTab(generalWidget,tr("General"));
}

//UNUSED
void Dialog::delSignal()
{
    QPushButton* button2 =toolRoutage->currentWidget()->layout()->findChild<QPushButton*>("supprimer");
    connect(button2,SIGNAL(clicked()),this,SLOT(deleteRoute()));

    QPushButton* button3 =(QPushButton*)toolRoutage->currentWidget()->layout()->itemAt(2);
    QLayoutItem* item = toolRoutage->currentWidget()->layout()->itemAt(2);
    QWidget* widget = item->widget();
    QPushButton* button = dynamic_cast<QPushButton*>(widget);
    connect(button,SIGNAL(clicked()),this,SLOT(deleteRoute()));
}
