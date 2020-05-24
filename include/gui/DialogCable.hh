#ifndef DIALOGCABLE_H
#define DIALOGCABLE_H

/*!
 * \file DialogCable.hh
 * \brief DialogCable
 * \author GT17S & Medish & nadjibian
 * \version 0.1
 */

#include <QObject>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include "Cable.hh"
#include "QPushButton"

/*!
 * \class DialogCable
 * \brief La classe DialogCable représentant une fenetre de configuration pour un cable lors de
 * la simulation du protocole TCP/IP.
 */
class Cable;
class DialogCable : public QDialog
{
    Q_OBJECT

public:

    /*!
         * \brief Construceur d'initialisation
         *  Constructeur de la classe DialogCable
         *  Initialise un DialogCable par un cable.
         * \param _type : voir #Cable
         * \param _debit : voir #Cable
         * \param _mtu : voir #Cable
    */
    DialogCable(QWidget *parent,int _type, int _debit, int _mtu,Cable * _cable);

    /*!
         * \brief Destructeur
         * Destructeur de la classe EspaceTravail
     */
    ~DialogCable();

    /*!
         * \brief init
         * Methode qui initialise la fentre de l'objet DialogCable dans l'EspaceTravail.
    */
    void init();

    /*!
         * \brief createSignals
         * Methode qui prepare les signaux de l'objet DialogCable.
    */
    void createSignals();

    /*!
         * \brief createInputs
         * Methode qui initialise l'objet DialogCable dans l'EspaceTravail.
         * \param  _type : voir #DialogCable
         * \param  _debit : voir #DialogCable
         * \param  _mtu : voir #DialogCable
    */
    void createInputs(int _type, int _debit, int _mtu);


    /*!
         * \brief showConfig
         * Methode qui affiche l'objet DialogCable dans ça fentre de logique vers graphique.
         * \param  *src : voir #Cable
    */
    void showConfig(Cable *src);

private:

    QLineEdit 	*debit;/*!< Ligne affichant le debit du cable*/
    QLineEdit   *mtu; /*!< Ligne affichant le MTU du cable*/
    QComboBox   *type; /*!< Une boite permettant de choisir le type de cable (CROISE ou bien DROIT)*/
    Cable *cableMemebre;/*!< Le cable sélectionne */
    QPushButton *appliquer;/*!< bouton pour appliquer les changements */

private slots:
    /*!
         * \brief onExitDialog
         * Methode qui initialise la fentre par des valeurs par default.
         * \param  int : voir #DialogCable
    */
    void onExitDialog(int);
    /*!
     * \brief onApplique
     * Methode qui vas appliquer les changements sur le cable
     */
    void onApplique();

};

#endif // DIALOGCABLE_H
