#ifndef INTERFACEG_H
#define INTERFACEG_H


/*!
 * \file InterfaceG.hh
 * \brief la fenetre des Interfaces des equipements
 * \author GT17 & Nadjibian & medish
 * \version 0.1
 */
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QWidget>
#include <QToolBox>
#include <QCheckBox>
#include "QString"
#include "QSignalMapper"

/*!
 * \class InterfaceG
 * \brief La classe InterfaceG représentant les champs d'interface de l'équipement dans une fentre lors de la simulation du protocole TCP/IP.
 */
class InterfaceG : public QWidget
{
    friend class Dialog;
    Q_OBJECT

public:


    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe InterfaceG
         *  Initialise un InterfaceG des champs d'une interface.
         * \param _AdresseIP : voir #InterfaceG
         * \param _AdresseMac : voir #InterfaceG
         * \param _AdresseRes : voir #InterfaceG
         * \param _mask : voir #InterfaceG
         * \param _AdresseIP : voir #InterfaceG
         * \param _interfaceName : voir #InterfaceG
         * \param _liaison : voir #InterfaceG

    */
    InterfaceG(QString _AdresseIP=QString(),QString _AdresseMac=QString(),QString _AdresseRes=QString(),QString _mask=QString(),QString _interfaceName=QString(),bool _liaison=false);
      /*!
         * \brief Destructeur
         * Destructeur de la classe EspaceTravail
     */
    ~InterfaceG();


private:
    /*!
         * \brief createInputs
         *  Initialise un InterfaceG des champs d'une interface.
         * \param _AdresseIP : voir #InterfaceG
         * \param _AdresseMac : voir #InterfaceG
         * \param _AdresseRes : voir #InterfaceG
         * \param _mask : voir #InterfaceG
         * \param _AdresseIP : voir #InterfaceG
         * \param _interfaceName : voir #InterfaceG
         * \param _liaison : voir #InterfaceG

    */
void createInputs(QString _AdresseIP,QString _AdresseMac,QString _AdresseRes,QString _mask,QString _interfaceName,bool _liaison);

/*!
         * \brief createLabels
         *  methode qui initialise les labels de la fenetre interface.
    */

void createLabels();

QGridLayout *gridLayoutinterface ;/*!< GridLayout permettant l'affichage de pleusieurs widgets sur la meme fenetre InterfaceG*/
QLineEdit 	*AdresseIP	;/*!< Champs de saisi de l'adresse IP*/
QLineEdit 	*AdresseMac	;/*!< Champs de saisi de l'adresse MAC*/
QLineEdit 	*AdresseRes	;/*!< Champs de saisi de l'adresse reseau*/
QLineEdit   *mask ;/*!< Champs de saisi de mask du reseau*/
QLineEdit   *interfaceName ;/*!< Champs de saisi de nom d'interface*/
QCheckBox   *liaison ;/*!< Une box pour cocher la laison de l'interface ou pas dans le cas non cocher*/
QPushButton *appliquer;/*!< Button servant a appliquer les champs saisi*/
QPushButton *supprimer;/*!< Button servant a supprimer l'interface*/
QGroupBox *portGroupBox ;/*!< Une box regroupant la validation et l'annulation de choix saisi*/
QFormLayout *layout ;/*!< Formulaire qui contient tous les champs de saisi*/

private slots:
/*!
         * \brief deleteInterfaceG
         *  methode qui supprime la fenetre interfaceG.
    */

    void deleteInterfaceG();
};


#endif
