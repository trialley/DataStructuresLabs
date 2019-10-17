#include <iostream>
#include <string>
using namespace std;

/*�ı�����ĳ���*/
template <class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)    //�����鳤��С��0���׳��쳣
    {
        throw "New length must be >= 0";
        cout << "New length must be >= 0" << endl;
    }
    T* temp = new T[newLength];  //������
    int number;                //��Ҫ���Ƶ�Ԫ����
    if (oldLength<newLength)
        number = oldLength;
    else
        number = newLength;
    for (int i=0; i<number; i++)
        temp[i] = a[i];
    delete []a;    //ɾ��������
    a = temp;     //�����µ�����
}

/*С����*/
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
		void pop();						//ɾ����СԪ��
		void push(const T& theElement);	//����Ԫ��
		void output();					//���
		void initialize(T*, int);		//����С����
		void deactivateArray()
		{

			heap = NULL;
			arrayLength = heapSize = 0;
		}
	private:
		int heapSize;					//Ԫ������
		int arrayLength;				//����Ԫ�ؼ�1
		T* heap;						//Ԫ������
};

/*���캯��*/
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

/*ɾ����Сֵ*/
template <class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)
	{
		string error = "empty heap";
		throw error;
	}
	heap[1].~T();
	T lastElement = heap[heapSize--];		//��β�ڵ㱣�沢������ɾ��
	int currentNode = 1;					//�Ӹ��ڵ���Ϊ��Ѱ��λ��
	int child = 2;
	while (child <= heapSize)				//childӦ���ǽ�С�ĺ���
	{
		if (child < heapSize && heap[child] > heap[child+1])
			child++;						//�ҵ���С�ĺ���
		if (lastElement <= heap[child])		//������ڵ��С��������ȷ��λ��
			break;
		heap[currentNode] = heap[child];	//����������һ��
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;		//��ȷ����β�ڵ�
}

/*������ֵ*/
template <class T>
void minHeap<T>::push (const T& theElement)
{
	if (heapSize == arrayLength-1)			//������������
	{
		changeLength1D (heap, arrayLength, 2*arrayLength);
		arrayLength *= 2;
	}
	int currentNode = ++heapSize;			//�²����Ԫ�����������
	while (currentNode != 1 && heap[currentNode/2] > theElement)
	{
		heap[currentNode] = heap[currentNode/2];	//�²���ֵ�ϴ��ƶ�˫��
		currentNode /= 2;							//��ֵ����˫��
	}
	heap[currentNode] = theElement;					//��ȷ������ֵ
}

/*���*/
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

/*�����*/
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
		void pop();						//ɾ�����Ԫ��
		void push(const T& theElement);	//����Ԫ��
		void output();					//���
		void initialize(T*, int);		//����С����
		void deactivateArray()
		{

			heap = NULL;
			arrayLength = heapSize = 0;
		}
	private:
		int heapSize;					//Ԫ������
		int arrayLength;				//����Ԫ�ؼ�1
		T* heap;						//Ԫ������
};

/*���캯��*/
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

/*ɾ�����ֵ*/
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

/*������ֵ*/
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

/*���*/
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
		maxHeap<T> max;		//�����
		minHeap<T> min;		//С����
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
