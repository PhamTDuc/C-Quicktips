#include <iostream>
#include <cassert>

//static_assert(1>10,"Compile time Error.");

int main(int argc, char const *argv[])
{
	assert(2<-2 && "Runtime Error");
	return 0;
}