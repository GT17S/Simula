#include "Data.hh"

Data::Data(std::string message){
//	std::reverse(std::begin(message), std::end(message));
	std::string s = this->strtobinary ( message);
	seq = new boost::dynamic_bitset<>( s);
	assert(seq);
	type = DATA_TOTAL;
}

Data::Data(boost::dynamic_bitset<>* seq, data_t type){
	setType(type);
	setSeq(seq);
}

Data::~Data(){
	delete seq;
}


void Data::setType(data_t _type){
	this->type = _type;
}

void Data::setSeq(boost::dynamic_bitset<>* _seq){
	assert(_seq);
	this->seq = _seq;
}


int Data::operator[](int index){
	assert(index >= 0 && index < (int)seq->capacity());
	boost::dynamic_bitset<>::size_type i = index;
	return (int)seq[i].to_ulong();
}

std::ostream& operator<<(std::ostream &os, Data& d){	
	boost::dynamic_bitset<> tmp = *d.getSeq();
	os << "Contenu : \n" ;
	for (unsigned int i = 0; i < d.getSeq()->size(); i++)	{
		if ( (i) % 32 == 0) os <<std::endl;
		os << tmp[i];
	}
	
	os << std::endl;
	std::string s;
	if (d.getType() == DATA_TOTAL) s = "Donnée";
	else if (d.getType() == DATA_SEGMENT) s = "Segment";
	else if (d.getType() == DATA_PAQUET) s = "Paquet";
	else if (d.getType() == DATA_TRAME) s = "Trame";
	os << "Type : " << s << std::endl;
	return os;
}

std::string Data::strtobinary(std::string msg){
	std::string binaryString = "";	
	const char * str = msg.c_str();
	for (int i = (int) msg.size()-1; i > -1 ; i--)	{
		char c = str[i];
		for (int j = 0; j < 8; j++)	{
			bool bit = c & (1<<j);
			binaryString+= bit ? "1" : "0";
		}
	}
    return binaryString;
}
