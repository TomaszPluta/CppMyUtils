#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <iostream>

#include <iterator>
#include <fstream>
#include <thread>
#include <chrono>

template <typename T>
class dBuff{
	std::unique_ptr<std::vector<T>> currentPtr;
	std::unique_ptr<std::vector<T>> nextPtr;
	std::mutex mx;

	void swap (void){
		std::unique_lock<std::mutex>lock(mx);
		currentPtr.swap(nextPtr);
		nextPtr->clear();
	}

public:

	dBuff(int size) {
		currentPtr = std::make_unique<std::vector<T>>(1, "nothing in current");
		currentPtr->reserve(size);
		nextPtr = std::make_unique<std::vector<T>>();
		nextPtr->reserve(size);
	}

	void write(T data){
//		std::cout<<"data: "<<data<<", size: "<<nextPtr->size()<<", cap: "<< nextPtr->capacity()<<std::endl;
		nextPtr->push_back(data);
		if (nextPtr->size() == nextPtr->capacity()){
			std::cout<<"swap called"<<std::endl;
			swap();
		}
	}


	template <typename U>
	void  read(U outputIter){
		std::unique_lock<std::mutex>lock(mx);
		std::copy(begin(*currentPtr), end(*currentPtr), outputIter);
	}

	T operator[](int index){
		std::unique_lock<std::mutex>lock(mx);
		return (*currentPtr)[index];
	}


	void showNextBuff(){
		for (int i = 0; i <(*nextPtr).size(); i++){
			std::cout<<(*nextPtr)[i]<<std::endl;
		}
		std::cout<<std::endl;
	}

	void print(){
		std::ostream_iterator<std::string> out_it (std::cout, "\n");
		read(out_it);
		std::cout<<std::endl;
	}

	void printToFile(std::string fName){
		std::ofstream file(fName);
		std::ostream_iterator<std::string> out_it(file, "\n");
		read(out_it);
		std::cout<<std::endl;
	}


};


std::vector<std::string>  testData= {
		std::string(40, 'a'),
		std::string(40, 'b'),
		std::string(40, 'c'),
		std::string(40, 'd'),
		std::string(40, 'e'),
		std::string(40, 'f'),
		std::string(40, 'g'),
		std::string(40, 'h'),
		std::string(40, 'i'),
		std::string(40, 'j'),
};

dBuff<std::string> dbuff(10);

void readFromDBuff(dBuff<std::string> & dbuff){
	for (int j=0; j< 1000; j++){
		std::cout<<"currbuff:"<<std::endl;
		dbuff.print();
		dbuff.printToFile("outtestthr.txt");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}


void writeToDBuff(dBuff<std::string> & dbuff){
	for (int j=0; j< 50; j++){
		for (int i=0; i<10; i++){
			//dbuff.write(i+(j*10));
			dbuff.write(testData[i]+": "+std::to_string(j));
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

}

void TestDoubleBuffReadWrite(dBuff<std::string> & dbuff){
	std::thread t1(readFromDBuff, std::ref(dbuff));
	std::thread t2(writeToDBuff,  std::ref(dbuff));
	t1.join();
	t2.join();

}





