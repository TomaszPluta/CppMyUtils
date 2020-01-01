#pragma once

#include <map>
#include <algorithm>
#include <vector>


//template<typename T>
//std::map<int, int> OccurenceCounter(T container){
//	std::map<int, int> oMap;
//	for (const auto &i :container){
//		oMap.emplace(i, std::count(begin(container), end(container), i));
//
//	}
//	return oMap;
//
//}



template <template<class, class> class C, class E, class A>
std::map<int, int> OccurenceCounter(const C<E, A> &container){
	std::map<E, int> oMap;
	for (const auto &i :container){
		oMap.emplace(i, std::count(begin(container), end(container), i));

	}
	return oMap;
}


