#include "../../include/traitementTcpIp/Data.hh"

Data::Data(std::string message){
	std::string binstr = strtobinary(message);
	seq = new boost::dynamic_bitset<>(message.size()*8);
	//std::cout << message << std::endl;
	assert(seq);
	for (int i = message.size(); i >= 0; i--){
		if(binstr[i] == '1'){
			seq->set(i);
		}
		if(binstr[i] == '0'){
			seq->set(i,false);
		}
	}

	seq->flip();
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
	//Maybe a deep copy
	this->seq = _seq;
}


int Data::operator[](int index){
	assert(index > 0 && index < (int)seq->capacity());
	boost::dynamic_bitset<>::size_type i = index;
	return (int)seq[i].to_ulong();
}

std::ostream& operator<<(std::ostream &os, Data& d){	
	os << "Contenu: " << *d.getSeq() << std::endl;
	os << "Type: " << d.getType() << std::endl;
	return os;
}

std::string Data::strtobinary(std::string msg){
	std::string binaryString = "";
    for (char& _char : msg) {
        binaryString += std::bitset<8>(_char).to_string();
    }
    return binaryString;
}