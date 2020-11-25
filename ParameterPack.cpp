#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>


using namespace std::string_literals;

template<typename T>
std::string to_string_impl(const T &t){
	std::stringstream s;
	s<<t;
	return s.str();
}


template<typename ...Ts>
std::vector<std::string> to_string(const Ts&...args)
{
	auto generic_lamdas=[](const auto &p){std::stringstream s;s<<p;return s.str();};
	return {generic_lamdas(args)...}; // Pack Expansion
}

template<typename ...Ts>
std::tuple<Ts...> makeTuple(const Ts ... args){
	return std::make_tuple(args...);
}

int main(int argc, char const *argv[])
{
	std::cout<<to_string_impl("Hello the world");
	auto vec=to_string("Hello",123,456.466,"The world");
	for(const auto e:vec){
		std::cout<<e; 
	}


	auto tuple=makeTuple("Hello",23.45,6.789);
	std::cout<<std::endl;
	std::cout<<std::get<0>(tuple)<<'|'<<std::get<1>(tuple)<<'|'<<std::get<2>(tuple);
	std::cin.get();
	return 0;
}
