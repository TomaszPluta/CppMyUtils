#include "mvc.h"

#include "vector"
#include "queue"
#include "list"






int main(int argc, char **argv)
{
	std::priority_queue<std::pair<int, std::string>> que;
	que.push(std::pair<int, std::string>(10, "asd"));
	que.push(std::pair<int, std::string>(8, "yyy"));
	que.push(std::pair<int, std::string>(15, "zzz"));
	que.push(std::pair<int, std::string>(75, "kjh"));
	que.push(std::pair<int, std::string>(65, "poi"));


	std::cout<<std::pair<int, std::string>(que.top()).first;

	que.pop();
//	que.top()<<std::endl;
}


