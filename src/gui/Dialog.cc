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
    changerNom = new QPushButton("Changer le nom");
    setWindowTitle(tr("Configuration de l'equipement"));
    tabWidget = new QTabWidget;
    generalWidget();


    toolRoutage = new QToolBox();
    toolInterface = new QToolBox();
    ajouterRoute = new QPushButton("Ajouter une route");
    ajouterInterface = new QPushButton("Ajouter une interface");
    supprimerInterface = new QPushButton("Supprimer une interface");
    routeWidget = new QWidget();
    intWidget = new QWidget();
    routeLayout = new QGridLayout;
    routeLayout->addWidget(ajouterRoute);
    routeWidget->setLayout(routeLayout);
    interfaceLayout = new QGridLayout;
    interfaceLayout->addWidget(ajouterInterface);
    interfaceLayout->addWidget(supprimerInterface);

    intWidget->setLayout(interfaceLayout);


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
    if(src->getTypeNoeud()==2 ||src->getTypeNoeud()==3 ){
        toolInterface->setEnabled(false);
        toolRoutage->setEnabled(false);

    }

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
    QString errorString;
    QTextStream stream(&errorString);
    stream<< "<h5><b><font color='red'>Veuillez entrer les parameres suivants :</font></b></h5><ul>";

    InterfaceG *ig=dynamic_cast<InterfaceG*>(toolInterface->widget(i));
    QString AdresseIPApp=ig->AdresseIP->text(),
            AdresseMacApp=ig->AdresseMac->text(),
            AdresseResApp=ig->AdresseRes->text(),
            maskApp=ig->mask->text(),
            interfaceNameApp=ig->interfaceName->text();
    bool liaisonApp=ig->liaison->checkState();


    InterfaceFE *iF = src->getInterface(i);
    if(!iF)return ;
    iF->setNomInterface(interfaceNameApp.toStdString());

    if(InterfaceFE::checkAdresse(AdresseIPApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP
            && InterfaceFE::checkAdresse(AdresseResApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP
            && InterfaceFE::checkAdresse(maskApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP
            ){
        iF->setAdresseIP(AdresseIPApp.toStdString());
        ig->AdresseIP->setStyleSheet("color:black");
        iF->setAdresseRes(AdresseResApp.toStdString());
        ig->AdresseRes->setStyleSheet("color:black");
        iF->setMasque(maskApp.toStdString());
        ig->mask->setStyleSheet("color:black");
        iF->setAdresseMac(AdresseMacApp.toStdString());
        ig->AdresseMac->setStyleSheet("color:black");
        QMessageBox::warning(this, "Bien ",
                             "adresses Sauvgardé ",
                             QMessageBox::Ok);
        src->getParent()->toolTipShow();

        return;

    }else{
        if(InterfaceFE::checkAdresse(AdresseIPApp.toStdString(),IP_REGEX,DEFAULT_IP) == DEFAULT_IP
                || AdresseIPApp.isEmpty()){
            ig->AdresseIP->setStyleSheet("color:red");
            stream<<"<li>Adresse ip</li>";

        }else{
            ig->AdresseIP->setStyleSheet("color:black");

        }

        if(InterfaceFE::checkAdresse(AdresseResApp.toStdString(),IP_REGEX,DEFAULT_IP) == DEFAULT_IP
                || AdresseResApp.isEmpty()){
            ig->AdresseRes->setStyleSheet("color:red");
            stream<<"<li>Adresse reseau</li>";

        }else{
            ig->AdresseRes->setStyleSheet("color:black");

        }

        if(InterfaceFE::checkAdresse(maskApp.toStdString(),IP_REGEX,DEFAULT_IP) == DEFAULT_IP
                || maskApp.isEmpty()){
            ig->mask->setStyleSheet("color:red");
            stream<<"<li>Masque reseau</li>";

        }else{
            ig->mask->setStyleSheet("color:black");

        }

        QMessageBox errorbox;
        stream<<"</ul>";
        errorbox.setText(errorString);
        errorbox.exec();
        return;
    }





    src->getParent()->toolTipShow();
}

void Dialog::appliquerRoute(int i){
    QString errorString;
    QTextStream stream(&errorString);
    stream<< "<h5><b><font color='red'>Veuillez entrer les parameres suivants :</font></b></h5><ul>";
    RouteG *ig=dynamic_cast<RouteG*>(toolRoutage->widget(i));
    QString AdresseIPApp=ig->getNextHope()->text(),
            AdresseResApp=ig->getAdresseRes()->text(),
            mask=ig->getMask()->text();
    Route *routeNew=new Route();

    if(InterfaceFE::checkAdresse(AdresseIPApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP
            && InterfaceFE::checkAdresse(AdresseResApp.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP
            && InterfaceFE::checkAdresse(mask.toStdString(),IP_REGEX,DEFAULT_IP) != DEFAULT_IP
            ){
        qDebug()<<"adress rx"+AdresseResApp;
        qDebug()<<"adress nexthopp"+AdresseIPApp;
        qDebug()<<"adress masque"+mask;

        routeNew->adresseReseau=AdresseResApp.toStdString();
         qDebug()<<"apres ajout "+QString::fromStdString(routeNew->adresseReseau);
        ig->AdresseRes->setStyleSheet("color:black");
        routeNew->passerelle=AdresseIPApp.toStdString();
        ig->nextHope->setStyleSheet("color:black");
        routeNew->masque=mask.toStdString();
        ig->mask->setStyleSheet("color:black");
        src->getParent()->toolTipShow();
        src->modifierRoute(i,routeNew);

        QMessageBox::warning(this, "Bien ",
                             "adresses Sauvgardé ",
                             QMessageBox::Ok);
        return;

    }else{
        if(InterfaceFE::checkAdresse(AdresseIPApp.toStdString(),IP_REGEX,DEFAULT_IP) == DEFAULT_IP
                || AdresseIPApp.isEmpty() ){
            ig->nextHope->setStyleSheet("color:red");
            stream<<"<li>Adresse nextHope</li>";
        }else
        {
            ig->nextHope->setStyleSheet("color:black");

        }

        if(InterfaceFE::checkAdresse(AdresseResApp.toStdString(),IP_REGEX,DEFAULT_IP) == DEFAULT_IP
                 || AdresseResApp.isEmpty() ){
            ig->AdresseRes->setStyleSheet("color:red");
            stream<<"<li>Adresse reseau</li>";
        }else
        {
            ig->AdresseRes->setStyleSheet("color:black");

        }
        if(InterfaceFE::checkAdresse(mask.toStdString(),IP_REGEX,DEFAULT_IP) == DEFAULT_IP
                 || mask.isEmpty() ){
            ig->mask->setStyleSheet("color:red");
            stream<<"<li>Masque reseau</li>";
        }else
        {
            ig->mask->setStyleSheet("color:black");

        }




        QMessageBox errorbox;
        stream<<"</ul>";
        errorbox.setText(errorString);
        errorbox.exec();
        return;
    }
    src->getParent()->toolTipShow();

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
