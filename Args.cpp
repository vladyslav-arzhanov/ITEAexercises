#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//ofstream write;

//1 2 3 4 5 -> 1 2 3 4 5 
//template<typename T>
//void WriteToFile(string NameFile, T val) {
//	if (!write.is_open())
//	write.open(NameFile);
//	write << val<<" ";
//	write.close();
//}
//
//template<typename T,typename ...Args>
//void WriteToFile(string NameFile,T val,Args... args) {
//	if(!write.is_open())
//	write.open(NameFile);
//	write << val<<" ";
//	WriteToFile(NameFile, args...);
//}

//1 2 3 4 5 -> 5 4 3 2 1
//template<typename T>
//void WriteToFile(string NameFile, T val) {
//	if (write.is_open())write.close();
//	write.open(NameFile);
//	write << val << " ";
//}
//
//template<typename T, typename ...Args>
//void WriteToFile(string NameFile, T val, Args... args) {
//	WriteToFile(NameFile, args...);
//	write << val << " ";
//}

template<typename T>
ofstream WriteToFile(string NameFile, T val) {
	ofstream write;
	write.open(NameFile);
	write << val << " ";
	return write;
}

template<typename T, typename ...Args>
ofstream WriteToFile(string NameFile, T val, Args... args) {
	return WriteToFile(NameFile, args...) << val << " ";
}

int main()
{

	WriteToFile("test.txt",4, 56.2, 'f', "fsfsgsg", 5, 4334, "fdsdf");
	WriteToFile("test2.txt","gffgddfgfd");
	WriteToFile("test3.txt","fdfs",54,87.54534,"jytj");

	return 0;
}