#ifndef INTERFACE_H
#define INTERFACE_H

/*!
 * \file InterfaceFE.hh
 * \brief Interface de la carte réseau
 * \author medish
 * \version 0.1
 */

#include <string>

/*!
 * \class InterfaceFE
 * \brief La classe InterfaceFE représentant une interface réseau
 */

class InterfaceFE{
private :
    std::string nomInterface; /*<! nom de l'interface réseau*/
    std::string adresseIP; /*<! adresse ip*/
    std::string masque; /*<! masque réseau */
    std::string adresseMac; /*<! adresse MAC*/
public :
    InterfaceFE(std::string nomInterface);
    string getNomInterface();
    string getAdresseIP();
    string getMasque();
    string getAdresseMac();
    void setNomInterface();
    void setAdresseIP();
    void setMasque();
    void setAdresseMac();

}


#endif
