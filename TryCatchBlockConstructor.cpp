#include <iostream>

class Foo{
private:
	int x_m;
public:
	Foo(int x=1000)try:x_m(x)
	{
		// throw 1;
	}
	catch(...)
	{
		std::cout<<"Error happened.\n";
		//Implicit throw here 
		//Implicit throw here 
	}
	int get(){
		return x_m;
	}
	~Foo()try
	{

	}
	catch(...)
	{
		std::cout<<"Error happened in deconstructor\n.";
		//Implicit throw here
		//Implicit throw here
	}
};

int main(int argc, char const *argv[])
{

	Foo foo;
	std::cout<<foo.get();
	std::cin.get();
	return 0;
}