
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <string_view>



//
//#include <iostream>     // std::cout
//#include <algorithm>    // std::find_if
//#include <vector>       // std::vector
//
//bool IsOdd (int i) {
//  return ((i%2)==1);
//}
//
//int main () {
//  std::vector<int> myvector;
//
//  myvector.push_back(10);
//  myvector.push_back(25);
//  myvector.push_back(40);
//  myvector.push_back(55);
//
//  std::vector<int>::iterator it = std::find_if (myvector.begin(), myvector.end(), IsOdd);
//  std::cout << "The first odd value is " << *it << '\n';
//
//
//  *it = 77;
//
//
//  std::cout << "The mod odd value is " << *it << '\n';
//
//  return 0;
//}




#include "program_opt.h"

int main(int argc, char *argv[]) {

	ProgramOptions programOptions;
	programOptions.addUnparamOpt("--help", "prints help");
	programOptions.addParamOpt("--port", "port to connect");

	const char *cmd[] = {"--help", "blabla", "--port", "1886", "nopenope"};
	std::vector<opt> options =  programOptions.parse(3, cmd);







//	std::string ipAddr{"127.0.0.1"};
//	int port{1886};
//	if ((argc<3) || (argc>3)){
//		std::cout<<"used default settings!"<<std::endl;
//	}else {
//		ipAddr = argv[1];
//		port = std::stoi(argv[2]);
//	}
//
//	boost::asio::io_service ioService;
//	boost::asio::ip::tcp::socket socket(ioService);
//	boost::asio::ip::address servIp = boost::asio::ip::address::from_string(ipAddr);
//	boost::asio::ip::tcp::endpoint endpoint(servIp, port);
//	socket.connect(endpoint);
//	std::string dataIn;
//	while (std::getline(std::cin, dataIn)){
//		std::cout<<"captured: "<<dataIn<<std::endl;
//		boost::system::error_code err;
//		boost::asio::write(socket, boost::asio::buffer(dataIn), err);
//	}

	return 0;
}
