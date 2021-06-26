#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
#include<functional>

template<typename T>
T foreach(typename std::vector<T>::iterator begins, typename std::vector<T>::iterator ends,std::function<T(T& val)> foo) {
	T res;   
	for (auto it = begins; it < ends; it++) {
		res=foo(*it);
	}
	return res;
}


int main() {
	std::vector<int> v1 = { 3,5,5,31,0,2,1,23 };
	std::vector<double> v2 = { 2.1,41.2,11.42,3.0,11.1 };
	std::vector<char> v3 = { 'd','a','w','q' };

	auto foo = [sum=0.0, counter=0](auto val) mutable{
		sum+=val;
		counter++;
		return sum / counter;
	};

	std::cout << "Mean1: " << foreach(v1.begin(), v1.end(), foo)<<'\n';
	std::cout << "Mean2: " << foreach(v2.begin(), v2.end(), foo)<<'\n';
	std::cout << "Mean3: " << foreach(v3.begin(), v3.end(), foo)<<'\n';
	return 0;
}