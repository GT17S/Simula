#ifndef HUB_H
#define HUB_H

/*!
 * \file Hub.hh
 * \brief Hub
 * \author Nadjibian
 * \version 0.1
 */

#include <string>
#include "Noeud.hh"

class Data;
using std::string;

/*!
 * \class Hub
 * \brief La classe Hub dérivée de la classe Noeud .
 */

class Hub: public Noeud{

public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe HUB,
     * qui permet d'initialiser un Hub avec les paramètres en entrée.
     * \param nom : voir #nom
     * \param idNoeud : voir #idNoeud
     * \param nbPort : voir #nbPort
     */
    Hub(string nom,int idNoeud,int nbPort);

    /*!
     * \brief Constructeur par défaut
     * Initialise un noeud #Noeud()
     * Génére un #nom automatiquement ( "Hub + #idNoeud")
     */
    Hub();

    /*!
     * \brief Destructeur
     * Destructeur de la classe Hub
     */
    ~Hub();

    /*!
     * \brief envoyerMessage
     * \param nRecepteur
     * \param message
     */
    void envoyerMessage(Data * data);
    void recevoirMessage(int interface, Data * data);


    /*!
     * \brief envoyerBroadCast
     * Méthode qui permet d'envoyer un message à tous les noeuds connecte au hub
     * \param message : le message à envoyer de type message
     * change string vers data
     */
    void envoyerBroadCast(string message);


};
#endif
