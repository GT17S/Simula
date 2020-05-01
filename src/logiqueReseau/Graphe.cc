#include "../include/logiqueReseau/Graphe.hh"
#include <iostream>

vector<Noeud*> Graphe::sommets;/*!< Liste des sommets du Graphe */
vector<vector<Cable*>> Graphe::matrice; /*!< Matrice d'adjacences du Graphe */
vector<vector<Chemin>> Graphe::table;/*!< Table de chemins du Graphe */

Graphe::Graphe(){

}

Graphe::Graphe(Graphe & g)
{
    sommets=g.sommets;
    matrice=g.matrice;
    table=g.table;
}


Graphe::~Graphe()
{
    //cout<<"destruction sommets"<<endl;
     // Destruction des noeuds


    for(auto i = sommets.begin(); i!= sommets.end() ;){

        //std::cout << "Supprimer " << (*i)->getNom() <<std::endl;
        delete *i;
        //*i = nullptr;
    }

    sommets.clear();

     // Destruction de la matrice
     matrice.clear();

     // Destruction de la table des chemins
     table.clear();
}


void Graphe::setSommet(Noeud* N)
{
    for(Noeud * n : sommets){
        if(n == N)
            return;
    }

    sommets.push_back(N);
}

void Graphe::setSommets(vector<Noeud*> s)
{
    sommets = s;
}

void Graphe::setTable(vector<vector<Chemin>> t)
{
    table=t;
}

void Graphe::setMatrice(vector<vector<Cable *>>m)
{
    matrice=m;
}

bool Graphe::verfierCoherence(Noeud *N1, Noeud *N2)
{

}

void Graphe::miseAjourDeMatrice(QEvent *event)
{

}

void Graphe::genererTableChemin()
{

}

void Graphe::ajoutNoeudMatrice(Noeud* n)
{

    //setSommet(n);
    for(Noeud * N : sommets){
        if(n == N)
            return;
    }

    sommets.push_back(n);

    int taille_s = sommets.size();

    vector<Cable *> temp(taille_s, nullptr);
    matrice.push_back(temp);

    for (int i = 0; i < taille_s; i++) {
       //cout << matrice.at(i).size() << endl;

       matrice[i].push_back(nullptr);
    }
}

void Graphe::ajoutCableMatrice(Cable * c)
{

    int size_s = sommets.size();
    int i_N1, i_N2;
    Noeud * N1 = c->getExt1() , * N2 = c->getExt2();
    for (int i = 0; i < size_s; i++) {
        if(sommets[i] == N1) i_N1 = i;
        if(sommets[i] == N2) i_N2 = i;
    }


    matrice[i_N1][i_N2] = c;
    matrice[i_N2][i_N1] = c;
}

void Graphe::supprimerNoeudMatrice(Noeud * n)
{
    int indice = 0;

    for(auto i = sommets.begin(); i != sommets.end(); i++)
        {
            if ( *i == n){
                *i = nullptr;
                delete *i;
                sommets.erase(i);
                //if( i < sommets.end())
                indice = i - sommets.begin();
                break;
            }

    }

    for ( auto i = matrice.begin(); i != matrice.end() ; i++){
        (*i).erase( (*i).begin()+indice);
    }

    matrice.erase(matrice.begin()+indice);

}

void Graphe::supprimerCableMatrice(Cable * c)
{
    int size_s = sommets.size();
    int i_N1, i_N2;
    Noeud * N1 = c->getExt1(), * N2 = c->getExt2();
    for (int i = 0; i < size_s; i++) {
        if(sommets[i] == N1) i_N1 = i;
        if(sommets[i] == N2) i_N2 = i;
    }

    //delete c;
    //c = nullptr;

    matrice[i_N1][i_N2] = nullptr;
    matrice[i_N2][i_N1] = nullptr;

}


