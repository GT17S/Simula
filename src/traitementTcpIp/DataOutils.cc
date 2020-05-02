#include "DataOutils.hh"


void ecrire_bits(boost::dynamic_bitset<> * sbe, boost::dynamic_bitset<> se, int pos, int taille){
	assert(sbe);
	if(pos < (int)sbe->size() && (pos+taille) <= (int)sbe->size()){
		if(pos < (int)se.size() && (pos+taille) <= (int)se.size())
			for (int i = pos; i < pos+taille; ++i)
			{
				sbe->set(i,se[i]); 
			}
	}
	
}

boost::dynamic_bitset<> lire_bits (boost::dynamic_bitset<> sbe, int pos, int taille){
	boost::dynamic_bitset<> b;
	if(pos < (int)sbe.size() && (pos+taille) <= (int)sbe.size())
		for (int i = pos; i < pos+taille; ++i)
		{
			b.set(i, sbe[i]);
		}
	return b;
}
