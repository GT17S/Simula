#ifndef __DATA_OUTILS_H__
#define __DATA_OUTILS_H__

#include "Data.hh"
#include "Noeud.hh"

using namespace boost;

void ecrire_bits ( boost::dynamic_bitset<> * sbe, boost::dynamic_bitset<> se, int pos, int taille);
boost::dynamic_bitset<> lire_bits ( boost::dynamic_bitset<> sbe, int pos, int taille);
void encapsule_donnee ( dynamic_bitset<> port_src, dynamic_bitset<> port_dest, dynamic_bitset<> num_seq, dynamic_bitset<> num_ack, dynamic_bitset<> flag, dynamic_bitset<> fen, Data * d);
void encapsule_segment ( Noeud * src, Noeud * dest, boost::dynamic_bitset<> ip_id, boost::dynamic_bitset<> flag, boost::dynamic_bitset<> offset, boost::dynamic_bitset<> ttl, Data *d);
void encapsule_paquet ( Noeud * src, Noeud * dest, Data * d);
void desencapsule_trame ( Data * d);
void desencapsule_paquet ( Data * d);
void desencapsule_segment ( Data * d);
void calculerChecksum ( Data * d);
void calculerFrameCheckSequence ( Data * d);
std::vector<Data *> fragmentationPaquet (Data p, int mtu = 1500);
Data reassemblagepaquet ( std::vector<Data *> paquets);
string BinaryStringToText(string binaryString);
#endif
