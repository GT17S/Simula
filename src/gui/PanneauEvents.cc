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
    evenements->setStyleSheet("border-radius : 10px;background :#f0c4c2;font-weight: bold; color: red;font: 18pt");

    timerSimulation=new QLCDNumber(this);
    timerSimulation->setDigitCount(8);
    timerSimulation->setSegmentStyle(QLCDNumber::Flat);
    timerSimulation->setStyleSheet("border :none;");
    timerSimulation->setMinimumHeight(30);
    timerSimulation->display(QTime(0,0).toString("hh:mm:ss"));
    layout.addWidget(timerSimulation);

    layout.addWidget(treeview);
    treeview->setColumnCount(1);
    treeview->setColumnWidth(0, 500);
    QStringList ColumnNames;
    ColumnNames << "Équipements";
    treeview->setHeaderLabels(ColumnNames);

    clear=new QPushButton("Effacer événements ");
    layout.addWidget(clear);

    connect(clear,SIGNAL(clicked()),this,SLOT(supItems()));
}

void PanneauEvents::supItems(){
    for(Noeud *n: Graphe::getSommets()){
       QTreeWidgetItem * tree=  n->getParent()->getTreeItem();

               foreach(auto i, tree->takeChildren()) delete i;
    }

}
void PanneauEvents::afftime(){

    timerSimulation->display(gSimulation::getTime()->toString("hh:mm:ss"));

}

PanneauEvents::~PanneauEvents(){

}
void PanneauEvents::setTreeview(QTreeWidget *value)
{
    treeview = value;
}

void PanneauEvents::addRoot(QTreeWidgetItem *treeIte ,QString nom){
    treeIte->setText(0,nom);
    treeview->addTopLevelItem(treeIte);
}



void PanneauEvents::addCh(QTreeWidgetItem *parent, QString nom){
    parent->setExpanded( true );
    QTreeWidgetItem *item1=new QTreeWidgetItem();
    parent->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    item1->setText(0,gSimulation::getTime()->toString()+" "+nom);
    parent->addChild(item1);


}


