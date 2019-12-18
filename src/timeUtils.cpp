#include "algorithm"
#include "iostream"
#include "string"
#include "string_view"
#include "fstream"
#include "string_view"
#include "sstream"
#include "memory"
#include "vector"
#include "chrono"
#include "ctime"
#include "functional"



void out(std::string t){
	std::cout<<t<<std::endl;
}

void doubleOut(std::string t, char x){
	std::cout<<t<<std::to_string(x)<<std::endl;
}


template<typename F, typename ... Args>
int funcProfile(F function, Args ... args){
	std::chrono::steady_clock::time_point startPoint = std::chrono::steady_clock::now();
	std::invoke(function, args ...);
	std::chrono::steady_clock::time_point endPoint = std::chrono::steady_clock::now();
	std::chrono::duration<double,  std::milli> dur;
	dur = endPoint - startPoint;
	std::cout<<"took: "<<dur.count()<<std::endl;
	return 1;
}


template<typename F, typename ... Args>
int funcProfile2(F function, Args ... args){
	std::chrono::high_resolution_clock::time_point startPoint = std::chrono::high_resolution_clock::now();
	std::invoke(function, args ...);
	std::chrono::high_resolution_clock::time_point endPoint = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double,  std::milli> dur;
	dur = endPoint - startPoint;
	std::cout<<"took: "<<dur.count()<<std::endl;
	return 1;
}


int mainT (void){

	funcProfile(out, "bbbb");
	funcProfile(doubleOut, "ccc", 'D');
	std::cout<<std::endl;

	funcProfile2(out, "bbbb");
	funcProfile2(doubleOut, "ccc", 'D');

}
