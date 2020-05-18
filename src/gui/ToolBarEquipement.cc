#include "ToolBarEquipement.hh"




ToolBarEquipement::ToolBarEquipement(EspaceTravail * _espaceTravail){
    espaceTravail = _espaceTravail;
    createButtons();
    createSignals();
    createShortcuts();
}	

void ToolBarEquipement::createButtons(){
    //this->setStyleSheet("background-color: pink");
    this->setMinimumSize(50,430);
    this->setMaximumWidth(100);
    this->setOrientation(Qt::Vertical);
    this->setObjectName("equiBarMain");
    //Creer les boutons

    QToolBar * hbar = new QToolBar;
    hbar->setOrientation(Qt::Horizontal);
    hbar->setObjectName("hbar");
    addWidget(hbar);
    selectAction = new QPushButton(this);
    selectAction->setObjectName("selectAction");
    //selectAction->setProperty("hbar", true);
    selectAction->setToolTip("Selectionner");
    hbar->addWidget(selectAction);

    supprAction = new QPushButton(this);
    supprAction->setObjectName("supprAction");
    //supprAction->setProperty("outilsBar", false);
    supprAction->setToolTip("Supprimer");
    hbar->addWidget(supprAction);
    addSeparator();
    cableAction = new QPushButton(this);
    cableAction->setObjectName("cableAction");
    cableAction->setProperty("outilsBar", false);
    cableAction->setToolTip("Cable");
    QMenu * menu = new QMenu;
    cableDAction = menu->addAction(QIcon(QPixmap("")),"Cable droit");
    cableCAction = menu->addAction(QIcon(QPixmap("")),"Cable croisé");
    cableAction->setMenu(menu);
    //exportButton->setPopupMode(QToolButton::MenuButtonPopup);
    addWidget(cableAction);

    stationAction = new QPushButton(this);
    stationAction->setObjectName("stationAction");
    stationAction->setProperty("outilsBar", false);
    stationAction->setToolTip("Station");
    addWidget(stationAction);

    routeurAction = new QPushButton(this);
    routeurAction->setObjectName("routeurAction");
    routeurAction->setProperty("outilsBar", false);
    routeurAction->setToolTip("Routeur");
    addWidget(routeurAction);

    hubAction = new QPushButton(this);
    hubAction->setObjectName("hubAction");
    hubAction->setProperty("outilsBar", false);
    hubAction->setToolTip("Hub");
    addWidget(hubAction);

    switchAction = new QPushButton(this);
    switchAction->setObjectName("switchAction");
    switchAction->setProperty("outilsBar", false);
    switchAction->setToolTip("Switch");
    addWidget(switchAction);

}

void ToolBarEquipement::createSignals(){
    //Mapper le 4 clicked vers
    QSignalMapper* mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(ajouterNoeud(int)));

    connect(cableAction, SIGNAL(clicked()), this, SLOT(ajouterCable()));
    connect(selectAction, SIGNAL(clicked()), this, SLOT(selectItem()));
    connect(supprAction, SIGNAL(clicked()), this, SLOT(supprimerEquipement()));
    mapper->setMapping(routeurAction, 1);
    mapper->setMapping(hubAction, 2);
    mapper->setMapping(stationAction, 3);
    mapper->setMapping(switchAction, 4);


    connect(routeurAction, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(hubAction, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(stationAction, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(switchAction, SIGNAL(clicked()), mapper, SLOT(map()));


}

void ToolBarEquipement::createShortcuts(){
    selectAction->setShortcut(Qt::Key_Escape);
    supprAction->setShortcut(QKeySequence::Delete);
}

void ToolBarEquipement::selectItem(){
    espaceTravail->setMode(SELECT_MODE);
}

void ToolBarEquipement::ajouterCable(){
   auto s  = this->parent();
   simulaGui* ss = dynamic_cast<simulaGui*>(s);
   auto ss2 = dynamic_cast<EspaceTravail*>(ss->getMainlayout()->itemAtPosition(1,1)->widget());
   assert(ss && ss2);  
  // ss2->addCatPos();
}

void ToolBarEquipement::ajouterNoeud(int n){
   auto s  = this->parent();
   simulaGui* ss = dynamic_cast<simulaGui*>(s);
   auto ss2 = dynamic_cast<EspaceTravail*>(ss->getMainlayout()->itemAtPosition(1,1)->widget());
   assert(ss && ss2); 

    switch(n){
    case 1:{ //Routour
                //NoeudG* tmpRouteur = new RouteurG(ss2->getScene());
               // ss2->addNoeud(new RouteurG(ss2->getScene()));
                espaceTravail->setMode(ROUTEUR_MODE);
                break;
            }
            case 2:{//
                //ss2->addNoeud(new HubG(ss2->getScene()));
                espaceTravail->setMode(HUB_MODE);
                break;
            }
            case 3:{
                //NoeudG* tmpStation = new StationG(ss2->getScene());
                //ss2->addNoeud(new StationG(ss2->getScene()));
                espaceTravail->setMode(STATION_MODE);
                break;
            }
            case 4:{
                 //ss2->addNoeud(new SwitchG(ss2->getScene()));
                 espaceTravail->setMode(SWITCH_MODE);
                break;
            }
       default: break;
    }
}

 void ToolBarEquipement::supprimerEquipement(){
      espaceTravail->setMode(DELETE_MODE);
 }
