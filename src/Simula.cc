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
    lireXml("test.xml");

    Data * data = new Data(message);

    Station * st = dynamic_cast<Station*>(graphe->getSommets()[n1]);

    envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 100,true, data);
     //envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 101, data2);
     //envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, st->getNextNumSeq(), 0, 102, data3);
   // Graphe::genererChemin(0, n1 ,n2, path, false);

     //std::cout << st->getControleur()->getMapFileEnvoyer().size()<<std::endl;
     st->getControleur()->verifieNbrSegment(st);

     delete graphe;

}
/////
