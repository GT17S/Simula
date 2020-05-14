#include "panneauOutils.hh"

#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QPixmap>
#include <QPlainTextEdit>
#include "GFichier.hh"
PanneauOutils::PanneauOutils(){

    this->setMinimumHeight(60);
    this->setMaximumHeight(70);
    this->setOrientation(Qt::Horizontal);

    QPixmap New("../../ressources/ajouterFichier.png");

    QPixmap open("../../ressources/ouvrirFichier.png");
    QPixmap save("../../ressources/sauvegarder.png");
    QPixmap exporte("../../ressources/exporter.jpeg");
    QPixmap png("../../ressources/img.png");
    QPixmap start("../../ressources/demarrer.jpeg");
    QPixmap paus("../../ressources/pause.jpeg");
    QPixmap stop("../../ressources/stop.jpeg");
    QPixmap relance("../../ressources/relancer.png");
    QPixmap change("../../ressources/changeMode.jpeg");
    QPixmap send("../../ressources/send.jpeg");
    //New.scaled(QSize(60,60),Qt::IgnoreAspectRatio);
    //Bouttons
    QAction *nouveau = this->addAction(QIcon(New),"Nouveau fichier");
    QAction *ouvrir = this->addAction(QIcon(open),"Ouvrir fichier");
    QAction *sauvegarder =this->addAction(QIcon(save),"Sauvegarder fichier");
    QAction *exporter = this->addAction(QIcon(exporte),"Exporter fichier");
    QAction *exporterPng=this->addAction(QIcon(png),"Exporter en Image");
    this->addSeparator();


    QAction *demarrer = this->addAction(QIcon(start),"demarrer Simulation");
    QAction *pause=this->addAction(QIcon(paus),"pause Simulation");
    QAction *arreter = this->addAction(QIcon(stop),"Arreter Simulation");
    QAction *relancer = this->addAction(QIcon(relance),"Relancer Simulation");
    QAction *changerMode = this->addAction(QIcon(change),"Changer mode");
    QAction *envoyer = this->addAction(QIcon(send),"Envoyer Message");

    //Racourcis
    nouveau->setShortcut(QKeySequence("Ctrl+N"));
    ouvrir->setShortcut(QKeySequence("Ctrl+O"));
    sauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    exporter->setShortcut(QKeySequence("Ctrl+E"));
    demarrer->setShortcut(QKeySequence("Ctrl+D"));
    arreter->setShortcut(QKeySequence("Ctrl+Q"));


    //connextion SIGNAL-SLOT
    connect(nouveau,SIGNAL(triggered()),this,SLOT(nouveauFichier()));
    connect(ouvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()));
    connect(sauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarderFichier()));
    connect(exporter,SIGNAL(triggered()),this,SLOT(exporterFichier()));
    connect(exporterPng,SIGNAL(triggered()),this,SLOT(toPng()));
    connect(this->gestSimulation.getTimer(),SIGNAL(timeout()),this,SLOT(timer()));
    connect(demarrer,SIGNAL(triggered()),this,SLOT(demarrerSimulation()));
    connect(pause,SIGNAL(triggered()),this,SLOT(pauseSimulation()));
    connect(arreter,SIGNAL(triggered()),this,SLOT(arreterSimulation())); 
    connect(relancer,SIGNAL(triggered()),this,SLOT(resetSimulation()));
    connect(changerMode,SIGNAL(triggered()),this,SLOT(changeMode()));
    connect(envoyer,SIGNAL(triggered()),this,SLOT(envoieD()));
}

void PanneauOutils::ouvrirFichier(){
    QString fileName=QFileDialog::getOpenFileName(this,
                                               tr("Open Address Book"), "",
                                               tr("Address Book (*.xml)"));

   curFile=fileName;
    //Graphe *g=new(); il faut rendre le constructeur public
    //lireXml(fileName,g);//appliquer le graphe sur la scene
   std::cout<<curFile.toStdString()<<std::endl;
   QMessageBox::information(NULL, "Information!", "Fichier importer avec succé");
}
void PanneauOutils::sauvegarderFichier()
{
    if(curFile.isEmpty())
    {
         QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Address Book"), "",
             tr("Address Book (*.xml)"));
         curFile=fileName;
        if (fileName.isEmpty())
              return;
         else {
             QFile file(fileName);
                 if (!file.open(QIODevice::WriteOnly)) {
                      QMessageBox::information(this, tr("Unable to open file"),
                        file.errorString());
                        return;
                    }
         }
    }
    //ecrireXml(curFile,EspaceTravail::g); //je dois acceder a la classe
    QMessageBox::information(NULL, "Information!", "Fichier sauvegarder !");
}
void PanneauOutils::exporterFichier()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Address Book"), "",
        tr("Address Book (*.dot)")); //confirmer comment s'ecrit l extention
    curFile=fileName;
    if (fileName.isEmpty())
       return;
    else {
       QFile file(fileName);
         if (!file.open(QIODevice::WriteOnly)) {
             QMessageBox::information(this, tr("Unable to open file"),
             file.errorString());
             return;
         }
        }
    //ecrireDot(fileName,EspaceTravail::g);//recuperer le graphe courant ;
    QMessageBox::information(NULL, "Information!", "Fichier exporter en DOT !");
}
void PanneauOutils::nouveauFichier()
{
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("voulez vous sauvegarder ce fichier courant ?"),
                               QMessageBox::Save | QMessageBox::Discard );
    switch (ret) {
    case QMessageBox::Save:
        sauvegarderFichier();
       // EspaceTravail::scene->clear();
     /*case QMessageBox::Discard
       EspaceTravail::scene->clear();
        je dois recuperer ce qu'il y'a dans la scene et le clean */
    default:
        break;
    }

    curFile.clear();
    QMessageBox::information(NULL, "Information!", "Nouveau Fichier créer !");
}


 void PanneauOutils::demarrerSimulation()
 {
     this->gestSimulation.demarrer();
     PanneauEvents::afftime();
 }
 void PanneauOutils::pauseSimulation()
{
  this->gestSimulation.pause();
}
void PanneauOutils::arreterSimulation()
{
  this->gestSimulation.arreter();
}
void PanneauOutils::resetSimulation()
{
  this->gestSimulation.reset();

}

void PanneauOutils::timer()
{
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
           /* QPixmap pixMap = QPixmap::grabWidget(EspaceTravail::getVue());
            pixMap.save(fileName+".png");
            */
}}






