#ifndef GSIMULATION_H
#define GSIMULATION_H

/*!
 * \file gSimulation.hh
 * \brief gSimulation
 * \author GT17S
 * \version 0.1
 */

#include <QTime>
#include <qtimer.h>
#include "ThreadManager.hh"

#ifndef ETATS_H
#define ETATS_H

/*!
 * \enum etats_s
 * \brief Etat du Simulation
 */

typedef enum
{
ARRET =0,/*!< Etat en ARRET */
DEMARRER,
PAUSE
} etat_s;


#endif

class ThreadManager;

/*!
 * \class G_Simulation
 * \brief La classe G_Simulation représentant la Gestion de la simulation TCP/IP.
 */
class gSimulation{

private:
        etat_s etat;/*!< Etat de la simulation */
        static QTimer *timer;/*!< Timer de la simulation */
        static QTime *time;/*!< Le temps de la simulation */
        ThreadManager* tm; /*!< Gère les envois concurents*/

public:
        /*!
             * \brief Constructeur par défaut
             * Constructeur par défaut de la classe G_Simulation.
        */
        gSimulation();

        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe G_Simulation
             *  Initialise une Simulation par:
             * \param _etat : voir #G_Simulation
             * \param *_timer : voir #G_Simulation
        */
        gSimulation(etat_s _etat, QTimer *_timer);

        /*!
             * \brief *getTimer
             * getter qui recupere le timer.
             * \return voir #QTimer
        */
      static   QTimer *getTimer()  {return timer;}


        /*!
             * \brief setTimer
             * setter qui insere un QTimer au time de la G_Simulation.
             * \param  *_timer : voir #QTimer
        */

        void setTimer(QTimer *_timer);

        /*!
             * \brief *getTime
             * getter qui recupere le temps de la simulation.
             * \return voir #QTime
        */

     static   QTime *getTime()  {return time;}

        /*!
             * \brief setTime
             * setter qui insere un Temps au time de la G_Simulation.
             * \param  *_time : voir #QTime
        */
        void setTime(QTime *_time);


        /*!
             * \brief getEtat
             * getter qui recupere l'etat.
             * \return voir #etats_s
        */
        etat_s getEtat(){return etat;}

        /*!
             * \brief setEtat
             * setter qui insere un etat_s à l'etat de la G_Simulation.
             * \param  _etat : voir #etat_s
        */
        void setEtat(etat_s _etat);

        /*!
             * \brief arreter
             * methode qui arrete la G_Simulation.
        */
        void arreter();

        /*!
             * \brief demarrer
             * methode qui demarre la G_Simulation.
        */
         void demarrer();
        /*!
             * \brief pause
             * methode qui met en pause la G_Simulation.
        */
        void pause();//3

        /*!
             * \brief reset
             * methode qui relance la G_Simulation.
        */
        void reset();

        /*!
             * \brief Destructeur
             * Destructeur de la classe G_Simulation
         */
        ~gSimulation();



        ThreadManager* getManager() { return this->tm;};
};
#endif
