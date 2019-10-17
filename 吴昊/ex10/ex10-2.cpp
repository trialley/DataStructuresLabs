/*Ex11_2.cpp*/
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
	if (initialCapacity <1)
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

/*二叉树结点*/
template <class E>
struct binaryTreeNode     
{
	E element;       //节点元素
	binaryTreeNode<E>* leftChild;   //左儿子
	binaryTreeNode<E>* rightChild;  //右儿子
	/*构造函数*/
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

/*二叉树*/
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
		void makeTree(const E&, linkedBinaryTree<E>&, linkedBinaryTree<E>&);	   //建树
	protected:
		binaryTreeNode<E>* root;   //二叉树的根节点
		int treeSize;			   //树的节点的个数
};

/*二叉树建树*/
template <class E>
void linkedBinaryTree<E>::makeTree (const E& theElement, linkedBinaryTree<E>& lT, linkedBinaryTree<E>& rT)
{
	root = new binaryTreeNode<E>(theElement, lT.root, rT.root);
	treeSize = lT.treeSize + rT.treeSize + 1;
	//避免从左树和右树访问
	lT.root = rT.root = NULL;
	lT.treeSize = rT.treeSize = 0;
}

/*霍夫曼树的节点*/
template <class T,class E>
struct huffmanNode
{
	linkedBinaryTree<T>* tree;
	E weight;
	operator E() const {return weight;}			//调用T时，返回权重
};

/*霍夫曼树*/
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
		int makeHuffman();				//构建霍夫曼树并获取编码长度
		void getin(string& in);			//获取输入
	private:
		linkedBinaryTree<T>* tree;		//霍夫曼树
		int stringLength;				//霍夫曼编码长度
		int countNum;					//元素数量
		int* weight;					//权重数组
		T* theElement;					//元素数组
};

/*获取输入*/
template <class T>
void huffmanTree<T>::getin(string& in)
{
	int countNeeded[26] = {0};			//统计每个字母出现的次数
	int len = in.length();
	for (int i=0; i<len; i++)
		countNeeded[in[i]-97]++;		//统计到的字母的对应元素值加1
	for (int i=0; i<26; i++)
	{
		if (countNeeded[i] != 0)
			countNum++;					//统计出现的字母的数量
	}
	if (countNum == 1)					//所有元素均相同
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

/*构建霍夫曼树*/
template <class T>
int huffmanTree<T>::makeHuffman ()
{
	if (countNum == 1)
		return stringLength;
	huffmanNode<T,int>* hNode = new huffmanNode<T,int>[countNum+1];
	linkedBinaryTree<T> emptyTree;			//创建n-1个单节点的二叉树
	for (int i=1; i<=countNum; i++)
	{
		hNode[i].weight = weight[i];				//权重
		hNode[i].tree = new linkedBinaryTree<T>;
		hNode[i].tree->makeTree(theElement[i],emptyTree,emptyTree);	//建树
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
