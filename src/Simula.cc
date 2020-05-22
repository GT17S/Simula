#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QDebug>
#include "simulaGui.hh"
#include "Graphe.hh"


void cleanup(){
    return;
}

int main ( int argc, char ** argv) {

    //lireXml("test.xml");
    gSimulation * gestionnaire = new gSimulation();
    gestionnaire->getManager()->initStation();

    QApplication app ( argc, argv);
    simulaGui g ( gestionnaire);
    QFile File(":/style/stylesheet.qss");
    File.open(QFile::ReadOnly);

    QString StyleSheet;
    if(File.isOpen()){
        StyleSheet = QLatin1String(File.readAll());
        File.close();
    }else qDebug ()<<"Problème de lecture de la feuille de style";

    app.setStyleSheet(StyleSheet);
    g.show();

    std::atexit(cleanup);
    return app.exec();
}
