#include<iostream>
#include<string>
#include <utility>
#define _CRTDBG_MAP_ALLOC

class Gadget
{
public:
	virtual int GetPrice() = 0;
	virtual ~Gadget() {

	}
};

class MobilePhone : public Gadget
{
private:
	std::string _model;
	int _year;
public:
	MobilePhone() = default;
	MobilePhone(const std::string& model, int year) {
		_model = model;
		_year = year;
	}

	int GetPrice() {
		return _year * 0.5;
	}

};


class Laptop : public Gadget
{
private:
	std::string _model;
	int _ram_size;
	int _cpu_level;
public:
	Laptop() = default;
	Laptop(const std::string& model, int ram_size, int cpu_level) {
		_model = model;
		_ram_size = ram_size;
		_cpu_level = cpu_level;
	}

	int GetPrice() {
		return (_ram_size + _cpu_level) * 0.5;
	}
};


template <typename... Ts>
std::unique_ptr<Gadget> Factory(const std::string& name, Ts&&... params)
{
	if (name == "Mobile phone") {
		if constexpr (std::is_constructible_v<MobilePhone, Ts...>) {
			return 	std::unique_ptr<MobilePhone>(new MobilePhone(std::forward<Ts>(params)...));
		}
	}

	if (name == "Laptop") {
		if constexpr (std::is_constructible_v<Laptop, Ts...>) {
			return std::unique_ptr<Laptop>(new Laptop(std::forward<Ts>(params)...));
		}
	}

	return nullptr;
}

void Test() {
	auto gadget1 = Factory("Mobile phone", "Samsung", 2020);
	std::cout << gadget1->GetPrice() << ' ';

	auto gadget2 = Factory("Mobile phone", "IPhone", 2021);
	std::cout << gadget2->GetPrice() << ' ';



	auto gadget3 = Factory("Laptop", "Asus", 16000, 2400);
	std::cout << gadget3->GetPrice() << ' ';

}


int main()
{
	Test();
	_CrtDumpMemoryLeaks();

	return 0;
}