#include<iostream>
#include<cstdlib>

const int RET_ERR_THE_LIST_IS_EMPTY = 0;
const int RET_ERR_POS_MORE_THAN_LENGHT_LIST = -1;

struct Item {
	Item(int val, Item* ptr = nullptr) {
		this->_val = val;
		this->_ptr = ptr;
	}
	int _val;
	Item* _ptr;
};


class Iterator
{
public:

	Iterator(Item* i) {
		_currentItem = i;
	}

	Item* operator ++() {
		if (_currentItem != nullptr)
			_currentItem = _currentItem->_ptr;
		return _currentItem;
	}

	Item* operator ++(int) {
		if (_currentItem != nullptr)
			_currentItem = _currentItem->_ptr;
		return _currentItem;
	}

	bool operator!=(const Iterator& it)const {
		return this->_currentItem != it._currentItem;
	}

	int operator*()const {
		return _currentItem->_val;
	}


private:
	Item* _currentItem;
};


class LinkedList {
private:
	Item* _begin;
	Item* _end;
	unsigned int _sizeList = 0;

	void del() {
		if (_begin != nullptr) {
			Item* beginPtr = _begin;
			while (beginPtr != nullptr) {
				Item* copyBeginPtr = beginPtr->_ptr;
				delete beginPtr;
				beginPtr = copyBeginPtr;
			}
		}
	}

public:

	LinkedList(unsigned int size) {
		if (size == 0) {
			_begin = nullptr;
		}
		else {
			_begin = new Item(rand() % 100);
			_end = _begin;
			for (int i = 0; i < size - 1; i++) {
				pushBack(rand() % 100);
			}
			_sizeList = size;
		}
	}

	LinkedList(const LinkedList& ll) {
		_begin = new Item(ll._begin->_val);
		_end = _begin;

		Item* copyBeginll = ll._begin->_ptr;
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

	void pushBack(int val) {
		_sizeList++;
		if (_begin == nullptr) {
			_begin = new Item(val);
			_end = _begin;
		}
		else {
			Item* newElement = new Item(val);
			_end->_ptr = newElement;
			_end = newElement;
		}
	}


	void pushFront(int val) {
		Item* newElement = new Item(val);
		newElement->_ptr = _begin;
		_begin = newElement;
		_sizeList++;
	}

	bool insert(int pos, int a) {
		int i = 1;
		Item* copyBegin = _begin;
		while (copyBegin != nullptr) {
			if (i++ == pos) {
				Item* element = new Item(a);
				element->_ptr = copyBegin->_ptr;
				copyBegin->_ptr = element;
				return true;
			}
			copyBegin = copyBegin->_ptr;
		}
		return false;
	}


	void printList() const {
		Item* beginPtr = _begin;
		while (beginPtr != nullptr) {
			std::cout << beginPtr->_val << " ";
			beginPtr = beginPtr->_ptr;
		}
		std::cout << std::endl;
	}


	LinkedList& operator=(LinkedList& ll) {
		del();
		_begin = new Item(ll._begin->_val);
		_end = _begin;

		Item* copyBeginll = ll._begin->_ptr;
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

	int operator[](int num) const {
		if (_begin == nullptr)return RET_ERR_THE_LIST_IS_EMPTY;
		int i = 0;
		Item* copyBeginItem = _begin;
		while (copyBeginItem != nullptr) {
			if (i == num) {
				return copyBeginItem->_val;
			}
			copyBeginItem = copyBeginItem->_ptr;
			i++;
		}
		return RET_ERR_POS_MORE_THAN_LENGHT_LIST;
	}

	unsigned int getSize()const {
		return _sizeList;
	}

	Iterator getBegin()const {
		return Iterator(_begin);
	}

	Iterator getEnd() const {
		return Iterator(nullptr);
	}
};


int main() {
	LinkedList ll1(6);

	ll1.pushBack(4);
	ll1.pushFront(32);

	ll1.printList();

	std::cout << std::endl;

	for (auto it = ll1.getBegin(); it != ll1.getEnd(); ++it) {
		std::cout << *it << " ";
	}

	return 0;
}