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


namespace fs = std::experimental::filesystem;

using namespace std::string_literals;



std::vector<fs::path> GetSubDirectories(fs::path dir){
	std::vector<fs::path> subDirs;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		for (const auto & entry : fs::directory_iterator(dir)){
			if (fs::is_directory(entry.status())){
				subDirs.push_back(entry);
			}
		}
	}
	return subDirs;
}

std::vector<fs::path> GetFilesInDir(fs::path dir){
	std::vector<fs::path> files;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		for (const auto & entry : fs::directory_iterator(dir)){
			if (fs::is_regular_file(entry.status())){
				files.push_back(entry);
			}
		}
	}
	return files;
}


std::map<std::string, std::string>  GetKeyValuesFromFile(fs::path filePath){
	std::ifstream file(filePath);
	//std::ifstream::open();

	std::map<std::string, std::string> mp;
	return mp;

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
//	std::cout<<procFiles;
	std::cin.get();
}


