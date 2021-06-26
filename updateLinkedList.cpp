#include<cstdlib>
#include<iostream>
#define _CRTDBG_MAP_ALLOC

using namespace std;

const int RET_ERR_THE_LIST_IS_EMPTY = 0;
const int RET_ERR_POS_MORE_THAN_LENGHT_LIST = -1;

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
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	template<typename T>friend class LinkedList;
	template<typename T>friend class Iterator;
	template<typename T>friend struct Item;
};


std::ostream& operator<<(std::ostream& os, const String& str) {
	os << str._str;
	return os;
}

template<typename T>
struct Item {
	Item(T val, Item* ptr = nullptr) {
		this->_val = val;
		this->_ptr = ptr;
	}

	Item(T* p, Item* ptr = nullptr) {
		this->_p = p;
		_val = *_p;
		_p = nullptr;
		this->_ptr = ptr;
	}
	T _val;
	T* _p;
	Item* _ptr;
};

template<typename T>
class Iterator
{
public:

	Iterator(Item<T>* i) {
		_currentItem = i;
	}

	Item<T>* operator ++() {
		if (_currentItem != nullptr)
			_currentItem = _currentItem->_ptr;
		return _currentItem;
	}

	Item<T>* operator ++(int) {
		if (_currentItem == nullptr)return _currentItem;
		Item<T>* retItem = _currentItem;
		_currentItem = _currentItem->_ptr;
		return retItem;
	}

	bool operator!=(const Iterator& it)const {
		return this->_currentItem != it._currentItem;
	}

	T operator*()const {
		return _currentItem->_val;
	}


private:
	Item<T>* _currentItem;
};

template<typename T>
class LinkedList {
private:
	Item<T>* _begin;
	Item<T>* _end;
	unsigned int _sizeList = 0;

	void del() {
		if (_begin != nullptr) {
			Item<T>* beginPtr = _begin;
			while (beginPtr != nullptr) {
				Item<T>* copyBeginPtr = beginPtr->_ptr;
				delete beginPtr;
				beginPtr = copyBeginPtr;
			}
		}
	}

public:

	LinkedList() {
		_begin = _end = nullptr;
	}

	LinkedList(T elem) {
		pushBack(elem);
	}

	LinkedList(const LinkedList& ll) {
		_begin = new Item<T>(ll._begin->_val);
		_end = _begin;

		Item<T>* copyBeginll = ll._begin->_ptr;
		while (copyBeginll != nullptr) {
			pushBack(copyBeginll->_val);
			copyBeginll = copyBeginll->_ptr;
		}
	}

	LinkedList(LinkedList&& ll) noexcept {
		_begin = ll._begin;
		_end = ll._end;

		ll._begin = nullptr;
	}


	~LinkedList() {
		del();
	}

	void pushBack(T& val) {
		_sizeList++;
		if (_begin == nullptr) {
			_begin = new Item<T>(val);
			_end = _begin;
		}
		else {
			Item<T>* newElement = new Item<T>(val);
			_end->_ptr = newElement;
			_end = newElement;
		}
	}

	void pushBack(T&& item) {
		_sizeList++;
		if (_begin == nullptr) {
			_begin = new Item<T>(&item);
			_end = _begin;
		}
		else {
			Item<T>* newElement = new Item<T>(&item);
			_end->_ptr = newElement;
			_end = newElement;

		}
	}


	void pushFront(T val) {
		Item<T>* newElement = new Item<T>(val);
		newElement->_ptr = _begin;
		_begin = newElement;
		_sizeList++;
	}

	bool insert(int pos, T a) {
		int i = 1;
		Item<T>* copyBegin = _begin;
		while (copyBegin != nullptr) {
			if (i++ == pos) {
				Item<T>* element = new Item(a);
				element->_ptr = copyBegin->_ptr;
				copyBegin->_ptr = element;
				return true;
			}
			copyBegin = copyBegin->_ptr;
		}
		return false;
	}


	void printList() const {
		Item<T>* beginPtr = _begin;
		while (beginPtr != nullptr) {
			std::cout << beginPtr->_val << " ";
			beginPtr = beginPtr->_ptr;
		}
		std::cout << std::endl;
	}


	LinkedList& operator=(LinkedList& ll) {
		del();
		_begin = new Item<T>(ll._begin->_val);
		_end = _begin;

		Item<T>* copyBeginll = ll._begin->_ptr;
		while (copyBeginll != nullptr) {
			pushBack(copyBeginll->_val);
			copyBeginll = copyBeginll->_ptr;
		}
		return *this;
	}


	LinkedList& operator=(LinkedList&& ll) noexcept {
		del();
		_begin = ll._begin;
		_end = ll._end;

		ll._begin = nullptr;
		ll._end = nullptr;
		return *this;
	}


	unsigned int getSize()const {
		return _sizeList;
	}

	Iterator<T> begin()const {
		return Iterator<T>(_begin);
	}

	Iterator<T> end() const {
		return Iterator<T>(nullptr);
	}
};


void Test(){
	LinkedList<String> list;
	list.pushBack(String("rtyui"));

	list.pushBack(String("abc") + String("def"));


	for (auto el : list)
	{
		std::cout << el << " ";
	}

}

int main() {
	Test();

	LinkedList ll(23);
	ll.pushBack(3);

	_CrtDumpMemoryLeaks();

	return 0;
}
