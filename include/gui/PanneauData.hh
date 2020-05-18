#ifndef PANNEAU_DATA_HPP
#define PANNEAU_DATA_HPP

#include <QApplication>
#include <QTabWidget>
#include <QMap>
#include "PanneauEvents.hh"
#include "Data.hh"
#include "DataG.hh"
#include "QTreeWidgetItem"

class PanneauData : public QTabWidget {
Q_OBJECT
public:
	PanneauData( QWidget *parent = nullptr);
	~PanneauData();
public slots:
	void addData ( Data * d);


    QTreeWidgetItem *getParentt() const;
    void setParentt(QTreeWidgetItem *value);

private:
    QMap <Data *, DataG *> onglets;
    QTreeWidgetItem *parentt;

};

#endif // PANNEAU_DATA_HPP

