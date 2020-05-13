#ifndef STATION_H
#define STATION_H

/*!
 * \file Station.hh
 * \brief Station
 * \author medish
 * \version 0.1
 */

#include <string>
#include <vector>
#include <map>
#include "Noeud.hh"
#include "Graphe.hh"
#include "Congestion.hh"

using std::string;
using std::vector;
using std::multimap;

class Noeud;
class Data;
class InterfaceFE;
class Congestion;
/*!
 * \class Station
 * \brief La classe Station représentant une station (machine).
 */
class Station : public virtual Noeud {
  private:
    string adressePasserelle; /*!< adresse de passerelle de la station*/
    vector<int> numSegmentsEnvoye; /*!< liste des numeros de séquences des segments envoyés */
    Congestion * controleur;
    int numSeq;
    bool isPasserelle;
    multimap<int, Data*> fragments;
public:
    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Station
     * Initialise un noeud #Noeud()
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
     */
    Station(string nom,int idNoeud,int nbPort,
            string adressePasserelle, bool isPasserelle = false);
    /*!
      * \brief Destructeur
      * Destructeur de la classe Station
      */
    ~Station(){}


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

    Congestion * getControleur(){return controleur; }
    int getNumSeq(){return numSeq;}
    int getNextNumSeq();
    bool getIsPasserelle(){return isPasserelle;}
    /*!
     * \brief setPasserelle
     * Modifier l'adresse de passerelle de la station, #adressePasserelle
     * \param adressePasserelle : adresse IP
     */
    void setPasserelle(string adressePasserelle);


    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * \param nRecepteur : pointeur sur le noeud recepteur
     * \param data : le message à envoyer de type Data
     */

    void setControleur(Congestion *c);

    void setNumSeq(int value);

    void setIsPasserelle(bool isPasserelle);
    int  checkFragment(Data* data);
    void envoyerMessage(int key, destination dest);
    void recevoirMessage(int key, int dest_i, destination dest);


};

#endif
