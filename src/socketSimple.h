#pragma once

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

#include<chrono>
#include<thread>

class Socket{
		int socket_desc;
		struct sockaddr_in server;
		std::string ip_;
		int port_ = 0;
public:

		Socket(std::string ip, int port) : ip_{ip}, port_{port}{
			socket_desc = socket(AF_INET , SOCK_STREAM , 0);
			if (socket_desc == -1)
			{
				std::cout<<"Could not create socket";
			}

			server.sin_addr.s_addr = inet_addr(ip.c_str());
			server.sin_family = AF_INET;
			server.sin_port = htons( port );
		}

		bool conn (void){
			return  (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) >= 0);
		}

		bool sendData(std::string msg){
			return ( send(socket_desc , msg.c_str(), msg.size(), 0) >= 0);
		}

		void reconnect(){
			while (!conn()){
				close(socket_desc);
				socket_desc = socket(AF_INET , SOCK_STREAM , 0);
							if (socket_desc == -1)
							{
								std::cout<<"Could not create socket";
							}
							server.sin_addr.s_addr = inet_addr(ip_.c_str());
							server.sin_family = AF_INET;
							server.sin_port = htons(port_);
				std::cout<<"reconnecting..."<<std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(15));
			}
		}





//		std::string receiveData(void){
//		constexpr int REPLY_MAX_SIZE = 2000;
//		char server_reply[REPLY_MAX_SIZE];
//		recv(socket_desc, server_reply , REPLY_MAX_SIZE , 0) > 0;
//		return std::string(server_reply);
//		}
};
