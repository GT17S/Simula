#ifndef __H_PANNEAUOUTILS__
#define __H_PANNEAUOUTILS__ 

#include <QToolBar>
#include <QWidget>
#include <QDebug>
#include <QMenu>
#include <QPushButton>
#include <QAction>

#include <QFormLayout>
#include <QInputDialog>
#include <QTextEdit>
#include <QCheckBox>

#include <stdio.h>
#include <string.h>

#include "EspaceTravail.hh"
#include "gSimulation.hh"
#include "PanneauEvents.hh"
#include "DataOutils.hh"

/*!
 * \class PanneauOutils
 * \brief La classe PanneauOutils représentant le panneau d'outils sur l'interface graphique lors de la simulation du protocole TCP/IP.
 */

class PanneauOutils : public QToolBar{
	Q_OBJECT
private :
    EspaceTravail * espaceTravail;/*!< Objet permettant de contenir les equipements et de realiser leurs differrentes interactions sur l'interface graphique*/
    QString curFile;/*!< Chaine de caractere contenant le nom de fichier current*/
    QWidget* formulaire;/*!< Formulaire*/
    std::vector<QWidget*> widgets;/*!< vecteur de fenetres*/
    gSimulation *gestSimulation;/*!< Objet permettant la gestion de temps de la simulation*/
    QPushButton *nouveau,/*!< Bouton de creation d'une nouvelle Espace de travail*/
                *ouvrir,/*!< Bouton d'ouverture d'un nouveau fichier*/
                *sauvegarder,/*!< Bouton de sauvegarde d'un nouveau fichier*/
                *simDemPause,/*!< Bouton de demarrer et pause de la simulation*/
                *arreter,/*!< Bouton d'arret de la simulation*/
                *relancer,/*!< Bouton de relancement de la simulation*/
                *changerMode,/*!< Bouton de changement de mode d'envoi*/
                *benvoyer,/*!< Bouton d'e demarrer et pause de la simulation d'envoi de message*/
                *zoomIn,/*!< Bouton de zoomer de l'espace de taravail*/
                *zoomOut,/*!< Bouton de DE-zoomer  de l'espace de taravail*/
                *quitb, /*!< Bouton pour quitter la simulation */
                *exportButton;/*!< Bouton d'importation de l'éspace de travail*/
    QAction     *exporterDot,/*!< Action de recupuration de l'espace de travail sous format dot*/
                *exporterPng;/*!< Action de recupuration de l'espace de travail sous format png*/


	void clearPanneauData();
    /*!
        * \brief createButtons
        * Construction et Initialisation  des differentes buttons de panneauoutils
   */
void createButtons();


/*!
    * \brief createSignals
    * Construction et Initialisation  des differentes signaux de panneauoutils
*/
void createSignals();


/*!
    * \brief createShortcuts
    * Initialisation  des differentes raccourcis de panneauoutils
*/
void createShortCuts();
public:

/*!
    * \brief Constructeur paramétré
    * Constructeur qui prends un espace de travail et un  objet de gSimulation
    * \param *e: voir #EspaceTravail
    * \param *g: voir #gSimulation
*/
    PanneauOutils(EspaceTravail * e,  gSimulation * g);
    /*!
        * \brief Destructeur
        * Destructeur de la classe PanneauOutils
    */
    virtual ~PanneauOutils();

    /*!
        * \brief getGestionnaire
        * recuperer le gestionnaire de simulation
   */
    gSimulation* getGestionnaire(){ return gestSimulation;}

    /*!
        * \brief setGestionnaire
        * affecte une valeur au gestionnaire de la simulation
        * \param *g: voir #gSimulation
   */

    void setGestionnaire ( gSimulation * g){gestSimulation = g;}

public slots:

    /*!
        * \brief timer
        * Construction et Initialisation  de timer de la simulation
   */
    void timer();


    /*!
        * \brief nouveauFichier
        * Slot de creation d'un fichier existant
   */
    void nouveauFichier();

    /*!
        * \brief ouvrirFichier
        * Slot d'ouverture d'un fichier existant
   */
    void ouvrirFichier();

    /*!
        * \brief sauvegardeFichier
        * Slot de sauvegarde le graphe de l'éspace de travail sous format XML
   */
    void sauvegarderFichier();

    /*!
        * \brief exportDot
        * Slot d'exportation de l'éspace de tarvail sous format DOT
   */
    void exportDot();

    /*!
        * \brief exportPng
        * Slot d'exportation de l'éspace de tarvail sous format PNG
   */
    void exportPng();

    /*!
        * \brief demarrerPauseSimulation
        * Slot de demarrage et pause de la simulation
   */
    void demarrerPauseSimulation();

    /*!
        * \brief arreterSimulation
        * Slot d'arret de la simulation
   */
    void arreterSimulation();

    /*!
        * \brief resetSimulation
        * Slot de relancement de la simulation
   */
    void resetSimulation();

    /*!
        * \brief changeMode
        * Slot de changement le mode d'envoi de la donnée
   */
    void changeMode();

    /*!
        * \brief envoiD
        * Slot d'envoi de la donnée
   */
    void envoieD();

    /*!
        * \brief zoomer
        * Slot de zoomage de l'espace de travail
   */
    void zoomer();

    /*!
        * \brief dezoomer
        * Slot de De-zoomage de l'espace de travail
   */
    void dezoomer();

    /*!
         * \brief toPng
         * slot qui permet d'exporter l'espace de travail en image png
    */
    void toPng();
};

#endif
