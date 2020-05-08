#include <iostream>
#include <vector>
#include "GFichier.hh"
#include "Graphe.hh"

using std::vector;

void envoyer(Noeud * n1, Noeud * n2, vector<Cable*> path){

    int size_p = path.size();

    // pas de chemin
    if(!size_p)
        return;

    extremite * ext1, * ext2;
    Cable * cable;

   // cable = path[--size_p];
   // ext1 = cable->getExt(n1); // 0
    Noeud * n = n1;

    for(int i = size_p - 1; i > -1; i--){
        cable = path[i];
        ext1 = cable->getExt(n); // 6
        ext2 = cable->getInverseExt(ext1->noeud); // 8
        std::cout <<"envoyer ( "<<ext1->noeud->getIdNoeud()<<", "
                 << ext2->noeud->getIdNoeud()<<")"<<std::endl;

        n = ext2->noeud;
    }
    std::cout << n->getIdNoeud() << std::endl;

}


int main( int argc, char ** argv)	{

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    vector<Cable*> path;
    graphe->genererChemin(n1, n1, n2, path);

    envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], path);


}
