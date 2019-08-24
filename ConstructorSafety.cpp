#include <iostream>
#include <memory>


class Storage
{
public:
	std::unique_ptr<int[]> m_int=nullptr;
	std::unique_ptr<float[]> m_float=nullptr;
private:
	Storage(std::unique_ptr<int[]> storage_int=nullptr, std::unique_ptr<float[]> storage_float=nullptr)
	{
		m_int=std::move(storage_int);
		m_float=std::move(storage_float);

	}
};

int main(int argc, char const *argv[])
{
	
	volatile int x=10;
	std::unique_ptr<int[]> array1=std::make_unique<int[]>(6);
	std::unique_ptr<float[]> array2=std::make_unique<float[]>(x);
	// array1[0]=1;
	// array1[1]=1;
	// array1[2]=1;
	// array1[3]=1;

	std::shared_ptr<std::string> s1=std::make_shared<std::string>("Hello");
	std::shared_ptr<std::string> s2=s1;
	std::cout<<s1.use_count();
	s1.reset();
	std::cout<<s2.use_count();
	std::cin.get();
	return 0;
}