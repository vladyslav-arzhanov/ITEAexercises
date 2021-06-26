#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
#include<functional>
#include<thread>


struct Subscriber {
	Subscriber(const std::string& name, const std::string& surname, const unsigned int phone) {
		_name = name;
		_surname = surname;
		_phone = phone;

	}


	std::string _name;
	std::string _surname;
	unsigned int _phone;
};

template<typename T>
class Task {
private:
	T _res;
	std::thread _thr;
public:
	Task(std::function<void(std::function<bool(Subscriber)>, std::vector<Subscriber>&)> fooSearch, std::function<bool(Subscriber)> fooMode) {
		_thr = std::thread(fooSearch, fooMode, std::ref(_res));
	}

	T GetResult() {
		_thr.join();
		return _res;
	}

	Task(Task<T>&& t) : _res(t._res) {

	}

	~Task() {
		_thr.join();
	}
};

std::ostream& operator<< (std::ostream& os, std::vector<Subscriber> vec) {
	std::for_each(vec.begin(), vec.end(), [&](auto&& obj) {
		std::cout << obj._name << ' ' << obj._surname << ": " << obj._phone << '\n'; });
	return os;
}


int main() {

	std::vector<Subscriber> data;

	auto Search = [&](auto foo, std::vector<Subscriber>& res)noexcept {
		std::copy_if(data.begin(), data.end(), std::back_inserter(res), foo);
	};

	auto SearchByPhone = [&](auto&& phone) noexcept {
		return Task<std::vector<Subscriber>>(Search, [&](auto&& obj) {return obj._phone == phone; });
	};

	auto SearchByName = [&](auto&& name)noexcept {
		return Task<std::vector<Subscriber>>(Search, ([&](auto&& obj) {return obj._name == name; }));
	};

	auto SearchBySurname = [&](auto&& surname)  noexcept {
		return Task<std::vector<Subscriber>>(Search, ([&](auto&& obj) {return obj._surname == surname; }));
	};

	auto SearchByNameAndPhone = [&](auto&& name, auto&& phone) noexcept {
		return Task<std::vector<Subscriber>>(Search, ([&](auto&& obj) {return (obj._name == name && obj._phone == phone); }));
	};

	auto SearchBySurameAndPhone = [&](auto&& surname, auto&& phone) noexcept {
		return Task<std::vector<Subscriber>>(Search, ([&](auto&& obj) {return (obj._surname == surname && obj._phone == phone); }));
	};

	data.emplace_back("Oleh", "Tulchin", 674914030);
	data.emplace_back("Mia", "Biden", 982265227);
	data.emplace_back("John", "Tete", 11154846);
	data.emplace_back("Sergii", "13", 123454);
	data.emplace_back("Misha", "T", 3523);
	data.emplace_back("Rwq", "yrt", 8768);



	Task<std::vector<Subscriber>> task1 = SearchByName("Sergii");
	Task<std::vector<Subscriber>> task2 = SearchByPhone(982265227);
	Task<std::vector<Subscriber>> task3 = SearchByNameAndPhone("Oleh", 674914030);
	Task<std::vector<Subscriber>> task4 = SearchBySurameAndPhone("Tete", 11154846);
	Task<std::vector<Subscriber>> task5 = SearchBySurname("T");

	std::cout << task1.GetResult();
	std::cout << task2.GetResult();
	std::cout << task3.GetResult();
	std::cout << task4.GetResult();
	std::cout << task5.GetResult();

	return 0;
}

