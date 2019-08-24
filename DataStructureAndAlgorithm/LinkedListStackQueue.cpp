#include <iostream>
#include <array>
#include <stdexcept>

template<typename T>
class DoubleLinkedList{
private:
	struct Node
	{	
		T data_m;
		Node* prev_m;
		Node* next_m;
		Node(const T& data, Node* prev=nullptr, Node* next=nullptr):data_m(data),prev_m(prev),next_m(next){}
	};	

	size_t size=0;
	Node* head=nullptr;
	Node* tail=nullptr;
public:
	DoubleLinkedList()=default;

	void append(const T& data)
	{
		if(!head){
			head=new Node(data);
			head->next_m=head;
			head->prev_m=head;
			tail=head;
		}
		else{
			Node* node=new Node(data,tail,head);
			tail->next_m=node;
			tail=node;
			head->prev_m=node;
		}
		size++;
	}

	T pop(){
		Node* new_tail=nullptr;
		T value;
		if(head){
			new_tail = tail->prev_m;
			value = std::move(tail->data_m);
			new_tail->next_m=head;
			delete tail;
			if (tail == head){
				head=nullptr;
				tail=nullptr;
			}else
				tail=new_tail;
			size--;
		}
		else
			throw std::out_of_range("Out of range");
		return value;
	}

	void clear(){
		Node* node=head;
		Node* temp=nullptr;
		while(node){
			if(node!=tail){
				temp=node->next_m;
				delete node;
				node=temp;
			}
			else{
				delete node;
				node=nullptr;
			}
		}
		size=0; head=nullptr; tail=nullptr;
	}

	bool isEmpty() const{
		return !head;
	}

	T& get(size_t index=0) const{
		Node* node=head;
		if(head && index>=0 && index < size)
		{
			size_t current=0;
			while(current<index)
			{
				node=node->next_m;
				current++;
			}
		}
		else
			throw std::out_of_range("Index out of range");
		return node->data_m;
	}
	void insert(const T& data, size_t pos){
		if(head){
			size_t current = 0;
			Node* currentNode = head;
			while(current<pos){
				currentNode = currentNode->next_m;
				current++;
			}
			Node* node = new Node(data);
			node->next_m = currentNode->next_m;
			node->prev_m=currentNode;
			currentNode->next_m=node;
			node->next_m->prev_m=node;
			if(pos==size-1)
				tail=node;
		}
		else
		{ 
			head=new Node(data);
			head->next_m=head;
			head->prev_m=head;
			tail=head;
		}
		size++;
	}
	~DoubleLinkedList(){
		clear();
	}
};

template<typename T>
class SingleLinkedList{
private:
	struct Node{
		T data_m;
		Node* next_m=nullptr;
		Node(const T& data):data_m(data){}
	};
	
	size_t size=0;
	Node* head=nullptr;
	Node* tail=nullptr;
public:
	SingleLinkedList()=default;
	void append(const T& data){
		if(!head){
			head=new Node(data);
			tail=head;
		}
		else{
			Node* node=new Node(data);
			tail->next_m=node;
			tail=node;				
		}
		size++;
	}

	bool isEmpty() const{
		return !head;
	}

	void insert(const T& data, size_t pos){
		if(head){
			size_t current = 0;
			Node* currentNode = head;
			while(current<pos){
				currentNode = currentNode->next_m;
				current++;
			}
			Node* node = new Node(data);
			node->next_m = currentNode->next_m;
			currentNode->next_m = node;
			if(pos==size-1)
				tail=node;
		}
		else
		{ 
			head=new Node(data);
			tail=head;
		}
		size++;
	}

	T& get(size_t index = 0) const {
		Node* node=head;
		if(head && index>=0 && index < size){
			size_t current=0;
			while(current<index)
				{
					node=node->next_m;
					current++;
				}	
		}
		else
			throw std::out_of_range("Index out of range");
		return node->data_m;
	}

	size_t getSize() const{
		return size;
	}
	void remove(size_t index=0){
		size_t current = 0;
		Node* node = head;
		if(index==0)
		{
			head=head->next_m; // Node is current node here
			delete node;
		}
		else{
			while(current<index-1){
				node=node->next_m; //Node is prev node here
				current++;
			}
			Node* removeNode=node->next_m;
			node->next_m=node->next_m->next_m;
			delete removeNode;
			if(index==size-1)
				tail=node;
		}
		size--;		
	}

