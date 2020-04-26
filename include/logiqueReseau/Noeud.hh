#ifndef NOEUD_H
#define NOEUD_H

/*!
 * \file Noeud.hh
 * \brief Noeud (Station, Hub, Switch, Routeur)
 * \author medish
 * \version 0.1
 */

#include <algorithm>
#include <string>
#include <vector>


using std::string;
using std::vector;

/*!
 * \class Noeud
 * \brief La classe Noeud représentant un noeud.
 */

class Noeud {
protected:
  static vector<int> idsNoeuds; /*!< Liste des identificateurs */

  string nom; /*!< Nom du noeud */
  int idNoeud;  /*< Identificateur du noeud */
  int nbPort; /*< Nombre de ports du noeud */
  vector<string> fileDattente; /*< File d'attente des données */
public:
    /*!
     * \brief Construceur
     *  Constructeur de la classe Noeud
     *  Initialise une liste vide de file d'attente des données #fileDattente.
     * \param nom : voir #nom
     * \param idNoeud : voir #idNoeud
     * \param nbPort : voir #nbPort
     */
    Noeud(string nom, int idNoeud, int nbPort);

    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Noeud
     * Initialise #idNoeud automatiquement.
     * Initialise #nbPort à 1 #nbPort.
     * Initialise une liste vide de file d'attente des données #fileDattente.
     */
    Noeud();

    /*!
     * \brief Destructeur
     * Destructeur de la classe noeud
     * Supprime #idNoeud de la liste des identificateurs.
     */
    virtual ~Noeud();

    /*!
     * \brief getNom
     * \return voir #nom
     */
    string getNom(){return nom;}
    /*!
     * \brief getIdNoeud
     * \return voir #idNoeud
     */
    int getIdNoeud(){return idNoeud;}
    /*!
     * \brief getNbPort
     * \return voir #nbPort
     */
    int getNbPort(){return nbPort;}
    /*!
     * \brief getFileDattente
     * \return voir #fileDattente
     */
    vector<string> getFileDattente(){return fileDattente;}
    /*!
     * \brief setNom
     * Modifier le nom du noeud, #nom
     * \param nom : nom du noeud (string)
     */
    void setNom(string nom);
    /*!
     * \brief setIdNoeud
     * Modifier l'identificateur du noeud, #idNoeud
     * Vérifier si id du noeud est unique.
     * Sinon attribuer automatiquement un ID unique.
     * \param idNoeud : id du noeud (int) doit être unique.
     */
    void setIdNoeud(int idNoeud);
    /*!
     * \brief setNbPort
     * Modifier le nombre de ports du noeud, #nbPort
     * Vérifier si entier positive.
     * \param int nbPort : nombre de ports du noeud (int)
     */
    void setNbPort(int nbPort);
    /*!
     * \brief setFileDattente
     * Modifier la file d'attente des données, #fileDattente
     * Verifier si la donnée existe déja.
     * Ajouter à la fin de la file une donnée.
     * \param data : la donnée à ajouter.
     */
    void setFileDattente(string data);
    /*!
     * \brief setFileDattente
     * Modifier la file d'attente des données déja existante, #fileDattente
     * \param file : File d'attente des données
     */
    void setFileDattente(vector<string> file);

    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * ( Redéfinie dans la classe dérivée)
     * \param nRecepteur : pointeur sur le noeud recepteur
     * \param data : le message à envoyer de type Data
     */
    virtual  void envoyerMessage(Noeud * nRecepteur, string data)=0;
};

#endif
