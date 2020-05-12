#include <iostream>
#include <vector>
#include "GFichier.hh"
#include "Graphe.hh"
#include "DataOutils.hh"

using std::vector;


int main( int argc, char ** argv)	{

    string message = argv[1];
    int n1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    //vector<Cable*> path;
    //graphe->genererChemin(n1, n1, n2, path, true);

     //string data = "Salam";
    Data * data = new Data(message);
    Data * data2 = new Data ("a");
    Data * data3 = new Data("bye");

    Station * st = dynamic_cast<Station*>(graphe->getSommets()[n1]);

     envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 100,false, data);
     envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 101,false, data2);
     //envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 102, data3);
   // Graphe::genererChemin(0, n1 ,n2, path, false);

     //std::cout << st->getControleur()->getMapFileEnvoyer().size()<<std::endl;
     st->getControleur()->verifieNbrSegment(st);

     delete graphe;
     //delete data;
     //delete data2;
     delete data3;
}
/////
