#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include <cstdlib>

class Ipv4
{
	static  constexpr int octetsNb = 4;
	std::vector<int> octets;
	std::initializer_list<int> init = {0,0,0,0};

	int convertToInt (Ipv4 &ip);

public:
	Ipv4(void){
	}


	Ipv4(std::string str);
	void ShowInRangeTo(Ipv4 &ipv4);

	friend std::ostream& operator << (std::ostream& out,  Ipv4 const &ipv4);
	friend std::istream& operator >> (std::istream& in, Ipv4 &ipv4);
	friend std::stringstream& operator>>(std::stringstream &ss, Ipv4 & ipv4);
};


Ipv4::Ipv4(std::string str){
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



int Ipv4::convertToInt (Ipv4 &ip){
	int givenIp { 0 };
	for (int i=0; i<4; i++){
		givenIp +=(ip.octets[i]<<((3-i)*8));
	}
	return givenIp;
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
	int ipVal = convertToInt(*this);
	std::cout<<ipVal<<std::endl;

	int givenIp = convertToInt(ipv4);
	std::cout<<givenIp<<std::endl;

	int diff = std::abs(givenIp -  ipVal);
	std::cout<<diff<<std::endl;

	std::vector<int> tmp = octets;
	for (int i=0; i<diff; i++){
		if (tmp[3] > 255){
			tmp[2]++;
			tmp[3] = 0;
		}
		if (tmp[2] > 255){
			tmp[1]++;
			tmp[3] = 0;
			tmp[2] = 0;
		}
		if (tmp[2] > 255){
			tmp[0]++;
			tmp[3] = 0;
			tmp[2] = 0;
			tmp[1] = 0;
		}


		for (auto i = tmp.begin(); i != tmp.end();i++ ) {
			std::cout << *i;
			if (i != tmp.end()-1){
				std::cout << ".";
			}
		}
		std::cout << std::endl;
		tmp[3]++;
	}
}


int main(int argc, char **argv)
{
	Ipv4 ipCli("14.15.17.178");
	Ipv4 ipServ("14.15.18.30");
	std::cout<<ipCli;
	std::cout<<ipServ;
	ipCli.ShowInRangeTo(ipServ);
	std::cin.get();
}


