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
#include <iostream>

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

	friend std::ostream & operator << (std::ostream &out, const ProcessInfo &);
};



std::ostream & operator << (std::ostream &out, const ProcessInfo & pInfo){
	out<< pInfo._name << " " << std::to_string(pInfo._pid)<<std::endl;
	return out;
}


template <typename T>
std::ostream & operator <<(std::ostream & out, const std::vector<T> v){
	for (const auto &i :v){
		out<<i<<"\n";
	}
	return out;
}



bool IsNumber(std::string num){
	return (std::find_if(num.begin(), num.end(), [&](auto i){return (!isdigit(i));}) ==  std::end(num));
}




std::vector<fs::path> GetSubDirsNUmberNamed(fs::path dir){
	std::vector<fs::path> subDirs;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		for (const auto & entry : fs::directory_iterator(dir)){
			if (fs::is_directory(entry.status())){

				std::cout<<entry.path()<<std::endl;
				std::cout<<entry.path().filename()<<std::endl;

				if (IsNumber(entry.path().filename().string())){
					std::cout<<"found "<<entry.path().c_str()<<std::endl;
					subDirs.push_back(entry);
				} else{
					std::cout<<"NOT found: "<<entry.path().c_str()<<std::endl;
				}
				std::cout<<std::endl;
			}
		}
	}
	return subDirs;
}







std::map<std::string, std::string>  GetKeyValuePairsFromFile(fs::path filePath){
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




std::vector<fs::path> GetFilesInDirX(fs::path dir){
	std::vector<fs::path> files;
	if ((fs::exists(dir)) && (fs::is_directory(dir))){
		//for (auto& entry : fs::directory_iterator(dir, fs::directory_options::skip_permission_denied)) {
			//std::cout<<entry.path()<<std::endl;
		for (auto& entry : fs::directory_iterator(dir)) {

			std::error_code ec;
			if (fs::is_regular_file(entry.status(ec))){
				std::cout<<ec<<std::endl;
			//	fs::perms p = entry.status().permissions();
//				std::cout <<"\t"<< ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
//																<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
//				std::cout <<"\t" << entry << std::endl;

				files.push_back(entry); ///
				if (entry.path().filename() == "status"){
					std::map<std::string, std::string> stats = GetKeyValuePairsFromFile(entry);
					ProcessInfo pInfo;
					pInfo.addName(std::string(stats["Name"])).addPid(std::stoi(std::string(stats["Pid"])));
					asm volatile ("nop");
				}
			}
		}
	}
	return files;
}


bool IsFileInDirectory(const fs::path &dir, const fs::path &fname){
	const auto pathIter = std::find_if(fs::directory_iterator(dir), end(fs::directory_iterator(dir)),
			[&fname](const auto &entry){return(entry.path().filename() == fname);});
	if (pathIter !=  end(fs::directory_iterator(dir))){
		return true;
	}
	return false;
}





//	std::vector<fs::path> files;
//	if ((fs::exists(dir)) && (fs::is_directory(dir))){
//		for (auto& entry : fs::directory_iterator(dir)) {
//			std::error_code ec;
//			if (fs::is_regular_file(entry.status(ec))){
//				std::cout<<ec<<std::endl;
//				files.push_back(entry); ///
//				if (entry.path().filename() == "status"){
//
//				}
//			}
//		}
//	}
//	return files;
//}



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

using StatsKeyValues = std::map<std::string, std::string>;

std::vector<ProcessInfo> GetProcessInfo(){
	std::vector<ProcessInfo> psInfos;
	std::vector<fs::path> subDirs = GetSubDirsNUmberNamed("/proc");
	for (const auto &i : subDirs){
		StatsKeyValues stats = GetKeyValuePairsFromFile(i / "status");
		ProcessInfo pInfo;
		pInfo.addName(std::string(stats["Name"])).addPid(std::stoi(std::string(stats["Pid"])));
		psInfos.push_back(pInfo);
	}
	return psInfos;
}





class Processes{
	void Traverse(){

	}

public:
	Processes() = default;

};



int main(int argc, char **argv)
{
	std::vector<fs::path> subDirs = GetSubDirsNUmberNamed("/proc");

//	std::vector<fs::path> files = GetFilesFromDirectory(subDirs[0]);
	std::cout<<IsFileInDirectory(subDirs[0], "status");
	std::vector<ProcessInfo> pInfos = GetProcessInfo();
	std::cout<<pInfos;
	std::cout<<"done"<<'\n';
	std::cin.get();
}


