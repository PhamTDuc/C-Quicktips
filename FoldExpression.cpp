#include <iostream>
template<typename...Ts>
auto sum(Ts...args)
{
	typename std::common_type<Ts...>::type result{};
	(void)std::initializer_list<int>{(result+=args,0)...};
	return result;
}

template<typename...Ts>
auto avg(Ts...args)
{
	typename std::common_type<Ts...>::type result{};
	(void)std::initializer_list<int>{(result+=args,0)...};
	return result/sizeof...(args);
}


// Folding expression
// Folding expression
template<typename...Ts>
auto sum2(Ts...args)
{
	const int n=23;
	return (n+...+args);
}

template<typename...Ts>
auto avg2(Ts...args)
{
	return (args+...)/sizeof...(args);
}


int main(int argc, char const *argv[])
{
	std::cout<<"Sum of 12, 3.45, 6 is "<<sum(12,3.45,6)<<'\n';
	std::cout<<"Sum2 of 12, 3.45, 6 is "<<sum2(12,3.45,6)<<'\n';

	std::cout<<"Avg of 2, 3, 4 is "<<avg(2,3,4)<<'\n';
	std::cout<<"Avg2 of 2, 3, 4 is "<<avg2(2,3,4)<<'\n';


	std::cin.get();
	return 0;
}