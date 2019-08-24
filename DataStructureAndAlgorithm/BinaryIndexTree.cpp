#include <iostream>
#include <array>

template<typename T,size_t size>
void updateBIT(std::array<T,size> &bit, size_t index, T value)
{
	index = index+1;

	while(index <= bit.size())
	{
		bit[index-1] += value;

		index += index & (-index);
	}
}


template<typename T, size_t size>
std::array<T,size> constructBIT(std::array<T, size> arr)
{
	std::array<T,size> bit{};

	for(size_t i=0;i<arr.size();i++)
	{
		updateBIT(bit, i, arr[i]);
	}
	return bit;
}

// Return sum of array[0..index]
// Return sum of array[0..index]
template<typename T, size_t size>
T getSum(std::array<T, size> bit, size_t index)
{
	T sum=0;
	index = index +1;
	while(index >0)
	{
		sum +=bit[index-1];
		index -= index & (-index);
	}
	return sum;
}

int main(int argc, char const *argv[])
{
	std::array<float,8> arr{2,3,4,5,6,7,8,9};
	std::array<float,8> bit = constructBIT(arr);
	std::cout<<getSum(bit,3);

	std::cin.get();
	return 0;
}