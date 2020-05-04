#ifndef __CONGESTION_OUTILS_H__
#define __CONGESTION_OUTILS_H__

#include <cmath>

#include "Congestion.hh"
<<<<<<< HEAD
#include "Data.hh"
#include "Graphe.hh"
=======
#include "../traitementTcpIp/Data.hh"
#include "../logiqueReseau/Graphe.hh"
>>>>>>> CongestionOutils

const float baseRTT = 200.0f;
const float alpha = 0.125f;

float CalculRTT(Congestion *g);
float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data);

#endif
