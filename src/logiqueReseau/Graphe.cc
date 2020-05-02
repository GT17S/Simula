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
    /*
    Station * S1 = dynamic_cast <Station *> n1;
    Routeur * R1 = dynamic_cast <Routeur *> n1;

    Station * S2 = dynamic_cast <Station *> n2;
    Routeur * R2 = dynamic_cast <Routeur *> n2;
    */

    int i,j;
    int sizeInterfaceI=n1->getInterfaces().size();
    int sizeInterfaceJ=n2->getInterfaces().size();
    int sizeTableRoutage1=n1->getTableRoutage().size();
                    for( i=0;i < sizeInterfaceI;i++)
                    {
                        for( j=0;j<sizeInterfaceJ;j++)
                        {
                            if (n1->getInterfaces()[i]->getAdresseRes() == n2->getInterfaces()[j]->getAdresseRes())
                            {
                                return n2->getInterfaces()[j]->getAdresseIP();
                            }
                        }
                    }

                    for( i=0;i < sizeTableRoutage1;i++)
                    {
                        for ( j = 0; j < sizeInterfaceJ; ++j)
                            {
                                if (n1->getTableRoutage()[i]->adresseReseau==n2->getInterfaces()[j]->getAdresseRes())
                                    {
                                        n1->getTableRoutage()[i]->passerelle;
                                    }
                            }
                    }

                    for ( i = 0; i < sizeTableRoutage1; ++i)
                    {
                        if (n1->getTableRoutage()[i]->adresseReseau== DEFAULT_IP)
                        {
                            return n1->getTableRoutage()[i]->passerelle;
                        }
                    }

                    return DEFAULT_IP ;

}

std::vector<int> rechercheVoisins ( std::vector<std::vector < Cable * >> matrice, int s)	{
	std::vector<int> v;
	for (unsigned int i = 0; i < matrice[s].size(); i++)	{
		if ( matrice[s][i] != nullptr)
			v.push_back(i);
	}
	return v;
}

std::vector<int> parcoursLargeur ( std::vector<std::vector < Cable * >> matrice, int src, int dest)	{
	std::vector <int> p;
	std::vector <int> file;
	unsigned int size = matrice.size();
	bool found = true; 
	p.resize( size);
	for (unsigned int i = 0; i < size; i++)	{
		p[i] = -2;
	}
	file.push_back ( src);
	p[src] = -1;
	while ( file.size() > 0 && found)	{
		int n_tmp = file[0];
		file.erase ( file.begin());
		std::vector<int> v = rechercheVoisins ( matrice, n_tmp);
		for ( unsigned int i = 0; i < v.size(); i++)	{
			if ( p[v[i]] != -2)	{
				file.push_back ( v[i]);
				p[i] = n_tmp;
			}
			if ( v[i] == dest) found = false;
		} 
	}
	return p;	
}

void Graphe::genererTableChemin()	{
	for (unsigned int i = 0; i < matrice.size(); i++)	{
		std::cout << "Pour aller de : " << sommets[i]->getNom() << std::endl;
		for (unsigned int j = 0; j < matrice[i].size(); j++)	{
			if ( i != j)	{
				std::cout << "\tvers " << sommets[j]->getNom() << std::endl;
				int path = i, o_path = i;
				Switch	* sw_src 	= dynamic_cast < Switch *> 	(sommets[path]),
						* sw_dest 	= dynamic_cast < Switch *> 	(sommets[j]);
				Hub 	* h_src 	= dynamic_cast < Hub *> 	(sommets[path]),
						* h_dest 	= dynamic_cast < Hub *> 	(sommets[j]);
				if ( !( sw_src || sw_dest || h_src || h_dest))	{
					std::cout << "\tNi Switch ni routeur" << std::endl;
					while ( (unsigned int)path != j)	{
						std::cout << "\tPasse par : " << path << std::endl;
						o_path = path;
						Station * s_src 	= dynamic_cast < Station *> (sommets[path]),
								* s_dest	= dynamic_cast < Station *> (sommets[j]);
						Routeur * r_src		= dynamic_cast < Routeur *> (sommets[path]),
								* r_dest 	= dynamic_cast < Routeur *> (sommets[j]);					
						std::string s;
						if ( (s_src && s_dest) || (r_src && r_dest) || (s_src && r_dest) || (r_src && s_dest) )	{
							s = verifierCoherence ( sommets[i], sommets[j]);
							// Par defaut
							bool loop = true;
							for ( unsigned int k = 0; k < sommets.size() && loop; k++)	{
								std::vector<InterfaceFE*> tmp = sommets[k]->getInterfaces();
								for (unsigned int l = 0; l < tmp.size(); l++)	{
									if ( tmp[l]->getAdresseIP() == s)	{
										path = k;
										loop = false;
									}
								}
							}
							std::vector<int> v_src = rechercheVoisins ( matrice, o_path);
							for (unsigned int k = 0; k < v_src.size() && !loop; k++)	{
								if ( v_src[k] == path)	{
									table[i][j].tab.push_back(path);
									loop = true;
								}
							}
							std::cout << "\t\t" << table[i][j].tab[i] << std::endl;
						}
					}
				}
			}
		}	
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


