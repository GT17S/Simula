#include "HubG.hh"

HubG::HubG(EspaceTravail *_parent): NoeudG(_parent){
    setPixmap(QPixmap(":/ressources/equipements/hub.png"));
}
HubG::~HubG(){}
