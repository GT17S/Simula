#include "panneauOutils.hh"

#include <iostream>
#include <QWidgetAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QStateMachine>
#include <QObject>
#include <cstring>

#include "simulaGui.hh"
#include "PanneauData.hh"
#include "GFichier.hh"
#include "NoeudG.hh"


PanneauOutils::PanneauOutils(EspaceTravail * _espaceTravail, gSimulation * g){
    espaceTravail = _espaceTravail;
    this->gestSimulation = g;

// Ajouté par Massi
//	Connexion signals/slots 
	QObject::connect ( espaceTravail, SIGNAL(createStation(NoeudG*)), g->getManager(), SLOT(createWorker(NoeudG*)));
    QObject::connect ( espaceTravail, SIGNAL(removeStation(NoeudG*)), g->getManager(), SLOT(removeStation(NoeudG*)));

    this->setMinimumHeight(60);
    this->setMaximumHeight(70);
    this->setOrientation(Qt::Horizontal);
    createButtons();
    createSignals();
    createShortCuts();


}

PanneauOutils::~PanneauOutils()
{

    delete gestSimulation;

	/*
    delete formulaire;
    delete nouveau;
    delete ouvrir;
    delete sauvegarder;
    delete exporterDot;
    delete exporterPng;
    delete demarrer;
    delete pause;
    delete arreter;
    delete relancer;
    delete changerMode;
    delete envoyer;
*/
}



void PanneauOutils::createButtons(){

    //Boutton
    setObjectName("outilsBarMain");
    // setStyleSheet("background-color : white;");
    nouveau = new QPushButton(this);
    nouveau->setObjectName("nvAction");
    nouveau->setProperty("outilsBar", true);
    nouveau->setToolTip("Nouveau");
    addWidget(nouveau);

    ouvrir = new QPushButton(this);
    ouvrir->setObjectName("ouvrirAction");
    ouvrir->setProperty("outilsBar", true);
    ouvrir->setToolTip("Ouvrir fichier");
    addWidget(ouvrir);

    sauvegarder = new QPushButton(this);
    sauvegarder->setObjectName("svgdAction");
    sauvegarder->setProperty("outilsBar", true);
    sauvegarder->setToolTip("Sauvegarder");
    addWidget(sauvegarder);

    exportButton = new QPushButton(this);
    exportButton->setObjectName("exportAction");
    exportButton->setProperty("outilsBar", true);
    exportButton->setToolTip("Exporter");
    QMenu * menu = new QMenu;
    exporterDot = menu->addAction(QIcon(QPixmap("../../ressources/outilsBar/exportImage.png")),"Exporter en Dot");
    exporterPng = menu->addAction(QIcon(QPixmap("../../ressources/outilsBar/exportImage.png")),"Exporter en Image");
    exportButton->setMenu(menu);
    //exportButton->setPopupMode(QToolButton::MenuButtonPopup);
    addWidget(exportButton);

    addSeparator();
    /* simulation */
    simDemPause = new QPushButton(this);
    simDemPause->setCheckable(true);
    simDemPause->setObjectName("simDP");
    simDemPause->setToolTip("Demarrer");
    simDemPause->setProperty("outilsBar", true);
    addWidget(simDemPause);

    arreter = new QPushButton(this);
    arreter->setObjectName("arreterAction");
    arreter->setProperty("outilsBar", true);
    arreter->setToolTip("Arreter");
    addWidget(arreter);

    relancer = new QPushButton(this);
    relancer->setObjectName("relancerAction");
    relancer->setProperty("outilsBar", true);
    relancer->setToolTip("Relancer");
    relancer->setVisible(false);
    addWidget(relancer);

    changerMode = new QPushButton(this);
    changerMode->setCheckable(true);
    changerMode->setObjectName("changeAction");
    changerMode->setProperty("outilsBar", true);
    changerMode->setToolTip("Mode");
    changerMode->setVisible(false);
    addWidget(changerMode);

    benvoyer = new QPushButton(this);
    benvoyer->setObjectName("envoyerAction");
    benvoyer->setProperty("outilsBar", true);
    benvoyer->setToolTip("Envoyer");

    addWidget(benvoyer);

    addSeparator();
    zoomIn = new QPushButton(this);
    zoomIn->setObjectName("zoomInAction");
    zoomIn->setProperty("outilsBar", true);
    zoomIn->setToolTip("Zoomer");
    addWidget(zoomIn);

    zoomOut = new QPushButton(this);
    zoomOut->setObjectName("zoomOutAction");
    zoomOut->setProperty("outilsBar", true);
    zoomOut->setToolTip("Dé-zoomer");
    addWidget(zoomOut);


    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(spacer);




    quitb = new QPushButton(this);
    quitb->setObjectName("quitAction");
    quitb->setProperty("outilsBar", true);
    quitb->setToolTip("Quitter");
    addWidget(quitb);

//connect(exportButton, SIGNAL(triggered(QAction*)), exportButton, SLOT(setDefaultAction(QAction*)));
}
void PanneauOutils::createSignals(){

    //connection SIGNAL-SLOT
    connect(nouveau,SIGNAL(clicked()),this,SLOT(nouveauFichier()));
    connect(ouvrir,SIGNAL(clicked()),this,SLOT(ouvrirFichier()));
    connect(sauvegarder,SIGNAL(clicked()),this,SLOT(sauvegarderFichier()));
    connect(exporterDot,SIGNAL(triggered()),this,SLOT(exportDot()));

    connect(exporterPng,SIGNAL(triggered()),this,SLOT(exportPng()));
    connect(gestSimulation->getTimer(),SIGNAL(timeout()),this,SLOT(timer()));

    connect(simDemPause,SIGNAL(clicked()),this,SLOT(demarrerPauseSimulation()));
    // connect(pause,SIGNAL(triggered()),this,SLOT(pauseSimulation()));
    connect(arreter,SIGNAL(clicked()),this,SLOT(arreterSimulation()));
    connect(relancer,SIGNAL(clicked()),this,SLOT(resetSimulation()));
    connect(changerMode,SIGNAL(clicked()),this,SLOT(changeMode()));

    connect(benvoyer,SIGNAL(clicked()),this,SLOT(envoieD()));
    connect(zoomIn,SIGNAL(clicked()),this,SLOT(zoomer()));
    connect(zoomOut,SIGNAL(clicked()),this,SLOT(dezoomer()));

    connect(quitb, SIGNAL(clicked()), qApp, SLOT(quit()));
}
void PanneauOutils::createShortCuts(){

    //Racourcis
    nouveau->setShortcut(QKeySequence::New);
    ouvrir->setShortcut(QKeySequence::Open);
    sauvegarder->setShortcut(QKeySequence::Save);
    //exporter->setShortcut(QKeySequence("Ctrl+E"));
    //demarrer->setShortcut(QKeySequence("Ctrl+D"));
    //arreter->setShortcut(QKeySequence("Ctrl+Q"));
}

