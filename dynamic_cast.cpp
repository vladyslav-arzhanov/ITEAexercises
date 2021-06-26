#include<iostream>

class Base
{
public:
	int* version_foo=nullptr;
	Base(){
		this->foo();
	}
	void foo() {
		version_foo=new int(0);
	}

	~Base() {
		if(version_foo!=nullptr)
		delete version_foo;
	}
};


class DerivedA : public Base
{
public:
	DerivedA() {
		DerivedA::foo();
	}
	void foo() {
		*(DerivedA::version_foo)=1;
	}
};

class DerivedB : public Base
{
public:
	DerivedB(){
		DerivedB::foo();
	}
	void foo() {
		*(DerivedB::version_foo)=2;
	}
};


void DetermineType(Base* base)
{
	int version_foo = *base->version_foo;
	if (version_foo==1)
	{
		std::cout <<"DerivedA type\n";
	}
	else
	{
		if (version_foo==2)
		{
			std::cout << "DerivedB type\n";
		}
		else {
				std::cout << "Base type\n";
		}
	}
}


int main()
{
	DetermineType(new DerivedA); //DerivedA type
	DetermineType(new Base); //Base type
	DetermineType(new DerivedB); //DerivedB type
}