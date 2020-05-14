#include "panneauOutils.hh"
#include <iostream>

#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QStateMachine>
#include "GFichier.hh"
#include "ConstantsRessources.hh"

PanneauOutils::PanneauOutils(){

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

    //Bouttons
    nouveau = this->addAction(QIcon(QPixmap(ICON_NEW)),"Nouveau fichier");
    ouvrir = this->addAction(QIcon(QPixmap(ICON_OUVRIR)),"Ouvrir fichier");
    sauvegarder =this->addAction(QIcon(QPixmap(ICON_SAVE)),"Sauvegarder fichier");
    exportButton = new QToolButton;
    addWidget(exportButton);
    this->addSeparator();
    demarrer = this->addAction(QIcon(QPixmap(ICON_SIM_START)),"demarrer Simulation");
    pause=this->addAction(QIcon(QPixmap(ICON_SIM_PAUSE)),"pause Simulation");
    arreter = this->addAction(QIcon(QPixmap(ICON_SIM_STOP)),"Arreter Simulation");
    relancer = this->addAction(QIcon(QPixmap(ICON_SIM_RESET)),"Relancer Simulation");
    changerMode = this->addAction(QIcon(QPixmap(ICON_SIM_CHANGEMODE)),"Changer mode");
    envoyer = this->addAction(QIcon(QPixmap(ICON_ENVOYER)),"Envoyer Message");

    QMenu * menu = new QMenu;
    exporterDot = menu->addAction(QIcon(QPixmap(ICON_EXPORT)),"Exporter en Dot");
    exporterPng = menu->addAction(QIcon(QPixmap(ICON_EXPORT_PNG)),"Exporter en Image");


    exportButton->setMenu(menu);
    exportButton->setPopupMode(QToolButton::MenuButtonPopup);
    //connect(exportButton, SIGNAL(triggered(QAction*)), exportButton, SLOT(setDefaultAction(QAction*)));
}
void PanneauOutils::createSignals(){

    //connection SIGNAL-SLOT
    connect(nouveau,SIGNAL(triggered()),this,SLOT(nouveauFichier()));
    connect(ouvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()));
    connect(sauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarderFichier()));
    connect(exporterDot,SIGNAL(triggered()),this,SLOT(exportDot()));
    connect(exporterPng,SIGNAL(triggered()),this,SLOT(exportPng()));
    connect(gestSimulation.getTimer(),SIGNAL(timeout()),this,SLOT(timer()));
    connect(demarrer,SIGNAL(triggered()),this,SLOT(demarrerSimulation()));
    connect(pause,SIGNAL(triggered()),this,SLOT(pauseSimulation()));
    connect(arreter,SIGNAL(triggered()),this,SLOT(arreterSimulation()));
    connect(relancer,SIGNAL(triggered()),this,SLOT(resetSimulation()));
    connect(changerMode,SIGNAL(triggered()),this,SLOT(changeMode()));
    connect(envoyer,SIGNAL(triggered()),this,SLOT(envoieD()));

}
void PanneauOutils::createShortCuts(){

    //Racourcis
    nouveau->setShortcut(QKeySequence("Ctrl+N"));
    ouvrir->setShortcut(QKeySequence("Ctrl+O"));
    sauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    //exporter->setShortcut(QKeySequence("Ctrl+E"));
    demarrer->setShortcut(QKeySequence("Ctrl+D"));
    arreter->setShortcut(QKeySequence("Ctrl+Q"));

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


void PanneauOutils::demarrerSimulation(){
    this->gestSimulation.demarrer();
}
void PanneauOutils::pauseSimulation(){
    this->gestSimulation.pause();
}
void PanneauOutils::arreterSimulation(){
    this->gestSimulation.arreter();
}
void PanneauOutils::resetSimulation(){
    this->gestSimulation.reset();

}

void PanneauOutils::timer(){
    QTime *t = this->gestSimulation.getTime();
    qDebug()<<t->toString("hh:mm:ss");
    this->gestSimulation.demarrer();
    *t=t->addSecs(1);
    this->gestSimulation.getTimer()->setInterval(1000);
}






