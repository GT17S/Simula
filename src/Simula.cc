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

int main()	{

    Graphe * graphe = Graphe::get();
    lireXml("test.xml", graphe);


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


       int n1 = 0;
       int n2 = 9;
       graphe->genererChemin(n1, n2);
        //graphe->genererTableChemin();
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


       while(  n1 != n2){
           extremite * x = graphe->getTable()[n1][n2];
           if(x){
              n1 = x->noeud->getIdNoeud();
              std::cout<< n1 << " ";
           }else break;
       }
       /*
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
