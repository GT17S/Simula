#ifndef CONGESTION_H
#define CONGESTION_H

/*!
 * \file Noeud.hh
 * \brief Congestion
 * \author Nadjibian
 * \version 0.1
 */

#include"string"
#include"vector"
#include "Data.hh"
#include "DataOutils.hh"
#include "congestionOutil.hh"
#include"Graphe.hh"
#include <map>

/*!
 * \class Congestion
 * \brief La classe Congestion représentant un contrôleur de congestion .
 */

class Station;
class Graphe;
class Congestion{

    friend class Station;
    friend void envoyer(Noeud *, Noeud *, int, int, bool, bool, int, int, int,bool, Data*);

private:
    int cwnd;/*!< La taille de la fentre de congestion */
    int ssthresh; /*!< taille maximum de cwnd en mode slow start */
    int cpt;/*!< nombre de fois que cwnd a changé */
    int nbrAcksDuplique;/*!<  Nombre d’ack dupliqués */
    int nbrAcksRecu; /*!<  Nombre de paquets acquittement reçus*/
    int numAckRecu;/*!< Numéro du dernier paquet acquittement reçu*/
    float baseRtt;/*!<  RoundTripTime de valeur prédéfinie*/
    std::vector<Data *> segAE;/*!< les segments a envoyer*/
     //pc recepteur
    int dataTotal;/*!< nombre total des fragment a envoyer */
    int countSegment;/*! compteur des segment recu */
    std::vector<Data *> segRecu;/*!< les segments recu */
    int dernierNumSegment;/*!<  numéro du dernier segment reçu */


    std::map<int,destination> mapFileEnvoyer;
    std::map<int ,destination> mapFileACK;

    //Cet valeur est à afficher dans le panneau d'evenement
    float latenceLastSend; /*!<  Latence d'un envoie entre A et B  en ms */


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
      * \brief latenceLastSend
      * \return RoundTripTime (int)
      */
    int getlatenceLastSend(){return latenceLastSend;}



    /*!
      * \brief getDataTotal
      * \return nombre total des semgents  (int)
      */
    int getDataTotal() const;//pc recepteur

    /*!
      * \brief getCountSegment
      * \return nombre des segments recu  (int)
      */
    int getCountSegment() const;//pc recepteur


    /*!
      * \brief getSegRecu
      * \return les segments recu  (vector<Data *>)
      */
    std::vector<Data *> getSegRecu() const;//pc recepteur

    /*!
      * \brief getSegAE
      * \return les segments a envoyer  (vector<Data *>)
      */
    std::vector<Data *> getSegAE() const;


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
      * \brief latenceLastSend
      * \param latence du dernier envoi
      * \return void
      */
    void setlatenceLastSend(float llt){ this->latenceLastSend = llt;};


    /*!
      * \brief setDataTotal
      *  Modifier le nombre total des fragment a envoyer
      *  Vérifier _dataTotal est positive
      * \param _dataTotal : nombre total (int)
      */
    void setDataTotal(int _dataTotal);//pc recepteur

    /*!
      * \brief setCountSegment
      *  Modifier le compteur des segments recu
      *  Vérifier _countSegment est positive
      * \param _countSegment : nombre (int)
      */
    void setCountSegment(int _countSegment);//pc recepteur

    /*!
      * \brief setSegRecu
      *  Modifier les segments recus
      * \param _segRecu : segment (vector<Data *>)
      */
    void setSegRecu(const std::vector<Data *> _segRecu);//pc recepteur

    /*!
      * \brief setSegRecu
      *  Modifier les segments recus
      * \param _segRecu : segment (Data)
      */
    void setSegRecu(Data* _segRecu);//pc recepteur

    /*!
      * \brief setSegAE
      *  Modifier les segments a envoyer
      * \param _segAE : segment (vector<Data *>)
      */
    void setSegAE(const std::vector<Data *> &_segAE);

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

    /*!
     * \brief verifieNumSegment
     * verification des numero des segments recus et l'ienvoie d'un ack
     * \param segment : Data recu
     * \param stDes : la station réceptrice des datas;
     */
    void verifieNumSegment(Noeud *stThis, Noeud *src, int nAck);//pc recepteur

    /*!
     * \brief verifieNumAck
     * verification des numero des Ack recus
     * \param ack : l'acquittement  recu
     * \param num_seq :vector des numeros des segments deja envoyé
     * \param stSrc : la station émettrice des datas;
     */
    void verifieNumAck(Noeud *n, int nAck);
    /*!
     * \brief verifieNumAck
     * retransmission des segments perdus
     * \param messages : les segments deja envoyeé
     * \param num :numero de segments perdu
     */
    void fastRetransmission(std::vector<Data> messages,int num);

    /*!
     * \brief verifieNumAck
     * verfication nombre des segments a envoyer
     * \param stSrc : la station émettrice des datas;
     */
    void verifieNbrSegment(Noeud *stSrc);


    friend float CalculRTT(Congestion *g);
    friend float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data);


   void retrnasmission(int key);
   void updateLatence();
   std::map<int, destination> getMapFileEnvoyer();
   void setMapFileEnvoyer(std::map<int, destination> _map);
   std::map<int, destination> getMapFileACK();
   void setMapFileACK(std::map<int, destination> _map);
};

#endif
