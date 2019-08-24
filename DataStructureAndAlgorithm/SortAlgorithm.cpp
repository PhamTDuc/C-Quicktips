#include <iostream>
#include <array>
template<typename T,size_t size>
void print(std::array<T,size> &arr){
	std::cout<<"Array[ ";
	for(const auto elm:arr){
		std::cout<<elm<<" ; ";
	}
	std::cout<<"]\n";
}

template<typename T>
void swap(T &x, T&y){
	T temp = std::move(x);
	x = std::move(y);
	y = std::move(temp);
}

size_t count=0;
template<typename T, size_t size>
void quickSort(std::array<T,size> &arr,long long int first,long long int last){
	long long int pivot_pos = last;
	if(first>=last)
		return;

	for(long long int i = first; i < pivot_pos; i++)
	{
		//Estimate BigO Notation only
		//Estimate BigO Notation only
		::count++;
		if(arr[last]<arr[i])
		{	
			swap(arr[i],arr[pivot_pos-1]);
			pivot_pos--;
			i--;
		}
	}
	swap(arr[last],arr[pivot_pos]);
	quickSort(arr,first,pivot_pos-1);
	quickSort(arr,pivot_pos+1,last);
	
}


int main(int argc, char const *argv[])
{
	std::array<int,17> arr{-20,-30,10,-10,-20,25,40,-50,60,10,20,-30,40,50,100,-45,60};
	print(arr);

	quickSort(arr,0,16);
	print(arr);
	std::cout<<count;
	std::cin.get();
	return 0;
}