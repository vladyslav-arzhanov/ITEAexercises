#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
#include<functional>
#include<thread>

class PhoneBook {
public:
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
private:
	std::vector<Subscriber> _data;

	template<typename Foo>
	auto Search(Foo&& foo) noexcept{
		auto search = [&]() {
			std::vector<Subscriber> retVec;
			std::copy_if(_data.begin(), _data.end(),std::back_inserter(retVec), foo);
			return retVec;
		};
		return search();
	}

public:
	friend std::ostream& operator<< (std::ostream& os, std::vector<Subscriber>& vec);
	
	PhoneBook() = default;

	PhoneBook(const std::string& name, const std::string& surname, const unsigned int phone) {
		_data.emplace_back(name, surname, phone);
	}

	void AddNewUsr(const std::string& name, const std::string& surname, const unsigned int phone) {
		_data.emplace_back(name, surname, phone);
	}

	void DelLastUsr(const std::string& name, const std::string& surname, const unsigned int phone) {
		_data.pop_back();
	}

	auto SearchByPhone(unsigned int phone)   noexcept{
		return Search([&](auto&& obj) {return obj._phone == phone; });
	}

	auto SearchByName(const std::string& name)  noexcept {
		return Search([&](auto&& obj) {return obj._name == name; });
	}

	auto SearchBySurname(const std::string& surname)  noexcept {
		return Search([&](auto&& obj) {return obj._surname == surname; });
	}

	auto SearchByNameAndPhone(const std::string& name, unsigned int phone) noexcept {
		return Search([&](auto&& obj) {return (obj._name == name && obj._phone==phone); });
	}

	auto SearchBySurameAndPhone(const std::string& surname, unsigned int phone) noexcept {
		return Search([&](auto&& obj) {return (obj._surname == surname && obj._phone == phone); });
	}
};

std::ostream& operator<< (std::ostream& os, std::vector<PhoneBook::Subscriber,std::allocator<PhoneBook::Subscriber>> vec) {
	std::for_each(vec.begin(), vec.end(), [&](auto&& obj) {
		std::cout << obj._name << ' ' << obj._surname << ": " << obj._phone << '\n'; });
	return os;
}


int main() {
	
		PhoneBook pb("Oleh", "Tulchin", 674914030);
		pb.AddNewUsr("Mia", "Biden", 982265227);
		pb.AddNewUsr("John", "Tete", 11154846);
		pb.AddNewUsr("Sergii", "13", 123454);
		
		auto = pb.SearchByName;

		std::cout << pb.SearchByName("Sergii");
		std::cout<<pb.SearchByPhone(982265227);
		std::cout << pb.SearchByNameAndPhone("Oleh", 674914030);

	return 0;
}
