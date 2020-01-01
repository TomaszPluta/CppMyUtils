#include "doubleBuff.h"
#include <iostream>
#include <map>

#include "occurenceCounter.h"


int main(int argc, char **argv)
{
	std::vector<int> v{4,5,6,6,7,6,4,3,2,1,5,6,7,3,4,6};
	std::map<int, int> m = OccurenceCounter(v);

	for (const auto & i : m){
		std::cout<<i.first<<": "<<i.second<<std::endl;
	}
}


