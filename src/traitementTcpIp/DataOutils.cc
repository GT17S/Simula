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

std::string showMessage(Data * d){
    boost::dynamic_bitset<> tmp = *d->getSeq();

       // std::cout << tmp << std::endl;
        std::string res = "";
        for (int i = 0; i < (int)tmp.size(); i+=8)    {
            char c = (char)0;
            for ( int j = i%8; j < 8; j++)
                if ( tmp[i+j])
                    c = c | ( 1<<(7-j));
            res += c;
        }

        return res;
}

std::string ip_to_string (unsigned int ip)	{
	int val = 0;
	unsigned int B = 0;
	std::string s;
	
	for ( int i = (int) sizeof(ip)*8 - 1; i >= 0  ; i--) {
		unsigned int c = (1<<i); 
		B = ip & c;
		if ( B != 0) val += pow (2, i%8);
		if ( i % 8 == 0) {
			s = s + std::to_string (val) + '.';
			val = 0;
		}
	}
	s.pop_back();
	
	return s;
}

unsigned long long lireAdresseMac ( Data * d, int flag)	{	// If mac src, flag = 0, if mac dest, flag = 1
	if ( d->getType () != 3) return -1;
	unsigned long long adresseMac = lire_bits ( *d->getSeq (), 48*flag, 48).to_ulong();
	return adresseMac;
}

std::string lireAdresseIp ( Data * d, int flag)	{	// If ip src, flag = 0, if ip dest, flag = 1
	if ( d->getType() == 0) return DEFAULT_IP;
	else if ( d->getType() == 1) return DEFAULT_IP;
	else if ( d->getType() == 2) return ip_to_string ( (unsigned int)lire_bits ( *d->getSeq (), 96+(flag*32), 32).to_ulong());
	else if ( d->getType() == 3) return ip_to_string ( (unsigned int)lire_bits ( *d->getSeq (), 208+(flag*32), 32).to_ulong());
	return DEFAULT_IP;
}

int lireIdIp ( Data * d)	{
	if ( d->getType() == 0) return -1;
	else if ( d->getType() == 1) return -1;
	else if ( d->getType() == 2) return (int)lire_bits ( *d->getSeq (), 32, 16).to_ulong();
	else if ( d->getType() == 3) return (int)lire_bits ( *d->getSeq (), 144, 16).to_ulong();
	return -2;
}

int lireFlagSegment ( Data * d)	{
	if ( d->getType() == 0) return -1;
	else if ( d->getType() == 1) return (int)lire_bits ( *d->getSeq (), 106, 6).to_ulong();
	else if ( d->getType() == 2) return (int)lire_bits ( *d->getSeq (), 266, 6).to_ulong();
	else if ( d->getType() == 3) return (int)lire_bits ( *d->getSeq (), 378, 6).to_ulong();
	return -2;
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

void calculerFrameCheckSequence ( Data * d)	{
	if ( d == nullptr) return;
	unsigned int fcs = 0xFFFF,
				 length = d->getSeq()->size();
	boost::dynamic_bitset<> tmp = *d->getSeq();
	for (unsigned int i = 0; i < tmp.size(); i++)	{
		bool bpf = fcs & 1;
		if ( bpf != tmp[i])
			fcs = fcs | 0x8408;
		fcs = fcs << 1;
	}
	d->getSeq()->resize(length+32);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 32, fcs), length, 32);
}

void encapsule_donnee ( dynamic_bitset<> port_src, dynamic_bitset<> port_dest, dynamic_bitset<> num_seq, dynamic_bitset<> num_ack, dynamic_bitset<> flag, dynamic_bitset<> fen, Data * d)	{
	if ( d->getType() != DATA_TOTAL) return;
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

unsigned int ipNoeud ( extremite * n)	{
	unsigned int ip = 0;
	if ( n != nullptr)	{
		if ( (int) n->noeud->getInterfaces().size() > n->interface)	{
			ip = ipToNumber ( n->noeud->getInterface(n->interface)->getAdresseIP());
            //std::cout << "In encaps : " << n->noeud->getInterface(n->interface)->getAdresseIP() << " " << ip << std::endl;
		}
	}
	return ip;	
}

void encapsule_segment ( extremite * src, extremite * dest, boost::dynamic_bitset<> ip_id, boost::dynamic_bitset<> flag, boost::dynamic_bitset<> offset, boost::dynamic_bitset<> ttl, Data *d)	{
	if ( d->getType() != DATA_SEGMENT) return;
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

unsigned long long macToNumber ( std::string str)	{
	unsigned int tmp = 0, sum = 0, shift = 48;
	int len = str.size();
	for ( int i = 0; i < len; i++)	{
		if ( str[i] != ':')	{
			tmp = tmp * 10 + (str[i] - '0');
		}
		if ( str[i] == ':')	{
			sum += (tmp * 1000000);
			tmp = 0;
		}
		if ( i == (len -1)) sum += tmp;
	}
	return sum;
}

unsigned long long macNoeud ( extremite * n)	{
	unsigned long long mac = 0;
	if ( n != nullptr)	{
		if ((int) n->noeud->getInterfaces().size() <= n->interface)
			mac = 0;
		else
			mac = macToNumber ( n->noeud->getInterface(n->interface)->getAdresseMac());
	}
	return mac;	
}

void encapsule_paquet ( extremite * src, extremite * dest, Data * d)	{
	if ( d->getType() != DATA_PAQUET) return;	
	size_t old = d->getSeq()->size();
	size_t length = old + 112;
	d->getSeq()->resize(length);
	decalage ( d, length-old, old);
	unsigned long long mac_src = macNoeud ( src);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 48, mac_src), 0, 48);
	unsigned long long mac_dest = macNoeud ( dest);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 48, mac_dest), 48, 48);
	ecrire_bits ( d->getSeq(), boost::dynamic_bitset<> ( 16, 2048), 96, 16);
	calculerFrameCheckSequence ( d);
	d->setType ( DATA_TRAME);
	return;
}

