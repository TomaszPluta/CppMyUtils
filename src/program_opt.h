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
		for (std::vector<std::string>::iterator it = begin(commandLineTokens); it < end(commandLineTokens); it++){
			std::cout << *it <<std::endl;
			auto iter = std::find_if(begin(opts), end(opts), [&](opt o){return (*it == o.name_);});
			if (iter!=end(opts)){
				if (iter->hasValue_){
					std::cout<<"has value"<<std::endl;
					it++;
					iter->value = *it;
				}
				givenOpt.push_back(*iter);
			} else{
				std::cout<<"invalid option: "<<*it<<std::endl;
			}
		}
		return givenOpt;
	}

};



/* Example usage:
 *
 * ProgramOptions programOptions;
 *	programOptions.addUnparamOpt("--help", "prints help");
 *	programOptions.addParamOpt("--port", "port to connect");
 *
 *	const char *cmd[] = {"programName", "--verbose", "blahblah", "--port", "1886", "foobar"};
 *	std::vector<opt> options =  programOptions.parse(6, cmd);
s *
 */
