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

class PanneauData : public QTabWidget {
Q_OBJECT
public:
	PanneauData( QWidget *parent = nullptr);
	~PanneauData();
	void clearPanneauData();
	
public slots:
	void addData ( Data * d);
	void askRemoveTab( int index);

private:
    QMap <Data *, DataG *> onglets;
	int compt;
};

#endif // PANNEAU_DATA_HPP

