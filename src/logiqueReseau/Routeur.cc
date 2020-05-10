#include "Routeur.hh"
#include "DataOutils.hh"


Routeur::Routeur() : Noeud(){
    // ID automatique
    // nb port = 1
    // filedattente vide
    nom = "Routeur"+std::to_string(idNoeud);
    type = ROUTEUR;
}

Routeur::Routeur(string _nom, int _idNoeud, int _nbPort) :
    Noeud(_nom, _idNoeud, _nbPort){
    type = ROUTEUR;

}

Routeur::~Routeur(){

}

void Routeur::envoyerMessage(Data * data){

    int id_dest = lireAdresseMac(data, 1);
    int id_src  = lireAdresseMac(data, 0);
    vector<Cable*> path;
    Graphe::genererChemin(id_src, idNoeud, id_dest, path, false);
    int size_p = path.size();

    if(!size_p){
        std::cout << "Je connais pas le chemin vers "<<id_dest<<std::endl;
        return;
    }

    extremite * extNext = path[size_p -1]->getInverseExt(this);

    //std::cout <<"J'envoie le message à "<<ext->noeud->getIdNoeud()<< std::endl;
    //_message = std::to_string(id_next)+"_"+std::to_string(id_dest);
    extNext->noeud->recevoirMessage(extNext->interface, data);


}

void Routeur::recevoirMessage(int interface, Data * data){
    std::cout <<"Je suis un routeur"<< idNoeud<<std::endl;
    if(idNoeud == lireAdresseMac(data, 1)){
        std::cout <<"Cest moi la passerelle" <<std::endl;
        desencapsule_trame(data);
        string ipSrc = getInterface(interface)->getAdresseIP();
        if(ipSrc == lireAdresseIp(data, 1)){
            std::cout <<"Cest moi la destination" <<std::endl;
            desencapsule_paquet(data);
            desencapsule_segment(data);
            std::cout <<showMessage(data) <<std::endl;
        }
        else {

            // generer chemin complet, jusqua la destination
            vector<Cable *> path;

            int id_src  = lireAdresseMac(data, 0);
            string ip_dest = lireAdresseIp(data, 1);
            //Graphe::genererChemin(id_src, idNoeud, ip_dest, path, false);

            int size_p = path.size();
            // pas de chemin
            if(!size_p){
                std::cout << "Je connais pas le chemin vers " <<ip_dest<<std::endl;
                return;
            }

            // get next
            extremite * destExt; // destination finale
            Cable * cable;
            Noeud * n = this;
            for(int i = size_p - 1; i > -1; i--){
                cable = path[i];
                destExt = cable->getInverseExt(n);

                n = destExt->noeud;
            }
            // encapsuler paquet avec la prochaine @mac
            envoyerMessage(data);
        }
    }
    else {
        std::cout <<"Mauvaise destination" <<std::endl;
        return;
    }
}



