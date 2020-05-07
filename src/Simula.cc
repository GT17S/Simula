#include <iostream>
#include <string>
#include "Cable.hh"
#include "Noeud.hh"
#include "Hub.hh"
#include "Routeur.hh"
#include "Graphe.hh"
#include "Station.hh"
#include "GFichier.hh"

using  namespace  std;

int main(int argc, char ** argv)	{

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);

    /*
    int size_m = graphe->getMatrice().size();
       for (int i =1; i < size_m; ++i) {
           //std::cout <<"ID =" <<graphe->getSommets()[i]->getIdNoeud()<<" --";
           for (int j = 0; j < i; ++j) {
               if(graphe->getMatrice()[i][j]){
                   int id = graphe->getMatrice()[i][j]->getId();
                    std::cout << id << " ";
               }
               else std::cout << "0" << " ";
           }
           std::cout <<std::endl;
       }
*/

  //     int n1 = 5;
//       int n2 = 0;


    //graphe->genererChemin(n1, n1,n1, n2);

       int  n1 = atoi(argv[1]);
       int n2 = atoi(argv[2]);

       int n3 = atoi(argv[3]);
       int n4 = atoi(argv[4]);

       vector<extremite*> path1;
       vector<extremite*> path2;

       graphe->genererChemin(n1,n2, path1);

       graphe->genererChemin(n3,n4, path2);

       for(extremite * x: path1){
           std::cout<< x->noeud->getIdNoeud()<<" ";
       }

       std::cout<<std::endl<<std::endl;

       for(extremite * x: path2){
           std::cout<< x->noeud->getIdNoeud()<<" ";
       }
       std::cout<<std::endl<<std::endl;
       /* std::cout<<std::endl<<std::endl;
       n1 = n3;
       n2 = n4;
       while(  n1 != n2){
           extremite * x = graphe->getTable()[n1][n2];
           if(x){
              n1 = x->noeud->getIdNoeud();
              std::cout<< n1 << " ";
           }else break;
       }
      std::cout<<std::endl;
      */

/*

        int size_tt = graphe->getTable().size();
          for (int i = 0; i < size_tt; ++i) {
              //std::cout <<"ID =" <<graphe->getSommets()[i]->getIdNoeud()<<" --";
              for (int j = 0; j < size_tt; ++j) {
                  extremite * x = graphe->getTable()[i][j];
                  if(x){
                      //int id = graphe->getTable[i][j]->getId();

                       std::cout << x->noeud->getIdNoeud() << " ";
                  }
                  else std::cout << "-1" << " ";
              }
              std::cout <<std::endl;
          }

*/
/*int n1, n2;

  int size_tt = graphe->getTable().size();
         for (int i = 0; i < size_tt; i++) {
             n1 = i;
             std::cout << "De "<<i<<std::endl;
             for (int j = 0; j < size_tt; j++) {
                 n2 =j;
                 std::cout << "Vers "<<j<<" = ";
                 //extremite * x;
                 while(  n1 != n2){
                     extremite * x = graphe->getTable()[n1][n2];
                     if(x){
                        n1 = x->noeud->getIdNoeud();
                        std::cout<< n1 << " ";
                     }else break;
                 }
                 std::cout << std::endl;
             }
         }
*/
       /*
         std::cout<< n1 << " ";
       do{
          n1 = graphe->getTable()[n1][n2]->noeud->getIdNoeud();
          std::cout<< n1 << " ";

       }while(n1 != n2);

           std::cout<<std::endl;


*/

    //ecrireXml("test.xml", graphe);
    delete graphe;
    return 0;
}
