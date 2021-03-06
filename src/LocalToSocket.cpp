
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <string_view>

#include <chrono>
#include <ctime>
#include <thread>
#include "program_opt.h"


int Sender(int argc, char *argv[]) {

	std::cout<<"hello"<<std::endl;

	while (1){
		auto now = std::chrono::system_clock::now();
		time_t timeLocal = std::chrono::system_clock::to_time_t(now);

		std::cout<<ctime(&timeLocal)<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}


	std::string ipAddr{"127.0.0.1"};
	int port{1886};
	if ((argc<3) || (argc>3)){
		std::cout<<"used default settings!"<<std::endl;
	}else {
		ipAddr = argv[1];
		port = std::stoi(argv[2]);
	}

	boost::asio::io_service ioService;
	boost::asio::ip::tcp::socket socket(ioService);
	boost::asio::ip::address servIp = boost::asio::ip::address::from_string(ipAddr);
	boost::asio::ip::tcp::endpoint endpoint(servIp, port);
	socket.connect(endpoint);
	std::string dataIn;
	while (std::getline(std::cin, dataIn)){
		std::cout<<"captured: "<<dataIn<<std::endl;
		boost::system::error_code err;
		boost::asio::write(socket, boost::asio::buffer(dataIn), err);
	}

	return 0;
}
