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
#include <stdarg.h>
#include <map>
#include <fstream>

#include "fileHandler.h"
#include <experimental/filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::experimental::filesystem;

using namespace std::string_literals;




class ProcessInfo{
	std::string _name{""};
	int memSize;
	int memPeek;
	int memSwap;
	int _pid {0};
	int _ppid{};
	int _threads;
	std::string _comandLine;
	std::string state;
public:
	ProcessInfo &addName(std::string name){
		_name = name;
		return *this;
	}
	ProcessInfo &addPid(int pid){
		_pid = pid;
		return *this;
	}
	ProcessInfo &addPpid(int ppid){
		_ppid = ppid;
		return *this;
	}
	ProcessInfo &addThreads(int threads){
		_pid = threads;
		return *this;
	}
	ProcessInfo &addComandLine(std::string name){
		_comandLine = name;
		return *this;
	}

};




bool IsNumber(std::string num){
	return (std::find_if(num.begin(), num.end(), [&](auto i){return (!isdigit(i));}) ==  std::end(num));
}


//std::string GetFileName




std::vector<fs::path> GetSubDirectories(fs::path dir){
	std::vector<fs::path> subDirs;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		for (const auto & entry : fs::directory_iterator(dir)){
			if (fs::is_directory(entry.status())){

				std::cout<<entry.path()<<std::endl;

				auto it = entry.path().end();
				it--;

				std::cout<<*it<<std::endl;
				if (IsNumber(std::string(*it))){
					std::cout<<"found "<<entry.path().c_str()<<std::endl;
					subDirs.push_back(entry); ////przerobic na zwenetrzna funkcje
				} else{
					std::cout<<"NOT found: "<<entry.path().c_str()<<std::endl;
				}
				std::cout<<std::endl;
			}
		}
	}
	return subDirs;
}




std::map<std::string, std::string>  GetKeyValuesFromFile(fs::path filePath){
	std::map<std::string, std::string> keyVals;
	std::ifstream sfile(filePath);
	if (sfile.is_open()){
		std::string line;
		while (std::getline(sfile, line)){
			std::stringstream streamLine(line);
			std::string key;
			while(std::getline(streamLine, key, ':')){
				std::string value;
				if (std::getline(streamLine, value)){
					keyVals[key]= value;
				}
			}

		}
	}
	return keyVals;
}



std::vector<fs::path> GetFilesInDir(fs::path dir){
	std::vector<fs::path> files;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		//for (auto& entry : fs::directory_iterator(dir, fs::directory_options::skip_permission_denied)) {
			//std::cout<<entry.path()<<std::endl;
		for (auto& entry : fs::directory_iterator(dir)) {

			std::error_code ec;
			if (fs::is_regular_file(entry.status(ec))){
				std::cout<<ec<<std::endl;
				fs::perms p = entry.status().permissions();
//				std::cout <<"\t"<< ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
//																<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
//				std::cout <<"\t" << entry << std::endl;

				files.push_back(entry); ///
				if (entry.path().filename() == "status"){
					std::map<std::string, std::string> stats = GetKeyValuesFromFile(entry);
					ProcessInfo pInfo;
					pInfo.addName(std::string(stats["Name"])).addPid(std::stoi(std::string(stats["Pid"])));
					asm volatile ("nop");
				}
			}
		}
	}
	return files;
}







//
//
//std::vector<fs::path> GetFilesInDir(fs::path dir){
//	std::vector<fs::path> files;
//	if ((fs::exists(dir)) && (fs::is_directory(dir))){
//		for (auto& entry : fs::directory_iterator(dir, fs::directory_options::skip_permission_denied)) {
//			std::cout<<entry.path()<<std::endl;
//
//			std::error_code ec;
//			if (fs::is_regular_file(entry.status(ec))){
//
//				fs::perms p = entry.status().permissions();
//				std::cout <<"\t"<< ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
//																<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
//				std::cout <<"\t" << entry << std::endl;
//
//				files.push_back(entry); ///
//				if (entry.path().filename() == "status"){
//					std::map<std::string, std::string> stats = GetKeyValuesFromFile(entry);
//					ProcessInfo pInfo;
//					pInfo.addName(std::string(stats["Name"])).addPid(std::stoi(std::string(stats["Pid"])));
//					asm volatile ("nop");
//				}
//			}
//		}
//	}
//	return files;
//}
//
//









class Processes{
	void Traverse(){

	}

public:
	Processes() = default;

};



int main(int argc, char **argv)
{
	std::vector<fs::path> subDirs = GetSubDirectories("/proc");
	std::vector<fs::path> files = GetFilesInDir(subDirs[0]);
//	std::cout<<procFiles;
	std::cout<<"done"<<'\n';
	std::cin.get();
}


