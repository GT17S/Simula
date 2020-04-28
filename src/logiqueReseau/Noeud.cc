#include "../include/logiqueReseau/Noeud.hh"

vector<int> Noeud::idsNoeuds;

Noeud::Noeud() : nbPort(1), interfaces(), fileDattente(){
    // Générer automatiquement un ID
    setIdNoeud(1);
    // Initialisation d'une seule interface
    interfaces.push_back(new InterfaceFE());
}

Noeud::Noeud(string _nom, int _idNoeud, int _nbPort) :
    idNoeud(0), interfaces(), fileDattente(){

    nom = _nom;
    setIdNoeud(_idNoeud);
    nbPort = _nbPort;
    // Initialisation des interfaces
    for (int i = 0; i < nbPort; i++) {
        interfaces.push_back(new InterfaceFE());
    }
}

Noeud::~Noeud(){
    // Supprimer ID du noeud de la liste
    idsNoeuds.erase(std::remove(idsNoeuds.begin(), idsNoeuds.end(), idNoeud), idsNoeuds.end());

    // Destruction des interfaces
    for (auto i : interfaces) {
        delete i;
    }
    interfaces.clear();

    // Destruction de la file d'attente
    /*for(auto d : fileDattente){
        delete d;
    }
    */
    fileDattente.clear();

}


InterfaceFE * Noeud::getInterface(int id){
    if(id < (int)interfaces.size())
        return interfaces[id];

    return nullptr;
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
    // nbport par défaut = 1

    // Ajouter des ports
    if(_nbPort > nbPort){
        for (int i = nbPort; i < _nbPort; i++) {
            interfaces.push_back(new InterfaceFE());
        }
        nbPort = _nbPort;

    }else if(_nbPort < nbPort){

        int cpt =0;
        // Compter les interfaces qui sont liées
        for (InterfaceFE * in : interfaces){
            if(in->getCable())
                cpt++;
        }
        // Possibilité d'ecraser des interfaces
        if(cpt <= _nbPort){
            // Ecraser les interfaces non liées ( connexion = false )
            for (auto i = interfaces.rbegin(); i != interfaces.rend(); i++){
                if(nbPort == _nbPort)
                    break;
                if(!(*i)->getCable()){
                    delete *i;
                    *i = nullptr;
                    //interfaces.erase(i);
                    nbPort--;
                }
            }
            interfaces.erase(std::remove(interfaces.begin(), interfaces.end(), nullptr), interfaces.end());

            nbPort = _nbPort;
        }
        // Sinon interdit!
    }
    // Sinon meme nbrPort!
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

void Noeud::setInterfaces(vector<InterfaceFE *> _interfaces){
    interfaces = _interfaces;
}


void Noeud::setInterfaces(InterfaceFE * _interface){
    interfaces.push_back(_interface);
}

bool Noeud::acceptCable(Cable * _cable, int _idInterface){
    InterfaceFE * i = getInterface(_idInterface);
    if(i)
        if(!i->getCable()){
            i->setCable(_cable);
            return true;
        }
    return false;
}

