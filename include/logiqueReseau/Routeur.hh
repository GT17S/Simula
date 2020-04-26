#ifndef ROUTEUR_H
#define ROUTEUR_H

/*!
 * \file Noeud.hh
 * \brief Station
 * \author medish
 * \version 0.1
 */


#ifndef ROUTE_H
#define ROUTE_H
struct Route {
    std::string adresseReseau;
    std::string masque;
    std::string passerelle;
};
#endif


#include <string>
#include <vector>
#include "Noeud.hh"
#include "InterfaceFE.hh"

using std::string;
using std::vector;



class InterfaceFE;
class Noeud;

class Routeur : public Noeud{
private:
  vector<Noeud*> tableNoeuds /*!< Liste des noeuds connectés*/;
  vector<Route*> tableRoutage; /*!< Table de routage */
  vector<InterfaceFE*> tableInterfaces; /*!< Liste des interfaces réseaux*/


public:
    Routeur();
    Routeur(String nom,int idNoeud,int nbPort,vector<InterfaceFE*>);
    ~Routeur();

    vector<Noeud*>  getTableNoeuds(){return tableNoeuds;}
    vector<Route*>  getTableRoutage(){return tableRoutage;}
    vector<InterfaceFE*>  getTableInterface(){return tableInterfaces;}

    void setTableNoeuds(vector<Noeud*>);
    void setTableNoeuds(Noeud*);
    void setTableRoutage(vector<Route*>);
    void setTableRoutage(Route*);
    void setTableInterface(vector<InterfaceFE*>);
    void setTableInterface(InterfaceFE*);
    void envoyerMessage(Noeud * Nrecepteur , string message);
};

#endif
