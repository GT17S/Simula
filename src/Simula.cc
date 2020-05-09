#include <iostream>
#include <vector>
#include "GFichier.hh"
#include "Graphe.hh"
#include "DataOutils.hh"

using std::vector;

void envoyer(Noeud * n1, vector<Cable*> path){

    int size_p = path.size();

    // pas de chemin
    if(!size_p)
        return;

    extremite * destExt;
    Cable * cable;
    Noeud * n = n1;
    extremite * nextExt = nullptr;
    bool check = false;
    for(int i = size_p - 1; i > -1; i--){
        cable = path[i];
        //ext1 = cable->getExt(n); //
        destExt = cable->getInverseExt(n); // 6
        std::cout <<"envoyer ( "<<destExt->noeud->getIdNoeud()<<", "
                 <<std::endl;

        n = destExt->noeud;
        if(!check)
        if(n->getTypeNoeud() == ROUTEUR || n->getTypeNoeud() == STATION)
        { nextExt = destExt; check =true;}

    }
    std::cout << destExt->noeud->getIdNoeud() << std::endl;
    std::cout << nextExt->noeud->getIdNoeud() << std::endl; //nextextPasserelle
    std::cout << path[size_p-1]->getExt(n1)->noeud->getIdNoeud()<<std::endl;
}


int main( int argc, char ** argv)	{

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    vector<Cable*> path;
    graphe->genererChemin(n1, n1, n2, path, true);

    //string data;
    //envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], 1025, 80, data);
    envoyer(graphe->getSommets()[n1], path);


}
