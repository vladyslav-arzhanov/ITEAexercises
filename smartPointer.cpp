#include<iostream>
#define _CRTDBG_MAP_ALLOC


template<typename T>
class SmartPtr {
private:
	T* _data;
	unsigned int* _counter;
public:
	SmartPtr() {
		_data = nullptr;
		_counter = nullptr;
	}

	SmartPtr(T* data) {
		_data = data;
		_counter = new unsigned int;
		(*_counter) = 1;
	}

	~SmartPtr() {
		(*_counter)--;
		if ((*_counter) == 0 &&_data!=nullptr) {
			delete[]_data;
			delete _counter;
		}
	}

	SmartPtr(SmartPtr&& sp) {
		_data = sp._data;
		_counter = sp._counter;
		sp._data = sp._counter = nullptr;
	}

	SmartPtr(const SmartPtr& sp) {
		_data = sp._data;
		_counter = sp._counter;
		if(sp._data!=nullptr)
		(*_counter)++;
	}

	SmartPtr& operator=(SmartPtr&& sp) {
		this->~SmartPtr();
		_data = sp._data;
		_counter = sp._counter;
		sp._data = nullptr;
		return *this;
	}

	SmartPtr& operator=(const SmartPtr& sp) {
		this->~SmartPtr();
		_data = sp._data;
		_counter = sp._counter;
		if (sp._data != nullptr)
		(*_counter)++;
		return *this;
	}

	T& operator*()const {
		return this->_data;
	}

	T* operator->() const{
		return this->_data;
	}

};
