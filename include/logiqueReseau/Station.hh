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
#include "InterfaceFE.hh"

/*!
 * \class Station
 * \brief La classe Station représentant une station (machine).
 */
class Station : public Noeud {
  private:
    InterfaceFE interfacePc; /*!< interface réseau de la station */
    std::string adressePasserelle; /*!< adresse de passerelle de la station*/
    std::vector<int> numSegmentsEnvoye; /*!< liste des numeros de séquences des segments envoyés */
    //Congestion controleur;
public:
    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Station
     */
    Station();
    /*!
     * \brief Constructeur
     * Constructeur de la classe Station, qui permet d'initialiser une station
     * \param nom : nom de la station (string)
     * \param idNoeud : id de la station (int)
     * \param nbPort : nombre de ports de la station (par défaut = 1)
     * \param adressePasserelle : adresse de passerelle de la station
     * \param interfacePc : interface réseau de la station
     */
    Station(std::string nom,int idNoeud,int nbPort = 1,
            std::string adressePasserelle, InterfaceFE interfacePc);
    /*!
      * \brief Destructeur de la classe Station
      */
    ~Station();

    /*!
     * \brief getInterfacePc
     * \return interface réseau de la station
     */
    InterfaceFE getInterfacePc(){return interfacePc;}
    /*!
     * \brief getPasserelle
     * \return adresse de passerelle de la station
     */
    std::string getPasserelle(){return adressePasserelle;}
    /*!
     * \brief getNumSegmentsEnvoye
     * \return les numeros de séquences des segments envoyés
     */
    std::vector<int> getNumSegmentsEnvoye(){return numSegmentsEnvoye;}

    /*!
     * \brief setInterfacePc
     * Modifier l'interface réseau de la station
     * \param interfacePc : interface réseau
     */
    void setInterfacePc(InterfaceFE interfacePc);
    /*!
     * \brief setPasserelle
     * Modifier l'adresse de passerelle de la station
     * \param adressePasserelle : adresse de passerelle de la station
     */
    void setPasserelle(std::string adressePasserelle);
    /*!
     * \brief setNumSegmentsEnvoye
     *  Modifier le tableau des numeros des segments envoyés
     *  Ajouter à la fin, un numero de séquence de segment
     * \param nSegment : numero de séquence de segment envoyé
     */
    void setNumSegmentsEnvoye(int nSegment);

    /*!
     * \brief setNumSegmentsEnvoye
     * Modifier un tableau des numeros des séquences de segments envoyés qui est déja existant.
     * \param numSegmentsEnvoye : liste des numéros de séquences de segments envoyés.
     */
    void setNumSegmentsEnvoye(std::vector<int> numSegmentsEnvoye);

    /*!
     * \brief envoyerMessage
     * Méthode qui permet d'envoyer un message à un noeud
     * \param nRecepteur : pointeur sur le noeud recepteur
     * \param data : le message à envoyer de type Data
     */
    void envoyerMessage(Noeud * Nrecepteur, Data message);
};

#endif
