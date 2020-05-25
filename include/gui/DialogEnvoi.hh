#ifndef DIALOGENVOI_H
#define DIALOGENVOI_H

/*!
 * \file DialogEnvoi.hh
 * \brief DialogEnvoi
 * \author Medish
 * \version 0.1
 */

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QPushButton>

#include "Noeud.hh"
#include "NoeudG.hh"

/*!
 * \class DialogEnvoi
 * \brief La classe DialogEnvoi représentant la fenetre d'envoi de message d'un equipement à un autre équipement lors de la simulation du protocole TCP/IP.
 */
class DialogEnvoi : public QDialog {
    Q_OBJECT

private :
    QLineEdit * editNoeud1,/*!< Ligne affichant le noeud source d'envoie*/
              * editNoeud2,/*!< Ligne affichant le noeud recepteur de l'envoie*/
              * editPortSrc,/*!< Ligne saisi de port source*/
              * editPortDest,/*!< Ligne saisi de port recepteur*/
              * editMessage;/*!< Ligne saisi de message à envoyer*/
    QCheckBox * checkAck,/*!< Une box pour cocher la validite de l'ACK lors de l'envoie du message*/
              * checkFrag;/*!< Une box pour cocher la validite de la fragmentation lors de l'envoie du message*/
    QPushButton * envoyerButton;/*!< Bouton d'envoie du message*/

    /*!
             * \brief createForm
             *  methode qui initialise la fentre d'envoie.
    */
    void createForm();

    /*!
             * \brief showForm
             *  methode qui affiche et remplit la fentre d'envoie par deux noeuds.
         * \param *n1 : voir #Noeud
         * \param *n2 : voir #Noeud
    */
    void showForm(Noeud * n1, Noeud * n2);
public :

    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe DialogEnvoi
         *  Initialise un DialogEnvoi des champs d'une lettre à envoyer.
         * \param *n1 : voir #Noeud
         * \param *n2 : voir #Noeud
         * \param *parent : voir #NoeudG

    */
    DialogEnvoi(Noeud *n1 = nullptr, Noeud *n2 = nullptr, NoeudG * parent = nullptr);
    /*!
       * \brief Destructeur
       * Destructeur de la classe DialogEnvoi
   */
    ~DialogEnvoi();

public slots:
    /*!
       * \brief prepareenvoi
       * Methode qui prepare l'envoi entre deux machines
   */
    void preparenvoi();

    /*!
         * \brief onExitDialog
         * Methode qui initialise la fenetre par des valeurs par default.
         * \param  int : voir #DialogEnvoi
    */
    void onExitDialog(int);

// Ajouté par Massi
signals:
    /*!
         * \brief addedData
         * Methode qui ajout de la donnee à la fenetre d'envoie.
         * \param  d : voir #Data
    */
	void addedData ( Data * d);

};

#endif
