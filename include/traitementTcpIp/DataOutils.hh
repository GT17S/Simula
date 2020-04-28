#ifndef __DATA_OUTILS_H__
#define __DATA_OUTILS_H__

#include "Data.hh"

//Ajouter Char to binaru
void ecrire_bits ( boost::dynamic_bitset<> * sbe, boost::dynamic_bitset<> se, int pos, int taille);
boost::dynamic_bitset<> lire_bits ( boost::dynamic_bitset<> sbe, int pos, int taille);
#endif