#include <iostream>
#include <algorithm>
#include <array>

struct Node{
	char data;
	Node* parent=nullptr;
	Node(const char &value):data(value){}
};


struct Edge{
	Node* src=nullptr;
	Node* des=nullptr;
	size_t weight;
	Edge(Node &node1, Node &node2,size_t val=0):src(&node1),des(&node2),weight(val){}
	friend std::ostream& operator<<(std::ostream& out,const Edge& edge)
	{
		out<<"Edge("<<edge.src->data<<", "<<edge.des->data<<')';
		return out;
	};
};


Node* find(Node &node){
	if (node.parent==nullptr)
		return &node;
	return find(*node.parent);
}

//IF 2 Nodes belong to Different Node, Union and return True
//IF 2 Nodes belong to Different Node, Union and return True
bool Union(Node &node1, Node &node2){
	Node* n1_pa=find(node1);
	Node* n2_pa=find(node2);

	if(n1_pa != n2_pa)
	{	
		n1_pa->parent=n2_pa;
		return true;
	}
	return false;
}

template<size_t size>
bool isCircle(std::array<Edge,size> edges){
	for(auto edge:edges)
	{
		if(find(*edge.src)==find(*edge.des))
			return true;
		Union(*edge.src, *edge.des);
	}
	return false;

}

template<size_t size>
bool findSpanningTree(std::array<Edge, size> edges,size_t vecs_size){
	size_t count = 0;
	for(auto edge:edges)
	{	
		if(find(*edge.src)!=find(*edge.des))
		{
			Union(*edge.src, *edge.des);
			std::cout<<edge<<"; ";
			count++;
			if (count == vecs_size-1)
				return true;
		}
	}
	return false;
}

int main(int argc, char const *argv[])
{
	// Node node1(1);
	// Node node2(2);
	// Node node3(3);
	// Node node4(4);
	// Node node5(5);
	// std::array<Edge,4> edges{Edge(node2,node1),Edge(node1,node5),Edge(node4,node1),Edge(node4,node5)};

	// if(isCircle(edges))
	// 	std::cout<<"Have loop\n";
	// else
	// 	std::cout<<"Not have loop\n";


	//Kruskal's Algorithm Minium Spanning Tree
	//Kruskal's Algorithm Minium Spanning Tree
	std::cout<<"Minium Spanning Tree Kruskal's Algorithm\n";
	Node nodeA('A');
	Node nodeB('B');
	Node nodeC('C');
	Node nodeD('D');
	Node nodeE('E');
	Node nodeF('F');
	Node nodeG('G');
	Node nodeH('H');
	Node nodeI('I');
	Node nodeJ('J');
	std::array<Edge,18> edges0{Edge(nodeI, nodeJ,0), Edge(nodeA,nodeE,1),Edge(nodeC,nodeI,1), 
	Edge(nodeE,nodeF,1),Edge(nodeG,nodeH,1),Edge(nodeB,nodeD,2), Edge(nodeC,nodeJ,2), Edge(nodeD,nodeE,2), 
	Edge(nodeD, nodeH,2), Edge(nodeA, nodeD,4), Edge(nodeB, nodeC, 4), Edge(nodeC, nodeH,4), Edge(nodeG, nodeI,4),
	Edge(nodeA,nodeB,5),Edge(nodeD,nodeF,5), Edge(nodeH,nodeI,6), Edge(nodeF, nodeG,7), Edge(nodeD, nodeG,11)};
	//std::sort(edges0.begin(),edges0.end(),[](const Edge &edge1, const Edge &edge2)->bool{return edge1.weight<edge2.weight;});

	std::cout<<"Edges connected:  ";
	if(findSpanningTree(edges0,10))
		std::cout<<"\nMininum spanning tree found";
	else
		std::cout<<"\nMininum spanning tree not found";

	std::cin.get();
	return 0;
}