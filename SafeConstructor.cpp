#include <iostream>
#include <memory>
#include <string>

class Foo
{
public:
	std::string str_m;
	Foo(const std::string &str):str_m(str)
	{
		std::cout<<"Foo created.\n";
	}

	~Foo()
	{
		std::cout<<"Foo delete.\n";
	}

	void print()
	{
		std::cout<<str_m;
	}
};

class Storage
{
private:
	std::unique_ptr<Foo> foo_m;
	std::unique_ptr<int[]> int_m;
public:
	Storage(std::unique_ptr<Foo> foo=nullptr,
		std::unique_ptr<int[]> storage=nullptr)
	{
		foo_m=std::move(foo);
		//foo_m.reset();
		int_m=std::move(storage);

	}

	std::unique_ptr<Foo>& get(){
		return foo_m;
	}
};

int main(int argc, char const *argv[])
{
	std::unique_ptr<Foo> foo=std::make_unique<Foo>("Hello hello\n");
	//std::unique_ptr<Bar> 
	Storage storage(std::move(foo));
	//storage.get()->print();
	std::cout<<storage.get().get()<<"\n";

	//Swap unique_ptr
	//Swap unique_ptr
	std::cout<<"Before\
 swapping:\n";
	auto bar=std::make_unique<Foo>("Ha ha ha ha\n");
	storage.get()->print();
	bar->print();
	std::cout<<storage.get().get()<<"\n";
	std::cout<<bar.get()<<"\n";

	std::cout<<"After swapping:\n";
	bar.swap(storage.get());

	storage.get()->print();
	bar->print();
	std::cout<<storage.get().get()<<"\n";
	std::cout<<bar.get()<<"\n";
	std::cin.get();
	return 0;
}