#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QDebug>
#include "simulaGui.hh"
#include "Graphe.hh"

int main ( int argc, char ** argv) {
    string message = argv[1];
    int n1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    Graphe * graphe = Graphe::get();
    lireXml("test.xml");


    gSimulation * gestionnaire = new gSimulation;
   

    QApplication app ( argc, argv);
    simulaGui g ( gestionnaire);
    QFile File(":/style/stylesheet.qss");
    File.open(QFile::ReadOnly);

    QString StyleSheet;
    if(File.isOpen()){
        StyleSheet = QLatin1String(File.readAll());
        File.close();
    }else qDebug ()<<"probleme de lecture";

    app.setStyleSheet(StyleSheet);
    g.show();




    return app.exec();
}
