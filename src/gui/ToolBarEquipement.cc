#include "ToolBarEquipement.hh"

ToolBarEquipement::ToolBarEquipement(): QToolBar(){

	this->setStyleSheet("background-color: yellow");
	this->setMinimumSize(50,430);
    this->setMaximumWidth(100);
}


void ToolBarEquipement::showInfos(){return;}
