#ifndef DATA_G_HPP
#define DATA_G_HPP

/*!
 * \file DataG.hh
 * \brief DataG
 * \author M4ssi
 * \version 0.1
 */

#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QTabBar>
#include <QLayout>
#include <QFont>
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QDebug>

#include "Data.hh"
#include "DataOutils.hh"

/*!
 * \class DataG
 * \brief La classe DataG représentant la donnee circulant d'un équipement à une autre équipement lors de la simulation du protocole TCP/IP.
 */
class DataG : public QTabBar    {
    Q_OBJECT

private :
		Data * d;
		std::vector<Data *> send;
		QPushButton detail, left, right;
		QHBoxLayout * grid;
		int curent;
		void addMessage (void);
		void addSegment (void);
		void addPaquet (void);
		void addTrame (void);
		void predicateData (void);
		void updatePanel(void);
		
public :
        /*!
             * \brief Construceur d'initialisation
             *  Constructeur de la classe DataG
             *  Initialise un DataG par une donne et une fentere parente.
             * \param d : voir #Data
             * \param parent : voir #QWidget
        */
        DataG( Data *d, QWidget* parent = 0 );
        ~DataG();
        Data * getDataptr()	{ return d;};

		
private slots:
//		void dataChanged();
        void detailPanel();
        void displayLeft();
        void displayRight();
		

};


#endif // DATA_G_HPP
