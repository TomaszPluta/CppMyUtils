#pragma once
/*  Boost-like utility to retrieve data passed by command line arguments */

#include "string"
#include "map"
#include "sstream"
#include "vector"
#include "algorithm"
#include "set"



	class opt{
		public:
			std::string name_;
			std::string desc_;
			bool hasValue_;
			std::string value = "";
			opt(std::string name, std::string desc, bool hasValue) : name_{name}, desc_{desc}, hasValue_{hasValue} {};
		};


class ProgramOptions{


	public:

	std::vector<opt> opts;

	void addUnparamOpt(std::string name,  std::string desc){
		opt newOpt(name, desc, false);
		opts.push_back(newOpt);
	}

	void addParamOpt(std::string name,  std::string desc){
		opt newOpt(name, desc, true);
		opts.push_back(newOpt);
	}

	std::vector<opt>  parse(int argc, const char *argv[]){
		std::vector<std::string>commandLineTokens(argv+1, argv+argc);
		std::vector<opt> givenOpt;
		for (auto &arg : commandLineTokens){
			std::cout << arg<<std::endl;
			auto iter = std::find_if(begin(opts), end(opts), [&](opt o){return (arg == o.name_);});
			if (iter!=end(opts)){
				if (iter->hasValue_){
					iter->value = arg;
				}
				givenOpt.push_back(*iter);
			} else{
				std::cout<<"invalid option: "<<arg<<std::endl;
			}
		}
		return givenOpt;
	}

};




