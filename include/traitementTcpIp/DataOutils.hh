#ifndef __DATA_OUTILS_H__
#define __DATA_OUTILS_H__

#include "Data.hh"
#include "Noeud.hh"
#include "Graphe.hh"
#include "Cable.hh"
#include <bitset>
#include <sstream>
#include <vector>

using namespace boost;
using std::vector;

std::string ip_to_string (unsigned int ip);
unsigned long long lireAdresseMac ( Data * d, int flag = 0);	// If mac src, flag = 0, if mac dest, flag = 1
std::string lireAdresseIp ( Data * d, int flag = 0);			// If ip src, flag = 0, if ip dest, flag = 1
int lirePortTcp ( Data * d, int flag = 0);						// If port src, flag = 0, if port dest, flag = 1
int lireIdIp ( Data * d);
int lireFlagSegment ( Data * d);
unsigned long long macToNumber ( std::string str);
void ecrire_bits ( boost::dynamic_bitset<> * sbe, boost::dynamic_bitset<> se, int pos, int taille);
boost::dynamic_bitset<> lire_bits ( boost::dynamic_bitset<> sbe, int pos, int taille);
std::string showMessage(Data * d);
void encapsule_donnee ( dynamic_bitset<> port_src, dynamic_bitset<> port_dest, dynamic_bitset<> num_seq, dynamic_bitset<> num_ack, dynamic_bitset<> flag, dynamic_bitset<> fen, Data * d);
void encapsule_segment ( extremite * src, extremite * dest, boost::dynamic_bitset<> ip_id, boost::dynamic_bitset<> flag, boost::dynamic_bitset<> offset, boost::dynamic_bitset<> ttl, Data *d);
void encapsule_paquet ( extremite * src, extremite * dest, Data * d);
void encapsuleAll(int portSrc, int portDest, bool ack, bool syn, int nSeq, int nAck, int ipId, bool df, extremite * n1, extremite * n2, extremite * nextMac, Data * data);
void desencapsule_trame ( Data * d);
void desencapsule_paquet ( Data * d);
void desencapsule_segment ( Data * d);
void calculerChecksum ( Data * d);
void calculerFrameCheckSequence ( Data * d);
std::vector<Data *> fragmentationPaquet (Data &d, int mtu = 1500);
Data *reassemblagepaquet( std::vector<Data *> paquets);
string BinaryStringToText(string binaryString);
std::string dataType ( Data * d);
std::string adresseMac ( Data * d, int flag = 0);
unsigned int lireFCS ( Data * d);
int lireLongueurPaquet ( Data * d);
int lireFlagPaquet ( Data * d);
int lireOffsetPaquet ( Data * d);
int lireTTL ( Data * d);
int lireSommePaquet ( Data * d);
int lireNumeroSequence ( Data * d);
int lireNumeroAck ( Data * d);
int lireFenetre ( Data * d);
int lireSommeSegment ( Data * d);
std::string findTcpFlags ( Data * d);
std::string showMessage ( Data * d);
void envoyer(Noeud * n1, Noeud *n2, int portSrc, int portDest, bool syn, bool ack, int nSeq, int nAck, int ipId, bool df, Data *data);
#endif
