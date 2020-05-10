#include <iostream>
#include <vector>
#include "GFichier.hh"
#include "Graphe.hh"
#include "DataOutils.hh"

using std::vector;


int main( int argc, char ** argv)	{

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    vector<Cable*> path;
    graphe->genererChemin(n1, n1, n2, path, true);

    string data = "Salam";
    envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, data);


}
