#include "../include/logiqueReseau/Graphe.hh"

#include <iostream>


Graphe::Graphe(){

}

Graphe::Graphe(Graphe & g)
{
    this->sommets=g.sommets;
    this->matrice=g.matrice;
    this->table=g.table;
}


Graphe::~Graphe()
{
    //cout<<"destruction sommets"<<endl;
     // Destruction des noeuds
     for (auto s : sommets) {
         delete s;
         s = nullptr;
     }
     sommets.clear();

     // Destruction de la matrice
     matrice.clear();

     // Destruction de la table des chemins
     table.clear();
}


void Graphe::setSommet(Noeud* N)
{
    for(Noeud * n : this->sommets){
        if(n == N)
            return;
    }

    sommets.push_back(N);
}

void Graphe::setSommets(vector<Noeud*> s)
{
    this->sommets = s;
}

void Graphe::setTable(vector<vector<Chemin>> t)
{
    this->table=t;
}

void Graphe::setMatrice(vector<vector<Cable *>>m)
{
    this->matrice=m;
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

    setSommet(n);

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

    int size_s = this->sommets.size();
    int i_N1, i_N2;
    Noeud * N1 = c->getExt1() , * N2 = c->getExt2();
    for (int i = 0; i < size_s; i++) {
        if(this->sommets[i] == N1) i_N1 = i;
        if(this->sommets[i] == N2) i_N2 = i;
    }


    this->matrice[i_N1][i_N2] = c;
    this->matrice[i_N2][i_N1] = c;
}

void Graphe::supprimerNoeudMatrice(Noeud * n)
{
    int indice = 0;

    for(auto i = this->sommets.begin(); i != this->sommets.end(); i++)
        {
            if ( *i == n){
                delete *i;
                *i = nullptr;
                sommets.erase(i);
                break;
            }
            indice++;
    }

    for ( auto i = this->matrice.begin(); i != this->matrice.end() ; i++){
        (*i).erase( (*i).begin()+indice);
    }
    this->matrice.erase(this->matrice.begin()+indice);

}

void Graphe::supprimerCableMatrice(Cable * c)
{
    int size_s = this->sommets.size();
    int i_N1, i_N2;
    Noeud * N1 = c->getExt1(), * N2 = c->getExt2();
    for (int i = 0; i < size_s; i++) {
        if(this->sommets[i] == N1) i_N1 = i;
        if(this->sommets[i] == N2) i_N2 = i;
    }

    delete c;

    this->matrice[i_N1][i_N2] = nullptr;
    this->matrice[i_N2][i_N1] = nullptr;

}


