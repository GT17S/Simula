#ifndef SWITCH_H
#define SWITCH_H

/*!
 * \file Switch.hh
 * \brief Switch
 * \author Nadjibian
 * \version 0.1
 */

#include "Hub.hh"
#include "Graphe.hh"

using std::string;

class Hub;

/*!
 * \class Switch
 * \brief La classe Switch dérivée de la classe Hub.
 */


class Switch : public virtual Hub {

public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe Switch,
     * qui permet d'initialiser un switch avec les paramètres en entrée.
     * \param nom : voir #nom
     * \param idNoeud : voir #idNoeud
     * \param nbPort : voir #nbPort
     */
    Switch(string nom,int idNoeud,int nbPort);
    /*!
     * \brief Constructeur par défaut
     * Initialise un noeud #Hub()
     * Génére un #nom automatiquement ( "Switch + #idNoeud")
     */
    Switch();

    /*!
     * \brief Destructeur
     * Destructeur de la classe Switch
     */
    ~Switch();

    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * \param nRecepteur : le noeud recepteur
     * \param data : le message à envoyer de type Data
     */
    void envoyerMessage(string message);//change string par data

};

#endif // SWITCH_H
