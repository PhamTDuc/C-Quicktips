#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>

class Foo{
public:
	Foo(){
		std::cout<<"Foo created\n";
	}
	Foo(const Foo &&foo){
		std::cout<<"Move sematic\n";
	}

	friend std::ostream& operator<<(std::ostream &out, const Foo &foo){
		out<<"Foo instance\n";
		return out;
	} 
	~Foo(){
		std::cout<<"Foo destroyed\n";
	}
};

void func(std::unique_ptr<Foo> foo){
	//if(std::shared_ptr<Foo> foo_shared=foo.lock())
	//{}
}

void func2(const std::string &y){
	std::cout<<"Print in func2: "<<y<<std::endl;
}
int main(int argc, char const *argv[])
{	
	auto ptr1=std::make_unique<Foo>();
	std::cout<<ptr1.get()<<std::endl;
	//std::cout<<ptr1<<std::endl; Can't happened

	func(std::move(ptr1));
	std::cout<<ptr1.get(); //Will print 0
	if(ptr1.get()){
		std::cout<<"Hello";
	}
	//std::cout<<ptr1; Can't happened

	//std::vector<Foo> v;

	

	std::cin.get();
	return 0;
}