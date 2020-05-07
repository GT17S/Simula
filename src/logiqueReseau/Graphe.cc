#include "Graphe.hh"
#include <iostream>
#include <typeinfo>


vector<Noeud*> Graphe::sommets;/*!< Liste des sommets du Graphe */
vector<vector<Cable*>> Graphe::matrice; /*!< Matrice d'adjacences du Graphe */
//vector<vector<extremite*>> Graphe::table;/*!< Table de chemins du Graphe */

Graphe *Graphe::singlPtr = nullptr;


Graphe::Graphe(){

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
/*
void Graphe::setTable(vector<vector<extremite *> > t)
{
    table=t;
}
*/

void Graphe::setMatrice(vector<vector<Cable *>>m)
{
    matrice=m;
}


extremite * Graphe::getExtremite(int n1, int n2){
    Cable * cable = matrice[n1][n2];
    extremite * ext = cable->getExt(sommets[n1]);

    return ext;

}

bool Graphe::verifierReseau(int n1, int n2){
    int size_i1 = sommets[n1]->getInterfaces().size();
    int size_i2 = sommets[n2]->getInterfaces().size();

    for (int i = 0; i < size_i1; i++) {
        InterfaceFE * interface1 = sommets[n1]->getInterfaces()[i];
        for (int j = 0; j < size_i2; j++) {
            InterfaceFE * interface2 = sommets[n2]->getInterfaces()[j];
            if(interface1->getAdresseRes() != DEFAULT_IP && interface2->getAdresseRes() != DEFAULT_IP && interface1->getAdresseRes() == interface2->getAdresseRes()){
                //std::cout << "Meme reseau "<<n1 <<" "<<n2<<std::endl;
                return true;
            }
        }
    }
    return false;
}

int Graphe::parcourirVoisins(int  id_src , int id_n, int id_dest, vector<extremite *>& path){
    int size_m = matrice.size();

    if(matrice[id_n][id_dest]){
        // Directement lié
        path.push_back(getExtremite(id_n, id_dest));
        return id_n;
    }



    for (int i = 0; i < size_m; i++) {
        if( i != id_n && i != id_src ){
            Cable * cable = matrice[id_n][i];
            if(cable){
                // voisin
                //string nom = sommets[i]->getNom();

                if(sommets[i]->getTypeNoeud() == SWITCH){
                    // switch
                    std::cout <<"SWITCH"<<std::endl;
                    if(parcourirVoisins(id_n ,i, id_dest, path) > -1){

                        // trouver id_dest, retourner id_n
                        path.push_back(getExtremite(id_n, i));

                        return id_n;
                    }


                }
                else{ //Station ou routeur
                    std::cout <<"ELSE"<<std::endl;
                    if( i == id_dest){
                        // destination trouvée
                        return id_n;
                    }
                }
            }
        }
    }
    return -1;
}

int Graphe::parcourirPasserelle(int id_src, int id_n , string adresse, int n2, vector<extremite*> &path){

    if(!sommets[id_src]->verifierPasserelle(adresse)){
        // pas le meme reseau avec la passerelle
        return -1;
    }

    int size_m = matrice.size();
    for (int i = 0; i < size_m; i++) {
        if( i != id_n && i != id_src){
            Cable * cable = matrice[id_n][i];
            if(cable){
                // voisin
                if(sommets[i]->getTypeNoeud() == SWITCH){
                    std::cout <<"SWITCH"<<std::endl;
                    int result = parcourirPasserelle(id_n, i, adresse, n2, path);
                    //
                    if(result > -1){
                        // adresse trouvée , retourner resultat
                        path.push_back(getExtremite(id_n, i));
                        return result;
                    }
                }
                else{
                    std::cout <<"ELSE"<<std::endl;
                    // station ou routeur
                    for(InterfaceFE * fe : sommets[i]->getInterfaces()){
                        if(fe->getAdresseIP() == adresse){
                            // adresse passerelle trouvée
                            if(genererChemin(i, n2, path)){
                                // chemin trouvée , entre passerelle et destination
                                path.push_back(getExtremite(id_n, i));
                                return i;
                            }
                            // chemin non trouvée
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return -1;

}


int Graphe::genererChemin(int n1, int n2, vector<extremite *> &path){

    if(verifierReseau(n1, n2)){
        // meme reseau
        if(parcourirVoisins(n1, n1, n2, path))
            // trouvée
            return 1;
        else
            return -1;
    }
    else {
        // pas le meme reseau
        string adresse = verifierCoherence(sommets[n1], sommets[n2]);
        if(adresse != DEFAULT_IP){
            // redirection vers adresse passerelle
            int result = parcourirPasserelle(n1, n1, adresse, n2, path);
            if(result > -1)
                // n2 trouvée
                return 1;

            else return -1;
        }
        // pas de passerelle
        else return -1;
    }
}


std::string Graphe::verifierCoherence(Noeud * n1, Noeud * n2)
{
    string adresse = DEFAULT_IP;

    int size_i = n2->getInterfaces().size();

    for (int i = 0; i < size_i; i++ ) {
        adresse = n1->getPasserelleTableRoutage(n2->getInterface(i)->getAdresseRes());
        if(adresse != DEFAULT_IP)
            return adresse;
    }

    return adresse;

}


void Graphe::ajoutNoeudMatrice(Noeud* n)
{

    //setSommet(n);
    for(Noeud * N : sommets){
        if(n == N)
            return;
    }

    n->setIdNoeud(sommets.size());
    sommets.push_back(n);

    int taille_s = sommets.size();

    vector<Cable *> tempCables(taille_s, nullptr);

    matrice.push_back(tempCables);

    for (int i = 0; i < taille_s; i++) {

        matrice[i].push_back(nullptr);
    }
}

void Graphe::ajoutCableMatrice(Cable * c)
{

    Noeud * N1 = c->getExt1()->noeud , * N2 = c->getExt2()->noeud;

    int i_N1 = N1->getIdNoeud();
    int i_N2 = N2->getIdNoeud();

    matrice[i_N1][i_N2] = c;
    matrice[i_N2][i_N1] = c;
}

void Graphe::supprimerNoeudMatrice(Noeud * n)
{
    int indice = n->getIdNoeud();

    n = nullptr;
    delete n;
    sommets.erase(sommets.begin() + indice);


    for (unsigned int i = indice; i < sommets.size(); i++) {
        sommets[i]->setIdNoeud(i);
    }

    for (unsigned int i = 0; i < matrice.size(); i++) {
        matrice[i].erase( matrice[i].begin() + indice);
    }



    matrice.erase(matrice.begin()+indice);

}

void Graphe::supprimerCableMatrice(Cable * c)
{
    Noeud * N1 = c->getExt1()->noeud, * N2 = c->getExt2()->noeud;

    int i_N1 = N1->getIdNoeud();
    int i_N2 = N2->getIdNoeud();

    matrice[i_N1][i_N2] = nullptr;
    matrice[i_N2][i_N1] = nullptr;

}


