#include <iostream>
#include <memory>
#include <stdexcept>

class Custom: public std::exception{
public:
	const char* what() const noexcept override{
		return "Custom exception happened.";
	}
};

class Foo{
public:
	Foo() try{
		throw 1;
	}
	catch(...)
	{
		throw;
	}
};

class Bar{
private:
	std::shared_ptr<Foo> bar=nullptr;
public:
	Bar():bar(new Foo[20]){}
};

void func(){
	throw Custom();
}

int main(int argc, char const *argv[])
{
	try
	{
		func();
	}
	catch(Custom &e)
	{
		std::cout<<"Error happened: "<<e.what()<<std::endl;
	}
	//Not be called
	catch(std::exception&)
	{
		std::cout<<"Exception is calling\n";
	}

	std::cout<<"Try to create Foo object\n";
	try{
		Foo();
	}
	catch(...)
	{
		std::cout<<"Exception happened\n";
	}
	std::cin.get();
	return 0;
}