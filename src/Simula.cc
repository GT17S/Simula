#include <iostream>

#include "../../include/traitementTcpIp/Data.hh"
#include "../../include/traitementTcpIp/DataOutils.hh"

int main(int argc, char ** argv)
{
	std::string s("Test");
	Data d(s);
	std::cout << d << std::endl;

 	return 0;
}	
