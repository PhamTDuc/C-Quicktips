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
	int height = 0; //Height the difference of height of right NodeTree and left NodeTree 

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

void preOrder(Node* root);
class AVLBinaryTree{
private:
	Node* root = nullptr;

	Node* _trace = nullptr; //Internal use only
public:
	void insert(float data)
	{	
		Node* parent = nullptr;
		if(!root)
		{
			root=new Node(data);
			_trace = root;
		}
		else
		{	
			parent = traceDown(root, data);
			Node* child = new Node(data);
			if(child->data > parent->data)
				parent->right = child;
			else
				parent->left = child;
		}

		// Balance
		// Balance

		//Left Left rotate
		if(_trace->height > 1)
		{
			swap(_trace->data,parent->data);
			_trace->right = _trace->left;
			_trace->left = parent->left;
			parent->left = nullptr;
			_trace->height = 0;
		}

		//Right Right rotate
		if(_trace->height < -1)
		{
			swap(_trace->data,parent->data);
			_trace->left = _trace->right;
			_trace->right =  parent->right;
			parent->right = nullptr; 
			std::cout<<"Trace height "<<_trace->height<<"    ";
			_trace->height = 0;

			preOrder(_trace);
			std::cout<<"Data root"<<root->data;
			std::cout<<"pre\n";
		}

	}

	//Return parent of inserted Node
	//Return parent of inserted Node
	Node* traceDown(Node* node, float data)
	{	
		if(node->data > data)
		{	
			
			node->height++; //Increase height if left node
			if(node->left !=nullptr)
			{	
				_trace = node;
				return traceDown(node->left,data);
			}
			else 
				return node;
		}

		if(node->data < data)
		{	
			node->height--; //Decrease height if right node
			if(node->right !=nullptr)
			{	
				_trace = node;
				return traceDown(node->right,data);
			}
			else 
				return node;
		}		

		throw std::runtime_error("Binary Tree can't have nodes of the same value");
	}

	Node* getRoot()
	{
		return root;
	}

};

void preOrder(Node *root)  
{  
    if(root != nullptr)  
    {  
        std::cout << root->data << "  ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  
  
int main(int argc, char const *argv[])
{

	AVLBinaryTree tree;
	tree.insert(10);
	tree.insert(20);
	tree.insert(30);
	tree.insert(40);
	tree.insert(50);
	tree.insert(60);
	tree.insert(70);


	std::cout<<tree.getRoot()->right->right->data;
	preOrder(tree.getRoot());

	std::cin.get();
	return 0;
}