#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <iostream>

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
		currentPtr->clear();
	}

public:

	dBuff(int size) {
		currentPtr = std::make_unique<std::vector<T>>();
		currentPtr->reserve(size);
		nextPtr = std::make_unique<std::vector<T>>();
		nextPtr->reserve(size);
	}

	void write(T data){
		std::cout<<"data: "<<data<<", size: "<<nextPtr->size()<<", cap: "<< nextPtr->capacity()<<std::endl;
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

};



dBuff<int> dbuff(10);

void writeToDBuff(dBuff<int> & dbuff){
	for (int j=0; j< 10; j++){
		for (int i=0; i<10; i++){
			dbuff.write(i+(j*10));
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

void readFromDBuff(dBuff<int> & dbuff){
	for (int j=0; j< 10; j++){
		for (int i=0; i<10; i++){
			std::cout<<dbuff[i]<<std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

void TestDoubleBuffReadWrite(dBuff<int> & dbuff){
	std::thread t1(readFromDBuff, std::ref(dbuff));
	std::thread t2(writeToDBuff, std::ref((dbuff)));
	t1.join();
	t2.join();

}











