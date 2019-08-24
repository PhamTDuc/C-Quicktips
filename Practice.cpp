#include <iostream>
#include <cassert>
#include <memory>

class Foo
{
public:
	int x_m;
	Foo(int x=0){
		x_m=x;
		std::cout<<"Foo created.\n";
	}

	Foo(const Foo &foo) = delete;
	Foo(const Foo &&foo){
		this->x_m=foo.x_m;
		std::cout<<"Move sematic happened.\n";
	}
	
	Foo& operator=(const Foo &foo)=delete;
	Foo& operator=(const Foo &&foo){
		this->x_m=foo.x_m;
		std::cout<<"Move assignement.\n";
		return *this;
	}
	friend std::ostream& operator<<(std::ostream &out, const Foo &foo)
	{
		out<<"Foo representation.\n";
		return out;
	}

	~Foo(){
		std::cout<<"Foo destroyed.\n";
	}
};

class Storage
{
private:
	size_t size_m;
	std::unique_ptr<Foo[]> foos_m;
public:
	Storage(size_t size=0):size_m(size),foos_m(std::make_unique<Foo[]>(size))
	{}

	Foo& operator[](size_t index)
	{	
		assert(0 <= index && index < size_m && "Out of range");
		return foos_m[index];}

	std::unique_ptr<Foo[]>& get(){
		return foos_m;
	}
};
int main(int argc, char const *argv[])
{
	Foo foo(50);
	Storage storage(5);
	storage[0]=Foo(30);
	storage[1]=Foo(59);
	std::cout<<&storage[0]<<"\n";
	std::cout<<&storage.get()<<"\n";


	std::shared_ptr<int> shared=std::make_shared<int>(100);
	auto shared2=shared;
	shared.reset();
	std::cout<<shared2.use_count()<<"\n";
	std::weak_ptr<int> weak=shared2;
	std::cout<<shared2.use_count()<<"\n";
	std::shared_ptr<int> shared3=weak.lock();
	std::cout<<weak.use_count()<<"\n";
	weak.reset();
	std::cout<<weak.use_count()<<"\n";
	std::cin.get();
	return 0;
}