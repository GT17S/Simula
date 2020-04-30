#ifndef GRAPHE_H
#define GRAPHE_H

/*!
 * \file Graphe.h
 * \brief Graphe
 * \author GT17S
 * \version 0.1
 */

#include "../include/logiqueReseau/Cable.hh"
#include "../include/logiqueReseau/Noeud.hh"
#include <vector>
#include <QEvent>


using std::vector;


/*!
 * \enum Chemin
 * \brief plus court chemin entre deux noeuds et son cout.
 */
struct Chemin
{
    vector<int> tab;
    int couts;
};


/*!
 * \class Graphe
 * \brief La classe Graphe représentant un Graphe.
 */

class Graphe{


    /*!
     * \function friend float CalculLatenceDynamique(Graphe*, Congestion*, Data*);
     * \bug La classe Graphe représentant un Graphe.
     */

/*fonction à traiter plus tard*///friend float CalculLatenceDynamique(Graphe*, Congestion*, Data*);

private:

        vector<Noeud*> sommets;/*!< Liste des sommets du Graphe */
        vector<vector<Cable*>> matrice; /*!< Matrice d'adjacences du Graphe */
        vector<vector<Chemin>> table;/*!< Table de chemins du Graphe */

public:


        /*!
         * \brief Constructeur par défaut
         * Constructeur par défaut de la classe Graphe
         */

        Graphe();

        /*!
         * \brief Construceur de copie
         *  Constructeur de copie de la classe Graphe
         *  Initialise un graphe par un autre graphe.
         * \param g : voir #Graphe
         */

        Graphe(Graphe& g);

        /*!
         * \brief Destructeur
         * Destructeur de la classe Graphe
         */

        ~Graphe();


        /*!
         * \brief getSommets
         * getter qui recupere le vecteur de sommets.
         * \return voir #vector<Noeud*>
         */

        vector<Noeud*> getSommets(){ return sommets;}


        /*!
         * \brief getMatrice
         * getter qui recupere la matrice d'adjacence de Graphe.
         * \return voir #vector<vector<Cable*>>
         */

        vector<vector<Cable*>> getMatrice(){return matrice;}

        /*!
         * \brief getTable
         * getter qui recupere la matrice de chemin de Graphe.
         * \return voir #vector<vector<Chemin>>
         */

        vector<vector<Chemin>> getTable(){return table;}

        /*!
         * \brief setSommet
         * setter qui insere un noeud dans la liste des sommets du Graphe.
         * \param  *N : voir #Noeud
         */

        void setSommet(Noeud* N);

        /*!
         * \brief setSommets
         * setter qui insere un vecteur de noeuds dans la liste des sommets du Graphe.
         * \param  S : voir #Noeud
         */

        void setSommets(vector<Noeud*> s);

        /*!
         * \brief setSommets
         * setter qui insere un matrice de chemin dans la table de chemins du Graphe.
         * \param  t : voir #Graphe
         */

        void setTable(vector<vector<Chemin>> t);

        /*!
         * \brief setMatrice
         * setter qui insere une matrice de cable dans la matrice d'adjacence du Graphe.
         * \param  m : voir #Cable
         */

        void setMatrice(vector<vector<Cable*>> m);

        bool verfierCoherence(Noeud* N1, Noeud* N2);
        void miseAjourDeMatrice(QEvent* event );
        void genererTableChemin();



        void ajoutNoeudMatrice(Noeud * n);
        void ajoutCableMatrice(Cable *C);
        void supprimerNoeudMatrice(Noeud * n);
        void supprimerCableMatrice(Cable* c);


};


#endif
