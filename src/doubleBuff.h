#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <iostream>


template <typename T>
class dBuff{
//	std::vector<T> buff1;
//	std::vector<T> buff2;
	std::unique_ptr<std::vector<T>> currentPtr;
	std::unique_ptr<std::vector<T>> nextPtr;
	std::mutex mx;
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

	void swap (void){
		std::unique_lock<std::mutex>lock(mx);
		currentPtr.swap(nextPtr);
		currentPtr->clear();
	}

	template <typename U>
	void  read(U outputIter){
		std::copy(begin(*currentPtr), end(*currentPtr), outputIter);
	}

	T operator[](int index){
		return (*currentPtr)[index];
	}



};
