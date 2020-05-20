#ifndef ROUTEG_H
#define ROUTEG_H
#include <QObject>

/*!
 * \file RouteG.hh
 * \brief la fenetre des routes des equipements
 * \author GT17 & Nadjibian & medish
 * \version 0.1
 */

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QWidget>
#include <QToolBox>
#include "QSignalMapper"

/*!
 * \class RouteG
 * \brief La classe RouteG représentant les champs d'une route de l'équipement dans une fenetre lors de la simulation du protocole TCP/IP.
 */
class RouteG: public QWidget
{
    friend class Dialog;

    Q_OBJECT
private:
QGridLayout *gridLayoutinterface ;/*!< GridLayout permettant l'affichage de pleusieurs widgets sur la meme fenetre RouteG*/
QLineEdit 	*nextHope	;/*!< Champs de saisi de la passerelle*/
QLineEdit 	*AdresseRes	;/*!< Champs de saisi de l'adresse reseau*/
QLineEdit     *mask ;/*!< Champs de saisi de masque de reseau*/
QLineEdit     *resName ;/*!< Champs de saisi de nom de reseau*/
QPushButton *supprimer ;/*!< Button servant a supprimer l'objet route*/
QPushButton *appliquer ;/*!< Button servant a appliquer les champs saisi*/
QGroupBox *portGroupBox ;/*!< Une box regroupant la validation et l'annulation de choix saisi*/
QFormLayout *layout ;/*!< Formulaire qui contient tous les champs de saisi*/
static int key;

/*!
         * \brief createInputs
         *  Initialise les champs d'une route.
         * \param _NextHope : voir #RouteG
         * \param _AdresseRes : voir #RouteG
         * \param _mask : voir #RouteG

    */
void createInputs(QString _nextHope,QString _AdresseRes,QString _mask);

/*!
         * \brief createLabels
         *  Initialise les labels des champs de la fentere de routeG.
*/
void createLabels();
public:


/*!
         * \brief constructeur d'initialisation
         *  Initialise les champs d'une route.
         * \param _NextHope : voir #RouteG
         * \param _AdresseRes : voir #RouteG
         * \param _mask : voir #RouteG

    */
    RouteG(QString _nextHope=QString(),QString _AdresseRes=QString(),QString _mask=QString());

/*!
         * \brief Destructeur
         * Destructeur de la classe EspaceTravail
     */
    ~RouteG();

    /*!
         * \brief getNextHope
         *  Recupere la passerelle de routeG.
         *\return *QLineEdit

    */
    QLineEdit *getNextHope() const;

    /*!
         * \brief setNextHope
         *  insere une la passerelle au routeG.
         *\param *value : voir #QLineEdit

    */
    void setNextHope(QLineEdit *value);

    /*!
         * \brief getAdresseRes
         *  Recupere l'adresse reseau de routeG.
         *\return *QLineEdit

    */
    QLineEdit *getAdresseRes() const;

    /*!
         * \brief setAdresseRes
         *  insere une l'adresse reseau au routeG.
         *\param *value : voir #QLineEdit

    */
    void setAdresseRes(QLineEdit *value);

    /*!
         * \brief getMask
         *  Recupere l'adresse masque de routeG.
         *\return *QLineEdit

    */
    QLineEdit *getMask() const;
    /*!
         * \brief setMask
         *  insere une le mask au routeG.
         *\param *value : voir #QLineEdit

    */
    void setMask(QLineEdit *value);

private slots:
    /*!
         * \brief deleteroute
         *  supprime le routeG selectionne.
    */
    void deleteroute();
};

#endif // ROUTE_H