void PanneauOutils::nouveauFichier(){
    if(!curFile.isEmpty()){
        const QMessageBox::StandardButton ret
                = QMessageBox::warning(this, tr("Modifications non enregistrées"),
                                       tr("Voulez-vous enregistrer les modifications ?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
        switch (ret) {
        case QMessageBox::Yes : {
            sauvegarderFichier();
            break;
        }
        case QMessageBox::No : {
            break;
        }
        case QMessageBox::Cancel : {
            return;
        }
        default:
            break;
        }
    }

    // nouveau fichier
    gestSimulation->getManager()->joinall();
    Graphe * graphe = Graphe::get();
    graphe->~Graphe();
    this->clearPanneauData();
    curFile = "";
}
void PanneauOutils::ouvrirFichier(){
    // verifier si un fichier est déja ouvert
    if(!curFile.isEmpty()){
        const QMessageBox::StandardButton ret
                = QMessageBox::warning(this, tr("Modifications non enregistrées"),
                                       tr("Voulez-vous enregistrer les modifications ?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
        switch (ret) {
        case QMessageBox::Yes : {
            sauvegarderFichier();
            break;
        }
        case QMessageBox::No : {
            break;
        }
        case QMessageBox::Cancel : {
            return;
        }
        default:
            break;
        }
    }
    gestSimulation->getManager()->joinall();
    Graphe * graphe = Graphe::get();
    graphe->~Graphe();

    // lire le fichier
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  tr("Ouvrir un fichier de configuration"), "",
                                                  tr("Fichier xml (*.xml)"));
    if(!fileName.isEmpty()){
        curFile = fileName;
      /*
          QMessageBox *msgBox = new QMessageBox(this);
           msgBox->setText("Test");
           msgBox->setWindowModality(Qt::NonModal);
           msgBox->setInformativeText("Do you want to save your changes?");
           msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                                      QMessageBox::Cancel);
           msgBox->setDefaultButton(QMessageBox::Save);
          msgBox->accept();
          */
        lireXml(fileName, espaceTravail, gestSimulation->getManager());

       // ret.accept();
    }
   }
}
void PanneauOutils::sauvegarderFichier(){
    // si pas de fichier , alors ouvrir sauvegarder
    // sinon ya fichier ,sauvegarder sans permission
    //
    if(curFile.isEmpty()){

        QString fileName=QFileDialog::getSaveFileName(this,
                                                      tr("Sauvegarder le fichier de configuration"), "",
                                                      tr("Fichier xml (*.xml)"));
        if(!fileName.isEmpty()){
            curFile = fileName+".xml";
            ecrireXml(fileName);
        }

    }else ecrireXml(curFile);
}
void PanneauOutils::exportDot(){
   if(curFile.isEmpty()){
             QString fileName=QFileDialog::getSaveFileName(this,
                                                      tr("Sauvegarder le fichier de configuration"), "",
                                                      tr("Fichier dot (*.dot)"));

        if(!fileName.isEmpty()){
            curFile = fileName;
            ecrireDot(curFile.toStdString());
            curFile.clear();
        }else{
            QMessageBox::critical(this, "Export vers Dot", "Veuillez entrer des paramétres valides");
        }     
   }
}

void PanneauOutils::exportPng(){
    toPng();
}


void PanneauOutils::demarrerPauseSimulation(){
    if(simDemPause->isChecked()){
        simDemPause->setToolTip("Pause");
        this->gestSimulation->demarrer();
    }

    else{
        simDemPause->setToolTip("Demarrer");
        this->gestSimulation->pause();
    }

}
void PanneauOutils::arreterSimulation(){
    this->gestSimulation->arreter();
	this->clearPanneauData();
	// Clear PanneauEvent
    simDemPause->setChecked(false);
}

void PanneauOutils::resetSimulation(){
    this->gestSimulation->reset();

}

void PanneauOutils::changeMode(){
    if(changerMode->isChecked()){
        changerMode->setToolTip("Mode manuel");
    }

    else{
        changerMode->setToolTip("Mode automatique");
    }
}

void PanneauOutils::timer(){
   QTime *t = this->gestSimulation->getTime();
    this->gestSimulation->demarrer();
    *t=t->addSecs(1);
    this->gestSimulation->getTimer()->setInterval(1000);
    PanneauEvents::afftime();
}

void PanneauOutils::toPng(){
    QString fileName=QFileDialog::getSaveFileName(this,
                                                     tr("Exporter le fichier en image"), "",
                                                     tr("Image png (*.png)"));

       espaceTravail->getScene()->clearSelection();
       espaceTravail->getScene()->setSceneRect(espaceTravail->getScene()->itemsBoundingRect());
       QImage image(espaceTravail->getScene()->sceneRect().size().toSize(), QImage::Format_ARGB32);
       image.fill(Qt::white);

       QPainter painter(&image);
       espaceTravail->getScene()->render(&painter);
       image.save(fileName+".png");
    }


void PanneauOutils::zoomer(){
    espaceTravail->getVue()->scale(1.2,1.2);
}

void PanneauOutils::dezoomer(){
     espaceTravail->getVue()->scale(1/1.2,1/1.2);
}

void PanneauOutils::envoieD(){
    espaceTravail->setMode(MESSAGE_MODE);   
}

void PanneauOutils::clearPanneauData()	{
   simulaGui * gui = dynamic_cast <simulaGui * > (this->parentWidget());
	if ( gui)	{
		PanneauData * pData = dynamic_cast <PanneauData *> ( gui->getMainlayout()->itemAtPosition( 4, 0)->widget());
		if ( pData)	{ 
			pData->clearPanneauData();
		}    
    }
    for(Noeud *n: Graphe::getSommets()){
     Station *x=dynamic_cast<Station*>(n);
     if(x){
         if(x->getControleur()){
        x->getControleur()->clearFiles();
     }}

    }

}


void MessageBoxShow(QMessageBox* info){

}
