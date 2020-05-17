#include <QApplication>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QDebug>
#include "simulaGui.hh"

int main ( int argc, char ** argv) {
    string message = argv[1];
    int n1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);


    gSimulation gestionnaire;
   
    auto lambda = [](int n1 , int n2, string message) { 
        Graphe * graphe = Graphe::get();
        lireXml("test.xml");
        Data * data = new Data(message);
        Station * st = dynamic_cast<Station*>(Graphe::get()->getSommets()[n1]);
        envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, false, false, st->getNextNumSeq(), 0, 100, false, data);
        //envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 101, data2);
        //envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 102, data3);
        // Graphe::genererChemin(0, n1 ,n2, path, false);

        //std::cout << st->getControleur()->getMapFileEnvoyer().size()<<std::endl;
        st->getControleur()->verifieNbrSegment(st);
    };

    std::thread test(lambda, n1,n2, message);
    //test.join();

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

   // test.join();
    return app.exec();
}
