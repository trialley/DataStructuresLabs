template <class T>
struct myTreeNode
{
public:
	myTreeNode()
	{
		left = right = nullptr;
	}
	myTreeNode(const T &it,myTreeNode<T> *one,myTreeNode<T> *two)
	{
		value = it;
		left = one;
		right = two;
	}
	T value;
	myTreeNode<T> *left, *right;
};

template <class T>
class myTree
{
private:
	myTreeNode<T> *root;
public:

	myTree()
	{
		root = new myTreeNode<T>;
	}

	void insert(int n,T **it);
	void iterativePreorder();	//?¡ãD¨°¦Ì¨¹¡ä¨²
	void iterativeInorder();	//?DD¨°¦Ì¨¹¡ä¨²
	void iterativePostorder();	//o¨®D¨°¦Ì¨¹¡ä¨²
	void breadthFirst();	//2?¡ä?¦Ì¨¹¡ä¨²
	int treeHeight(myTreeNode<T> *it,int *p);
	int treeNum(myTreeNode<T>*it, int *p);

	void everyHeight(int n);	//¡ä?o¡¥¨ºy¨®?¨¤¡ä?????????¨²¦Ì?¦Ì????¨¨¡ê?
	//¨ª¡§1y¦Ì¡Â¨®?treeHeight()¨¤¡ä?????¡ê
	void everyNum(int n);
};



template<class T>
void myTree<T>::everyHeight(int n)
{
	int *p = new int[n];
	treeHeight(root, p);
	for (int i = 0; i < n; ++i)
		cout << p[i] << " ";
	delete[]p;
}

template<class T>
int myTree<T>::treeHeight(myTreeNode<T> *it,int *p)
{
	if (it == nullptr)
		return 0;
	else 
	{
		int m=treeHeight(it->left,p);
		int n=treeHeight(it->right,p);
		return p[it->value-1]=(m > n) ? m + 1 : n + 1;
	}
}


template<class T>
void myTree<T>::everyNum(int n)
{
	int *p = new int[n];
	for (int i = 0; i < n; ++i)
		p[i] = 0;
	treeNum(root, p);
	for (int i = 0; i < n; ++i)
		cout << p[i] << " ";
}

template<class T>
int myTree<T>::treeNum(myTreeNode<T>*it, int *p)
{
	if (it == nullptr)
		return 0;
	else
	{
		int m=treeNum(it->left, p);
		int n=treeNum(it->right, p);
		return p[it->value - 1] = m + n + 1;
	}
}



template<class T>
void myTree<T>::insert(int n,T **it)
{
	int i = 0;
	myQueue<myTreeNode<T>*> travQueue;
	root->value = 1;
	myTreeNode<T> *t = root;
	if (t)
	{
		travQueue.push(t);
		while (!travQueue.empty()&&i!=n)
		{
			t = travQueue.front();
			travQueue.pop();
			if (it[t->value-1][0] != -1)
			{
				myTreeNode<T> *new_node = new myTreeNode<T>;
				new_node->value = it[t->value-1][0];
				new_node->left = nullptr;
				new_node->right = nullptr;
				t->left = new_node;
			}
			if (it[t->value-1][1] != -1)
			{
				myTreeNode<T> *new_node = new myTreeNode<T>;
				new_node->value = it[t->value-1][1];
				new_node->left = nullptr;
				new_node->right = nullptr;
				t->right = new_node;
			}
			i++;
			if (t->left)
				travQueue.push(t->left);
			if (t->right)
				travQueue.push(t->right);
		}
	}
}

template<class T>
void myTree<T>::iterativePreorder()
{
	myStack<myTreeNode<T>*> travStack;
	myTreeNode<T>* t = root;
	if (t!=nullptr)
	{
		travStack.push(t);
		while (!travStack.empty())
		{
			t = travStack.TopAndPop();
			cout << t->value << " ";
			if (t->left)
				travStack.push(t->left);
			if (t->right)
				travStack.push(t->right);
		}
	} 
}

template<class T>
void myTree<T>::breadthFirst()
{//2?¡ä?¡À¨¦¨¤¨²
	myQueue<myTreeNode<T>*> travQueue;
	myTreeNode<T> *t = root;
	if (t != nullptr)
	{
		travQueue.push(t);
		while (!travQueue.empty())
		{
			t = travQueue.front();
			travQueue.pop();
			cout << t->value<<" ";
			if (t->left)
				travQueue.push(t->left);
			if (t->right)
				travQueue.push(t->right);
		}
	}
}



template<class T>
void myTree<T>::iterativeInorder()
{
	myStack<myTreeNode<T>*> travStack;
	myTreeNode<T> *t = root;
	do {
		while (t)
		{
			travStack.push(t);
			t = t->left;
		}
		if (!travStack.empty())
		{
			t = travStack.TopAndPop();
			cout << t->value << " ";
			t = t->right;
		}
	} while (t || !travStack.empty());
}

template<class T>
void myTree<T>::iterativePostorder()
{
	myStack<myTreeNode<T>*> travStack;
	myTreeNode<T>*p = root, *q = root;
	while (p)
	{
		for (; p->left != nullptr; p = p->left)
			travStack.push(p);
		while (p->right == 0 || p->right == q)
		{
			cout << p->value << " ";
			if (travStack.empty())
				return;
			p = travStack.pop();
		}
		//¨¨?1?p->right!=0,?¨°¨¨?????D?¨¨???
		travStack.push(p);
		p = p->right;
	}
}

//#include "myTree.h"
#include <iostream>

using namespace std;

int main()
{
	myTree<int> tree;
	int n;
	cin >> n;
	int **p = new int *[n];
	for (int i = 0; i < n; ++i)
		p[i] = new int[2];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 2; ++j)
			cin >> p[i][j];

	tree.insert(n, p);
	tree.breadthFirst();
	cout << endl;
	tree.everyNum(n);
	cout << endl;
	tree.everyHeight(n);
}
