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

    Graphe * graphe = new Graphe();

    //ecrireXml("test.xml", graphe);
    lireXml("test.xml");


    int size_m = graphe->getMatrice().size();
    std::cout << size_m << endl;
       for (int i = 0; i < size_m; ++i) {
           for (int j = 0; j < size_m; ++j) {
               if(graphe->getMatrice()[i][j]){
                   int id = graphe->getMatrice()[i][j]->getId();
                    std::cout << id << " ";
               }
               else std::cout << "0" << " ";
           }
           std::cout <<std::endl;
       }

   delete graphe;
    return 0;
}
