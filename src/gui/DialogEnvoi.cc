#include "DialogEnvoi.hh"
#include "DataOutils.hh"
#include "gSimulation.hh"
#include "PanneauData.hh"

#include <QIntValidator>

DialogEnvoi::DialogEnvoi(Noeud * n1, Noeud * n2){
    createForm();
    connect(envoyerButton, SIGNAL(clicked()),this , SLOT(preparenvoi()));
    showForm(n1, n2);
}

DialogEnvoi::~DialogEnvoi(){

}

void DialogEnvoi::createForm(){
    QFormLayout * layout = new QFormLayout();
    setLayout(layout);
    setWindowTitle("Paramètres d'envoi");

    editNoeud1 = new QLineEdit();
    editNoeud1->setPlaceholderText("Emetteur");
    editNoeud1->setEnabled(false);
    layout->addWidget(editNoeud1);

    editNoeud2 = new QLineEdit();
    editNoeud2->setPlaceholderText("Recepteur");
    editNoeud2->setEnabled(false);
    layout->addWidget(editNoeud2);

    editPortSrc = new QLineEdit();
    editPortSrc->setPlaceholderText("Port source");
    editPortSrc->setValidator( new QIntValidator(0, 100, this) );
    layout->addWidget(editPortSrc);

    editPortDest = new QLineEdit();
    editPortDest->setPlaceholderText("Port destination");
    editPortSrc->setValidator( new QIntValidator(0, 100, this) );
    layout->addWidget(editPortDest);

    checkAck = new QCheckBox("Attendre retour (ACK)");
    layout->addWidget(checkAck);

    checkFrag = new QCheckBox("Autoriser fragmentation");
    layout->addWidget(checkFrag);

    editMessage = new QLineEdit();
    editMessage->setPlaceholderText("Message à envoyer");
    layout->addWidget(editMessage);

    envoyerButton = new QPushButton("Envoyer");
    layout->addWidget(envoyerButton);


}

void DialogEnvoi::showForm(Noeud * n1,  Noeud * n2){
    if(n1 && n2){
    editNoeud1->setText(QString::fromStdString(n1->getNom()));
    editNoeud2->setText(QString::fromStdString(n2->getNom()));

    editNoeud1->setToolTip(QString::number(n1->getIdNoeud()));
    editNoeud2->setToolTip(QString::number(n2->getIdNoeud()));
    }
}


void DialogEnvoi::preparenvoi(){
   //Vérifier que les info sont bonnes
    QString errorString;
    QTextStream stream(&errorString);
    stream<< "<h5><b><font color='red'>Veuillez entrer les parameres suivants :</font></b></h5><ul>";


    bool ok = true;
    if(editNoeud1->text().isEmpty()){
        stream<<"<li>Equipement emetteur</li>";
        ok = false;
    }
    if(editNoeud2->text().isEmpty()){
        stream<<"<li>Equipement recepteur</li>";
        ok = false;
    }
    if(editPortSrc->text().isEmpty()){
        stream<<"<li>Numero de port source</li>";
        ok = false;
    }
    if(editPortDest->text().isEmpty()){
        stream<<"<li>Numero de port destinataire</li>";
        ok = false;
    }
    if(editMessage->text().isEmpty()){
        stream<<"<li>Message a envoyer</li>";
        ok = false;
    }

    if(ok){
       Graphe * graphe = Graphe::get();

        //Récuperer les noeuds
        Station* s1 = dynamic_cast<Station*>(graphe->getSommets()[editNoeud1->toolTip().toInt()]);
        Noeud* s2 = dynamic_cast<Station*>(graphe->getSommets()[editNoeud2->toolTip().toInt()]);
        int portsrc =  editPortSrc->text().toInt();
        int portdest = editPortDest->text().toInt();


        bool syn = true;
        bool ack = (checkAck->isChecked() ?  1 : 0);

        int nseq = s1->getNextNumSeq();
        int nack = 0;
        int ipid = nseq + 100;
        bool df = (checkFrag->isChecked() ?  1 : 0);

        Data* sendData = new Data(editMessage->text().toStdString());
        //Préparer l'envoi
        envoyer(s1,  s2 ,  portsrc ,  portdest ,  syn ,  ack ,  nseq ,  nack,  ipid,  df ,  sendData);
        //Signaler que l'envoi est possible
        //if ( sendData)
          //  emit addedData ( sendData);

        s1->getMutexEnvoiOk()->lock();
        s1->getControleur()->setok(true);
        s1->getMutexEnvoiOk()->unlock();

       }else{
       QMessageBox errorbox;
       stream<<"</ul>";
       errorbox.setText(errorString);
       errorbox.exec();
    }

}

void DialogEnvoi::onExitDialog(int)
{/*
    editNoeud1->setText("");
    editNoeud2->setText("");
    editPortSrc->setText("");
    editPortDest->setText("");
    editMessage->setText("");
    checkAck->setChecked(false);
    checkFrag->setChecked(false);*/
    delete this;
}
