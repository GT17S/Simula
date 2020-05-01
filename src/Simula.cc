#include <iostream>
#include "../include/logiqueReseau/Cable.hh"
#include "../include/logiqueReseau/Noeud.hh"
#include "../include/logiqueReseau/Graphe.hh"
#include "../include/logiqueReseau/Station.hh"
using  namespace  std;

int main()
{
  std::string s("Test");
	Data d(s);
	std::cout << d << std::endl;


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

    A->connexionNoeuds(mougi, 0, nadjib, 0);
    A1->connexionNoeuds(mougi, 1, babou, 0);
    A2->connexionNoeuds(mougi, 2, mahdi, 0);
    A3->connexionNoeuds(nadjib, 1, mahdi, 1);




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

    delete mahdi;

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

    std::cout << graphe->getSommets().size() <<std::endl;
    delete graphe;

    return 0;
}
