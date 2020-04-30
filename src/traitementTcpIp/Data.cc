#include "../../include/traitementTcpIp/Data.hh"

Data::Data(std::string message){
	std::cout << "Message: " <<  message << std::endl;
	std::string binstr = strtobinary(message);
	//Penser à en allouer plus pour pouvoir contenir toutes les infos d'un paquet
	seq = new boost::dynamic_bitset<>();
	assert(seq);
	for (int i = (int)binstr.size(); i >= 0; i--){
		//std::cout << binstr[i];
		if(binstr[i] == '1'){
			//seq->set(i, true);
			seq->push_back(1);
		}
		if(binstr[i] == '0'){
			seq->push_back(0);
		}
	}


	//seq->flip();
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
	for (int i = 0; i < (int)d.getSeq()->size(); ++i)
	{
		os << d.getSeq()[i] ;
	}
	os << std::endl;
	os << "Type: " << d.getType() << std::endl;
	return os;
}

std::string Data::strtobinary(std::string msg){
	std::string binaryString = "";
    for (char& _char : msg) {
        binaryString += std::bitset<8>(_char).to_string();
    }
    std::cout << "Binary: " <<  binaryString << std::endl;
    return binaryString;
}