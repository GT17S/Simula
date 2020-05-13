#ifndef PANNEAU_DATA_HPP
#define PANNEAU_DATA_HPP

#include <QApplication>
#include <QTabWidget>
#include <QMap>

#include "Data.hh"
#include "DataG.hh"

class PanneauData : public QTabWidget {
Q_OBJECT
public:
	PanneauData( QWidget *parent = nullptr);
	~PanneauData();
public slots:
	void addData ( Data * d);
private:
	QMap <Data *, DataG *> onglets;

};

#endif // PANNEAU_DATA_HPP

