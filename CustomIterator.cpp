#include <iostream>
#include <memory>
#include <iterator>


template<typename T>
class CustomVector{
private:
	size_t capacity_m;
	std::unique_ptr<T[]> vector_m;

public:
	class CustomIterator{
	private:
		T* current;
	public:
		CustomIterator(T* ptr):current(ptr){}
		CustomIterator operator++()
		{
			++current;
			return *this;
		}
		CustomIterator operator++(int no_use)
		{
			++current;
			return *this;
		}

		bool operator==(const CustomIterator &iter)
		{
			return current==iter.current;
		}

		CustomIterator operator=(const CustomIterator &iter)
		{
			this->current=iter.current;
			return *this;
		}

		bool operator!=(const CustomIterator &iter)
		{
			return current!=iter.current;
		}

		T& operator*()
		{
			return *current;
		}
	};

	CustomVector(int capacity=4):capacity_m(capacity),vector_m(std::make_unique<T[]>(capacity_m))
	{}

	CustomVector(std::initializer_list<T> li):capacity_m(li.size()),vector_m(std::make_unique<T[]>(capacity_m))
	{
		std::cout<<"\nCalling it\n";
		memcpy(&vector_m[0],li.begin(),sizeof(T)*capacity_m);
	}

	T& operator[](size_t index)
	{
		return vector_m[index];
	}

	const T& operator[](size_t index) const
	{
		return vector_m[index];
	}

	size_t capacity() const
	{
		return capacity_m;
	}

	void reserve(size_t capacity)
	{	
		if(capacity>capacity_m)
		{
			auto temp = std::make_unique<T[]>(capacity);
			vector_m.swap(temp);
		}
	}

	CustomIterator begin() const
	{
		return CustomIterator(&vector_m[0]);
	}
	CustomIterator end() const
	{
		return CustomIterator(&vector_m[0]+capacity_m);
	}
};



int main(int argc, char const *argv[])
{
	CustomVector<float> vec(2);
	vec[0]=2.34;
	vec[1]=5.67;

	std::cout<<vec[0];
	vec.reserve(5);
	vec[3]=23.6;
	std::cout<<'\n'<<vec[1];
	std::cout<<'\n'<<vec[3];

	const CustomVector<float> vec2={2,3.02,4,5.5,6.78,9.1};
	std::cout<<'\n'<<vec2[3];

	auto unique=std::make_unique<int[]>(4);
	unique[0]=1;
	unique[1]=2;
	unique[2]=3;

	int* ptr=unique.get(); // unique still is the owner of ptr
	std::cout<<"\nUnique: "<<ptr[1];

	//ptr_release take care of delete the object at the same point
	//ptr_release take care of delete the object at the same point
	int* ptr_release=unique.release(); //ptr_release take care of delete the object at the same point
	std::cout<<"\nptr_release: "<<ptr_release[2];
	delete[] ptr_release; //ptr_release take care of delete the object at the same point

	std::cout<<std::endl;
	for(auto elm=vec2.begin();elm!=vec2.end();elm++)
	{
		std::cout<<*elm<<';';
	}

	std::cout<<"\nUsing Range_Based For loop:\n";
	for(float elm:vec2)
	{
		std::cout<<elm<<";";
	}
	std::cin.get();
	return 0;
}