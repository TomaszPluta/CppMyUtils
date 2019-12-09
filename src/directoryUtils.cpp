#include "algorithm"
#include "numeric"
#include "experimental/filesystem"
#include "iostream"
#include "chrono"


namespace fs = std::experimental::filesystem;


int GetDirectorySize (fs::path dir){
	int sum = 0;
	for (const auto & item : fs::recursive_directory_iterator(dir, fs::directory_options::skip_permission_denied)){
		std::error_code ec;
		if (fs::is_regular_file(item.path(), ec)){
			sum += fs::file_size(item.path());
		}
	}
	return sum;
}


constexpr auto chrono_days(int d){
	using namespace std::chrono_literals;
	auto day = 24h;
	return d* day;
}


int RemoveFilesOlderThanDays(fs::path dir, int days){
	try{
		for (const auto & entry : std::experimental::filesystem::recursive_directory_iterator(dir, fs::directory_options::skip_permission_denied)){
			if (std::experimental::filesystem::is_regular_file(entry.path())){
				std::cout<<entry.path()<<": ";
				if(std::experimental::filesystem::last_write_time(entry) < (std::chrono::system_clock::now() - chrono_days(days))){
					std::cout<<"older "<<std::endl;
				} else{
					/*std::remove(entry.path().c_str()); */
					std::cout<<"younger"<<std::endl;
				}
			}
		}
		return 1;
	}
	catch (std::experimental::filesystem::filesystem_error & err){
		return 0;
	}
}




int mainDir(void){

	RemoveFilesOlderThanDays("/home/tomek/test", 10);
	std::cout<<GetDirectorySize("/proc/1");
}
