#include <iostream>
#include <array>
#include <variant>

#define variant_types std::variant<int,float>

class KinkBase{
protected:
	variant_types value_m;
public:
	KinkBase(){std::cout<<"Kink created.\n";}
	~KinkBase(){std::cout<<"Kink destroyed.\n";}
	variant_types& get(){return value_m;}
};

class KinkOut:public KinkBase{
public:
	template<typename T>
	void set(T&& value){
		value_m=value;
	}
};

template<int in_size, int out_size>
class NodeBase{
protected:
	std::array<KinkBase*, in_size> in_m{nullptr};
	std::array<KinkOut*, out_size> out_m{nullptr};
public:
	void addKinkIn(KinkBase &in, int kink=0)
	{
		in_m[kink]=&in;
	}

	void removeKinkIn(int kink=0)
	{
		in_m[kink]=nullptr;
	}

	
	variant_types getKinkInVal(int kink=0)
	{
		if(in_m[kink])
			return in_m[kink]->get();
		else
			return 0;
	}
	
	KinkBase& getKinkOut(int kink=0)
	{
		return *out_m[kink];
	}

	void addKinkOut(KinkOut &out, int kink=0)
	{
		out_m[kink]=&out;
	}

	void removeKinkOut(int kink=0)
	{
		out_m[kink]=nullptr;
	}
	
	template<typename T>
	void setKinkOutVal(T&& value,int kink=0)
	{
		out_m[kink]->set(value);
	}


	variant_types getKinkOutVal(int kink=0)
	{
		return out_m[kink]->get();
	}
};

struct PrintVistor{
	void operator()(const float &val){
		std::cout<<"Float value:"<<val<<"\n";
	}
	void operator()(const int &val){
		std::cout<<"Int value:"<<val<<"\n";
	}

};

struct ReturnVisitor{
	float operator()(const float &val){
		return val;
	}

	int operator()(const int &val){
		return val;
	}
};


int main(int argc, char const *argv[])
{
	

	NodeBase<1,1> InNode;
	KinkOut out;
	out.set(334.255f);
	InNode.addKinkOut(out);
	InNode.setKinkOutVal(41.346f);
	// std::cout<<InNode.getKinkOutVal()<<"\n";
	// std::cout<<out.get()<<"\n";
	std::visit(PrintVistor{},InNode.getKinkOutVal());
	std::visit(PrintVistor{},out.get());


	std::cout<<"Setting up value from InNode to MiddleNode\n";
	NodeBase<1,1> MiddleNode;
	MiddleNode.addKinkIn(InNode.getKinkOut());
	//std::cout<<MiddleNode.getKinkInVal()<<"\n";
	std::visit(PrintVistor{},MiddleNode.getKinkInVal());

	KinkOut out2;
	MiddleNode.addKinkOut(out2);

	try
	{
	float val=std::get<float>(MiddleNode.getKinkInVal())+55;
	MiddleNode.setKinkOutVal(val);
	}
	catch(...)
	{
		std::cout<<"ERROR::Bad access of variant type\n";
	}

	// std::cout<<MiddleNode.getKinkOutVal()<<"\n";
	std::visit(PrintVistor{},MiddleNode.getKinkOutVal());

	std::cout<<"Setting up value from MiddleNode to OutNode\n";
	NodeBase<1,1> OutNode;
	OutNode.addKinkIn(MiddleNode.getKinkOut());
	//std::cout<<OutNode.getKinkInVal()<<"\n";
	std::visit(PrintVistor{},OutNode.getKinkInVal());
	

	std::cout<<"After OutNode.removeKinkIn() is called"<<std::endl;
	OutNode.removeKinkIn();
	std::visit(PrintVistor{},OutNode.getKinkInVal());


	std::cin.get();
	return 0;
}