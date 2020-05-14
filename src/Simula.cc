#include <QApplication>
#include <QtWidgets>
#include <QDebug>

#include "simulaGui.hh"

int main ( int argc, char ** argv) {
	QApplication app ( argc, argv);
	simulaGui g;
	g.show();
  	return app.exec();

}
