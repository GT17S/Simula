#ifndef ROUTEUR_H
#define ROUTEUR_H

/*!
 * \file Noeud.hh
 * \brief Station
 * \author medish
 * \version 0.1
 */




#include <string>
#include <vector>
#include "Noeud.hh"
using std::string;
using std::vector;


#ifndef ROUTE_H
#define ROUTE_H
struct Route {
    string adresseReseau;
    string masque;
    string passerelle;
};
#endif


class Noeud;

class Routeur : public Noeud{
private:
  vector<Route*> tableRoutage; /*!< Table de routage */

public:
    Routeur();
    Routeur(string nom,int idNoeud,int nbPort);
    ~Routeur();

    vector<Route*>  getTableRoutage(){return tableRoutage;}

    void setTableRoutage(vector<Route*>);
    void setTableRoutage(Route*);
    void envoyerMessage(Noeud * Nrecepteur , string message);
};

#endif
