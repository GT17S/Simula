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
    src=parent;
  createWidget();
  createSignals();
}

Dialog::~Dialog(){}



void Dialog::addRoute()
{

Route *newRoute=new Route();
src->setTableRoutage(newRoute);

    showConfig(src);
    update();
}

void Dialog::addInterface()
{
    int nbPort=src->getNbPort();

    src->setNbPort(nbPort+1);

     showConfig(src);
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
    src->supprimerRoute(i);
    showConfig(src);

}
void Dialog::deleteInterfaceG(){
   int nbPort=src->getNbPort();

   src->setNbPort(nbPort-1);
   showConfig(src);
  update();

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
    interfaceLayout->addWidget(supprimerInterface);

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

    mapperInterfaceAp = new QSignalMapper(this);
    mapperRouteAp = new QSignalMapper(this);
    update();



}
void Dialog::createSignals(){
    connect(ajouterRoute,SIGNAL(clicked()),this,SLOT(addRoute()));
    connect(ajouterInterface,SIGNAL(clicked()),this,SLOT(addInterface()));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    connect(supprimerInterface, SIGNAL(clicked()), this, SLOT(deleteInterfaceG()));

    connect(mapperRoute, SIGNAL(mapped(int)), this, SLOT(deleteRouteG(int )));

    connect(mapperInterfaceAp, SIGNAL(mapped(int)), this, SLOT(appliquerInterface(int )));
    connect(mapperRouteAp, SIGNAL(mapped(int)), this, SLOT(appliquerRoute(int )));
    connect(this,SIGNAL(finished(int)),this,SLOT(onExitDialog(int)));

}
void Dialog::showConfig(Noeud *src){
    onExitDialog(0);
    NomStation->setText(QString::fromStdString(src->getNom()));
    for(InterfaceFE *i:src->getInterfaces()){
        QString AdresseIP=QString::fromStdString(i->getAdresseIP()),
                AdresseMac=QString::fromStdString(i->getAdresseMac()),
                AdresseRes=QString::fromStdString(i->getAdresseRes()),
                mask=QString::fromStdString(i->getMasque()),
                interfaceName=QString::fromStdString(i->getNomInterface());
        bool liaison= i->getCable() != nullptr ? true : false;
        InterfaceG *ig=new InterfaceG(AdresseIP,AdresseMac,AdresseRes,mask,interfaceName,liaison);
       // mapperInterface->setMapping(supprimerInterface,toolInterface->count());
     //  connect(supprimerInterface, SIGNAL(clicked()), mapperInterface, SLOT(map()));

        mapperInterfaceAp->setMapping(ig->appliquer,toolInterface->count());
        connect(ig->appliquer, SIGNAL(clicked()), mapperInterfaceAp, SLOT(map()));

        toolInterface->addItem(ig,"Interface");
    }

    for(Route *r: src->getTableRoutage()){
        int a=src->getTableRoutage().size();
        QString nextHope=QString::fromStdString(r->passerelle),
               AdresseRes=QString::fromStdString(r->adresseReseau),
                mask=QString::fromStdString(r->masque);
        RouteG *rg=new RouteG(nextHope,AdresseRes,mask);
        mapperRoute->setMapping(rg->supprimer,toolRoutage->count());
        connect(rg->supprimer, SIGNAL(clicked()), mapperRoute, SLOT(map()));

        mapperRouteAp->setMapping(rg->appliquer,toolRoutage->count());
        connect(rg->appliquer, SIGNAL(clicked()), mapperRouteAp, SLOT(map()));

        toolRoutage->addItem(rg,"Route");
}
}
void Dialog::appliquerInterface(int i){
    InterfaceG *ig=dynamic_cast<InterfaceG*>(toolInterface->widget(i));
    QString AdresseIPApp=ig->AdresseIP->text(),
            AdresseMacApp=ig->AdresseMac->text(),
            AdresseResApp=ig->AdresseRes->text(),
            maskApp=ig->mask->text(),
            interfaceNameApp=ig->interfaceName->text();
   bool liaisonApp=ig->liaison->checkState();

   if(AdresseIPApp.isEmpty() || AdresseMacApp.isEmpty() ||  AdresseResApp.isEmpty() ||
           maskApp.isEmpty() ||     interfaceNameApp.isEmpty()) return ;

    InterfaceFE *iF = src->getInterface(i);
    if(!iF)return ;
    iF->setAdresseIP(AdresseIPApp.toStdString());
    iF->setAdresseMac(AdresseMacApp.toStdString());
    iF->setAdresseRes(AdresseResApp.toStdString());
    iF->setMasque(maskApp.toStdString());
    iF->setNomInterface(interfaceNameApp.toStdString());

    showConfig(src);


}
void Dialog::appliquerRoute(int i){
    int size_table = src->getTableRoutage().size();
    RouteG *ig=dynamic_cast<RouteG*>(toolRoutage->widget(i));
    QString AdresseIPApp=ig->getNextHope()->text(),
            AdresseResApp=ig->getAdresseRes()->text(),
            mask=ig->getMask()->text();
            if(AdresseIPApp.isEmpty() || AdresseResApp.isEmpty() ||  mask.isEmpty()) return ;
    Route *routeNew=new Route();
    routeNew->adresseReseau=AdresseResApp.toStdString();
    routeNew->adresseReseau=AdresseResApp.toStdString();
    routeNew->masque=mask.toStdString();
    src->modifierRoute(i,routeNew);
     size_table = src->getTableRoutage().size();
  showConfig(src);

}
void Dialog::onExitDialog(int i){
    NomStation->clear();

    while(toolInterface->count())
        delete toolInterface->widget(toolInterface->currentIndex());

    while(toolRoutage->count())
        delete toolRoutage->widget(toolRoutage->currentIndex());


}
