#ifndef ROUTEUR_H
#define ROUTEUR_H

/*!
 * \file Routeur.hh
 * \brief Routeur
 * \author medish
 * \version 0.1
 */


#include <string>
#include <vector>
#include "Noeud.hh"

using std::string;
using std::vector;


class Noeud;

class Routeur : public Noeud{

public:
    Routeur();
    Routeur(string nom,int idNoeud,int nbPort);
    ~Routeur();

    void envoyerMessage(Noeud * Nrecepteur , string message);
};

#endif
