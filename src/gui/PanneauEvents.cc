#include "PanneauEvents.hh"
#include "gSimulation.hh"
using namespace std;
#include "QDebug"
PanneauEvents::PanneauEvents(){
    setMinimumSize(100,410);
    setMaximumWidth(350);
    this->setLayout(&layout);
    evenements=new QLabel(this);
    evenements->setText("Evenements");
    layout.addWidget(evenements);
    evenements->setAlignment(Qt::AlignHCenter);
    evenements->setStyleSheet("font-weight: bold; color: red;font: 15pt");

    timerSimulation=new QLCDNumber(this);
    timerSimulation->setDigitCount(8);
    timerSimulation->setSegmentStyle(QLCDNumber::Flat);
    layout.addWidget(timerSimulation);
    timerSimulation->setMinimumHeight(30);
    txt=new QTextEdit(this);
    txt->setReadOnly(true);
    //txt->setEnabled(false);
    layout.addWidget(txt);
    txt->setStyleSheet(QString::fromUtf8("background-color: rgb(122, 122, 122);"));
    txt->setText(gSimulation::getTime()->toString("hh:mm:ss")+"  Debut de sumulation");

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
