#include<iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include"linkedBinaryTree.h"
#include"huffmanNode.h"

template<class T>
class minHeap
{
	public:
		int heapSize;
		int arrLen;
		T *heap;
		minHeap(int initialCapacity = 100)
		{
			heap = new T[initialCapacity];
			arrLen = initialCapacity;
			heapSize = 0;
		}
		~minHeap()
		{
			delete[] heap;
		}
		void erase(const T& target)
		//输入删除元素，将该元素删除.
		{
			//这里不允许异常出现.
			int where = 0;
			for(int i=1; i<=heapSize; i++)
			{
				if(heap[i]==target)	where = i;
			}
			int p = heapSize;
			int temp = heap[where];
			heap[where] = heap[p];
			heap[p] = temp;
			heapSize--;
		}
		void push(const T &theElement)
		//在大根堆数组尾部插入元素，而又不破坏大根堆结构
		{
			// find place for theElement
			// currentNode starts at new leaf and moves up tree
			int currentNode = ++heapSize;
			while (currentNode != 1 && heap[currentNode / 2] > theElement)
			{
				// cannot put theElement in heap[currentNode]
				heap[currentNode] = heap[currentNode / 2]; // move element down
				currentNode /= 2;                          // move to parent
			}

			heap[currentNode] = theElement;
		}
		void initialize(T* theHeap, int theSize)
		//将一个数组初始化成为一个大根堆
		//实际上也就是堆排序
		//该函数为实验定制版本，会输出排序过程.
		{
			// Initialize max heap to element array theHeap[1:theSize].
			delete [] heap;
			heap = theHeap;
			heapSize = theSize;

			// heapify
			int k = 2;
			for (int root = heapSize / 2; root >= 1; root--)
			{
				T rootElement = heap[root];
				// find place to put rootElement
				int child = 2 * root; // parent of child is target
				// location for rootElement
				while (child <= heapSize)
				{
					// heap[child] should be smaller sibling
					if (child < heapSize && heap[child] > heap[child + 1])
						child++;

					// can we put rootElement in heap[child/2]?
					if (rootElement <= heap[child])
						break;  // yes

					// no
					heap[child / 2] = heap[child]; // move child up
					child *= 2;                    // move down a level
				}
				heap[child / 2] = rootElement;
				for(int i=1; i<=k; i++)
					cout << heap[i] << " ";
				cout << endl;
				k = k+2;
			}
		}
		void qinitialize(T* theHeap, int theSize)
		//将一个数组初始化成为一个大根堆
		//实际上也就是堆排序
		//该函数为实验定制版本，会输出排序过程.
		{
			// Initialize max heap to element array theHeap[1:theSize].
			delete [] heap;
			heap = theHeap;
			heapSize = theSize;

			// heapify
			for (int root = heapSize / 2; root >= 1; root--)
			{
				T rootElement = heap[root];

				// find place to put rootElement
				int child = 2 * root; // parent of child is target
				// location for rootElement
				while (child <= heapSize)
				{
					// heap[child] should be smaller sibling
					if (child < heapSize && heap[child] > heap[child + 1])
						child++;

					// can we put rootElement in heap[child/2]?
					if (rootElement <= heap[child])
						break;  // yes

					// no
					heap[child / 2] = heap[child]; // move child up
					child *= 2;                    // move down a level
				}
				heap[child / 2] = rootElement;
			}
		}
		void output() const
		{
			for(int i=1; i<=heapSize; i++)
				cout << heap[i] << " ";
			cout << endl;
		}
		void pop()
		{
			// Remove max element.
			// if heap is empty return null
			if (heapSize == 0)   // heap empty
				throw queueEmpty();

			// Delete min element
			heap[1].~T();

			// Remove last element and reheapify
			T lastElement = heap[heapSize--];

			// find place for lastElement starting at root
			int currentNode = 1,
			    child = 2;     // child of currentNode
			while (child <= heapSize)
			{
				// heap[child] should be smaller child of currentNode
				if (child < heapSize && heap[child] > heap[child + 1])
					child++;

				// can we put lastElement in heap[currentNode]?
				if (lastElement <= heap[child])
					break;   // yes

				// no
				heap[currentNode] = heap[child]; // move child up
				currentNode = child;             // move down a level
				child *= 2;
			}
			heap[currentNode] = lastElement;
		}
		const T &top()
		{
			// return min element
			if (heapSize == 0)
				throw queueEmpty();
			return heap[1];
		}
};

template <class T>
linkedBinaryTree<int> *huffmanTree(T weight[], int n)
{
	// Generate Huffman tree with weights weight[1:n], n >= 1.
	// create an array of single node trees
	huffmanNode<T> *hNode = new huffmanNode<T> [n + 1];
	linkedBinaryTree<int> emptyTree;
	for (int i = 1; i <= n; i++)
	{
		hNode[i].weight = weight[i];
		hNode[i].tree = new linkedBinaryTree<int>;
		hNode[i].tree->makeTree(i, emptyTree, emptyTree);
	}

	// make node array into a min heap
	minHeap<huffmanNode<T> > heap(1);
	heap.qinitialize(hNode, n);

	// repeatedly combine trees from min heap
	// until only one tree remains
	huffmanNode<T> w, x, y;
	linkedBinaryTree<int> *z;
	for (int i = 1; i < n; i++)
	{
		// remove two lightest trees from the min heap
		x = heap.top();
		heap.pop();
		y = heap.top();
		heap.pop();

		// combine into a single tree
		z = new linkedBinaryTree<int>;
		z->makeTree(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}

	// destructor for min heap deletes hNode
	return heap.top().tree;
}

int main()
{
	minHeap<int> zjs;
	int n = 0;
	//2.
	cin >> n;
	for(int i=0; i<n; i++)
	{
		int temp;
		cin >> temp;
		zjs.push(temp);
	}
	zjs.output();
	//3.
	int temp = 0;
	cin >> temp;
	zjs.push(temp);
	zjs.output();
	cin >> temp;
	zjs.erase(temp);
	minHeap<int> zjs2;
	zjs2.qinitialize(zjs.heap,zjs.heapSize);
	zjs.output();
	//4.
	cin >> n;
	srand((unsigned)time(NULL));
	int*arr = new int[n+1];
	for(int i=1; i<=n; i++)
	{
		arr[i] = rand() % 1000;
		cout << arr[i] << " ";
	}
	cout << endl;
	zjs.initialize(arr,n);
	zjs.output();
	//5.
	cin >> n;
	char* _char = new char[n];
	int* _int = new int[n];
	for(int i=0; i<n; i++)
	{
		cin >> _char[i] >> _int[i];
	}
	linkedBinaryTree<int>* x = huffmanTree(_int,n);
	
	x->levelOrderOutput();
	x->preOrderOutput();
	x->postOrderOutput();
	for(int i=0; i<n; i++)
	{
		cout << _char[i] << " ";
	}
	return 0;
}
