#include <vector>
#include <memory>


template <typename T>
class dBuff{
//	std::vector<T> buff1;
//	std::vector<T> buff2;
	std::unique_ptr<std::vector<T>> currentPtr;
	std::unique_ptr<std::vector<T>> nextPtr;
public:

	dBuff(int size) {
		currentPtr = std::make_unique<std::vector<T>>(size);
		nextPtr = std::make_unique<std::vector<T>>(size);
	}

	void write(T data){
		if (nextPtr->size() > nextPtr->max_size()){
			swap();
		}
		nextPtr->push_back(data);
	}

	void swap (void){
		currentPtr.swap(nextPtr);
	}

//	T read(){
//		//send to stream
//	}



	T operator[](int index){
		return currentPtr[index];
	}



};
