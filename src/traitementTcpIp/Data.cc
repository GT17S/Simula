#include "../../include/traitementTcpIp/Data.hh"

Data::Data(std::string message){
	orignalstring.assign(message);
	ossize = orignalstring.size();
	//std::cout << "Message: " <<  message << std::endl;
	std::reverse(std::begin(message), std::end(message));
	//std::cout << "Message: " <<  message << std::endl;
	seq = new boost::dynamic_bitset<unsigned char>(std::begin(message),std::end(message));
	assert(seq);
	
	type = DATA_TOTAL;
}

Data::Data(boost::dynamic_bitset<unsigned char>* seq, data_t type){
	setType(type);
	setSeq(seq);
}

Data::~Data(){
	delete seq;
}


void Data::setType(data_t _type){
	this->type = _type;
}

void Data::setSeq(boost::dynamic_bitset<unsigned char>* _seq){
	assert(_seq);
	this->seq = _seq;
}


int Data::operator[](int index){
	assert(index >= 0 && index < (int)seq->capacity());
	boost::dynamic_bitset<>::size_type i = index;
	return (int)seq[i].to_ulong();
}

std::ostream& operator<<(std::ostream &os, Data& d){	
	
	os << "Contenu" << *d.getSeq() << std::endl;
	os << "Type: " << d.getType() << std::endl;
	return os;
}

std::string Data::strtobinary(std::string msg){
	std::string binaryString = "";
    for (char& _char : msg) {
        binaryString += std::bitset<8>(_char).to_string();
    }
    //std::cout << "Binary: " <<  binaryString << std::endl;
    return binaryString;
}