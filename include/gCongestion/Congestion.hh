#ifndef CONGESTION_H
#define CONGESTION_H

/*!
 * \file Noeud.hh
 * \brief Congestion
 * \author Nadjibian
 * \version 0.1
 */

#include <string>
#include <vector>

/*!
 * \class Congestion
 * \brief La classe Congestion représentant un contrôleur de congestion .
 */


class Congestion{
private:
    int cwnd;/*!< La taille de la fentre de congestion */
    int ssthresh; /*!< taille maximum de cwnd en mode slow start */
    int cpt;/*!< nombre de fois que cwnd a changé */
    int dernierNumSegment;/*!<  numéro du dernier segment reçu */
    int nbrAcksDuplique;/*!<  Nombre d’ack dupliqués */
    int nbrAcksRecu; /*!<  Nombre de paquets acquittement reçus*/
    int numAckRecu;/*!< Numéro du dernier paquet acquittement reçu*/
    float baseRtt;/*!<  RoundTripTime de valeur prédéfinie*/
    //ajout un nombre pour verfie si nbr seqgemnt recu = total et le remttre a 0 apres
public:
    /*!
     * \brief Constructeur par défaut
     * Constructeur par défaut de la classe Station
     * Initialise tous les attributs de la classe
     */
    Congestion();

    /*!
      * Constructeur par copie de la classe congestion
      * \brief Construceur
      * \param c :contrôleur de Congestion
      */
    Congestion(Congestion & c);


    /*!
     * \brief Destructeur
     * Destructeur de la classe congestion
     */
    ~Congestion();

    /*!
      * \brief getCwnd
      * \return taille de la fentre de congestion (int)
      */
    int getCwnd(){return cwnd;}

    /*!
      * \brief getSsthresh
      * \return taille maximum de cwnd en mode slow start (int)
      */
    int getSsthresh(){return ssthresh;}

    /*!
      * \brief getCpt
      * \return nombre de fois que cwnd a changé (int)
      */
    int getCpt(){return cpt;}
    /*!
      * \brief getDernierNumSegment
      * \return numéro du dernier segment reçu (int)
      */
    int getDernierNumSegment(){return dernierNumSegment;}
    /*!
      * \brief getNbrAcksDuplique
      * \return Nombre d’ack dupliqués (int)
      */
    int getNbrAcksDuplique(){return nbrAcksDuplique;}
    /*!
      * \brief getNbrAcksRecu
      * \return Nombre de paquets acquittement reçus (int)
      */
    int getNbrAcksRecu(){return nbrAcksRecu;}
    /*!
      * \brief getNumAckRecu
      * \return Numéro du dernier paquet acquittement reçu (int)
      */
    int getNumAckRecu(){return nbrAcksRecu;}
    /*!
      * \brief getBaseRtt
      * \return RoundTripTime (int)
      */
    int getBaseRtt(){return baseRtt;}


    /*!
      * \brief setCwnd
      *  Modifier la taille de la fentre de congestion
      *  Vérifier si _cwnd est positive
      * \param _cwnd : taille de la fentre de congestion
      */
    void setCwnd(int _cwnd);
    /*!
      * \brief setSsthresh
      *  Modifier taille maximum de cwnd en mode slow start
      *  Vérifier si _ssthresh est positive
      * \param _ssthresh : taille maximum de cwnd (int)
      */
    void setSsthresh(float _ssthresh);

    /*!
      * \brief setCpt
      *  Modifier nombre de fois que cwnd a changé
      *  Vérifier si _cpt est positive
      * \param _cpt : nombre de fois que cwnd a changé(int)
      */
    void setCpt(int _cpt);

    /*!
      * \brief setDernierNumSegment
      *  Modifier numéro du dernier segment reçu
      *  Vérifier si _dernierNumSegment est positive
      * \param _dernierNumSegment : numéro du dernier segment reçu(int)
      */
    void setDernierNumSegment(int _dernierNumSegment );

    /*!
      * \brief setNbrAcksDuplique
      *  Modifier nombre d’ack dupliqués
      *  Vérifier si _nbrAcksDuplique est positive
      * \param _nbrAcksDuplique : nombre d’ack dupliqués (int)
      */

    void setNbrAcksDuplique(int _nbrAcksDuplique);
    /*!
      * \brief setNbrAcksRecu
      *  Modifier nombre de paquets acquittement reçus
      *  Vérifier si _nbrAcksRecu est positive
      * \param _nbrAcksRecu : nombre de paquets acquittement reçus (int)
      */
    void setNbrAcksRecu(int _nbrAcksRecu);

    /*!
      * \brief setNumAckRecu
      *  Modifier numéro du dernier paquet acquittement reçu
      *  Vérifier si _numAckRecu est positive
      * \param _numAckRecu : numéro du dernier paquet acquittement reçu (int)
      */
    void setNumAckRecu(int _numAckRecu);

    /*!
      * \brief setBaseRtt
      *  Modifier RoundTripTime
      *  Vérifier si _baseRtt est positive
      * \param _baseRtt : RoundTripTime (int)
      */
    void setBaseRtt(int _baseRtt);
    /*!
     * \brief slowStart
     * Méthode : Méthode qui va augmenter la taille de la fenêtre de congestion de une façon exponentielle et augmenter
        le cpt.
     * Vérifier si cwnd supérieur au ssthresh.
     */
    void slowStart();

    /*!
     * \brief fastRecovery
     * Méthode : Méthode qui va décroître la taille de la fenêtre de congestion et le ssthresh
        pour augmenter le compteur
     */
    void fastRecovery();
    /*!
     * \brief congestionAvoidance
     * Méthode : Méthode qui va augmenter la fenêtre de congestion linéairement
     */
    void congestionAvoidance();


    void verifieNumSegment(std::string * segment);
    void verifieNumAck(std::string * ack,std::vector<int> num_seq);
    void fastRetransmission(std::vector<std::string> messages);
    void verifieNbrSegment(std::string * nbr_segment);
    //friend float CalculLatenceDynamique(Graph *,Congestion *,Data *);


};

#endif
