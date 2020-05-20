#include <StationG.hh>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

StationG::StationG(EspaceTravail *parent): NoeudG(parent){
   setPixmap(QPixmap(":/ressources/equipements/station.png"));
}

StationG::~StationG(){}
