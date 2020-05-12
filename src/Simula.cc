#include <QApplication>
#include <QtWidgets>
#include <QDebug>

#include "Data.hh"
#include "DataOutils.hh"
#include "simulaGui.hh"	
#include "Graphe.hh"
#include "GFichier.hh"
#include "DataG.hh"
#include "PanneauData.hh"

#include "simulaGui.hh"	
/*int main (int argc, char ** argv)	{
    QApplication a(argc, argv);

// Creation de ma Data

	Data * d = new Data ("Azul");
	
	
	
	encapsule_donnee ( 	dynamic_bitset<> (16, 1025),
						dynamic_bitset<> (16,80),
						dynamic_bitset<> (32, 15),
						dynamic_bitset<> (32, 15),
						dynamic_bitset<> (6, 15),
						dynamic_bitset<> (16, 15), 
						d);
	
	encapsule_segment ( nullptr, nullptr,
						boost::dynamic_bitset<> (16, 0xAAAA),
						boost::dynamic_bitset<> ( 3, 7),
						boost::dynamic_bitset<> ( 13, 1016),
						boost::dynamic_bitset<> ( 8, 0xC3), 
						d);

	encapsule_paquet ( nullptr, nullptr, d);
	
	QWidget f;
//	QScrollArea * qs = new QScrollArea(&f);		// Redimentionner en fonction de la fenetre
    PanneauData p ( &f);//qs);							// Redimentionner en fonction des données

	f.setMinimumSize(1000,600);
	
//	p.setMinimumSize(1200, 80); 
	p.setMinimumSize(900, 80); 

// Fait dans SimulaGUI
//	qs->setMinimumSize(900, 100);
//	qs->setMaximumSize(2000, 100);
	
//	qs->move(50, 500);
	p.move(50, 500);
//	!Fait dans SimulaGUI

    
//	qs->setWidget(&p);
//	f.setWidget(&p);
    
    p.addData ( d);
    
    f.show();
    return a.exec();
}
*/

int main ( int argc, char ** argv) {

	Data * d = new Data ("Azul");
	encapsule_donnee ( 	dynamic_bitset<> (16, 1025),
						dynamic_bitset<> (16,80),
						dynamic_bitset<> (32, 15),
						dynamic_bitset<> (32, 15),
						dynamic_bitset<> (6, 0),
						dynamic_bitset<> (16, 15), 
						d);
	encapsule_segment ( nullptr, nullptr,
						boost::dynamic_bitset<> (16, 1000),
						boost::dynamic_bitset<> ( 3, 0),
						boost::dynamic_bitset<> ( 13, 0),
						boost::dynamic_bitset<> ( 8, 0xC3), 
						d);	
	encapsule_paquet ( nullptr, nullptr, d);
	QApplication a ( argc, argv);
	simulaGui g;
	PanneauData * p = dynamic_cast <PanneauData *> (g.getMainlayout()->itemAtPosition ( 4,0)->widget());
	if ( !p) return 1;
	
	p->addData(d);
	p->addData(new Data ("Coucou"));
	
	g.show();
	return a.exec();
	return 0;
}
