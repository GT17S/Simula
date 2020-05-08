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

    // 0 6 8 9 10 7 5

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

}


int main( int argc, char ** argv)	{

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    vector<Cable*> path;
    graphe->genererChemin(n1, n1, n2, path);

    // cable last (src, suivant)
    // cable last-1 (suivant , suivant+1)
    // cable last-i (suivant +1, suivant+i)
    // cable 0 (suivant+size-1, dest)

    // ext 1 *;
    // ext 2 *;
    // cable 1
    // ext1 = cable1->getExt(src)
    // ext2 = cable1->Inverse(ext1->noeud);
    // envoyer (ext1, ext2)
    // cable 2
    // ext1 = cable2 ->getExt(ex2->noeud);
    // ext2 = cable2 ->Inverse(ext1->noeud);
    // envoyer(ext1, ext2)



    std::cout <<path.size()<<std::endl;
    for (int i = path.size()-1; i > -1; i--) {
        std::cout<<"Cable "<<i<<"("<<path[i]->getExt1()->noeud->getIdNoeud()<<
                   " ,"<<path[i]->getExt2()->noeud->getIdNoeud()<<" )"<<std::endl;
    }
    std::cout<<std::endl;

    envoyer(graphe->getSommets()[n1], graphe->getSommets()[n2], path);
    /*
    int i = path.size() -1;
    extremite * x  = path[i]->getExt1();
    do{
        std::cout<< x->noeud->getIdNoeud()<<" envoie à "<<std::endl;
        x = path[i]->getExt(x->noeud);
        i--;

    }while(i > -1);
*/

}
