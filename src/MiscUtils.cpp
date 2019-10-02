#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>

class Ipv4
{
	static  constexpr int octetsNb = 4;
	std::vector<int> octets;
	std::initializer_list<int> init = {0,0,0,0};



public:
	Ipv4(void){
	}


	Ipv4(std::string str){
		std::string octet;
		std::stringstream ss(str);
		while (octets.size() < octetsNb) {
			if (getline(ss, octet, '.')){
				octets.push_back(std::stoi(octet));
			} else {
				octets.push_back(0);
			}
		}
	}

	void ShowInRangeTo(Ipv4 &ipv4);

	friend std::ostream& operator << (std::ostream& out,  Ipv4 const &ipv4);
	friend std::istream& operator >> (std::istream& in, Ipv4 &ipv4);
	friend std::stringstream& operator>>(std::stringstream &ss, Ipv4 & ipv4);
};


std::ostream& operator << (std::ostream& out,  Ipv4 const & ipv4)
{
	for (auto i = ipv4.octets.begin(); i != ipv4.octets.end();i++ ) {
		out << *i;
		if (i != ipv4.octets.end()-1){
			out << ".";
		}
	}

	out<<std::endl;
	return out;


}

std::istream& operator >> (std::istream& in, Ipv4 & ipv4)
{
	ipv4.octets.clear();
	std::string s;
	in  >> s;

	std::string octet;
	std::stringstream ss(s);

	while (ipv4.octets.size() < ipv4.octetsNb) {
		if (getline(ss, octet, '.')){
			ipv4.octets.push_back(std::stoi(octet));
		} else {
			ipv4.octets.push_back(0);
		}
	}
	return in;
}

std::stringstream& operator>>(std::stringstream &ss, Ipv4 & ipv4){
	ipv4.octets.clear();
	std::string octet;

	while (ipv4.octets.size() < ipv4.octetsNb) {
		if (getline(ss, octet, '.')){
			ipv4.octets.push_back(std::stoi(octet));
		} else {
			ipv4.octets.push_back(0);
		}
	}
	return ss;
}




void Ipv4::ShowInRangeTo(Ipv4 &ipv4){
	long long ipVal = (octets[3]<<24) + (octets[2]<<16) + (octets[1]<<8) + (octets[0]);
	std::cout<<ipVal<<std::endl;
}


int main(int argc, char **argv)
{
	Ipv4 ipv4("14.15.17.18");
	std::cout<<ipv4;
	ipv4.ShowInRangeTo(ipv4);
	std::cin.get();
}


