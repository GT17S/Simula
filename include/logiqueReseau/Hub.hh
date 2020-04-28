#ifndef HUB_H
#define HUB_H

/*!
 * \file Hub.h
 * \brief Hub
 * \author Nadjibian
 * \version 0.1
 */

#include <string>
#include "Noeud.hh"

using std::string;

/*!
 * \class Hub
 * \brief La classe Hub hérite de la classe Noeud .
 */

class Hub: public Noeud{

public:
   /*!
   * \brief Construceur
   *  Constructeur de la classe Noeud
   * \param nom : nom du hub
   * \param idNoeud : identificateur du hub
   * \param nbPort : nombre de ports du hub
   */
    Hub(string nom,int idNoeud,int nbPort);

    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Hub
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
    void envoyerMessage(Noeud *nRecepteur, string message);


    /*!
     * \brief envoyerBroadCast
     * Méthode qui permet d'envoyer un message à tous les noeuds connecte au hub
     * \param message : le message à envoyer de type message
     * change string vers data
     */
    void envoyerBroadCast(string message);


};
#endif
