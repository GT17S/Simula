#include "gSimulation.hh"
#include "QStandardItem"
#include "panneauOutils.hh"
#include "QHeaderView"

using namespace std;
#include "QDebug"
//QTextEdit *PanneauEvents::txt;
QLCDNumber *PanneauEvents::timerSimulation;
QTreeWidget *PanneauEvents::treeview;


PanneauEvents::PanneauEvents(){
    treeview=new QTreeWidget();
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
    /*-
    txt=new QTextEdit(this);
    txt->setReadOnly(true);
    //txt->setEnabled(false);
    layout.addWidget(txt);
    txt->setStyleSheet(QString::fromUtf8("background-color: rgb(122, 122, 122);"));
    txt->setText(gSimulation::getTime()->toString("hh:mm:ss")+"  Debut de sumulation");
*/
    layout.addWidget(treeview);
    treeview->setColumnCount(1);
    treeview->setColumnWidth(0, 500);
    QStringList ColumnNames;
    ColumnNames << "Équipements";

    treeview->setHeaderLabels(ColumnNames);
    //treeview->setStyleSheet("background-color: red");//background
}
void PanneauEvents::afftime(){

    timerSimulation->display(gSimulation::getTime()->toString("hh:mm:ss"));

}

PanneauEvents::~PanneauEvents(){

}
/*
void PanneauEvents::affichage(QString text){
    txt->append(gSimulation::getTime()->toString()+" "+text);

}
*/
void PanneauEvents::setTreeview(QTreeWidget *value)
{
    treeview = value;
}

void PanneauEvents::addRoot(QTreeWidgetItem *pf ,QString nom){
    //QTreeWidgetItem *pf=new QTreeWidgetItem(treeview);
    pf->setText(0,nom);
    treeview->addTopLevelItem(pf);
}



void PanneauEvents::addCh(QTreeWidgetItem *parent, QString nom){
    QTreeWidgetItem *item=new QTreeWidgetItem();
    item->setText(0,gSimulation::getTime()->toString()+" "+nom);
    parent->addChild(item);
}


