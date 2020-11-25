#include <iostream>

class Binding
{
public:
template<typename Function, typename ...Ts>
    double invoker(Function func, Ts&&...args)
    {
        return func(args...);
    }
};

class Sum
{
public:
    double operator()(double a, double b)
    {
        return a+b;
    }
};

int main()
{
    Sum sum;
    Binding bind;
    std::cout << bind.invoker([](double a, double b){return a*b;}, 20, 40);
    return 0;
}
