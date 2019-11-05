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
#include <iomanip>

#include "extern/variadic_table.h"


namespace fs = std::experimental::filesystem;

using namespace std::string_literals;




class ProcessInfo{
public:
	std::string _name{""};
	int memSize;
	int memPeek;
	int memSwap;
	int _pid {0};
	int _ppid{0};
	int _threads{0};
	int _memory{0};
	std::string _comandLine;
	std::string state;

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

	ProcessInfo &addMemory(int memory){
		_memory = memory;
		return *this;
	}


	friend std::ostream & operator << (std::ostream &out, const ProcessInfo &);
};



std::ostream & operator << (std::ostream &out, const ProcessInfo & pInfo){
	out<< "| name:" << std::setw(20) << pInfo._name << " | pid: "<< std::setw(20) << std::to_string(pInfo._pid)<<"| mem: "<< std::setw(20) <<std::to_string(pInfo._memory)<<" |"<<std::endl;
	return out;
}


template <typename T>
std::ostream & operator << (std::ostream & out, const std::vector<T> v){
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
				if (IsNumber(entry.path().filename().string())){
					subDirs.push_back(entry);
				}
			}
		}
	}
	return subDirs;
}



void RemoveTabs(std::string &s){
	s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());
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
					RemoveTabs(value);
					keyVals[key]= value;
				}
			}
		}
	}
	return keyVals;
}



bool IsFileInDirectory(const fs::path &dir, const fs::path &fname){
	const auto pathIter = std::find_if(fs::directory_iterator(dir), end(fs::directory_iterator(dir)),
			[&fname](const auto &entry){return(entry.path().filename() == fname);});
	if (pathIter !=  end(fs::directory_iterator(dir))){
		return true;
	}
	return false;
}


int safeStoi(std::string s){
	int res = 0;
	try{
		res = std::stoi(s.empty()? "0" : s);
	} catch (std::exception & err){
		std::cout<<"stoi conv error: " << err.what() <<std::endl;
	}
	return res;
}

using StatsKeyValues = std::map<std::string, std::string>;

std::vector<ProcessInfo> GetProcessInfo(){
	std::vector<ProcessInfo> psInfos;
	std::vector<fs::path> subDirs = GetSubDirsNUmberNamed("/proc");
	for (const auto &i : subDirs){
		StatsKeyValues stats = GetKeyValuePairsFromFile(i / "status");
		ProcessInfo pInfo;
		try{
			pInfo.addName(std::string(stats["Name"])).addPid(std::stoi(std::string(stats["Pid"]))).addMemory(safeStoi(stats["RssAnon"]));
		}
		catch (std::exception &err){
			std::cout<<"conversion failure\n";
		}
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
	std::vector<ProcessInfo> pInfos = GetProcessInfo();

	RemoveTabs(pInfos[0]._name);

	std::cout<<pInfos;
//	VariadicTable<std::string, int, int> vt{{"Name","PID","Memory"}, pInfos.size()};
//	for (const auto & i : pInfos){
//		vt.addRow(i._name, i._pid, i._memory);
//	}

//    VariadicTable<std::string, double, int, std::string> vt({"Name", "Weight", "Age", "Brother"},
//                                                            10);
//
//    vt.addRow({pInfos[0]._name, 180.2, 40, "John"});
//    vt.addRow({"David", 175.3, 38, "Andrew"});
//    vt.addRow({"Robert", 140.3, 27, "Fande"});
//
//	vt.print(std::cout);

	std::cout<<"done"<<'\n';
	std::cin.get();
}


