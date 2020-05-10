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

    vector<Cable*> path;
    //graphe->genererChemin(n1, n1, n2, path, true);

     //string data = "Salam";
    Data * data = new Data(message);
     envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, true, false, 10, 0, 100, data);
   // Graphe::genererChemin(0, n1 ,n2, path, false);


}
