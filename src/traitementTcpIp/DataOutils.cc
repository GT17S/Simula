#include "DataOutils.hh"


void ecrire_bits(boost::dynamic_bitset<> * sbe, boost::dynamic_bitset<> se, int pos, int taille){
	assert(sbe);
	if(pos < (int)sbe->size() && (pos+taille) <= (int)sbe->size()){
		if(taille <= (int)se.size())
			for (int i = 0; i < taille; ++i)
			{
				sbe->set(i+pos,se[taille-i-1]); 
			}
	}
	
}

boost::dynamic_bitset<> lire_bits (boost::dynamic_bitset<> sbe, int pos, int taille){
	boost::dynamic_bitset<> b (taille);
	if(pos < (int)sbe.size() && (pos+taille) <= (int)sbe.size())	{
		int j = taille-1;
		for ( int i = 0 ; i < taille; ++i)	{
			b.set( j, sbe[pos + i]);
			j--;
		}
	}
	return b;
}

void decalage ( Data * d, size_t shift, size_t old)	{
	boost::dynamic_bitset<> tmp = *d->getSeq();
	for (size_t i = 0; i < old; i++)	{
		d->getSeq()->set(i+shift,tmp[i]);
		if ( i < shift) d->getSeq()->set(i, false);
	}
}

void encapsule_donnee ( dynamic_bitset<> port_src, dynamic_bitset<> port_dest, dynamic_bitset<> num_seq, dynamic_bitset<> num_ack, dynamic_bitset<> flag, dynamic_bitset<> fen, Data * d)	{
	size_t old = d->getSeq()->size();
	size_t length = port_src.size() + port_dest.size() + num_seq.size() + num_ack.size() + flag.size() + fen.size() + old + 74;
	d->getSeq()->resize(length);
	decalage ( d, length-old, old);
	ecrire_bits ( d->getSeq(), port_src, 0, 16);
	ecrire_bits ( d->getSeq(), port_dest, 16, 16);
	ecrire_bits ( d->getSeq(), num_seq, 32, 32);
	ecrire_bits ( d->getSeq(), num_ack, 64, 32);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 4, 6), 96, 4);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 6, 0), 100, 6);
	ecrire_bits ( d->getSeq(), flag, 106, 6);
	ecrire_bits ( d->getSeq(), fen, 112, 16);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 64, 0), 128, 64);
	// Checksum;
	
	d->setType ( DATA_SEGMENT);
	return;
}

void encapsule_segment ( Noeud * src, Noeud * dest, boost::dynamic_bitset<> ip_id, boost::dynamic_bitset<> flag, boost::dynamic_bitset<> offset, boost::dynamic_bitset<> ttl, Data *d)	{
	size_t old = d->getSeq()->size();
	size_t length = ip_id.size() + flag.size() + offset.size() + ttl.size() + old + 120;
	d->getSeq()->resize(length);
	decalage ( d, length-old, old);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 4, 6), 0, 4);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 4, 5), 4, 4);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 8, 0), 8, 8);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 16, old/8+20), 16, 16);
	ecrire_bits ( d->getSeq(), ip_id, 32, 16);
	ecrire_bits ( d->getSeq(), flag, 48, 3);
	ecrire_bits ( d->getSeq(), offset, 51, 13);
	ecrire_bits ( d->getSeq(), ttl, 64, 8);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 8, 6), 72, 8);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 16, 0), 80, 16);
	int ip_src = 0xFFFFFFFF;
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 32, ip_src), 96, 32);
	int ip_dest = 0x99999999;
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 32, ip_dest), 128, 32);
	//Checksum
	d->setType ( DATA_PAQUET);
	return;
}

void encapsule_paquet ( Noeud * src, Noeud * dest, Data * d)	{
	
	size_t old = d->getSeq()->size();
	size_t length = old + 112;
	d->getSeq()->resize(length);
	decalage ( d, length-old, old);
	unsigned long long mac_src = 0xFFFFFFFFFFFF;
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 48, mac_src), 0, 48);
	unsigned long long mac_dest = 0x999999999999;
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 48, mac_dest), 48, 48);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 16, 2048), 96, 16);
	d->getSeq()->resize(length+32);
	int fcs = 0xFFFFFFF0;
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 32, fcs), length, 32);
	d->setType ( DATA_TRAME);
	return;
}

void desencapsule_trame ( Data * d)	{
	boost::dynamic_bitset<> length = lire_bits ( *d->getSeq(), 128, 16);
	int taille_paquet = (int) length.to_ulong() * 8;
	boost::dynamic_bitset<> tmp = *d->getSeq();
	d->getSeq()->resize(taille_paquet); 
	for (int i = 0; i < taille_paquet; i++)	{
		boost::dynamic_bitset<> b = lire_bits ( tmp, i+112, 1);
		ecrire_bits ( d->getSeq(), b, i, 1);
	}
	d->setType ( DATA_PAQUET);
}

void desencapsule_paquet ( Data * d)	{
	boost::dynamic_bitset<> length = lire_bits ( *d->getSeq(), 4, 4);
	int ihl = (int) length.to_ulong() * 32;
	length = lire_bits ( *d->getSeq(), 16, 16);
	int taille_paquet = (int) length.to_ulong() * 8;
	
	boost::dynamic_bitset<> tmp = *d->getSeq();
	d->getSeq()->resize(taille_paquet - ihl); 
	for (int i = 0; i < taille_paquet - ihl; i++)	{
		boost::dynamic_bitset<> b = lire_bits ( tmp, i+ihl, 1);
		ecrire_bits ( d->getSeq(), b, i, 1);
	}
	d->setType ( DATA_SEGMENT);
}

void desencapsule_segment ( Data * d)	{
	boost::dynamic_bitset<> length = lire_bits ( *d->getSeq(), 96, 4);
	int t = (int) length.to_ulong() * 32,
		taille = d->getSeq()->size();
	boost::dynamic_bitset<> tmp = *d->getSeq();
	d->getSeq()->resize(taille - t); 
	for (int i = 0; i < taille - t; i++)	{
		boost::dynamic_bitset<> b = lire_bits ( tmp, i+t, 1);
		ecrire_bits ( d->getSeq(), b, i, 1);
	}
	d->setType ( DATA_TOTAL);
}
