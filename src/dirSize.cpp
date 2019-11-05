#include "algorithm"
#include "experimental/filesystem"



namespace fs = std::experimental::filesystem;


int GetDirectorySize (fs::path dir){
	int sum = 0; ///use algorithm instead sum()
	for (const auto & item : fs::directory_iterator(dir)){
		if (fs::is_regular_file(item.path())){ //also dir, recurs
			sum += fs::file_size(item.path());
		}
	}
	return sum;
}




int main (void){

	GetDirectorySize("/home/tomek/Dokumenty");
	;
}
