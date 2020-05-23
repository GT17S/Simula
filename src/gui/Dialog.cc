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
#include "InterfaceFE.hh"


Dialog::Dialog(Noeud *parent)
{
    src=parent;
  createWidget();
  createSignals();
}

Dialog::~Dialog(){}



void Dialog::addRoute()
{
int a=src->getTableRoutage().size();
Route *newRoute=new Route();
src->setTableRoutage(newRoute);
if(a==src->getTableRoutage().size()){
   QMessageBox::warning(this, "Erreur d'ajout de route",
                            "La route existe deja !",
                            QMessageBox::Yes);
}
    showConfig(src);

    update();
}

void Dialog::addInterface()
{

    int nbPort=src->getNbPort();
    src->setNbPort(nbPort+1);
    if(nbPort==src->getNbPort()){
       QMessageBox::warning(this, "Erreur d'ajout de route",
                                "La route existe deja !",
                                QMessageBox::Yes);
    }
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

    QGroupBox *generalGroupBox = new QGroupBox(tr(" General"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Nom station:")), NomStation);
    layout->addRow(changerNom);

    generalGroupBox->setLayout(layout);
    gridLayoutGeneral->addWidget(generalGroupBox);
    generalWidget->setLayout(gridLayoutGeneral);

    tabWidget->addTab(generalWidget,tr("General"));
}
void Dialog::deleteRouteG(int i){
    int a=src->getTableRoutage().size();
    src->supprimerRoute(i);

    if(a==src->getTableRoutage().size()){
       QMessageBox::warning(this, "Erreur de suppression",
                                "Erreur de suppression de la route !",
                                QMessageBox::Yes);
    }
    showConfig(src);

}
void Dialog::deleteInterfaceG(){
   int nbPort=src->getNbPort();

   src->setNbPort(nbPort-1);
   if(nbPort==src->getNbPort()){
      QMessageBox::warning(this, "Erreur de suppression",
                               "Erreur de suppression de la l'interface !",
                               QMessageBox::Yes);
   }
   showConfig(src);
  update();

}

void Dialog::createWidget(){
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    tabWidget = new QTabWidget;
    toolRoutage = new QToolBox();
    toolInterface = new QToolBox();
    ajouterRoute = new QPushButton("Ajouter une route");
    ajouterInterface = new QPushButton("Ajouter une interface");
    supprimerInterface = new QPushButton("Supprimer une interface");
    changerNom = new QPushButton("Changer le nom");
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
    setWindowTitle(tr("Configuration de l'equipement"));
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);

    mapperInterface = new QSignalMapper(this);
    mapperRoute = new QSignalMapper(this);

    mapperInterfaceAp = new QSignalMapper(this);
    mapperRouteAp = new QSignalMapper(this);
    maapperNom=new QSignalMapper(this);
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
    connect(changerNom, SIGNAL(clicked()), this, SLOT(appliquerChangerNom()));

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
    int count=0;
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
    if(InterfaceFE::checkAdresse(AdresseIPApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP){
        iF->setAdresseIP(AdresseIPApp.toStdString());
        ig->AdresseIP->setStyleSheet("color:black");

    }else{

        ig->AdresseIP->setStyleSheet("color:red");
        count++;
    }
    if(InterfaceFE::checkAdresse(AdresseResApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP){
        iF->setAdresseRes(AdresseResApp.toStdString());
        ig->AdresseRes->setStyleSheet("color:black");

    }else{

        ig->AdresseRes->setStyleSheet("color:red");
        count++;
    }
    if(InterfaceFE::checkAdresse(maskApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP){
        iF->setMasque(maskApp.toStdString());
        ig->mask->setStyleSheet("color:black");

    }else{

        ig->mask->setStyleSheet("color:red");
        count++;
    }
    if(InterfaceFE::checkAdresse(AdresseMacApp.toStdString(),MAC_REGEX,DEFAULT_MAC) != DEFAULT_MAC){
    iF->setAdresseMac(AdresseMacApp.toStdString());
        ig->AdresseMac->setStyleSheet("color:black");

    }else{

        ig->mask->setStyleSheet("color:red");
        count++;

    }

    iF->setNomInterface(interfaceNameApp.toStdString());
    if(iF->getMasque()==DEFAULT_IP ||iF->getMasque()==DEFAULT_IP || iF->getAdresseMac()==DEFAULT_MAC
            ||iF->getAdresseIP()==DEFAULT_IP ){
        if(count==1){
        QMessageBox::warning(this, "Invalide ",
                                 "Invalide adresse !",
                             QMessageBox::Ok);}else{
            QMessageBox::warning(this, "Invalide ",
                                     "Invalide adresses !",  QMessageBox::Ok);
        }
        return;}
    src->getParent()->toolTipShow();
    showConfig(src);
}
void Dialog::appliquerRoute(int i){
    int count=0;
    int size_table = src->getTableRoutage().size();
    RouteG *ig=dynamic_cast<RouteG*>(toolRoutage->widget(i));
    QString AdresseIPApp=ig->getNextHope()->text(),
            AdresseResApp=ig->getAdresseRes()->text(),
            mask=ig->getMask()->text();
            if(AdresseIPApp.isEmpty() || AdresseResApp.isEmpty() ||  mask.isEmpty()) return ;
    Route *routeNew=new Route();


    if(InterfaceFE::checkAdresse(AdresseIPApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP){
        routeNew->adresseReseau=AdresseResApp.toStdString();
        ig->AdresseRes->setStyleSheet("color:black");

    }else{

        count++;
        ig->AdresseRes->setStyleSheet("color:red");


    }
    if(InterfaceFE::checkAdresse(AdresseResApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP){
        routeNew->passerelle=AdresseIPApp.toStdString();
        ig->nextHope->setStyleSheet("color:black");
    }else{
        count++;
        ig->nextHope->setStyleSheet("color:red");
    }

    if(InterfaceFE::checkAdresse(mask.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP){
        routeNew->masque=mask.toStdString();
        ig->mask->setStyleSheet("color:black");
    }else{
        count++;
        ig->mask->setStyleSheet("color:red");
    }

    if(routeNew->passerelle==DEFAULT_IP || routeNew->adresseReseau==DEFAULT_IP
            || routeNew->masque==DEFAULT_IP){
        if(count==1){
            QMessageBox::warning(this, "Invalide ",
                                     "Invalide adresse !",  QMessageBox::Ok);

        }else{
        QMessageBox::warning(this, "Invalide ",
                                 "Invalide adresses !",  QMessageBox::Ok);}
      return ;

    }
    src->modifierRoute(i,routeNew);
    src->getParent()->toolTipShow();

    showConfig(src);

}
void Dialog::appliquerChangerNom(){
    QString nom=NomStation->text();
    src->setNom(nom.toStdString());
    showConfig(src);

}
void Dialog::onExitDialog(int i){
    NomStation->clear();

    while(toolInterface->count())
        delete toolInterface->widget(toolInterface->currentIndex());

    while(toolRoutage->count())
        delete toolRoutage->widget(toolRoutage->currentIndex());


}
