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
#include <iomanip>

class Ipv4
{
	static  constexpr int octetsNb = 4;
	std::vector<int> octets;
	std::initializer_list<int> init = {0,0,0,0};



public:
	int ToInt(void);


	Ipv4(void){
	}


	Ipv4(std::string str);
	Ipv4(int ip);
	void ShowInRangeTo(Ipv4 &ipv4);

	Ipv4& operator++();
	Ipv4 operator++(int);
	bool operator>(const Ipv4 & rhs);

	bool operator<(const Ipv4 & rhs);
	bool operator>=(const Ipv4 & rhs);
	bool operator<=(const Ipv4 & rhs);

	friend std::ostream& operator << (std::ostream& out,  Ipv4 const &ipv4);
	friend std::istream& operator >> (std::istream& in, Ipv4 &ipv4);
	friend std::stringstream& operator>>(std::stringstream &ss, Ipv4 & ipv4);

};


bool Ipv4::operator>(const Ipv4 & rhs){
	return octets > rhs.octets;
}


bool Ipv4::operator<(const Ipv4 & rhs){
	return !operator>(rhs);
}

bool Ipv4::operator>=(const Ipv4 & rhs){
	return  !operator<(rhs);
}
bool Ipv4::operator<=(const Ipv4 & rhs){
	return  !operator>(rhs);
}


Ipv4& Ipv4::operator++(void){
	octets[3]++;

	if (octets[3] > 255){
		octets[3] = 0;
		octets[2]++;
	}
	if (octets[2] > 255){
		octets[2] = 0;
		octets[1]++;
	}
	if (octets[1] > 255){
		octets[1] = 0;
		octets[0]++;
	}

return *this;
}


Ipv4 Ipv4::operator++(int){
	Ipv4 copy {*this};
	operator++();
	return copy;
}




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




Ipv4::Ipv4(int ip){
	octets.resize(4);
	for (auto i = octets.rbegin(); i != octets.rend(); i++){
		*i=(ip&0xFF);
		ip = ip>>8;
	}
}



int Ipv4::ToInt (){
	int givenIp { 0 };
	for (auto i : octets){
		givenIp = givenIp<<8;
		givenIp += i;
	}
	return givenIp;
}


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






void Ipv4::ShowInRangeTo(Ipv4 &ip){
	if (*this > ip){
		std::cout<<"no valid range";
	}
	Ipv4 ipThis = *this;

	while (ipThis < ip){
		std::cout<<ipThis<<std::endl;
		ipThis++;
	}
}


int main(int argc, char **argv)
{
	Ipv4 ipCli("14.15.17.255");
	Ipv4 ipServ("14.15.18.30");
	std::cout<<ipCli;
	ipCli++;
	std::cout<<ipCli;


//	std::cout<<ipServ;
//	ipCli.ShowInRangeTo(ipServ);


	Ipv4 ipInt(3452516227);
	std::cout<<ipInt;
	std::cout<<ipInt.ToInt();
	std::cin.get();
}


