#include<cstdlib>
#include<iostream>
#include<chrono>
#include <vector>

using namespace std;

class String {
private:
	char* _str;
	unsigned int _lenght;

public:
	String() {
		_str = nullptr;
		_lenght = 0;
	}

	String(const char* ch) {
		_lenght = strlen(ch);
		_str = new char[_lenght + 1];

		strcpy_s(_str, _lenght + 1, ch);
	}

	String(const String& st) {
		_lenght = st._lenght;

		_str = new char[_lenght + 1];
		strcpy_s(_str, _lenght + 1, st._str);
	}

	String(String&& st)noexcept {
		_lenght = st._lenght;
		_str = st._str;
		st._str = nullptr;
	}

	String& operator=(const String& st) {
		if (_str != nullptr)
			this->~String();
		_lenght = st._lenght;

		_str = new char[_lenght + 1];
		strcpy_s(_str, _lenght + 1, st._str);
		return *this;
	}

	String& operator=(String&& st) noexcept {
		if (_str != nullptr)
			this->~String();
		_lenght = st._lenght;

		_str = st._str;
		st._str = nullptr;

		return *this;
	}

	String operator+(const String& st) {
		int sumLenght = st._lenght + _lenght;

		char* sumStr = new char[sumLenght + 1];

		strcpy_s(sumStr, _lenght + 1, _str);
		strcat_s(sumStr, sumLenght + 1, st._str);
		String retStr(sumStr);
		delete[]sumStr;
		return retStr;
	}

	~String() {
		if (_str != nullptr)
			delete[]_str;
	}
};

int main() {
	vector<String> strColect;
	auto start0 = std::chrono::high_resolution_clock::now();
	//..Move assignment test with noexcept -- 8979000
	for (int i = 0; i < 10000; i++) {
		strColect.push_back(String("abc"));
	}
	  
	auto end0 = std::chrono::high_resolution_clock::now();
	std::cout << "Move assignment test (with noexcept): " << (end0 - start0).count() << std::endl;

	//auto start1 = std::chrono::high_resolution_clock::now();
	////..Copy assignment test -- 13420900
	//for (int i = 0; i < 10000; i++) {
	//	String str1("abc");
	//	strColect.push_back(str1);
	//}
	//auto end1 = std::chrono::high_resolution_clock::now();
	//std::cout << "Copy assignment test: " << (end1 - start1).count() << std::endl;




	//auto start2 = std::chrono::high_resolution_clock::now();
	////..Move assignemnt test No noexcept--10698500
	//for (int i = 0; i < 10000; i++) {
	//	strColect.push_back(String("abc"));
	//}	
	//auto end2 = std::chrono::high_resolution_clock::now();
	//std::cout << "Move assignment test (No noexcept): " << (end2 - start2).count() << std::endl;

	return 0;
}

//..Move assignment test with noexcept -- 8979000
//..Copy assignment test --		          13420900
//..Move assignemnt test No noexcept--	  10698500
