#include <string>
#include <iostream>
#include <variant>
#include <vector>


struct MyVisitor
{
   void operator()(int& _in){_in += _in}
   void operator()(double& _in){_in += _in;}
   void operator()(std::string& _in){_in += _in;}
};

struct PrintVisitor
{
   template <class T>
   void operator()(T&& _in){std::cout << _in;}
};

template<typename ...T>
struct VariantContainer{
    using variant_types = std::variant<T...>;
    std::vector<variant_types> objects;

    template<typename V>
    void visit(V&& visitor)
    {
        for(auto &obj:objects)
        {
            std::visit(visitor,obj);
        }
    }

    template<typename V>
    void getVisit(V&& visitor,int index){
        std::visit(visitor,objects[index]);
    }
};

int main(int argc, char const *argv[])
{
     std::variant<int, double, std::string> myVariant;
     myVariant = 1;

    auto lambda=[](auto&& _in){std::cout<<_in;};

    std::cout<<std::visit(MyVisitor{},myVariant);
    // std::visit(lambda,myVariant);


    VariantContainer<int, double, std::string> variantCollection;
    variantCollection.objects.emplace_back(1);
    variantCollection.objects.emplace_back(2.2);
    variantCollection.objects.emplace_back("foo");

     // print them
    variantCollection.visit(lambda);
    std::cout << std::endl;

     // double them
    variantCollection.visit(MyVisitor{});

    // print again
    variantCollection.visit(lambda);
    std::cout<<std::endl;

    std::cin.get();
    return 0;
}