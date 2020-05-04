#include <iostream>
#include <string>
#include "Hub.hh"
#include "Data.hh"
#include "Cable.hh"
#include "Noeud.hh"
#include "Graphe.hh"
#include "Routeur.hh"
#include "Station.hh"
#include "DataOutils.hh"
using namespace  std;
using namespace boost;

int main( int argc, char ** argv)	{
	
	Data d ( argv[1]);
	int p_src = 0xF00F, p_dest = 15, n_seq = 15, n_ack = 15, n_flag = 15, n_fen =15;
	
	dynamic_bitset<> port_src(16, p_src);
	dynamic_bitset<> port_dest(16,p_dest);
	dynamic_bitset<> num_seq(32, n_seq);
	dynamic_bitset<> num_ack(32, n_ack);
	dynamic_bitset<> flag(6, n_flag);
	dynamic_bitset<> fen(16, n_fen);
	
	
	std::cout << d << std::endl;
	
	encapsule_donnee ( port_src, port_dest, num_seq, num_ack, flag, fen, &d);

	std::cout << d << std::endl;
	
	boost::dynamic_bitset<> ip_id (16, 0b1010101010101010);
	boost::dynamic_bitset<> p_flag ( 3, 0b111);
	boost::dynamic_bitset<> offset ( 13, 0b0001111111000);
	boost::dynamic_bitset<> ttl ( 8, 11000011);
	encapsule_segment ( nullptr, nullptr, ip_id, p_flag, offset, ttl, &d);

	std::cout << d << std::endl;

	encapsule_paquet ( nullptr, nullptr, &d);

	std::cout << d << std::endl;
	
	desencapsule_trame ( &d);

	std::cout << d << std::endl;

	desencapsule_paquet ( &d);

	std::cout << d << std::endl;

	desencapsule_segment ( &d);

	std::cout << d << std::endl;

	
	boost::dynamic_bitset<> tmp = *d.getSeq();
	std::string res = "";
	for (int i = 0; i < (int)tmp.size(); i+=8)	{
		char c = (char)0;
		for ( int j = i%8; j < 8; j++)	
			if ( tmp[i+j])
				c = c | ( 1<<(7-j));
		res += c;
	}
	std::cout << "Message original : " << res << std::endl;
    return 0;
}
