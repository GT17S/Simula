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


Cable *A, *A1,*A2 , *A3 ,*A4,*A5 ,*A6 , *A7, *A8, *A9;

    A = new Cable();
    A1= new Cable();
    A2= new Cable();
    A3 = new Cable();
    A4= new Cable();
    A5= new Cable();
    A6 = new Cable();
    A7= new Cable();
    A8 = new Cable();
    A9 = new Cable();


    Graphe  *  graphe = new Graphe();

    Station * s1, * s2 , *s3 , *s4 , *s5 ,*s6;
    s1 = new Station();
    s2 = new Station();
    s3 = new Station();
    s4 = new Station();
    s5 = new Station();
    s6 = new Station();

    Switch *sw1 ,*sw2 , *sw3 ;
     sw1 = new Switch();
     sw2 = new Switch();
     sw3 = new Switch();

     sw1->setNbPort(3);
     sw2->setNbPort(3);
     sw3->setNbPort(3);

    Routeur * r1, *r2;
    r1 = new Routeur();
    r2 = new Routeur();


    r1->setNbPort(3);
    r2->setNbPort(3);




    A->connexionNoeuds( s1, 0, sw1, 0);
    A1->connexionNoeuds(s2, 0, sw1, 1);
    A2->connexionNoeuds(sw1, 2, r1, 0);

    A3->connexionNoeuds( s3, 0, sw2, 0);
    A4->connexionNoeuds(s4, 0, sw2, 1);
    A5->connexionNoeuds(sw2, 2, r1, 1);

    A6->connexionNoeuds( r1, 2, r2, 0);
    A7->connexionNoeuds(r2, 1, sw3, 0);

    A8->connexionNoeuds(sw3, 1, s5, 0);
    A9->connexionNoeuds( sw3, 2, s6, 0);




    s1->getInterface( 0)->setAdresseIP( "192.168.10.1");
    s1->getInterface( 0)->setAdresseRes ("192.168.10.0");
    s1->getInterface( 0)->setMasque ("255.255.255.192");

    Route *Rs1 = new Route();
    Rs1->adresseReseau = "0.0.0.0";
    Rs1->masque = "0.0.0.0";
    Rs1->passerelle = "192.168.10.3";

    s1->setTableRoutage(Rs1);
    s1->setPasserelle ("192.168.10.3");

    s2->getInterface( 0)->setAdresseIP( "192.168.10.2");
    s2->getInterface( 0)->setAdresseRes ("192.168.10.0");
    s2->getInterface( 0)->setMasque ("255.255.255.192");


    Route * Rs2 = new Route();

    Rs2->adresseReseau = "0.0.0.0";
    Rs2->masque = "0.0.0.0";
    Rs2->passerelle = "192.168.10.3";

  s2->setTableRoutage(Rs2);
   s2->setPasserelle ("192.168.10.3");


    r1->getInterface( 0)->setAdresseIP("192.168.10.3");
    r1->getInterface( 0)->setAdresseRes ("192.168.10.0");
    r1->getInterface( 0)->setMasque ("255.255.255.192");


    r1->getInterface( 1)->setAdresseIP("192.168.10.4");
    r1->getInterface( 1)->setAdresseRes ("192.168.10.0");
    r1->getInterface( 1)->setMasque ("255.255.255.192");


    s3->getInterface( 0)->setAdresseIP( "192.168.10.5");
    s3->getInterface( 0)->setAdresseRes ("192.168.10.0");
    s3->getInterface( 0)->setMasque ("255.255.255.192");

    Route * Rs3 = new Route();
    Rs3->adresseReseau = "0.0.0.0";
    Rs3->masque = "0.0.0.0";
    Rs3->passerelle = "192.168.10.4";

    s3->setTableRoutage(Rs3);
    s3->setPasserelle ("192.168.10.4");


    s4->getInterface( 0)->setAdresseIP( "192.168.10.6");
    s4->getInterface( 0)->setAdresseRes ("192.168.10.0");
    s4->getInterface( 0)->setMasque ("255.255.255.192");

    Route *Rs4 = new Route();
    Rs4->adresseReseau = "0.0.0.0";
    Rs4->masque = "0.0.0.0";
    Rs4->passerelle = "192.168.10.4";

    s4->setTableRoutage(Rs4);
    s4->setPasserelle ("192.168.10.4");

    r1->getInterface( 2)->setAdresseIP("192.168.10.65");
    r1->getInterface( 2)->setAdresseRes ("192.168.10.64");
    r1->getInterface( 2)->setMasque ("255.255.255.192");

    Route *Rr1 = new Route();
    Rr1->adresseReseau = "192.168.10.128";
    Rr1->masque = "255.255.255.192";
    Rr1->passerelle = "192.168.10.66";

    //r1->setTableRoutage(Rr1);


    r2->getInterface( 0)->setAdresseIP("192.168.10.66");
    r2->getInterface( 0)->setAdresseRes ("192.168.10.64");
    r2->getInterface( 0)->setMasque ("255.255.255.192");

    Route *Rr2 = new Route();
    Rr2->adresseReseau = "192.168.10.0";
    Rr2->masque = "255.255.255.192";
    Rr2->passerelle = "192.168.10.65";

    r2->setTableRoutage(Rr2);



    r2->getInterface( 1)->setAdresseIP("192.168.10.129");
    r2->getInterface( 1)->setAdresseRes ("192.168.10.128");
    r2->getInterface( 1)->setMasque ("255.255.255.192");




    s5->getInterface( 0)->setAdresseIP( "192.168.10.130");
    s5->getInterface( 0)->setAdresseRes ("192.168.10.128");
    s5->getInterface( 0)->setMasque ("255.255.255.192");

    Route *Rs5 = new Route();
    Rs5->adresseReseau = "0.0.0.0";
    Rs5->masque = "0.0.0.0";
    Rs5->passerelle = "192.168.10.129";

    s5->setTableRoutage(Rs5);
   s5->setPasserelle ("192.168.10.129");

    s6->getInterface( 0)->setAdresseIP( "192.168.10.131");
    s6->getInterface( 0)->setAdresseRes ("192.168.10.128");
    s6->getInterface( 0)->setMasque ("255.255.255.192");

    Route *Rs6 = new Route();
    Rs6->adresseReseau = "0.0.0.0";
    Rs6->masque = "0.0.0.0";
    Rs6->passerelle = "192.168.10.129";

    s6->setTableRoutage(Rs6);
   s6->setPasserelle ("192.168.10.129");


int size_m = graphe->getMatrice().size();
       for (int i = 0; i < size_m; ++i) {
           std::cout << graphe->getSommets()[i]->getNom() << ' ';
           for (int j = 0; j < size_m; ++j) {
               if(graphe->getMatrice()[i][j]){
                   int id = graphe->getMatrice()[i][j]->getId();
                    std::cout << id << " ";
               }
               else std::cout << "0" << " ";
           }
           std::cout <<std::endl;
       }

   // ecrireXml("test.xml", graphe);
    delete graphe;
    return 0;
}
