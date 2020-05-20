#include "StationG.hh"

StationG::StationG(EspaceTravail *parent): NoeudG(parent){
   setPixmap(QPixmap(":/ressources/equipements/station.png"));
}

StationG::~StationG(){}
