#include "InterfaceFE.hh"
#include <iostream>

const string IP_REGEX = "^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$";
const string MAC_REGEX = "^([0-9]{6}[:])([0-9]{6})$";
const string DEFAULT_IP = "0.0.0.0";
const string DEFAULT_MAC = "111111:111111";

InterfaceFE::InterfaceFE(int idNoeud, string _nomInterface, string _adresseIP,
                         string _adresseRes, string _masque){

    nomInterface = _nomInterface;
    cable = nullptr;
    setAdresseIP(_adresseIP);
    setAdresseRes(_adresseRes);
    setMasque(_masque);
    // generer adresse Mac
    char s[14];
    sprintf(s,"000000:%06d",idNoeud);
    std::cout <<s<<std::endl;
    adresseMac = s;
    setAdresseMac(adresseMac);
}

InterfaceFE::~InterfaceFE(){
    //std::cout << "Destruction de l'interface" << std::endl;
    // Destruction du cable lié
   // if(cable){
        delete cable;
        cable = nullptr;
    //}
}


void InterfaceFE::setNomInterface(string _nomInterface){
    nomInterface = _nomInterface;
}

void InterfaceFE::setAdresseIP(string _adresseIP){
     adresseIP = checkAdresse(_adresseIP, IP_REGEX, DEFAULT_IP);
}

void InterfaceFE::setAdresseRes(string _adresseRes){
     adresseRes = checkAdresse(_adresseRes, IP_REGEX, DEFAULT_IP);
}

void InterfaceFE::setMasque(string _masque){
    masque = checkAdresse(_masque, IP_REGEX, DEFAULT_IP);
}

void InterfaceFE::setAdresseMac(string _adresseMac){
     adresseMac = checkAdresse(_adresseMac, MAC_REGEX, DEFAULT_MAC);
}

void InterfaceFE::setCable(Cable * _cable){
    cable = _cable;
}

bool InterfaceFE::regexValide(string adresse, string _regex){
    std::regex regex_ip(_regex, std::regex::ECMAScript);

    if(std::regex_match(adresse, regex_ip))
        return true;
    std::cout <<"False"<<std::endl;
    return false;
}

string InterfaceFE::checkAdresse(std::string _adresse, std::string _regex, std::string _defaut){
    if(regexValide(_adresse, _regex))
        return _adresse;
    else
        return _defaut;
}

bool InterfaceFE::ipValide(string _adresseIP, string _masque, string _adresseRes){
    vector<string> vip, vmasque, vres;

    boost::algorithm::split(vip    , _adresseIP , boost::is_any_of("."));
    boost::algorithm::split(vmasque, _masque    , boost::is_any_of("."));
    boost::algorithm::split(vres   , _adresseRes, boost::is_any_of("."));

    for(int i = 0; i < 4; i++){
       if( ( std::stoi(vip[i]) & std::stoi(vmasque[i])) != std::stoi(vres[i]))
            return false;
    }

    return true;
}
