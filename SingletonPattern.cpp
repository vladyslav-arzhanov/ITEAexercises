#include<iostream>
#include<fstream>

class ITextOut {
protected:
	std::ofstream _out;
public:
	virtual void open(std::string fileName)=0;
	virtual std::ofstream& operator<<(std::string log) = 0;
};

class FileOut:public ITextOut
{
public:
	void open(std::string fileName) {
		_out.open(fileName);
	}

	std::ofstream& operator<<(std::string log) {
		_out << log << '\n';
		return _out;
	}
};


class TestOut :public ITextOut {
private:
	static std::string* _lastLine ;
	static std::string* _fileName;
public:
	void open(std::string fileName) {
		if ((_fileName != nullptr)&&(fileName!=*_fileName))
			delete _fileName;
		_fileName = new std::string(fileName);
	}

	std::ofstream& operator<<(std::string log) {
		if (_lastLine != nullptr)
			delete _lastLine;
		_lastLine=new std::string(log);
		return _out;
	}

	static std::string& GetLastLine() {
		return *_lastLine;
	}

	static std::string& GetFileName() {
		return *_lastLine;
	}

	static void Destroy() {
		if (_lastLine != nullptr)
			delete _lastLine;
		if (_fileName != nullptr)
			delete _fileName;
	}


};


 std::string* TestOut::_lastLine=nullptr;
 std::string* TestOut::_fileName=nullptr;


template<typename T>
class LogManager {
private:
	ITextOut* _out;
	static LogManager* sp;

	LogManager(std::string fileName) {
		if(_out==nullptr)
		_out = new T;
		_out->open(fileName);
	}

public:	
	LogManager() = delete;
	LogManager(LogManager& sp) = delete;
	LogManager& operator=(LogManager& sp) = delete;

	static LogManager* GetInstance() {
		if (sp == nullptr)
			sp = new LogManager("file.txt");
		return sp;
	}

	void AddLog(std::string l) {
		*_out << l;
	}

};

template <typename T>
LogManager<T>* LogManager<T>::sp = nullptr;

bool Test1() {
	LogManager<FileOut>* sp1 = LogManager<FileOut>::GetInstance();
	LogManager<FileOut>* sp2 = LogManager<FileOut>::GetInstance();
	if (sp1 == sp2)return true;
	return false;
}

bool Test2() {
	LogManager<TestOut>* sp1 = LogManager<TestOut>::GetInstance();
std::string s = "some text";
sp1->AddLog(s);
if (TestOut::GetLastLine() != s) {
	TestOut::Destroy();
	return false;
}
else {
	TestOut::Destroy();
	return true;
}
}
