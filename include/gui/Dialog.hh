#ifndef DIALOG_H
#define DIALOG_H

/*!
 * \file Dialog.hh
 * \brief la fenetre de la configuration des equipements
 * \author GT17 & Nadjibian & medish
 * \version 0.1
 */

#include <QObject>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QToolBox>
#include <QMainWindow>
#include <QGridLayout>
#include "Noeud.hh"

/*!
 * \class Dialog
 * \brief La classe Dialog représentant la fenetre de configuration de l'équipement lors de la simulation du protocole TCP/IP.
 */


class Noeud;
class Dialog : public QDialog
{
    Q_OBJECT

public:

   /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe Dialog
         *  Initialise un Dialog.
         * \param *parent : voir #Noeud
    */

    Dialog(Noeud * parent);

     /*!
         * \brief Destructeur
         * Destructeur de la classe EspaceTravail
     */
    ~Dialog();

    /*!
         * \brief generalWidget
         *  Initialise un la premiere page de la fenetre demandant la saisi de nom de l'équipement.
      */
    void generalWidget();
    void configurationWidget();
    void interfaceWidget(int nbPorts);
    void routageWidget(int nbres);

    /*!
         * \brief showConfig
         *  Affiche la configuration de noeud selectionne sur çà fentetre de dialogue.
         * \param *src : voir #Noeud
     */
    void showConfig(Noeud *src);

private:

    QTabWidget *tabWidget;/*!< QTabWidget permettant l'affichage de pleusieurs widgets sur la meme fenetre de dialogue */
    QDialogButtonBox *buttonBox;/*!Une box regroupant la validation et l'annulation de choix saisi*/
    QToolBox *toolRoutage;/*!ToolBox contenant tous les routes de l'équipement sur des widgets*/
    QToolBox *toolInterface;/*!< ToolBox contenant tous les interface de l'équipement sur des widgets*/
    QPushButton *ajouterRoute,*supprimerRoute,*ajouterInterface,*supprimerInterface;/*!<Buttons d'ajout et de suppression d'interfaces et route de l'equipement selectionne*/
    QWidget *routeWidget;/*!< QWidget contenant la toolroutage*/
    QWidget *intWidget;/*!< QWidget contenant la toolinterface*/
    QGridLayout *routeLayout;/*!< Layout contenant le widget principale des routes */
    QGridLayout *interfaceLayout;/*!< Layout contenant le widget principale des interfaces*/
    int numberRoutes=0;
    QLineEdit 	*NomStation;/*!< Champs de saisi de nom de la station*/
    QSignalMapper* mapperInterface,*mapperRoute,*mapperRouteAp,*mapperInterfaceAp;/*!< Un signalMapper qui sera utile pour traiter les signaux des suppressions des interfaces & routes*/
    Noeud *src;/*! Noeud au quel la configuration est effectue*/


    /*!
         * \brief createWidget
         *  initialise la fenetre de dialogue.

     */
    void createWidget();

    /*!
         * \brief createSignals
         *  Creation des signaux.

     */
    void createSignals();

    std::vector<QPushButton *> buttons;
    std::vector<QWidget *> ports;
private slots:

    /*!
         * \brief addRoute
         *  Ajouter un champs route.

     */
    void addRoute();

    /*!
         * \brief deleteRouteG
         *  suppression d'une route.
         * \param i : voir #int
     */
    void deleteRouteG(int i);
    /*!
         * \brief deleteInterfaceG
         *  suppression d'une interface.

     */
    void deleteInterfaceG();
    /*!
         * \brief ajoutInterfaceG
         *  Ajout d'une interface.
     */
    void addInterface();
    /*!
         * \brief appliquerInterface
         *  appliquer modification sur une interface.
         * \param i : voir #int
     */
    void appliquerInterface(int );
    /*!
         * \brief appliquerRoute
         *  appliquer modification sur une route.
         * \param i : voir #int
     */
    void appliquerRoute(int );
    /*!
         * \brief onExitDialog
         *  reinitialiser les champs au valeurs par default (vide).
         * \param i : voir #int
     */

    void onExitDialog(int );

};

#endif // DIALOG_H
