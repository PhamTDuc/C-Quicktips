#include <iostream>
#include <vector>


int main(int argc, char const *argv[])
{
	std::vector<int> v1{1, 2, 3, 4};
	std::vector<int> v2{5, 6, 7};
	std::vector<int>::iterator it;

	std::cout<<"Vec1: ";
	for(it=v1.begin();it!=v1.end();it++)
	{
		
		std::cout<<*it<<";";
	}

	// std::cout<<"\nCopy not using inserter\n";
	// std::copy(v2.begin(),v2.end(), v1.begin()+1);
	// std::cout<<"Vec1: ";
	// for(it=v1.begin();it!=v1.end();it++)
	// {
		
	// 	std::cout<<*it<<";";
	// }


	std::cout<<"\nCopy using inserter\n";
	std::copy(v2.begin(),v2.end(), std::inserter(v1,v1.begin()+1));
	std::cout<<"Vec1: ";
	for(const auto elm:v1)
	{
		
		std::cout<<elm<<";";
	}
	std::cin.get();
	return 0;
}