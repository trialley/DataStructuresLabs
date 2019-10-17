/*Ex11_2.cpp*/
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
	if (initialCapacity <1)
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

/*���������*/
template <class E>
struct binaryTreeNode     
{
	E element;       //�ڵ�Ԫ��
	binaryTreeNode<E>* leftChild;   //�����
	binaryTreeNode<E>* rightChild;  //�Ҷ���
	/*���캯��*/
	binaryTreeNode()
	{rightChild = leftChild = NULL;}
	binaryTreeNode(const E& theElement):element(theElement)
	{rightChild = leftChild = NULL;}
	binaryTreeNode(const E& theElement, binaryTreeNode<E>* theLeftChild, binaryTreeNode<E>* theRightChild):element(theElement)
	{
		rightChild = theRightChild;
		leftChild = theLeftChild;
	}
};

/*������*/
template <class E>
class linkedBinaryTree
{
	public:
		linkedBinaryTree()
		{
			root = NULL;
			treeSize = 0;
		}
		~linkedBinaryTree(){;}
		int size() const {return treeSize;}
		void makeTree(const E&, linkedBinaryTree<E>&, linkedBinaryTree<E>&);	   //����
	protected:
		binaryTreeNode<E>* root;   //�������ĸ��ڵ�
		int treeSize;			   //���Ľڵ�ĸ���
};

/*����������*/
template <class E>
void linkedBinaryTree<E>::makeTree (const E& theElement, linkedBinaryTree<E>& lT, linkedBinaryTree<E>& rT)
{
	root = new binaryTreeNode<E>(theElement, lT.root, rT.root);
	treeSize = lT.treeSize + rT.treeSize + 1;
	//�������������������
	lT.root = rT.root = NULL;
	lT.treeSize = rT.treeSize = 0;
}

/*���������Ľڵ�*/
template <class T,class E>
struct huffmanNode
{
	linkedBinaryTree<T>* tree;
	E weight;
	operator E() const {return weight;}			//����Tʱ������Ȩ��
};

/*��������*/
template <class T>
class huffmanTree
{
	public:
		huffmanTree()
		{
			stringLength = 0;
			countNum = 0;
		}
		~huffmanTree()
		{
			tree->~linkedBinaryTree();
			delete []weight;
			delete []theElement;
		}
		int makeHuffman();				//����������������ȡ���볤��
		void getin(string& in);			//��ȡ����
	private:
		linkedBinaryTree<T>* tree;		//��������
		int stringLength;				//���������볤��
		int countNum;					//Ԫ������
		int* weight;					//Ȩ������
		T* theElement;					//Ԫ������
};

/*��ȡ����*/
template <class T>
void huffmanTree<T>::getin(string& in)
{
	int countNeeded[26] = {0};			//ͳ��ÿ����ĸ���ֵĴ���
	int len = in.length();
	for (int i=0; i<len; i++)
		countNeeded[in[i]-97]++;		//ͳ�Ƶ�����ĸ�Ķ�ӦԪ��ֵ��1
	for (int i=0; i<26; i++)
	{
		if (countNeeded[i] != 0)
			countNum++;					//ͳ�Ƴ��ֵ���ĸ������
	}
	if (countNum == 1)					//����Ԫ�ؾ���ͬ
		stringLength = len;
	theElement = new char[countNum+1];
	weight = new int[countNum+1];
	int index = 0;
	for (int i=0; i<26; i++)
	{
		if (countNeeded[i] != 0)
		{
			theElement[index+1] = i+97;
			weight[index+1] = countNeeded[i];
			index++;
		}
	}
}

/*������������*/
template <class T>
int huffmanTree<T>::makeHuffman ()
{
	if (countNum == 1)
		return stringLength;
	huffmanNode<T,int>* hNode = new huffmanNode<T,int>[countNum+1];
	linkedBinaryTree<T> emptyTree;			//����n-1�����ڵ�Ķ�����
	for (int i=1; i<=countNum; i++)
	{
		hNode[i].weight = weight[i];				//Ȩ��
		hNode[i].tree = new linkedBinaryTree<T>;
		hNode[i].tree->makeTree(theElement[i],emptyTree,emptyTree);	//����
	}
	minHeap<huffmanNode<T,int> > heap(1);
	heap.initialize(hNode,countNum);
	huffmanNode<T,int> w, x, y;
	stringLength = 0;
	for (int i=1; i<countNum; i++)
	{
		x = heap.top();
		heap.pop();
		y = heap.top();
		heap.pop();
		tree = new linkedBinaryTree<T>;
		tree->makeTree('0', *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		stringLength += w.weight;
		w.tree = tree;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}

	return stringLength;
}

int main()
{
	string in;
	cin >> in;
	huffmanTree<char> huffman;
	huffman.getin(in);
	cout << huffman.makeHuffman();
	return 0;
}
