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

/*!
 * \class Routeur
 * \brief La classe Routeur représentant un routeur
 */

class Routeur : public Noeud{

public:
    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Routeur
     * Initialise un noeud #Noeud()
     * Génére un #nom automatiquement ( "Station + #idNoeud")
     */
    Routeur();
    /*!
     * \brief Constructeur
     * Constructeur de la classe Routeur,
     * qui permet d'initialiser un routeur avec les paramètres en entrée.
     * \param nom : voir #nom
     * \param idNoeud : voir #idNoeud
     * \param nbPort : voir #nbPort
     */
    Routeur(string nom,int idNoeud,int nbPort);
    /*!
      * \brief Destructeur
      * Destructeur de la classe Routeur
      */
    ~Routeur();
    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * \param nRecepteur : pointeur sur le noeud recepteur
     * \param data : le message à envoyer de type Data
     */
    void envoyerMessage(Noeud * Nrecepteur , string message);
};

#endif
