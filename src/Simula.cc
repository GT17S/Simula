#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QDebug>
#include "simulaGui.hh"

int main ( int argc, char ** argv) {
    QApplication app ( argc, argv);
    simulaGui g;
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
