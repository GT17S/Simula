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
  createWidget();
  createSignals();
}

Dialog::~Dialog(){}



void Dialog::addRoute()
{


    RouteG *road=new RouteG("","","");
    QString Num=QString::number(toolRoutage->count());
    toolRoutage->insertItem(toolRoutage->count(),road, "Route"+Num);
    //mainly changes
    routeLayout->addWidget(toolRoutage);
    routeWidget->setLayout(routeLayout);


    update();
}

void Dialog::addInterface()
{
    InterfaceG *inter=new InterfaceG("","","","","",false);
    QString Num=QString::number(toolInterface->count());
    toolInterface->insertItem(toolInterface->count(),inter, "Interface"+Num);
    //mainly changes
    interfaceLayout->addWidget(toolInterface);
    intWidget->setLayout(interfaceLayout);

    update();
}



void Dialog::generalWidget()
{
    //GENERAL
    //GENERALWIDGET
    QWidget *generalWidget = new QWidget();
    //GENERALLAYOUT
    QGridLayout *gridLayoutGeneral = new QGridLayout();
    //GENERALEDITLINES
   NomStation	 = new QLineEdit ();


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
void Dialog::deleteRouteG(int i){
    qDebug()<<"delete route valeur de i est :"<<i;
}
void Dialog::deleteInterfaceG(int i){
    qDebug()<<"delete interface valeur de i est :"<<i;

}

void Dialog::createWidget(){
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

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
    interfaceLayout = new QGridLayout;
    interfaceLayout->addWidget(ajouterInterface);
    intWidget->setLayout(interfaceLayout);
    generalWidget();
    interfaceLayout->addWidget(toolInterface);
    intWidget->setLayout(interfaceLayout);
    tabWidget->addTab(intWidget,"Interface");
    routeLayout->addWidget(toolRoutage);
    routeWidget->setLayout(routeLayout);
    tabWidget->addTab(routeWidget,"Routage");
    tabWidget->setMovable(true);
    tabWidget->setDocumentMode(true);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    setWindowTitle(tr("Configuration Tab"));
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);

    mapperInterface = new QSignalMapper(this);
    mapperRoute = new QSignalMapper(this);

    update();



}
void Dialog::createSignals(){
    connect(ajouterRoute,SIGNAL(clicked()),this,SLOT(addRoute()));
    connect(ajouterInterface,SIGNAL(clicked()),this,SLOT(addInterface()));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(mapperInterface, SIGNAL(mapped(int)), this, SLOT(deleteInterfaceG(int )));
    connect(mapperRoute, SIGNAL(mapped(int)), this, SLOT(deleteRouteG(int )));


}
void Dialog::showConfig(Noeud *src){
    NomStation->setText(QString::fromStdString(src->getNom()));
    for(InterfaceFE *i:src->getInterfaces()){
        QString AdresseIP=QString::fromStdString(i->getAdresseIP()),
                AdresseMac=QString::fromStdString(i->getAdresseMac()),
                AdresseRes=QString::fromStdString(i->getAdresseRes()),
                mask=QString::fromStdString(i->getMasque()),
                interfaceName=QString::fromStdString(i->getNomInterface());
        bool liaison= i->getCable() != nullptr ? true : false;
        InterfaceG *ig=new InterfaceG(AdresseIP,AdresseMac,AdresseRes,mask,interfaceName,liaison);
        mapperInterface->setMapping(ig->supprimer,toolInterface->count());
        toolInterface->addItem(ig,"Interface");
    }

    for(Route *r: src->getTableRoutage()){
        QString nextHope=QString::fromStdString(r->passerelle),
               AdresseRes=QString::fromStdString(r->adresseReseau),
                mask=QString::fromStdString(r->masque);
        RouteG *rg=new RouteG(nextHope,AdresseRes,mask);
        mapperRoute->setMapping(rg->supprimer,toolRoutage->count());
        toolRoutage->addItem(rg,"Route");
}
}
void Dialog::appliquer(int i){
    qDebug()<<"TESTTT"<<i;
}
