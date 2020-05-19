#include "panneauOutils.hh"
#include <iostream>
#include <QWidgetAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QStateMachine>
#include "GFichier.hh"

PanneauOutils::PanneauOutils(EspaceTravail * _espaceTravail){
    espaceTravail = _espaceTravail;
    this->setMinimumHeight(60);
    this->setMaximumHeight(70);
    this->setOrientation(Qt::Horizontal);
    createButtons();
    createSignals();
    createShortCuts();


}

PanneauOutils::~PanneauOutils()
{/*
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
    addWidget(relancer);

    changerMode = new QPushButton(this);
    changerMode->setCheckable(true);
    changerMode->setObjectName("changeAction");
    changerMode->setProperty("outilsBar", true);
    changerMode->setToolTip("Mode");
    addWidget(changerMode);

    envoyer = new QPushButton(this);
    envoyer->setObjectName("envoyerAction");
    envoyer->setProperty("outilsBar", true);
    envoyer->setToolTip("Envoyer");

    addWidget(envoyer);

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

    //connect(exportButton, SIGNAL(triggered(QAction*)), exportButton, SLOT(setDefaultAction(QAction*)));
}
void PanneauOutils::createSignals(){

    //connection SIGNAL-SLOT
    connect(nouveau,SIGNAL(clicked()),this,SLOT(nouveauFichier()));
    connect(ouvrir,SIGNAL(clicked()),this,SLOT(ouvrirFichier()));
    connect(sauvegarder,SIGNAL(clicked()),this,SLOT(sauvegarderFichier()));
    connect(exporterDot,SIGNAL(triggered()),this,SLOT(exportDot()));
    connect(exporterPng,SIGNAL(triggered()),this,SLOT(toPng()));
    connect(gestSimulation.getTimer(),SIGNAL(timeout()),this,SLOT(timer()));
    connect(simDemPause,SIGNAL(clicked()),this,SLOT(demarrerPauseSimulation()));
    // connect(pause,SIGNAL(triggered()),this,SLOT(pauseSimulation()));
    connect(arreter,SIGNAL(clicked()),this,SLOT(arreterSimulation()));
    connect(relancer,SIGNAL(clicked()),this,SLOT(resetSimulation()));
    connect(changerMode,SIGNAL(clicked()),this,SLOT(changeMode()));
    connect(envoyer,SIGNAL(clicked()),this,SLOT(envoieD()));
    connect(zoomIn,SIGNAL(clicked()),this,SLOT(zoomer()));
    connect(zoomOut,SIGNAL(clicked()),this,SLOT(dezoomer()));

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
    // lire le fichier
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  tr("Ouvrir un fichier de configuration"), "",
                                                  tr("Fichier xml (*.xml)"));
    if(!fileName.isEmpty()){
        curFile = fileName;
        qDebug() << curFile;

    }

}
void PanneauOutils::sauvegarderFichier(){
    // si pas de fichier , alors ouvrir sauvegarder
    // sinon ya fichier ,sauvegarder sans permission
    //
    if(curFile.isEmpty()){

        QString fileName=QFileDialog::getOpenFileName(this,
                                                      tr("Sauvegarder le fichier de configuration"), "",
                                                      tr("Fichier xml (*.xml)"));
        if(!fileName.isEmpty()){
            curFile = fileName;
            qDebug() << curFile;
        }

    }
}
void PanneauOutils::exportDot(){
    qDebug() << "DOT";
}

void PanneauOutils::exportPng(){
    qDebug() << "PNG";
}


void PanneauOutils::demarrerPauseSimulation(){
    if(simDemPause->isChecked()){
        simDemPause->setToolTip("Pause");
        this->gestSimulation.demarrer();
    }

    else{
        simDemPause->setToolTip("Demarrer");
        this->gestSimulation.pause();
    }

}
void PanneauOutils::arreterSimulation(){
    this->gestSimulation.arreter();
    simDemPause->setChecked(false);
}
void PanneauOutils::resetSimulation(){
    this->gestSimulation.reset();

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
    QTime *t = this->gestSimulation.getTime();
    qDebug()<<t->toString("hh:mm:ss");
    this->gestSimulation.demarrer();
    *t=t->addSecs(1);
    this->gestSimulation.getTimer()->setInterval(1000);
    PanneauEvents::afftime();
}

void PanneauOutils::toPng(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save PNG"));

    if (fileName.isEmpty())
        return;
    else{
        QPixmap pixMap = QPixmap::grabWidget(espaceTravail->getVue());
        int a=espaceTravail->getVue()->verticalScrollBar()->width();
        int b=espaceTravail->getVue()->horizontalScrollBar()->width();
        int c=espaceTravail->getVue()->rect().height();
        int d=espaceTravail->getVue()->rect().width();

        QRect rect(0, 0, d-a,c-a);
        QPixmap original(pixMap);
        QPixmap cropped = original.copy(rect);
        cropped.save(fileName+".png");
        //PanneauEvents::addCh(parent,"Votre espace est exporte en png");
    }
}

void PanneauOutils::zoomer(){
    espaceTravail->getVue()->scale(1.2,1.2);
}

void PanneauOutils::dezoomer(){
     espaceTravail->getVue()->scale(1/1.2,1/1.2);
}








