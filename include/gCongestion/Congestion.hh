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
#include <mutex>
#include "PanneauEvents.hh"

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
    float baseRtt;/*!<  RoundTripTime de valeur prédéfinie*/
    std::map<int,destination> mapFileEnvoyer;/*!<  liste des datas a envoyer avec num de segments*/
    std::map<int ,destination> mapFileACK;/*!<  liste des Acks a recevoir */

    //Cet valeur est à afficher dans le panneau d'evenement
    float latenceLastSend; /*!<  Latence d'un envoie entre A et B  en ms */

    //mutex de vérouillage
    std::mutex* mutexcable; // A voir si beosin ici
	std::mutex* mutexFileEnvoyer;
	std::mutex* mutexFileACK;
	std::mutex* mutexEnvoiOk;
    bool envoiok;

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
      * \brief getNbrAcksRecu
      * \return Nombre de paquets acquittement reçus (int)
      */
    int getNbrAcksRecu(){return nbrAcksRecu;}
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
      * \brief setMutex
      * initialise le Mutex qui va sécuriser la manipulation des cbales
      * \param le mutex du threadManager
    */
    void setMutex(std::mutex* _m){this->mutexcable = _m;};
    
    /*!
      * \brief setMutexFileEnvoyer
      * initialise le Mutex qui va sécuriser la manipulation de la liste des data a envoyer
      * \param le mutex de la station
    */
    void setMutexFileEnvoyer(std::mutex* _m){this->mutexFileEnvoyer = _m;};

    /*!
      * \brief setMutexFileACK
      * initialise le Mutex qui va sécuriser la manipulation de la liste des ACK
      * \param le mutex de la station
    */
    void setMutexFileACK(std::mutex* _m){this->mutexFileACK = _m;};

    /*!
      * \brief setMutexEnvoiOk
      * initialise le Mutex qui va sécuriser la manipulation du booléen d'envoie
      * \param le mutex dz la station
    */
    void setMutexEnvoiOk(std::mutex* _m){this->mutexEnvoiOk = _m;};

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
     * param \n : la station ou se trouve le controleur

     */

    void slowStart(Noeud * n);

    /*!
     * \brief fastRecovery
     * Méthode : Méthode qui va décroître la taille de la fenêtre de congestion et le ssthresh
        pour augmenter le compteur
     * param \n : la station ou se trouve le controleur

     */
    void fastRecovery(Noeud * n);
    /*!
     * \brief congestionAvoidance
     * Méthode : Méthode qui va augmenter la fenêtre de congestion linéairement
     * param \n : la station ou se trouve le controleur
     */
    void congestionAvoidance(Noeud * n);

    /*!
     * \brief verifieNumSegment
     * verification des numero des segments recus et l'ienvoie d'un ack
     * \param stThis : station qui va envoyer l'ack
     * \param src : la station réceptrice des acks;
     * \param nAck : numero d'ack
     */
    void verifieNumSegment(Noeud *stThis, Noeud *src, int nAck);//pc recepteur

    /*!
     * \brief verifieNumAck
     * verification des numero des Ack recus
     * \param n : station qui va vérifier l'ack
     * \param nAck :numero d'ack
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
     * \brief verifieNbrSegment
     * verfication nombre des segments à envoyer
     * \param stSrc : la station émettrice des datas;
     */
    void verifieNbrSegment(Noeud *stSrc);

    /*!
     * \brief CalculRTT
     * calculer le Rtt
     * \param g : controleur de congestion;
     */
    friend float CalculRTT(Congestion *g);
    /*!
     * \brief CalculLatenceDynamique
     * calculer la latence dynamique
     * \param graphe : graphe de simulation  ;
     * \param congestion : controleur de congestion;
     * \param data : paquet à envoyer;
     */
    friend float CalculLatenceDynamique(Graphe *graphe,Congestion *congestion,Data *data);


    /*!
     * \brief retrnasmission
     * retrnasmission des datas apres un certain temps sans ack
     * \param key : trouve le data dans mapFileEnvoyer;
     */
   void retrnasmission(int key);
   /*!
     * \brief getMapFileEnvoyer
     * \return liste des datas a envoyer avec num de segments
     */
   std::map<int, destination> getMapFileEnvoyer(){    return mapFileACK;;}

   /*!
     * \brief getMapFileACK
     * \return liste des Acks a recevoir
     */
   std::map<int, destination> getMapFileACK(){return mapFileACK;}
   /*!
     * \brief setMapFileEnvoyer
     *  Modifier liste des datas a envoyer avec leurs numeros de segments
     * \param _map : liste des datas a envoyer avec leurs numeros de segments
     */
   void setMapFileEnvoyer(std::map<int, destination> _map);
   /*!
     * \brief setMapFileACK
     *  Modifier liste des Acks a recevoir
     * \param _map : liste des Acks a recevoir
     */
   void setMapFileACK(std::map<int, destination> _map);
   /*!
     * \brief setlatence
     *  Modifier la valeur de la latence
     * \param _f : latence à attribuer
     */
   void setlatence(float f){ this->latenceLastSend = f;};


   bool getok(){return envoiok;};
   void setok(bool b){ this->envoiok = b;};
};

#endif
