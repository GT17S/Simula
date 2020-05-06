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

void calculerChecksum ( Data * d)	{
	boost::dynamic_bitset<> tmp = *d->getSeq();
	unsigned short ck = 0;
	unsigned int taille;
	if ( d->getType() == DATA_SEGMENT) taille = tmp.size();
	else if ( d->getType() == DATA_PAQUET) 	{
		taille = 160;
		// Recuperer checksum et la mettre a 0
	}
	for (unsigned int i = 0; i < taille; i+=16)	{
		boost::dynamic_bitset<> p = lire_bits ( tmp, i, taille - i >= 16 ? 16 : taille - i);
		if ( taille - i < 16)	{
			p.resize(16);
			p = p << (16 - (taille-i));
		}
		ck += (unsigned short) ~p.to_ulong();
			ck = ~ck;
	}
	if (d->getType() == DATA_SEGMENT)
		ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 16, ck), 128, 16);
	else if ( d->getType() == DATA_PAQUET)
		ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 16, ck), 80, 16);

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
	d->setType ( DATA_SEGMENT);
	calculerChecksum ( d);

	return;
}

unsigned int ipToNumber ( std::string str)	{
	unsigned int tmp = 0, sum = 0, shift = 32;
	int len = str.size();
	for ( int i = 0; i < len; i++)	{
		if ( str[i] != '.')	{
			tmp = tmp * 10 + (str[i] - '0');
		}
		if ( str[i] == '.' || i == (len -1))	{
			shift -= 8;
			sum += tmp << shift;
			tmp = 0;
		}
	}
	return sum;
}

unsigned int ipNoeud ( Noeud * n)	{
	unsigned int ip = 0;
	if ( n != nullptr)	{
		if ( n->getInterfaces().size() == 0)
			ip = 0;
		else if ( n->getInterfaces().size() == 1)
			ip = ipToNumber ( n->getInterface(0)->getAdresseIP());
		// else : laquelle choisir ?
	}
	return ip;	
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
	unsigned int ip_src = ipNoeud ( src);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 32, ip_src), 96, 32);
	int ip_dest = ipNoeud ( dest);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 32, ip_dest), 128, 32);
	d->setType ( DATA_PAQUET);
	calculerChecksum ( d);
	return;
}

unsigned int macToNumber ( std::string str)	{
	unsigned int tmp = 0, sum = 0, shift = 48;
	int len = str.size();
	for ( int i = 0; i < len; i++)	{
		if ( str[i] != ':')	{
			tmp = tmp * 10 + (str[i] - '0');
		}
		if ( str[i] == ':' || i == (len -1))	{
			shift -= 8;
			sum += tmp << shift;
			tmp = 0;
		}
	}
	return sum;
}

unsigned long long macNoeud ( Noeud * n)	{
	unsigned long long mac = 0;
	if ( n != nullptr)	{
		if ( n->getInterfaces().size() == 0)
			mac = 0;
		else if ( n->getInterfaces().size() == 1)
			mac = macToNumber ( n->getInterface(0)->getAdresseMac());
		// else : laquelle choisir ?
	}
	return mac;	
}

void encapsule_paquet ( Noeud * src, Noeud * dest, Data * d)	{
	
	size_t old = d->getSeq()->size();
	size_t length = old + 112;
	d->getSeq()->resize(length);
	decalage ( d, length-old, old);
	unsigned long long mac_src = macNoeud ( src);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 48, mac_src), 0, 48);
	unsigned long long mac_dest = macNoeud ( dest);
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

std::vector<Data *> fragmentationPaquet (Data d, int mtu)	{
	std::vector<Data*> pi;
	boost::dynamic_bitset<> s = *d.getSeq(),	
							ip_src 	= lire_bits ( s, 96, 32),
							ip_dest = lire_bits ( s, 128, 32),
							ip_id 	= lire_bits ( s, 32, 16),
							f 		= lire_bits ( s, 48, 3),
							offset	= lire_bits ( s, 51, 13),
							ttl		= lire_bits ( s, 64, 8);
	int tp_initial = (int) lire_bits ( s, 16, 16).to_ulong()-20,
		tp = 0;
	desencapsule_paquet (&d);
	s = *d.getSeq();

	while ( tp < tp_initial)	{
		boost::dynamic_bitset<> bs;
		if ( tp + mtu >= tp_initial)	{
			bs = lire_bits ( s, tp*8, (tp_initial-tp)*8);
		}
		else {
			bs = lire_bits ( s, tp*8, mtu*8);
		}
		boost ::dynamic_bitset<> s_tmp ( bs.size());
		ecrire_bits ( &s_tmp, bs, 0, (int)s_tmp.size());
		if ( tp + mtu >= tp_initial)	ecrire_bits ( &f, boost::dynamic_bitset<> ( 1, 0), 0, 1);
		else 							ecrire_bits ( &f, boost::dynamic_bitset<> ( 1, 1), 0, 1);
		pi.push_back ( new Data ( new boost::dynamic_bitset<> ( s_tmp), DATA_SEGMENT));
		encapsule_segment ( nullptr, nullptr, ip_id, f, boost::dynamic_bitset<> ( 13, tp*8), ttl, pi[pi.size()-1]);
		tp+=mtu;
	}
	return pi;
}

Data reassemblagepaquet ( std::vector<Data *> paquets)	{
	unsigned int offsetAttendu = 0, mf = 1, br = 0;
	boost::dynamic_bitset<> * s_tmp = new boost::dynamic_bitset<> (0),
							ip_src, ip_dest, ip_id, f, ttl;
	while ( mf != 0 && br < 5)	{
		for (unsigned int i = 0; i < paquets.size(); i++)	{
			boost::dynamic_bitset<> p = *paquets[i]->getSeq();
			unsigned int offset = (unsigned int)lire_bits ( p, 51, 13).to_ulong();
			if ( offset == offsetAttendu)	{
				int h_len = (int) lire_bits ( p, 4, 4).to_ulong()*32,
					longueur = (int) lire_bits ( p, 16, 16).to_ulong()*8,
					old = s_tmp->size();
				mf = (unsigned int) lire_bits ( p, 50, 1).to_ulong();
				boost::dynamic_bitset<> s_lu = lire_bits ( p, h_len, longueur-h_len);
				s_tmp->resize( old + s_lu.size());
				ecrire_bits ( s_tmp, s_lu, offset,	longueur - h_len);
				offsetAttendu = offset + longueur - h_len;
				if ( mf == 0)	{
					ip_src = lire_bits ( p, 96, 32);
					ip_dest = lire_bits ( p, 128, 32);
					ip_id = lire_bits ( p, 32, 16);
					f = lire_bits ( p, 48, 3);
					ttl = lire_bits ( p, 64, 8);
				}
			}
		}
		br++;
	}	
	Data d ( s_tmp, DATA_SEGMENT);
	encapsule_segment ( nullptr, nullptr, ip_id, f, boost::dynamic_bitset<> ( 13, 0), ttl, &d);
	ecrire_bits ( d.getSeq(), ip_src, 96, 32);
	ecrire_bits ( d.getSeq(), ip_dest, 128, 32);	
	return d;
}
