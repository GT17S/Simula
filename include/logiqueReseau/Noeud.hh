#ifndef NOEUD_H
#define NOEUD_H

/*!
 * \file Noeud.h
 * \brief Noeud (Station, Hub, Switch, Routeur)
 * \author medish
 * \version 0.1
 */

#include <string>
#include <vector>

/*!
 * \class Noeud
 * \brief La classe Noeud représentant un noeud.
 */

class Noeud {
protected:

  std::string nom; /*!< Nom du noeud */
  int idNoeud;  /*< Identificateur du noeud */
  int nbPort; /*< Nombre de ports du noeud */
  std::vector<std::string> fileDattente; /*< File d'attente des données */
public:
    /*!
     * \brief Construceur
     *  Constructeur de la classe Noeud
     * \param nom : nom du noeud
     * \param idNoeud : identificateur du noeud
     * \param nbPort : nombre de ports du noeud
     */
    Noeud(std::string nom, int idNoeud, int nbPort);

    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Noeud
     */
    Noeud();

    /*!
     * \brief Destructeur
     * Destructeur de la classe noeud
     */
    virtual ~Noeud();

    /*!
     * \brief getNom
     * \return Le nom du noeud (string)
     */
    std::string getNom(){return nom;}
    /*!
     * \brief getIdNoeud
     * \return Identificateur du noeud (int)
     */
    int getIdNoeud(){return idNoeud;}
    /*!
     * \brief getNbPort
     * \return Nombre de ports du noeud (int)
     */
    int getNbPort(){return nbPort;}
    /*!
     * \brief getFileDattente
     * \return File d'attente des données du noeud (vector)
     */
    std::vector<std::string> getFileDattente(){return fileDattente;}
    /*!
     * \brief setNom
     * Modifier le nom du noeud
     * Vérifier si le nom est unique.
     * \param nom : nom du noeud (string) doit être unique
     */
    void setNom(std::string nom);
    /*!
     * \brief setIdNoeud
     * Modifier l'identificateur du noeud
     * Vérifier si id du noeud est unique.
     * \param idNoeud : id du noeud (int) doit être unique.
     */
    void setIdNoeud(int idNoeud);
    /*!
     * \brief setNbPort
     * Modifier le nombre de ports du noeud
     * \param int nbPort : nombre de ports du noeud (int)
     */
    void setNbPort(int nbPort);
    /*!
     * \brief setFileDattente
     * Modifier la file d'attente des données
     * Ajouter à la fin de la file une données.
     * \param data : la donnée à ajouter.
     */
    void setFileDattente(std::string data);
    /*!
     * \brief setFileDattente
     * Modifier la file d'attente des données déja existante
     * \param file : File d'attente des données
     */
    void setFileDattente(std::vector<std::string> file);

    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * ( Redéfinie dans la classe dérivée)
     * \param nRecepteur : le noeud recepteur
     * \param data : le message à envoyer de type Data
     */
    virtual  void envoyerMessage(Noeud * nRecepteur, std::string data)=0;
};

#endif
