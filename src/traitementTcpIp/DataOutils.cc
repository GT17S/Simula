#include "../../include/traitementTcpIp/DataOutils.hh"


void ecrire_bits(boost::dynamic_bitset<> * sbe, boost::dynamic_bitset<> se, int pos, int taille){
	assert(sbe);
	//Faut vérifier les types et les tailles
	for (int i = pos; i < pos+taille; ++i)
	{
		sbe->set(i,se[i]); 
	}
}

boost::dynamic_bitset<> lire_bits (boost::dynamic_bitset<> sbe, int pos, int taille);