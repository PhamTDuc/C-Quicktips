#include <iostream>
#include <array>
#include <stdexcept>

//Using Binary Heap is an efficent way to implement Priority Queue 
//Using Binary Heap is an efficent way to implement Priority Queue 

template<typename T>
void swap(T& x, T& y){
	T temp = std::move(x);
	x = std::move(y);
	y = std::move(temp);
}

template<typename T,size_t capacity>
class MinHeap{
private:
	std::array<T, capacity> heap;
	size_t heap_size=0;
public:
	MinHeap() = default;

	static size_t getPin(size_t i){return (i-1)/2;}	
	static size_t getLin(size_t i){return 2*i+1;}	
	static size_t getRin(size_t i){return 2*i+2;}

	T getMin(){ return heap[0];}

	void insertKey(const T &key)
	{	
		size_t i = heap_size;
		if (heap_size < capacity)
		{
			heap[heap_size] = key;
			while(i != 0 && heap[getPin(i)] > heap[i])
			{
				swap(heap[getPin(i)],heap[i]);
				i = getPin(i);
			}
			heap_size++;
		}else
			throw std::out_of_range("Heap::insertKey:  Heap is full");
	}

	// Assume new_key < prev_key
	// Assume new_key < prev_key
	void decreaseKey(size_t i, const T &key)
	{
		if(i < heap_size && i >=0 && heap_size > 0)
		{
			heap[i]=key;
			while(i != 0 && heap[getPin(i)] > heap[i])
			{
				swap(heap[getPin(i)],heap[i]);
				i = getPin(i);
			}
		}
		else
			throw std::out_of_range("Heap::decreaseKey:  Invalid index");
	}

	void heapify(size_t i)
	{
		size_t smallest = i;
		size_t l = getLin(i);
		size_t r = getRin(i);
		if(l < heap_size && heap[l] < heap[smallest])
			smallest = l;
		if(r < heap_size && heap[r] < heap[smallest])
			smallest = r;
		if (smallest != i)
		{
			swap(heap[i],heap[smallest]);
			heapify(smallest);
		}
	}	

	T extractMin()
	{
		T root;
		if(heap_size>0)
		{
			root = heap[0];
			heap[0] = heap[heap_size - 1];
			heap_size--;
			heapify(0);
		}else
			throw std::out_of_range("Heap::extractMin:  Heap Empty");
		return root;
	}

	void deleteKey(size_t i)
	{
		if(i < heap_size && i >=0 && heap_size > 0)
		{
			swap(heap[i],heap[heap_size-1]);
			heap_size--;
			heapify(i);
		}else
			throw std::out_of_range("Heap::DeleteKey:  Index out of range");
	}

	std::array<T,capacity>& get()
	{
		return heap;
	}

};

template<typename T,size_t size>
void print(std::array<T,size> &arr){
	std::cout<<"Array[ ";
	for(const auto elm:arr){
		std::cout<<elm<<" ; ";
	}
	std::cout<<"]\n";
}

int main(int argc, char const *argv[])
{
	MinHeap<float,10> heap;
	heap.insertKey(3);
	heap.insertKey(2);
	heap.deleteKey(1);
	heap.insertKey(15); 
    heap.insertKey(5); 
    heap.insertKey(4); 
    heap.insertKey(45); 
    //print(heap.get());
    std::cout << heap.extractMin() << " "; 
    //print(heap.get());
    std::cout << heap.getMin() << " "; 
    heap.decreaseKey(2,1);
    std::cout << heap.getMin()<<'\n';

    std::cout<<"Turn into max heap\n";
    MinHeap<float,10> maxheap;
    maxheap.insertKey(-3);
	maxheap.insertKey(-2);
	maxheap.deleteKey(1);
	maxheap.insertKey(-15); 
    maxheap.insertKey(-5); 
    maxheap.insertKey(-4); 
    maxheap.insertKey(-45); 
    std::cout << -maxheap.extractMin() << " "; 
    //print(heap.get());
    std::cout << -maxheap.getMin() << " "; 
    heap.decreaseKey(2,-1);
    std::cout << -maxheap.getMin()<<'\n';

	std::cin.get();
	return 0;
}