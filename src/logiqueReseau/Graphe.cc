#include "Graphe.hh"
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

std::string Graphe::verifierCoherence(Noeud * n1, Noeud * n2)
{
    int i,j;
    int sizeInterfaceI=n1->getInterfaces().size();
    int sizeInterfaceJ=n2->getInterfaces().size();
    int sizeTableRoutage1=n1->getTableRoutage().size();

	for( i=0;i < sizeInterfaceI;i++)
		for( j=0;j<sizeInterfaceJ;j++)
			if (n1->getInterfaces()[i]->getAdresseRes() == n2->getInterfaces()[j]->getAdresseRes())	{
				return n2->getInterfaces()[j]->getAdresseIP();
			}
	for( i=0;i < sizeTableRoutage1;i++)
		for ( j = 0; j < sizeInterfaceJ; ++j)
				if (n1->getTableRoutage()[i]->adresseReseau==n2->getInterfaces()[j]->getAdresseRes())	{
						return n1->getTableRoutage()[i]->passerelle;
				}
	for ( i = 0; i < sizeTableRoutage1; ++i)
		if (n1->getTableRoutage()[i]->adresseReseau== DEFAULT_IP)	{
			return n1->getTableRoutage()[i]->passerelle;
		}
/*    Station * S1 = dynamic_cast <Station *> (n1);
		if ( S1)	{
			return S1->getPasserelle();
		}
*/	return DEFAULT_IP;
}

std::vector<int> rechercherVoisins ( std::vector<std::vector < Cable * >> matrice, int s)	{
	std::vector<int> v;
	for (unsigned int i = 0; i < matrice[s].size(); i++)	{
		if ( matrice[s][i] != nullptr)
			v.push_back(i);
	}
	return v;
}

std::vector<int> initParcoursLargeur ( std::vector<int> * f, unsigned int size, int src)	{
	std::vector<int> p;
	p.resize( size);
	for (unsigned int i = 0; i < size; i++)
		p[i] = -2;
	f->push_back ( src);
	p[src] = -1;	
	return p;
}

std::vector<int> parcoursLargeur ( std::vector<std::vector < Cable * >> matrice, int src, int dest)	{
	bool found = true; 
	std::vector <int> file;
	std::vector <int> p = initParcoursLargeur ( &file,  matrice.size(), src);
	while ( file.size() > 0 && found)	{
		std::vector<int> v = rechercherVoisins ( matrice, file[0]);
		for ( unsigned int i = 0; i < v.size(); i++)	{
			if ( p[v[i]] == -2)	{
				file.push_back ( v[i]);
				p[v[i]] = file[0];
			}
			if ( v[i] == dest) found = false;
		}
		file.erase ( file.begin());
	}
	return p;	
}

int rechercherNoeudsIntermediaires ( std::vector < Noeud *> sommets, std::string s)	{

	for ( unsigned int i = 0; i < sommets.size(); i++)	{
		std::vector<InterfaceFE*> tmp = sommets[i]->getInterfaces();
		for (unsigned int j = 0; j < tmp.size(); j++)
			if ( tmp[j]->getAdresseIP() == s)
				return i;
	}
	return -1;
}

std::vector<int> reconstituerChemin ( std::vector<std::vector < Cable * >> matrice, int o_path, int path) {
	std::vector <int> p = parcoursLargeur ( matrice, o_path, path);
	std::vector <int> route;
	int pred = path;
	while ( p[pred] != o_path)	{
		route.push_back (p[pred]);
		pred = p[pred];
	}
	return route;	
}

void ajouterChemin ( Chemin * c, std::vector <int> route, int path)	{
	for (int i = (int)route.size()-1; i >= 0 ; i--)
		c->tab.push_back(route[i]);
	c->tab.push_back(path);
	return;
}

bool trouverChemin ( std::vector<std::vector < Cable * >> matrice, std::vector < Noeud *> sommets, Chemin * c, std::string s, int * path, int o_path)	{
	
	if ( s == DEFAULT_IP)	return false;
	*path = rechercherNoeudsIntermediaires ( sommets, s);
	if ( *path == -1) return false;
	std::vector <int> route = reconstituerChemin ( matrice, o_path, *path);
	ajouterChemin ( c, route, *path);
	return true;	
}

void Graphe::rechercherChemin ( Chemin * c, int src, int dest)	{
	int path = src, o_path = src;
	bool way = true;
	while ( path != dest && way)	{
		o_path = path;
		Station * s_src 	= dynamic_cast < Station *> (sommets[path]);
		Routeur * r_src		= dynamic_cast < Routeur *> (sommets[path]);
		if ( (s_src != nullptr) ^ (r_src != nullptr))	{
			std::string s = verifierCoherence ( sommets[path], sommets[dest]);
			way = trouverChemin (matrice, sommets, c, s, &path, o_path);
		}
	}
	return;
}

void Graphe::remplirChemins ( int src) {	
	if ( dynamic_cast < Switch *> 	(sommets[src]) || dynamic_cast < Hub *> 	(sommets[src]))
		return;
	for (unsigned int i = 0; i < sommets.size(); i++)	{
		Chemin c;
		if ( (unsigned int) src != i)	{
			Switch	* sw_dest 	= dynamic_cast < Switch *> 	(sommets[i]);
			Hub		* h_dest 	= dynamic_cast < Hub *> 	(sommets[i]);
			if ( !( sw_dest || h_dest))
				rechercherChemin( &c, src, i);
		}
		table[src].push_back(c);
	}
}

void Graphe::genererTableChemin()	{
	for (unsigned int i = 0; i < sommets.size(); i++)	{
		std::vector<Chemin> vc;
		table.push_back(vc);
		remplirChemins ( i);
	}
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


