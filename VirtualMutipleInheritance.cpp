#include <iostream>

class Base1{
public:

	virtual void func(){
		std::cout<<"Base1 is calling.\n";
	}
};

class Base2{
public:
	virtual void func(){
		std::cout<<"Base2 is calling.\n";
	}
};

class Child:public Base1,Base2{
public:
	void func() override{
		std::cout<<"Child is callilng\n";
	}

};

int main(int argc, char const *argv[])
{
	Child child;
	child.func();

	std::cin.get();
	return 0;
}