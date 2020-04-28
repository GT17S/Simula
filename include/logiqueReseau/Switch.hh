#ifndef SWITCH_H
#define SWITCH_H

/*!
 * \file Switch.h
 * \brief Switch
 * \author Nadjibian
 * \version 0.1
 */

#include "../include/logiqueReseau/Hub.hh"


using std::string;

/*!
 * \class Switch
 * \brief La classe Switch hérite de la classe Hub.
 */



class Switch:public Hub
{
public:

    /*!
    * \brief Construceur
    *  Constructeur de la classe Switch
    * \param nom : nom du Switch
    * \param idNoeud : identificateur du Switch
    * \param nbPort : nombre de ports du Switch
    */
    Switch(string nom,int idNoeud,int nbPort);
    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Switch
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
    void envoyerMessage(Noeud *nRecepteur, string message);//change string par data

};

#endif // SWITCH_H
