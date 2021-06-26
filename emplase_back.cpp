#include<iostream>
#include<fstream>
#include <utility>
#include<string>

#define _CRTDBG_MAP_ALLOC
using namespace std;

class Item1;
class Item2;

template<typename T>
struct Item {
	Item(T& val, Item* ptr = nullptr) {
		this->_val = val;
		this->_ptr = ptr;
	}

	Item(T&& p, Item* ptr = nullptr) {
		_val = move(p);
		this->_ptr = ptr;
	}
	T _val;
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

	template<typename T2>
	LinkedList(T2&& elem) {
		pushBack(forward<T2>(elem));
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


	// update method
	template<typename T1>
	void pushBack(T1&& item) {
		_sizeList++;
		if (_begin == nullptr) {
			_begin = new Item<T>(forward<T1>(item));
			_end = _begin;
		}
		else {
			Item<T>* newElement = new Item<T>(forward<T1>(item));
			_end->_ptr = newElement;
			_end = newElement;
		}
	}

	//new method 
	template<typename ...Args>
	void emplace_back(Args... args) {
		_sizeList++;
		if (_begin == nullptr) {
			_begin = new Item<T>(T(args...));
			_end = _begin;
		}
		else {
			Item<T>* newElement = new Item<T>(T(args...));
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

class Item1 {
private:
	int _a;
	char _b;
	double _c;
public:
	Item1() = default;
	Item1(int a, char b, double c) {
		_a = a;
		_b = b;
		_c = c;
	}

	/*Item1& operator=(Item1&& i)noexcept {
		???
		return *this;
	}*/

};


class Item2 {
private:
	string _a;
	char _b;
	int _c;
	int _d;
public:
	Item2() = default;
	Item2(string a, char b, int c, int d) {
		_a = a;
		_b = b;
		_c = c;
		_d = d;
	}

	//Item2& operator=(Item2&& i) {
	//	 ???
	//	return *this;
	//}
};

void Test() {
	LinkedList<string> list;
	string s1("fddfs");
	string s2("fddfsjk");
	list.pushBack(s1);
	list.pushBack(move(s2));

	LinkedList<int> li;
	int d=4;
	li.pushBack(d);
	li.pushBack(32);

	Item1 i(2, 'v', 4.32);
	LinkedList<Item1> ll(move(i));
	ll.emplace_back(3, '~', 3.14);

	LinkedList<Item2> ll2;
	ll2.emplace_back("gfdsaf", 'v', 3, 5);
}


int main() {
	Test();


	_CrtDumpMemoryLeaks();

	return 0;
}