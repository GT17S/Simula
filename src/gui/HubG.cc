#include <HubG.hh>

HubG::HubG(EspaceTravail *parent): NoeudG(parent){
    setPixmap(QPixmap(":/ressources/equipements/hub.png"));
}
HubG::~HubG(){}
