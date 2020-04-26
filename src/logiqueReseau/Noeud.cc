#include "../include/logiqueReseau/Noeud.hh"

vector<int> Noeud::idsNoeuds;

Noeud::Noeud() : nbPort(1), fileDattente(){
    // Générer automatiquement un ID
    setIdNoeud(1);
}

Noeud::Noeud(string _nom, int _idNoeud, int _nbPort) :
    idNoeud(0), fileDattente(){

    nom = _nom;
    setIdNoeud(_idNoeud);
    setNbPort(_nbPort);

}

Noeud::~Noeud(){
    // Supprimer ID du noeud de la liste
    idsNoeuds.erase(std::remove(idsNoeuds.begin(), idsNoeuds.end(), idNoeud), idsNoeuds.end());
}

void Noeud::setNom(string _nom){
    nom = _nom;
}

void Noeud::setIdNoeud(int _idNoeud){
    // Liste vide
    if(idsNoeuds.empty()){
        idNoeud = _idNoeud;
        idsNoeuds.push_back(idNoeud);
    }
    // Liste n'est pas vide
    else {
        // Supprimer ancien ID
        if(idNoeud != 0)
            idsNoeuds.erase(std::remove(idsNoeuds.begin(), idsNoeuds.end(), idNoeud), idsNoeuds.end());

        for (int id : idsNoeuds) {
            // ID existe déja
            if(id == _idNoeud){
                idNoeud = *max_element(idsNoeuds.begin(), idsNoeuds.end()) + 1;
                idsNoeuds.push_back(idNoeud);
                return;
            }
        }

        // ID n'existe pas
        idNoeud = _idNoeud;
        idsNoeuds.push_back(idNoeud);
    }
}

void Noeud::setNbPort(int _nbPort){
    // Entier positive
    nbPort = _nbPort ? _nbPort : 1;
}

void Noeud::setFileDattente(vector<string> _file){
        fileDattente = _file;
}

void Noeud::setFileDattente(string _data){
    for(string d : fileDattente){
        // Existe déja
        if(d == _data)
            return;
    }

    fileDattente.push_back(_data);
}
Noeud::Noeud(){}
Noeud::Noeud(std::string nom, int idNoeud, int nbPort){}
Noeud:: ~Noeud(){}
