#include "../include/logiqueReseau/InterfaceFE.hh"

const string IP_REGEX = "^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$";
const string MAC_REGEX = "^([0-9A-Fa-f]{2}[:]){5}([0-9A-Fa-f]{2})$";
const string DEFAULT_IP = "0.0.0.0";
const string DEFAULT_MAC = "00:00:00:00:00:00";

InterfaceFE::InterfaceFE(string _nomInterface, string _adresseIP,
                         string _adresseRes, string _masque, string _adresseMac){

    nomInterface = _nomInterface;
    cable = nullptr;
    setAdresseIP(_adresseIP);
    setAdresseRes(_adresseRes);
    setMasque(_masque);
    setAdresseMac(_adresseMac);
}

InterfaceFE::~InterfaceFE(){
    // Destruction du cable lié
    if(cable)
        delete cable;
}

void InterfaceFE::setNomInterface(string _nomInterface){
    nomInterface = _nomInterface;
}

void InterfaceFE::setAdresseIP(string _adresseIP){
    if(regexValide(_adresseIP, IP_REGEX))
        adresseIP = _adresseIP;
    else
        adresseIP = DEFAULT_IP;

}

void InterfaceFE::setAdresseRes(string _adresseRes){
    if(regexValide(_adresseRes, IP_REGEX))
        adresseRes = _adresseRes;
    else
        adresseRes = DEFAULT_IP;

}

void InterfaceFE::setMasque(string _masque){
    if(regexValide(_masque, IP_REGEX))
        masque = _masque;
    else
        masque = DEFAULT_IP;
}

void InterfaceFE::setAdresseMac(string _adresseMac){
    if(regexValide(_adresseMac, MAC_REGEX))
        adresseMac = _adresseMac;
    else
        adresseMac = DEFAULT_MAC;
}

void InterfaceFE::setCable(Cable * _cable){
    cable = _cable;
}

bool InterfaceFE::regexValide(string adresse, string _regex){
    std::regex regex_ip(_regex, std::regex::ECMAScript);

    if(std::regex_match(adresse, regex_ip))
        return true;

    return false;
}

bool InterfaceFE::ipValide(){
    vector<string> vip, vmasque, vres;

    boost::algorithm::split(vip    , adresseIP , boost::is_any_of("."));
    boost::algorithm::split(vmasque, masque    , boost::is_any_of("."));
    boost::algorithm::split(vres   , adresseRes, boost::is_any_of("."));

    for(int i = 0; i < 4; i++){
       if( ( std::stoi(vip[i]) & std::stoi(vmasque[i])) != std::stoi(vres[i]))
            return false;
    }

    return true;
}
