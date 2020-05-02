#include <iostream>
#include "Cable.hh"
#include "Noeud.hh"
#include "Routeur.hh"
#include "Graphe.hh"


using  namespace  std;

int main()	{


    Cable * A, *A1;//,*A2,*A3, ;
    A = new Cable();
    A1= new Cable();
//    A2= new Cable();
//    A3= new Cable();

    Graphe  *  graphe = new Graphe();

    Station * s1, * s2;
    s1 = new Station();
    s2 = new Station();
	Routeur * r1;
	r1 = new Routeur();

    r1->setNbPort(3);

    A->connexionNoeuds( s1, 0, r1, 0);
    A1->connexionNoeuds(s2, 0, r1, 1);

	s1->getInterface( 0)->setAdresseIP( "192.168.10.1");
	s1->getInterface( 0)->setAdresseRes ("192.168.10.0");
	s1->getInterface( 0)->setMasque ("255.255.255.0");
	
	s2->getInterface( 0)->setAdresseIP( "192.168.10.2");
	s2->getInterface( 0)->setAdresseRes ("192.168.10.0");
	s2->getInterface( 0)->setMasque ("255.255.255.0");

	r1->getInterface( 0)->setAdresseIP( "192.168.10.3");
	r1->getInterface( 0)->setAdresseRes ("192.168.10.0");
	r1->getInterface( 0)->setMasque ("255.255.255.0");

	r1->getInterface( 1)->setAdresseIP( "192.168.10.4");
	r1->getInterface( 1)->setAdresseRes ("192.168.10.0");
	r1->getInterface( 1)->setMasque ("255.255.255.0");

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


    delete graphe;
    return 0;
}
