#ifndef INTERFACE_H
#define INTERFACE_H

/*!
 * \file InterfaceFE.hh
 * \brief Interface de la carte réseau
 * \author medish
 * \version 0.1
 */

#include <string>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "Cable.hh"


using std::string;
using std::vector;

class Cable;

#ifndef CONSTANTS_H
#define CONSTANTS_H

/*! \relates InterfaceFE
 * Constante qui définit l'expression réguliere d'une adresse IP
 * XXX.XXX.XXX.XXX
 * (XXX est entre 0 et 255).
 */
extern const string IP_REGEX;
/*! \relates InterfaceFE
 * Constante qui définit l'expression réguliere d'une adresse MAC
 * XX:XX:XX:XX:XX:XX
 * (X est de 0 à 9 et de A à F)
 */
extern const string MAC_REGEX;
/*! \relates InterfaceFE
 * Constante d'une adresse IP par défaut.
 * 0.0.0.0
 */
extern const string DEFAULT_IP;
/*! \relates InterfaceFE
 * Constante d'une adresse MAC par défaut.
 * 00:00:00:00:00:00
 */
extern const string DEFAULT_MAC;
#endif

/*!
 * \class InterfaceFE
 * \brief La classe InterfaceFE représentant une interface réseau
 */

class InterfaceFE{
private :
    string nomInterface; /*<! nom de l'interface réseau*/
    string adresseIP; /*<! adresse ip*/
    string adresseRes; /*<! adresse réseau */
    string masque; /*<! masque réseau */
    string adresseMac; /*<! adresse MAC*/
    Cable * cable; /*<! Cable lié à l'interface */
    /*!
     * \brief ipValide
     * Vérifier si une adresse IP est bien configuré
     * par rapport à son réseau.
     * \see #adresseIP #adresseRes #masque
     * \return vrai si adresse IP est configuré, faux sinon.
     */
    bool ipValide();
public :
    /*!
     * \brief Constructeur
     * Constructeur de la classe InterfaceFE
     * \param nomInterface : voir #nomInterface, Intialisé par défaut à "Interface"
     * \param adresseIP : voir #adresseIP, Intialisé par défaut à #DEFAULT_IP
     * \param adresseRes : voir #adresseRes, , Intialisé par défaut à #DEFAULT_IP
     * \param masque : voir #masque, Intialisé par défaut à #DEFAULT_IP
     * \param adresseMac : voir #adresseMac, Intialisé par défaut à #DEFAULT_MAC
     */
    InterfaceFE(string nomInterface = "Interface", string adresseIP = DEFAULT_IP, string adresseRes = DEFAULT_IP,
                string masque = DEFAULT_IP, string adresseMac = DEFAULT_MAC);

    /*!
     * \brief Destructeur
     * Destructeur de la classe InterfaceFE
     * Destruction du cable lié.
     */
    ~InterfaceFE();

    /*!
     * \brief getNomInterface
     * \return voir #nomInterface
     */
    string getNomInterface(){return nomInterface;}
    /*!
     * \brief getAdresseIP
     * \return voir #adresseMac
     */
    string getAdresseIP(){return adresseIP;}
    /*!
     * \brief getAdresseRes
     * \return voir #adresseRes
     */
    string getAdresseRes(){return adresseRes;}
    /*!
     * \brief getMasque
     * \return voir #masque
     */
    string getMasque(){return masque;}

    /*!
     * \brief getAdresseMac
     * \return voir #adresseIP
     */
    string getAdresseMac(){return adresseIP;}

    /*!
     * \brief getCable
     * \return voir #cable
     */
    Cable * getCable(){return cable;}

    /*!
     * \brief setNomInterface
     * Modifier le nom de l'nterface, #nomInterface
     * \param nomInterface
     */
    void setNomInterface(string nomInterface);
    /*!
     * \brief setAdresseIP
     * Modifier l'adresse IP de l'interface, #adresseIP
     * Vérifier si l'adresse en entrée est valide, voir regexValide()
     * Sinon mettre la valeur par défaut #DEFAULT_IP
     * \param adresseIP
     */
    void setAdresseIP(string adresseIP);
    /*!
     * \brief setAdresseRes
     * Modifier l'adresse réseau de l'interface, #adresseRes
     * Vérifier si l'adresse en entrée est valide, voir regexValide()
     * Sinon mettre la valeur par défaut #DEFAULT_IP
     * \param adresseRes
     */
    void setAdresseRes(string adresseRes);
    /*!
     * \brief setMasque
     * Modifier le masque de l'interface, #masque
     * Vérifier si l'adresse en entrée est valide, voir regexValide()
     * Sinon mettre la valeur par défaut #DEFAULT_IP
     * \param masque
     */
    void setMasque(string masque);
    /*!
     * \brief setAdresseMac
     * Modifier l'adresse MAC de l'interface
     * Vérifier si l'adresse en entrée est valide, voir regexValide()
     * Sinon mettre la valeur par défaut #DEFAULT_MAC
     * \param adresseMac
     */
    void setAdresseMac(string adresseMac);

    /*!
     * \brief setCable
     * Modifier le cable lié à l'interface.
     * \param cable
     */
    void setCable(Cable * cable);


    /*!
     * \brief regexValide
     * Vérifier si l'adresse IP en entrée est valide.
     * \param adresse : adresse IP
     * \param regex : expression réguliere #IP_REGEX
     * \return vrai si adresse valide, faux sinon.
     */
    static bool regexValide(string adresse, string regex);

};

#endif
