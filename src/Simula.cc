#include <iostream>
#include "../include/logiqueReseau/Cable.hh"
#include "../include/logiqueReseau/Noeud.hh"
#include "../include/logiqueReseau/Graphe.hh"
#include "../include/logiqueReseau/Station.hh"
using  namespace  std;

int main()
{

    Cable * A, *A1,*A2,*A3;
    A = new Cable();
    A1= new Cable();
    A2= new Cable();
    A3= new Cable();

    Graphe  *  graphe = new Graphe();

    Station * nadjib, *mougi, *babou, *mahdi;
    nadjib= new Station();
    mougi = new Station();
    babou = new Station();
    mahdi = new Station();

    nadjib->setNbPort(2);
    mougi->setNbPort(3);
    mahdi->setNbPort(2);


    nadjib->setNom("nadjib");
    mougi->setNom("mougi");
    babou->setNom("babou");
    mahdi->setNom("mahdi");

    graphe->ajoutNoeudMatrice(nadjib);
    graphe->ajoutNoeudMatrice(mougi);
    graphe->ajoutNoeudMatrice(babou);
    graphe->ajoutNoeudMatrice(mahdi);


    if(A->connexionNoeuds(mougi, 0, nadjib, 0))
       graphe->ajoutCableMatrice(A);

    if(A1->connexionNoeuds(mougi, 1, babou, 0))
           graphe->ajoutCableMatrice(A1);
    if(A2->connexionNoeuds(mougi, 2, mahdi, 0))
            graphe->ajoutCableMatrice(A2);
    if(A3->connexionNoeuds(nadjib, 1, mahdi, 1))
            graphe->ajoutCableMatrice(A3);

/*
    int size_s = graphe->getSommets().size();
    for (int i = 0; i < size_s; i++) {
        int id = graphe->getSommets()[i]->getIdNoeud();
        std::cout << id << " ";
    }
*/


    int size_m = graphe->getMatrice().size();
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


    //graphe->supprimerCableMatrice(A3);

    graphe->supprimerNoeudMatrice(mougi);
    graphe->supprimerNoeudMatrice(babou);
    graphe->supprimerNoeudMatrice(nadjib);
    graphe->supprimerNoeudMatrice(mahdi);

    //if(graphe->getSommets()[3]->getInterface(1)->getCable())
    //    std::cout <<"**********I HAVE CABLE************"<<std::endl;
/*
    int size_s = graphe->getCables().size();
    for (int i = 0; i < size_s; i++) {
        int id = graphe->getCables()[i]->getId();
        std::cout << id << " ";
    }
*/

    std::cout <<"**********************"<<std::endl;
    size_m = graphe->getMatrice().size();

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
