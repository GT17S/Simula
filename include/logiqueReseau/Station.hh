#ifndef STATION_H
#define STATION_H

/*!
 * \file Noeud.hh
 * \brief Station
 * \author medish
 * \version 0.1
 */

#include <string>
#include <vector>
#include "Noeud.hh"
#include "../../include/logiqueReseau/InterfaceFE.hh"


using std::string;
using std::vector;

class InterfaceFE;
class Noeud;

/*!
 * \class Station
 * \brief La classe Station représentant une station (machine).
 */
class Station : public Noeud {
  private:
    InterfaceFE interfacePc; /*!< interface réseau de la station */
    string adressePasserelle; /*!< adresse de passerelle de la station*/
    vector<int> numSegmentsEnvoye; /*!< liste des numeros de séquences des segments envoyés */
    //Congestion controleur;
public:
    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Station
     * Initialise un noeud #Noeud()
     * Initialise une interface #InterfaceFE()
     * Génére un #nom automatiquement ( "Station + #idNoeud")
     * Initialise #adressePasserelle à #DEFAULT_IP
     * Initialise #numSegmentsEnvoye vide
     *
     */
    Station();
    /*!
     * \brief Constructeur
     * Constructeur de la classe Station,
     * qui permet d'initialiser une station avec les paramètres en entrée.
     * \param nom : voir #nom
     * \param idNoeud : voir #idNoeud
     * \param nbPort : voir #nbPort
     * \param adressePasserelle : voir #adressePasserelle
     * \param interfacePc : voir #interfacePc
     */
    Station(string nom,int idNoeud,int nbPort,
            string adressePasserelle, InterfaceFE interfacePc );
    /*!
      * \brief Destructeur
      * Destructeur de la classe Station
      */
    ~Station(){}

    /*!
     * \brief getInterfacePc
     * \return voir #interfacePc
     */
    InterfaceFE getInterfacePc(){return interfacePc;}
    /*!
     * \brief getPasserelle
     * \return voir #adressePasserelle
     */
    string getPasserelle(){return adressePasserelle;}
    /*!
     * \brief getNumSegmentsEnvoye
     * \return voir #numSegmentsEnvoye
     */
    vector<int> getNumSegmentsEnvoye(){return numSegmentsEnvoye;}

    /*!
     * \brief setInterfacePc
     * Modifier l'interface réseau de la station
     * \param interfacePc : interface réseau
     */
    void setInterfacePc(InterfaceFE interfacePc);
    /*!
     * \brief setPasserelle
     * Modifier l'adresse de passerelle de la station, #adressePasserelle
     * \param adressePasserelle : adresse IP
     */
    void setPasserelle(string adressePasserelle);
    /*!
     * \brief setNumSegmentsEnvoye
     *  Modifier le tableau des numeros des segments envoyés, #numSegmentsEnvoye
     *  Vérifier si nSegment n'existe pas déja0
     *  Ajouter à la fin, un numero de séquence de segment
     * \param nSegment : numero de séquence de segment envoyé
     */
    void setNumSegmentsEnvoye(int nSegment);

    /*!
     * \brief setNumSegmentsEnvoye
     * Modifier un tableau des numeros des séquences de segments envoyés qui est déja existant.
     * #numSegmentsEnvoye
     * \param numSegmentsEnvoye : liste des numéros de séquences de segments envoyés.
     */
    void setNumSegmentsEnvoye(vector<int> numSegmentsEnvoye);

    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * \param nRecepteur : pointeur sur le noeud recepteur
     * \param data : le message à envoyer de type Data
     */
    void envoyerMessage(Noeud * Nrecepteur, string message);
};

#endif