void encapsuleAll(int portSrc, int portDest, bool ack, bool syn, int nSeq, int nAck, int ipId,
                  extremite * n1, extremite * n2, extremite * nextMac, Data * data)	{

	int flag = 0, 
		n_ack = ack ? 1 : 0,
		n_syn = syn ? 1 : 0; //
	
	flag = (n_ack << 4) + (n_syn << 1);
	
	encapsule_donnee (	boost::dynamic_bitset<> ( 16, portSrc), 
						boost::dynamic_bitset<> ( 16, portDest), 
						boost::dynamic_bitset<> ( 32, nSeq), 
						boost::dynamic_bitset<> ( 32, nAck), 
						boost::dynamic_bitset<> ( 6, flag),
						boost::dynamic_bitset<> ( 16, 0), 
						data);
	
	encapsule_segment ( n1, 
						n2, 
						boost::dynamic_bitset<> ( 16, ipId), 
						boost::dynamic_bitset<> ( 3, 0), 
						boost::dynamic_bitset<> ( 13, 0), 
						boost::dynamic_bitset<> ( 8, 20),
						data);
							
    encapsule_paquet ( n1, nextMac, data);

}

void desencapsule_trame ( Data * d)	{
	if ( d->getType() != DATA_TRAME) return;
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
	if ( d->getType() != DATA_PAQUET) return;
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
	if ( d->getType() != DATA_SEGMENT) return;
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
//	if ( d->getType() != DATA_PAQUET) return;
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
/*	for (int i = 0; i < paquets.size(); i++)
		if ( paquet[i]->getType() != DATA_PAQUET)
			Signaler erreur		
*/	
	unsigned int offsetAttendu = 0, mf = 1;
	boost::dynamic_bitset<> * s_tmp = new boost::dynamic_bitset<> (0),
							ip_src, ip_dest, ip_id, f, ttl;
	while ( mf != 0)	{
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
	}	
	Data d ( s_tmp, DATA_SEGMENT);
	encapsule_segment ( nullptr, nullptr, ip_id, f, boost::dynamic_bitset<> ( 13, 0), ttl, &d);
	ecrire_bits ( d.getSeq(), ip_src, 96, 32);
	ecrire_bits ( d.getSeq(), ip_dest, 128, 32);	
	return d;
}

string BinaryStringToText(string binaryString) {
    string text = "";
    std::stringstream sstream(binaryString);
    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        text += char(bits.to_ulong());
    }
    return text;
}


void envoyer(Noeud * n1, Noeud *n2, int portSrc, int portDest, bool syn, bool ack, int nSeq, int nAck, int ipId, Data * data){
    // switch ou hub , ne peuvent ni envoyer ni recevoir
    if(n1->getTypeNoeud() == SWITCH || n2->getTypeNoeud() == SWITCH
     ||n1->getTypeNoeud() == HUB || n2->getTypeNoeud() == HUB)

        return;

    int id_n1 = n1->getIdNoeud(),
        id_n2 = n2->getIdNoeud();

    vector<Cable *> path;
    // generer chemin complet, jusqua la destination
    Graphe::genererChemin(id_n1, id_n1, id_n2, path, true);

    int size_p = path.size();
    // pas de chemin
    if(!size_p)
        return;

    // get next
    extremite * srcExt = path[size_p -1]->getExt(n1); // source
    extremite * destExt; // destination finale
    Cable * cable;
    Noeud * n = n1;
    extremite * nextExt = nullptr; // prochaine destination
    bool check = false;
    for(int i = size_p - 1; i > -1; i--){
        cable = path[i];
        destExt = cable->getInverseExt(n);

        n = destExt->noeud;
        if(!check)
        if(n->getTypeNoeud() == ROUTEUR || n->getTypeNoeud() == STATION)
            { nextExt = destExt; check =true;}
    }


    //std::cout<<"J'envoie le message : "<<message<<" à "<<n2->getIdNoeud()<<std::endl;
    encapsuleAll(portSrc, portDest, ack, syn, nSeq, nAck, ipId, srcExt, destExt, nextExt, data);
/*
    std::cout << " "<<srcExt->noeud->getIdNoeud()
              << " "<<destExt->noeud->getIdNoeud()
              << " "<<nextExt->noeud->getIdNoeud()<<std::endl;

              */
    Station * st = dynamic_cast<Station*>(n1);
    if(st){

        destination dest;
        dest.data = data;
        dest.interface_src = srcExt->interface;
        //n1->envoyerMessage(key, dest); // to data
        st->getControleur()->mapFileEnvoyer.insert({nSeq,dest});
        //st->getControleur()->verifieNbrSegment(n1);

    }else return;

}













