#include <iostream>
#include <stdexcept>
template<typename T>
void swap(T &x, T&y){
	T temp = std::move(x);
	x = std::move(y);
	y = std::move(temp);
}

struct Node{
	float data;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(float val):data(val){}
	~Node(){
		if(left !=nullptr)
			delete left;
		if(right !=nullptr)
			delete right;
		left=nullptr;
		right=nullptr;
		std::cout<<"Delete\n";
	}
};

class BinaryTree{
private:
	Node* root=nullptr;
public:
	void insert(float data)
	{
		if(!root)
			root=new Node(data);
		else
		{	
			Node* parent = traceDown(root, data);
			Node* child = new Node(data);
			if(child->data > parent->data)
				parent->right = child;
			else
				parent->left = child;
		}
	}

	//Return position to insert Node
	//Return position to insert Node
	Node* traceDown(Node* root, float data)
	{	
		if(root->data > data)
		{
			if(root->left !=nullptr)
				return traceDown(root->left,data);
			else 
				return root;
		}

		if(root->data < data)
		{
			if(root->right !=nullptr)
				return traceDown(root->right,data);
			else 
				return root;
		}		
		throw std::runtime_error("Binary Tree can't have nodes of the same value");
	}

	
	//Return pointer to the parent of node that has value data
	//Return pointer to the parent of node that has value data
	Node* find(Node* root, float data)
	{	
		if(root)
		{
			if((root->left !=nullptr && root->left->data==data) || (root->right !=nullptr && root->right->data==data))
				return root;
			else
			{
				if(data < root->data)
					return find(root->left, data);
				if(data > root->data)
					return find(root->right,data);
			}
		}
		return nullptr;
	}


	Node* findMin( Node* root) const
	{
		if (root == nullptr)
			return nullptr;
		if( root->left == nullptr)
			return root;
		return findMin(root->left);
	}

	// Remove node from binary tree (except for Root)
	// Remove node from binary tree (except for Root)
	bool remove(Node* root, float data)
	{	
		Node* pa = find(root, data);
		if(pa)
		{
			Node* node = (pa->left !=nullptr && pa->left->data == data)? pa->left : pa->right;
			if(node->left ==nullptr && node->right==nullptr)
			{
				if(pa->left == node)
					pa->left = nullptr;
				else
					pa->right = nullptr;
				delete node;
			}
			else
			{
				if(node->left !=nullptr && node->right !=nullptr)
				{
					Node* leftMost = findMin(node->right);
					swap(node->data,leftMost->data);
					remove(node,data);
				}
				else
				{
					Node* child = (node->left !=nullptr)? node->left : node->right;
					node->data = child->data;
					node->left = child->left;
					node->right = child->right;
					child->left=nullptr;
					child->right=nullptr;
					delete child;
				}
			}
			return true;
		}
		return false;
	}
	
	Node* getRoot(){return root;}
	~BinaryTree(){
		delete root;
	}
};



int main(int argc, char const *argv[])
{

	BinaryTree tree;
	tree.insert(10);
	tree.insert(12);
	tree.insert(9);
	tree.insert(6);
	tree.insert(8);
	tree.insert(7.5);
	tree.insert(13);
	tree.insert(11);
	// std::cout<<tree.getRoot()->right->left->data<<"\n";
	// std::cout<<tree.getRoot()->left->left->right->left->data<<"\n";
	// std::cout<<tree.find(tree.getRoot(),9)->left<<"\n";
	// std::cout<<tree.getRoot()->left <<"\n";
	std::cout<<std::boolalpha<<tree.remove(tree.getRoot(),12);


	BinaryTree tree2;
	tree2.insert(15);
	tree2.insert(10);
	tree2.insert(20);
	tree2.insert(8);
	tree2.insert(12);
	tree2.insert(18);
	tree2.insert(25);
	tree2.insert(16);
	tree2.insert(19);
	tree2.insert(30);
	std::cout<<"\nTree2 example\n";
	std::cout<<tree2.getRoot()->right->left->right->data;
	std::cout<<std::boolalpha<<tree2.remove(tree2.getRoot(),19);
	std::cout<<tree2.getRoot()->right->left->right;
	std::cin.get();
	return 0;
}