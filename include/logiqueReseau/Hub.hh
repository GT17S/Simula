#ifndef HUB_H
#define HUB_H

/*!
 * \file Hub.h
 * \brief Hub
 * \author Nadjibian
 * \version 0.1
 */

#include "../../include/logiqueReseau/Noeud.hh"
#include<string>
#include <vector>


/*!
 * \class Hub
 * \brief La classe Hub hérite de la classe Noeud .
 */

class Hub: public Noeud{
private:
std::vector<Noeud*> tableNoeuds; /*!< Les noeuds connecte au hub*/
public:
   /*!
   * \brief Construceur
   *  Constructeur de la classe Noeud
   * \param nom : nom du hub
   * \param idNoeud : identificateur du hub
   * \param nbPort : nombre de ports du hub
   */
    Hub(std::string nom,int idNoeud,int nbPort);

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
     * \brief getTableNoeuds
     * \return Les noeuds connecte au hub (vector<Noeud*>)
     */
    std::vector<Noeud*>  getTableNoeuds(){return tableNoeuds;}

    /*!
     * \brief setTableNoeuds
     * Modifier Les noeuds connecte au hub
     * \param noeuds : Les noeuds (std::vector<Noeud*>)
     */
    void setTableNoeuds(std::vector<Noeud*> noeuds);

    /*!
     * \brief setTableNoeuds
     * Modifier Les noeuds connecte au hub
     * \param noeuds : Le noeud (Noeud)
     */
    void setTableNoeuds(Noeud* noeud);
    void envoyerMessage(Noeud *nRecepteur, std::string message);


    /*!
     * \brief envoyerBroadCast
     * Méthode qui permet d'envoyer un message à tous les noeuds connecte au hub
     * \param message : le message à envoyer de type message
     * change string vers data
     */
    void envoyerBroadCast(std::string message);


};
#endif
