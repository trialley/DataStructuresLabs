#include <iostream>
#include <string>
using namespace std;

/*改变数组的长度*/
template <class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)    //新数组长度小于0，抛出异常
    {
        throw "New length must be >= 0";
        cout << "New length must be >= 0" << endl;
    }
    T* temp = new T[newLength];  //新数组
    int number;                //需要复制的元素数
    if (oldLength<newLength)
        number = oldLength;
    else
        number = newLength;
    for (int i=0; i<number; i++)
        temp[i] = a[i];
    delete []a;    //删除旧数组
    a = temp;     //复制新的数组
}

/*小根堆*/
template <class T>
class minHeap
{
	public:
		minHeap (int initialCapacity = 10);
		~minHeap () {delete []heap;}
		bool empty() const {return heapSize == 0;}
		int size() const {return heapSize;}
		T& top()
		{
			if (heapSize == 0)
			{
				string error = "empty heap";
				throw error;
			}
			return heap[1];
		}
		void pop();						//删除最小元素
		void push(const T& theElement);	//插入元素
		void output();					//输出
		void initialize(T*, int);		//构建小根堆
		void deactivateArray()
		{

			heap = NULL;
			arrayLength = heapSize = 0;
		}
	private:
		int heapSize;					//元素数量
		int arrayLength;				//队列元素加1
		T* heap;						//元素数组
};

/*构造函数*/
template <class T>
minHeap<T>::minHeap (int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "wrong capacity" << endl;
		return;
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

/*删除最小值*/
template <class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)
	{
		string error = "empty heap";
		throw error;
	}
	heap[1].~T();
	T lastElement = heap[heapSize--];		//将尾节点保存并在树中删除
	int currentNode = 1;					//从根节点起，为其寻找位置
	int child = 2;
	while (child <= heapSize)				//child应该是较小的孩子
	{
		if (child < heapSize && heap[child] > heap[child+1])
			child++;						//找到较小的孩子
		if (lastElement <= heap[child])		//如果根节点较小，则是正确的位置
			break;
		heap[currentNode] = heap[child];	//否则孩子上移一层
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;		//正确放置尾节点
}

/*插入新值*/
template <class T>
void minHeap<T>::push (const T& theElement)
{
	if (heapSize == arrayLength-1)			//堆已满，扩容
	{
		changeLength1D (heap, arrayLength, 2*arrayLength);
		arrayLength *= 2;
	}
	int currentNode = ++heapSize;			//新插入的元素在数组最后
	while (currentNode != 1 && heap[currentNode/2] > theElement)
	{
		heap[currentNode] = heap[currentNode/2];	//新插入值较大，移动双亲
		currentNode /= 2;							//新值移向双亲
	}
	heap[currentNode] = theElement;					//正确放置新值
}

/*输出*/
template <class T>
void minHeap<T>::output ()
{
	for (int i=1; i<heapSize; i++)
		cout << heap[i] << " ";
	cout << endl;
}

template <class T>
void minHeap<T>::initialize(T* theHeap, int theSize)
{
	delete []heap;
	heap = theHeap;
	heapSize = theSize;
	for (int root = heapSize/2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = 2*root;
		while (child <= heapSize)
		{
			if (child < heapSize && heap[child] > heap[child+1])
				child++;
			if (rootElement <= heap[child])
				break;
			heap[child/2] = heap[child];
			child *= 2;
		}
		heap[child/2] = rootElement;
	}
}

/*大根堆*/
template <class T>
class maxHeap
{
	public:
		maxHeap (int initialCapacity = 10);
		~maxHeap () {delete []heap;}
		bool empty() const {return heapSize == 0;}
		int size() const {return heapSize;}
		T& top()
		{
			if (heapSize == 0)
			{
				string error = "empty heap";
				throw error;
			}
			return heap[1];
		}
		void pop();						//删除最大元素
		void push(const T& theElement);	//插入元素
		void output();					//输出
		void initialize(T*, int);		//构建小根堆
		void deactivateArray()
		{

			heap = NULL;
			arrayLength = heapSize = 0;
		}
	private:
		int heapSize;					//元素数量
		int arrayLength;				//队列元素加1
		T* heap;						//元素数组
};

/*构造函数*/
template <class T>
maxHeap<T>::maxHeap (int initialCapacity)
{
	if (initialCapacity < 1)
	{
		cout << "wrong capacity" << endl;
		return;
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

/*删除最大值*/
template <class T>
void maxHeap<T>::pop()
{
	if (heapSize == 0)
	{
		string error = "empty heap";
		throw error;
	}
	heap[1].~T();
	T lastElement = heap[heapSize--];
	int currentNode = 1;
	int child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child+1])
			child++;
		if (lastElement >= heap[child])
			break;
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

/*插入新值*/
template <class T>
void maxHeap<T>::push (const T& theElement)
{
	if (heapSize == arrayLength-1)
	{
		changeLength1D (heap,arrayLength, 2*arrayLength);
		arrayLength *= 2;
	}
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode/2] < theElement)
	{
		heap[currentNode] = heap[currentNode/2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

/*输出*/
template <class T>
void maxHeap<T>::output ()
{
	for (int i=1; i<heapSize; i++)
		cout << heap[i] << " ";
	cout << endl;
}

template <class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	delete []heap;
	heap = theHeap;
	heapSize = theSize;
	for (int root = heapSize/2; root >= 1; root--)
	{
		T rootElement = heap[root];
		int child = 2*rootElement;
		while (child <= heapSize)
		{
			if (child < heapSize && heap[child] < heap[child+1])
				child++;
			if (rootElement >= heap[child])
				break;
			heap[child/2] = heap[child];
			child *= 2;
		}
		heap[child/2] = rootElement;
	}
}

template <class T>
class minNok
{
	public:
		minNok() {;}
		~minNok() {;}
		void insert(const T& theElement);
		void remove();
		void out();
	private:
		maxHeap<T> max;		//大根堆
		minHeap<T> min;		//小根堆
};

template <class T>
void minNok<T>::insert(const T& theElement)
{
	min.push(theElement);
	if (!max.empty())
	{
		if (max.top() > min.top())
		{
			T temp = min.top();
			min.pop();
			min.push(max.top());
			max.pop();
			max.push(temp);
		}
	}
}

template <class T>
void minNok<T>::remove()
{
	max.push(min.top());
	min.pop();
}

template <class T>
void minNok<T>::out()
{
	cout << max.top() << endl;
}

int main()
{
	minNok<int> test;
	int num;
	cin >> num;
	char choice;
	for (int i=0; i<num; i++)
	{
		cin >> choice;
		switch(choice)
		{
			case 'M':
				int n;
				cin >> n;
				test.insert(n);
				break;
			case 'L':
				test.remove();
				break;
			case 'W':
				test.out();
			default:
				break;
		}
	}
	return 0;
}
