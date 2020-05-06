#include "Graphe.hh"
#include <iostream>
#include <typeinfo>


vector<Noeud*> Graphe::sommets;/*!< Liste des sommets du Graphe */
vector<vector<Cable*>> Graphe::matrice; /*!< Matrice d'adjacences du Graphe */
vector<vector<extremite*>> Graphe::table;/*!< Table de chemins du Graphe */

Graphe *Graphe::singlPtr = nullptr;


Graphe::Graphe(){

}
/*
Graphe::Graphe(Graphe & g)
{
    sommets=g.sommets;
    matrice=g.matrice;
    table=g.table;
}
*/

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

void Graphe::setTable(vector<vector<extremite *> > t)
{
    table=t;
}

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
            if(interface1->getAdresseRes() == interface2->getAdresseRes()){
                std::cout << "Meme reseau "<<n1 <<" "<<n2<<std::endl;
                return true;
            }
        }
    }
    std::cout << "Pas le meme reseau"<<n1<<" "<<n2<<std::endl;
    return false;
}

int Graphe::parcourirVoisins(int  id_src , int id_n, int id_dest){
    std::cout << "Parcourir voisins "<<id_src<<" "<<id_n<<" "<<id_dest<<std::endl;
    int size_m = matrice.size();

    if(table[id_n][id_dest]){
        std::cout << " Parcourir déja existe"<<std::endl;
        return id_n;
    }
    //  S1 ---SW1 --- SW2 -- S2
    if(matrice[id_n][id_dest]){
        //Cable * cable = matrice[id_n][id_dest];
        //extremite * ext_dest = cable->getExt(sommets[id_n]);
        table[id_n][id_dest] = getExtremite(id_n, id_dest);
        //std::cout << "Directment = Chemin de "<<id_n<<" "<<id_dest<<" = "<<ext_dest->noeud->getIdNoeud()<<std::endl;
        return id_n;
    }



    for (int i = 0; i < size_m; i++) {
        if( i != id_n && i != id_src ){
            Cable * cable = matrice[id_n][i];
            if(cable){
                std::cout << "voisin "<<id_n <<" "<<i<< std::endl;
                //Switch * n = sommets[i];
                string nom = sommets[i]->getNom();
                std::cout << nom << std::endl;
                if(nom == "Switch"){
                    std::cout << "Cest un switch"<<std::endl;
                    if(parcourirVoisins(id_n ,i, id_dest) > -1){

                        //Cable * cable2 = matrice[id_n][i];
                        //extremite * ext_src = cable2->getExt(sommets[id_n]);
                        //std::cout << "DEFAULT =Chemin de "<<id_n<<" "<<id_dest<<" = "<<ext_src->noeud->getIdNoeud()<<std::endl;
                        table[id_n][id_dest] = getExtremite(id_n, i);

                        return id_n;
                    }


                }
                else{ //Station ou routeur
                    std::cout << "Cest une station ou routuer"<<std::endl;
                    if( i == id_dest){
                        std::cout << "DISTINATION FINALE "<<id_dest<<std::endl;
                        extremite * ext = cable->getExt(sommets[id_n]);

                        table[id_n][id_dest] = ext;

                        return id_n;
                    }


                }

            }

        }
    }
    return -1;
}

int Graphe::parcourirPasserelle(int id_src, int id_n , string adresse, int n2){
    std::cout << "Parcourir passerelle "<<id_src<<" "<<id_n<<" "<<adresse<<std::endl;

    if(!sommets[id_src]->verifierPasserelle(adresse)){
        std::cout << "verifier passerelle pas le meme reseau"<<std::endl;
        return -1;
    }

    int size_m = matrice.size();
    for (int i = 0; i < size_m; i++) {
        if( i != id_n && i != id_src ){
            Cable * cable = matrice[id_n][i];
            if(cable){
                std::cout << "voisin "<<id_n <<" "<<i<< std::endl;
                //Switch * n = sommets[i];
                string nom = sommets[i]->getNom();
                std::cout << nom << std::endl;
                if(nom == "Switch"){
                    std::cout << " I = SWITCH =" <<i<<std::endl;
                    int result = parcourirPasserelle(id_n, i, adresse, n2);
                    if(result > -1){
                        // result = routeur
                        std::cout << "Result SWITCH= "<< result<< std::endl;
                        std::cout << "Appeller switch"<< i<<" "<<result<<std::endl;
                        //Cable * cable2 = matrice[id_n][i];
                        //extremite * ext_src = cable2->getExt(sommets[id_n]);
                        //std::cout << "Chemin de "<<id_n<<" "<<result<<" = "<<ext_src->noeud->getIdNoeud()<<std::endl;
                        table[id_n][result] = getExtremite(id_n, i);
                        int result_gen = genererChemin(result, n2);
                        std::cout << "GENERER = "<< result<<std::endl;
                        if( result_gen == 1){
                            table[i][n2] = getExtremite(i , result);
                            table[id_n][n2] = getExtremite(id_n, i);
                            return i;

                        }else if(result_gen ==2){
                            //                              i, rest       id_n ,result
                             // 6 (0, 6, ad(10), 10)---> 8, 6,   10    = (6,10 ??8) ;;  0    ,10     = (0,6)


                             // 8 (6, 8, ad(10), 10) --> 10  , 8,10 = (8,10) ;; 6,10 = (6,10??8)
                            // s1 -- sw6 --sw8 -- r9 --r10
                            table[i][n2] = getExtremite(i , result);
                            table[id_n][n2] = getExtremite(id_n, i);
                            return result_gen;
                        }
                        // i -> n2 = result
                        // id_n -> n2 == result

                        return -1;
                    }

                }
                else{
                    std::cout << " I = STATION =" <<i<<std::endl;
                    for(InterfaceFE * fe : sommets[i]->getInterfaces()){
                        if(fe->getAdresseIP() == adresse){

                            extremite * ext = cable->getExt(sommets[id_n]);
                            std::cout << "Adresse trouvé = Chemin de "<<id_n<<" "<<i<<" = "<<ext->noeud->getIdNoeud()<<std::endl;
                            table[id_n][i] = ext;

                            //std::cout << "Result STATION= "<< result<< std::endl;

                            return i;
                        }
                    }

                }
            }
        }
    }
    return -1;

}


