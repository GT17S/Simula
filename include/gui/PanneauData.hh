#ifndef PANNEAU_DATA_HPP
#define PANNEAU_DATA_HPP

#include <QApplication>
#include <QTabWidget>
#include <QMap>
#include "PanneauEvents.hh"
#include "EspaceTravail.hh"
#include "Data.hh"
#include "DataG.hh"
#include "Graphe.hh"
#include "QTreeWidgetItem"


/*!
 * \class PanneauData
 * \brief La classe PanneauData représentant le panneau de la Donne traité sur l'interface graphique lors de la simulation du protocole TCP/IP.
 */
class PanneauData : public QTabWidget {
Q_OBJECT
public:

    /*!
        * \brief Constructeur paramétré
        * Constructeur qui prend un parent QWidget.
        * \param *parent : voir #QWidget
   */
	PanneauData( QWidget *parent = nullptr);

    /*!
        * \brief Destructeur
        * Destructeur de la classe PanneauData
    */
	~PanneauData();
public slots:
    /*!
        * \brief addData
        * Ajout d'une donne sur le PanneauData
         * \param *d: voir #Data

*/
	void addData ( Data * d);


private:
    QMap <Data *, DataG *> onglets;/*!< Onglets d'affichage de la donne des sa construction a sa destruction*/

};

#endif // PANNEAU_DATA_HPP

