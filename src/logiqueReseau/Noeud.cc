#include "Noeud.hh"
#include "Graphe.hh"

#include <iostream>
vector<int> Noeud::idsNoeuds;

Noeud::Noeud() : nbPort(1), interfaces(), fileDattente(){
    // Générer automatiquement un ID
    setIdNoeud(1);
    // Initialisation d'une seule interface
    interfaces.push_back(new InterfaceFE());
    Graphe::ajoutNoeudMatrice(this);
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
    Graphe::ajoutNoeudMatrice(this);
}

Noeud::~Noeud(){

    std::cout << "Desutruction noeud "<< idNoeud<<std::endl;
    // Supprimer ID du noeud de la liste
    idsNoeuds.erase(std::remove(idsNoeuds.begin(), idsNoeuds.end(), idNoeud), idsNoeuds.end());

    // Destruction des interfaces
    for (auto i : interfaces) {
        delete i;
        i = nullptr;
    }
    interfaces.clear();

    // Destruction de la file d'attente
    /*for(auto d : fileDattente){
        delete d;
        d = nullptr;
    }
    */
    fileDattente.clear();

    Graphe::supprimerNoeudMatrice(this);

}


InterfaceFE * Noeud::getInterface(int id){
    if(id < (int)interfaces.size())
        return interfaces[id];

    return nullptr;
}

InterfaceFE * Noeud::getInterface(Cable * _cable){
    if(_cable){
        for( InterfaceFE * i : interfaces){
            if(i->getCable() == _cable)
                return i;
        }
    }

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


void Noeud::setTableRoutage(Route * route){
    // Ajouter un route
    Route * n_Route = new Route();

    n_Route->adresseReseau = InterfaceFE::checkAdresse(route->adresseReseau, IP_REGEX, DEFAULT_IP);
    n_Route->masque        = InterfaceFE::checkAdresse(route->masque       , IP_REGEX, DEFAULT_IP);
    n_Route->passerelle    = InterfaceFE::checkAdresse(route->passerelle   , IP_REGEX, DEFAULT_IP);

    // Interdiction d'ajout d'une ligne non valide
    if(n_Route->masque == DEFAULT_IP || n_Route->passerelle == DEFAULT_IP)
        return;
    //
    for(Route *r : tableRoutage){
        // Sous réseau existe déja
        if(r->adresseReseau == n_Route ->adresseReseau)
            return;
    }

    tableRoutage.push_back(n_Route);
    // Pour vérfier plustard que la route à été ajoutée,
    // il suffit juste de vérifier que la table de routage à un élement de plus.
}

string Noeud::getPasserelleTableRoutage(string _adresseReseau){
    string p = DEFAULT_IP;

    for( Route * r: tableRoutage){
        // Sous réseau trouvé
        if(r->adresseReseau == _adresseReseau){
            p = r->passerelle;
            return p;
        }
        // Adresse par défaut trouvé
        if(r->adresseReseau == DEFAULT_IP)
            p = r->passerelle;
    }

    return p;
}

void Noeud::supprimerRoute(int id){
    if(id < (int)tableRoutage.size()){
        // Libérer mémoire
        vector<Route*>::iterator i =  tableRoutage.begin() + id;

        delete *i;
        *i = nullptr;

        tableRoutage.erase(i);
    }
}

void Noeud::modifierRoute(int id, Route * route){
    size_t size_table = tableRoutage.size();
    // Ajouter
    setTableRoutage(route);

    // Modifier la route
    if(size_table < tableRoutage.size()){
        supprimerRoute(id);
        tableRoutage.insert (tableRoutage.begin()+ id , *(tableRoutage.end()) );
        tableRoutage.pop_back();
    }
}

void Noeud::setTableRoutage(vector<Route *> _tableRoutage){
    tableRoutage = _tableRoutage;
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



