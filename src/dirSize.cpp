#include "algorithm"
#include "numeric"
#include "experimental/filesystem"
#include "iostream"


namespace fs = std::experimental::filesystem;


int GetDirectorySize (fs::path dir){
	int sum = 0;
	for (const auto & item : fs::recursive_directory_iterator(dir)){
		if (fs::is_regular_file(item.path())){ //also dir, recurs
			sum += fs::file_size(item.path());
		}
	}
	return sum;
}




int mainDirSize (void){


	std::cout<<GetDirectorySize("/home/tomek/Dokumenty");
}
