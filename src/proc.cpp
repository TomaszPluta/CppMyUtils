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


namespace fs = std::experimental::filesystem;

using namespace std::string_literals;



bool IsNumber(std::string num){
	for (const auto & i : num){
		if (!(isdigit(i))){
			return false;
		}
	}
	return true;
}


std::vector<fs::path> GetSubDirectories(fs::path dir){
	std::vector<fs::path> subDirs;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		for (const auto & entry : fs::directory_iterator(dir)){
			if (fs::is_directory(entry.status())){
				subDirs.push_back(entry);
				std::cout<<entry.path()<<std::endl;
				auto it = entry.path().end();
				it--;

				std::cout<<*it<<std::endl;
				if (IsNumber(std::string(entry.path()))){
					std::cout<<"found "<<entry.path().c_str()<<std::endl;
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
//z https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c/6892829#6892829
}



std::vector<fs::path> GetFilesInDir(fs::path dir){
	std::vector<fs::path> files;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		for (const auto & entry : fs::directory_iterator(dir)){
			if (fs::is_regular_file(entry.status())){
				files.push_back(entry);
				GetKeyValuesFromFile(entry);
			}
		}
	}
	return files;
}






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
	ProcessInfo &comandLine(std::string name){
		_comandLine = name;
		return *this;
	}

};



class Processes{
	void Traverse(){

	}
public:
	Processes() = default;

};



int main(int argc, char **argv)
{
	std::vector<fs::path> subDirs = GetSubDirectories("/proc");
	std::vector<fs::path> files = GetFilesInDir("/proc/1487");
//	std::cout<<procFiles;
	std::cin.get();
}


