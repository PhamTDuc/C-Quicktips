#include <iostream>
#include <vector>
#include <initializer_list>
#include <typeinfo>


template<typename T>
class S{
public:
	std::vector<T> v;
	S(std::initializer_list<T> l):v(l){}
	void append(std::initializer_list<T> l)
	{
		v.insert(v.end(),l.begin(),l.end());
	}
};
struct vec2{
	float x;
	float y;
};

int main(int argc, char const *argv[])
{
	auto l={2,3,4,5};

	//if having initializer list in constructor, it will be call before other constructor
	//if having initializer list in constructor, it will be call before other constructor
	vec2 vec{1,2.34};
	S<int> s{2,3,4};
	std::cout<<"The list bound to auto has size "<<l.size()<<'\n';
	for(auto i:l){
		std::cout<<i<<typeid(vec).name()<<"; ";
	}


	std::cin.get();
	return 0;
}