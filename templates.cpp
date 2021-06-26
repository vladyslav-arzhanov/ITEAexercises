#include<iostream>
#include<string>

using namespace std;

template <typename T>
class  Data
{
	T _data;

public:
	Data(T str):_data(std::move(str))
	{
	}

	template <typename T1,typename T2>
	friend T1& operator<< (T1& stream, const Data<T2>& test);
};


template <typename T1,typename T2>
T1& operator<<(T1& stream, const Data<T2>& test) {
	stream = stream + test._data;
	return stream;
}

template<>   
string& operator<< <string,int>(string& stream, const Data<int>& test) {
	stream += to_string(test._data);
	return stream;
}

template<> 
int& operator<< <int, string>(int& stream, const Data<string>& test) {
	stream += test._data.size();
	return stream;
}

int main()
{
	const Data<std::string> test1("2AAABB");
	const Data<int> test2(300);


	std::string str;
	str << test1;
	str << test2;


	std::cout << "Str: " << str << std::endl;   //Str: 2AAABB300


	int val(0);
	val << test1; //+strlen(data)
	val << test2;


	std::cout << "Val: " << val;  //Val: 306
	return 0;
}