#ifndef __DATA_H__
#define __DATA_H__ 

/*!
 * \file Data.hh
 * \brief Data
 * \author m4ssi
 * \version 0.1
 */

#include <assert.h>
#include <iostream>
#include <bitset>
#include <algorithm>
#include <iterator>
#include <boost/dynamic_bitset.hpp>

/*!
 * \enum data_t
 * \brief Type d'une donnée (Trame, Paquet IP, Segment TCP, Donnée brute).
 */
enum data_t
{
	DATA_TOTAL = 0,
	DATA_SEGMENT,
	DATA_PAQUET,
	DATA_TRAME
};	


/*!
 * \class Data
 * \brief Classe Graphe représentant une donnée circulant sur le réseau.
 */

class Data {
private:
	boost::dynamic_bitset<>* seq;	/*!< Sequence de bit contenant la donnée */
	data_t type;					/*!< Type de la donnée */
	std::string orignalstring;		/*!< Donnée brute avant conversion en binaire */
	int ossize;						/*!< Taille de la donnée brute */
	
	    /*!
         * \brief strtobinary
         * Méthode de conversion d'une chaine de caractère en claire en représentaiton binaire
         * \param  msg : string contanant le message d'origine
         */
	std::string strtobinary(std::string msg);


public:
    /*!
         * \brief Construceur par défaut
         *  Constructeur par défaut de la classe Data
         *  Initialise une séquence de bit à null et met le type TOTAL (donnée brute)
         */
	Data();
	
    /*!
         * \brief Construceur
         *  Constructeur de la clsse Data
         *  Initialise une Data à partir d'une message en claire.
         * \param message : donnée
         */	
	Data(std::string message);

    /*!
         * \brief Construceur
         *  Constructeur de la clsse Data
         *  Initialise une Data à partir d'une suite de bits et du type représenté par cette suite.
         * \param seq : suite de bit
         * \param type : type de la donnée
         */	
	Data(boost::dynamic_bitset<>* seq, data_t type = DATA_SEGMENT);

    /*!
         * \brief Destructeur
         *  Destructeur de la clsse Data
         *  Initialise une Data à partir d'une message en claire.
         * \param message : donnée
         */	
	~Data();


    data_t getType(void) const {return this->type;}
    boost::dynamic_bitset<>* getSeq(void) {return this->seq;}

	int getOriginialStringSize(void) const {return this->ossize;}
	void setType (data_t _type);
	void setSeq (boost::dynamic_bitset<>* _seq);
	int operator[](int index);
	Data& operator=( Data& d);
	friend std::ostream& operator<<(std::ostream &os, Data& d);
};


#endif
