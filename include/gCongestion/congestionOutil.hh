#ifndef __CONGESTION_OUTILS_H__
#define __CONGESTION_OUTILS_H__

#include <cmath>

#include "Data.hh"
#include "Graphe.hh"

class Congestion;
class Graphe;

const float baseRTT = 200.0f; /*!< Valeur du RTT définie à l'initialisation*/
const float alpha = 0.125f; /*!< Cconstante alpha definie dans [RFC2098]*/
/*!
         * \brief Actualise le RTT de chaque gestionnaire de congestion à chaque envoie de message
         * Algorithme de Karn pour le calcul du RTT
         * \param g le gestionnaire de congestion à modifier
*/

float CalculRTT(Congestion *g);
/*!
         * \brief Calcule la latence de façon dynamique
         * Applique l'algorithme de latence dynamique sur l'émetteur 
         * \param congestion le controleur de congestion résponsable
         * \param graphe qui représente le réseau
         * \param data la donnée envoyée qui modifie la latence
*/

float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data);

#endif


