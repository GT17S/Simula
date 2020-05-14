#include "PanneauEvents.hh"
#include "gSimulation.hh"
using namespace std;
#include "QDebug"
PanneauEvents::PanneauEvents(){
    txt=new QTextEdit(this);
    txt->setReadOnly(true);
    //txt->setEnabled(false);
    txt->setStyleSheet(QString::fromUtf8("background-color: rgb(122, 122, 122);"));
    txt->setGeometry(0,70,300,350);

    evenements=new QLabel(this);

    evenements->setText("Evenements");
   txt->setText(gSimulation::getTime()->toString("hh:mm:ss")+"  Debut de sumulation");
    evenements->setGeometry(80,-15,120,50);
    evenements->setStyleSheet("font-weight: bold; color: red;font: 15pt");
    timerSimulation=new QLCDNumber(this);
    timerSimulation->setSegmentStyle(QLCDNumber::Flat);
    timerSimulation->setGeometry(40,25,200,40);
    txt->append(gSimulation::getTime()->toString("hh:mm:ss")+"  Events 1");

}
void PanneauEvents::afftime(){

timerSimulation->display(gSimulation::getTime()->toString("hh:mm:ss"));

}

PanneauEvents::~PanneauEvents(){

}

void PanneauEvents::affichage(QString text){
    txt->append(gSimulation::getTime()->toString()+" "+text);

}

QTextEdit *PanneauEvents::txt;
QLCDNumber *PanneauEvents::timerSimulation;