	void clear(){
			Node* node=head;
			Node* temp=nullptr;
			while(node){
				if(node!=tail){
					temp=node->next_m;
					delete node;
					node=temp;
				}
				else{
					delete node;
					node=nullptr;
				}
			}
			size=0; head=nullptr; tail=nullptr;
	}
	~SingleLinkedList(){
		clear();
	}
};

template<typename T,size_t size>
class Queue{
private:
	std::array<T,size> items;
	long long int front = -1;
	long long int rear = -1;
public:
	bool isFull() const{
		if((front == 0 && rear == size-1) || (front == rear +1 )) 
			{
				return true;
			}
		return false;
	}

	bool isEmpty() const{
		if(front == -1ll)
			return true;
		return false;
	}

	void enQueue(const T &elm){
		if(!isFull()){
			if(front == -1ll)
				front = 0;
			rear=(rear+1) % size;
			items[rear] = elm;
		}else
			throw std::runtime_error("Queue is full");
	}

	T deQueue(){
		size_t prefront;
		if(!isEmpty()){
			prefront=front;
			if(front == rear){
				front = -1;
				rear = -1;
			}
			else
				front = (front+1) % size;
		}

		else
			throw std::runtime_error("Queue is empty");
		return items[prefront];
	}

	friend std::ostream& operator<<(std::ostream& out,const Queue &queue){
		if(!queue.isEmpty()){
			out<<"Queue[ ";
			for(const auto &elm:queue.items)
				out<<elm<<' ';
			out<<']';
		}else
			out<<"Queue empty";
		return out;

	}
};

template<typename T>
struct Node{
	T data_m;
	Node* left_m; Node* right_m;
	Node(const T &data, Node* left=nullptr, Node* right=nullptr):data_m(data),left_m(left),right_m(right){}
};


//Breath First Search or Level Order Tranverse
//Breath First Search or Level Order Tranverse
template<size_t max_size,typename T>
void printLevelOrder(const Node<T> &root){
		// max_size is define by elm_size_in_lowest_level  
		// max_size is define by elm_size_in_lowest_level  
	Queue<Node<T>*, max_size> q;
	const Node<T>* temp_node = &root;

	while(temp_node)
	{	std::cout<<temp_node->data_m<<"  ";
		if(temp_node->left_m)
			q.enQueue(temp_node->left_m);
		if(temp_node->right_m)
			q.enQueue(temp_node->right_m);
		if(q.isEmpty())
			temp_node=nullptr;
		else
			temp_node=q.deQueue();
	}
}


int main(int argc, char const *argv[]){
	
	int* x=new int(20);
	std::cout<<'\n'<<x;
	std::cout<<'\n'<<*x;
	delete x;
	std::cout<<'\n'<<x;

	
	//DoubleLinkedList
	std::cout<<"\nDoubledLinkedList";
	DoubleLinkedList<float> link;
	link.insert(35.6,0);
	link.append(235.6);
	std::cout<<'\n'<<link.get();
	std::cout<<'\n'<<link.pop();
	std::cout<<'\n'<<link.pop();
	std::cout<<std::boolalpha<<'\n'<<link.isEmpty();
	//std::cout<<'\n'<<link.pop();
	//link.clear();

	std::cout<<"\nSingled Linked List\n";
	SingleLinkedList<float> single;
	single.insert(33.6,0);
	single.append(2.354);
	single.append(3.56);
	single.append(6.78);
	single.append(7.8);
	single.insert(8.9,3);
	single.append(25.6);
	std::cout<<single.get(0)<<'\n';
	single.remove(0);
	single.remove(4);
	single.clear();
	std::cout<<single.isEmpty()<<'\n';

	std::cout<<"Queue implementation\n";
	Queue<float,5> q;
	std::cout<<std::boolalpha<<q.isEmpty()<<'\n';
	q.enQueue(3.5);
	q.enQueue(3.7);
	q.enQueue(3.9);
	q.enQueue(4.1);
	q.enQueue(4.3);
	// q.enQueue(4.5);
	std::cout<<std::boolalpha<<q.isFull();
	std::cout<<std::boolalpha<<q;

	std::cout<<"\nLevel Order Tree Tranverser: ";
	Node<float> node8(8.8);
	Node<float> node9(9.9);
	Node<float> node4(4.4,&node8,&node9);
	Node<float> node10(10.0);
	Node<float> node6(6.6,&node10);
	Node<float> node7(7.7);
	Node<float> node5(5.5);
	Node<float> node2(2.2,&node4,&node5);
	Node<float> node3(3.3,&node6,&node7);
	Node<float> node1(1.1,&node2,&node3);
	printLevelOrder<5>(node1);
	std::cin.get();
	return 0;
}