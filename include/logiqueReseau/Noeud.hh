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
#include <typeinfo>
#include "InterfaceFE.hh"
#include "Cable.hh"

using std::string;
using std::vector;


#ifndef ROUTE_H
#define ROUTE_H
/*!
 * \struct Route
 *  Struct qui représente une ligne dans la table de routage
 */
struct Route {
    string adresseReseau; /*!< Adresse sous réseau */
    string masque;  /*!< masque sous réseau*/
    string passerelle; /*!< adresse de passerelle*/
};
#endif

class InterfaceFE;
class Cable;
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
  vector<InterfaceFE*> interfaces; /*< Liste des interfaces réseaux du noeud*/
  vector<string> fileDattente; /*< File d'attente des données */
  vector<Route*> tableRoutage; /*!< Table de routage */


public:
    /*!
     * \brief Construceur
     *  Constructeur de la classe Noeud
     *  Initialise les #interfaces selon le nombre de ports #nbPort.
     *  Initialise la file d'attente des données #fileDattente.
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
     * Initialise une interface réseau
     * Initialise la file d'attente des données #fileDattente.
     */
    Noeud();

    /*!
     * \brief Destructeur
     * Destructeur de la classe noeud
     * Supprime #idNoeud de la liste des identificateurs.
     * Destruction des #interfaces
     * Destruction de la file d'attente (#fileDattente).
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
     * \brief getInterfaces
     * \return voir #interfaces
     */
    vector<InterfaceFE*> getInterfaces(){return interfaces;}
    /*!
     * \brief getInterface
     * Retourne un pointeur sur l'interface dans #interfaces,
     *  sinon retourne pointeur null
     * \param id : Numero de l'interface dans #interfaces
     * \return pointeur sur #InterfaceFE
     */
    InterfaceFE * getInterface(int id);
    /*!
     * \brief getInterface
     * \param cable : cable lié à l'interface
     * \return L'interface lié à le cable en entrée
     */
    InterfaceFE * getInterface(Cable * cable);

    /*!
     * \brief getTableRoutage
     * \return  #voir tableRoutage
     */
    vector<Route*>  getTableRoutage(){return tableRoutage;}

    /*!
     * \brief setNom
     * Modifier le nom du noeud, #nom
     * \param nom : nom du noeud (string)
     */
    void setNom(string nom);
    /*!
     * \brief setIdNoeud
     * Modifier l'identificateur du noeud, #idNoeud
     * Vérifier si #idNoeud est unique dans #idsNoeuds.
     * Sinon attribuer automatiquement un ID unique.
     * \param idNoeud : id noeud.
     */
    void setIdNoeud(int idNoeud);
    /*!
     * \brief setNbPort
     * Modifier le nombre de ports du noeud, #nbPort
     * Vérifier l'état des #interfaces.
     * Initialisation des #interfaces si besoin.
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
     * \brief setInterfaces
     * Modifier les #interfaces
     * \param interfaces
     */
    void setInterfaces(vector<InterfaceFE*> interfaces);
    /*!
     * \brief setInterfaces
     * \param interface
     * \deprecated N'est pas utilisée.
     */
    void setInterfaces(InterfaceFE* interface);

    /*!
     * \brief setTableRoutage
     * Modifier la table de routage
     * \param tableRoutage : voir #tableRoutage
     */
    void setTableRoutage(vector<Route*> tableRoutage);
    /*!
     * \brief setTableRoutage
     * Ajouter une route dans la table de routage
     * \param route : voir #Route
     */
    void setTableRoutage(Route* route);

    /*!
     * \brief getPasserelleTableRoutage
     * Retourner l'adresse de passerelle d'une adresse réseau dans la table de routage
     * \param _adresseReseau : voir ::adresseReseau
     * \return voir ::passerelle
     */
    string getPasserelleTableRoutage(string _adresseReseau);
    /*!
     * \brief supprimerRoute
     * Supprimer une route depuis la table de routage
     * \param id : indice de la #Route dans la table de routage
     */
    void supprimerRoute(int id);
    /*!
     * \brief modifierRoute
     * Modifier une route déja existante
     * \param id : indice de la #Route dans la table de routage
     * \param route : voir #Route
     */
    void modifierRoute(int id, Route * route);

    /*!
     * \brief acceptCable
     * Vérifie si le #Noeud peut être lié à un #Cable
     * \param cable : pointeur sur le cable à lié.
     * \param idInterface : numero de port de l'interface dans le noeud.
     * \return vrai si cable lié, faux sinon.
     */
    bool acceptCable(Cable * cable, int idInterface);

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