int Graphe::genererChemin(int n1, int n2){
    std::cout << "Generer chemin "<<n1 <<" "<<n2<<std::endl;
    if(table[n1][n2]){
        std::cout << "Generer existe déja"<<std::endl;
        return 2;
    }
    // ST1 -- SW --SW --ST2
    // parcourir(0,0,2) == 6
    // parcourir (0,6,2) > -1 == 6
    // parcourir (6, 8, 2) > -1 == 8


    if(verifierReseau(n1, n2)){
        parcourirVoisins(n1, n1, n2);
        return 1;
    }
    else {
        string adresse = verifierCoherence(sommets[n1], sommets[n2]);
        if(adresse != DEFAULT_IP){
            std::cout << "Trouver "<<n1<< " adresse "<<adresse<<std::endl;
            int inter = parcourirPasserelle(n1, n1,adresse, n2);
            return 1;
           // std::cout << "Resultat passerelle ="<< inter<<std::endl;
           /* if(inter > -1){
                genererChemin(inter, n2);
                //n1   s7
                // n1 --> n2 == inter
            }
            else return;
            */
       }
        else return -1;
    }
}


std::string Graphe::verifierCoherence(Noeud * n1, Noeud * n2)
{

    /* if(verifier_meme_reseau(n1 , n2))
        voir si matrice[n1][n2] == un cable , retourner vrai;
        sinon parcourir_voisin( id_src ,id_n2) , sauf id_src!
            si voisin = Station, Routeur , verifier si voisin = n2 , sinon arreter
            si switch parcourir_voisin(n1_id, id_n2)
      else {
        Si N1 = Station {
                chercherDansTableRoutage( adresseReseau n2)
                si trouvé : verifier_meme_reseau(n1 , resultat) -> vrai , chercher chemin(n1,resultat) , faux pas de chemin
                sinon : pas de chemin
            }
        Si N1 = routeur{
            verifier s'il y a une interface qui a le meme reseau que n2
            si trouvé : chercher_chemin(n1_interface, n2)
            sinon : chercher dans table de routage (adresseReseau n2)
                si trouvé : verifier_meme_reseau(n1 , resultat) -> vrai , chercher chemin(n1,resultat) , faux pas de chemin
                sinon : pas de chemin
        }

       }


      */
    //int i,j;
    //int sizeInterfaceI= n1->getInterfaces().size();
    //int sizeInterfaceJ= n2->getInterfaces().size();
    /*
    for( i=0;i < sizeInterfaceI;i++)
        for( j=0;j<sizeInterfaceJ;j++)
            if (n1->getInterfaces()[i]->getAdresseRes() == n2->getInterfaces()[j]->getAdresseRes())	{
                return n2->getInterfaces()[j]->getAdresseIP();
            }
*/
    string adresse = DEFAULT_IP;
    int size_i = n2->getInterfaces().size();

    for (int i = 0; i < size_i; i++ ) {
        adresse = n1->getPasserelleTableRoutage(n2->getInterface(i)->getAdresseRes());
        if(adresse != DEFAULT_IP)
            return adresse;
    }

    return adresse;

}




void Graphe::genererTableChemin(){
    int size_s = sommets.size();
    for(int i = 0; i < size_s; i++){
        //Hub * h_n1 = dynamic_cast<Hub*>(sommets[i]);
        string type1 = sommets[i]->getNom();
        for(int j = 0; j < size_s; j++){
            string type2 = sommets[j]->getNom();
            //Hub * h_n2 = dynamic_cast<Hub*>(sommets[j]);
            //generer chemin  generer_chemin_entre(n1, n2)
            if(i != j && type1 != "Switch" && type2 != "Switch")
                genererChemin(i, j);
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

    n->setIdNoeud(sommets.size());
    sommets.push_back(n);

    int taille_s = sommets.size();

    vector<Cable *> tempCables(taille_s, nullptr);
    vector<extremite*> tempExtremites(taille_s, nullptr);

    matrice.push_back(tempCables);
    table.push_back(tempExtremites);

    for (int i = 0; i < taille_s; i++) {
        //cout << matrice.at(i).size() << endl;

        matrice[i].push_back(nullptr);
        table[i].push_back(nullptr);
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
        table[i].erase( table[i].begin() + indice);
    }
    /*
    for ( auto i = matrice.begin(); i != matrice.end() ; i++){
        (*i).erase( (*i).begin()+indice);
    }*/



    matrice.erase(matrice.begin()+indice);
    table.erase(table.begin()+indice);

}

void Graphe::supprimerCableMatrice(Cable * c)
{
    Noeud * N1 = c->getExt1()->noeud, * N2 = c->getExt2()->noeud;

    int i_N1 = N1->getIdNoeud();
    int i_N2 = N2->getIdNoeud();

    matrice[i_N1][i_N2] = nullptr;
    matrice[i_N2][i_N1] = nullptr;

}


