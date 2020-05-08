#include <iostream>
#include <vector>
#include "GFichier.hh"
#include "Graphe.hh"

using std::vector;

int main( int argc, char ** argv)	{

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    vector<Cable*> path;
    graphe->genererChemin(n1, n2, path);

    int i = path.size() -1;
    extremite * x  = path[i]->getExt1();
    do{
        std::cout<< x->noeud->getIdNoeud()<<" envoie à "<<std::endl;
        x = path[i]->getExt(x->noeud);
        i--;

    }while(i > -1);


}
