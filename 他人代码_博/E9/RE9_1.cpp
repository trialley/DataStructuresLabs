#include<iostream>
using namespace std;
//#include"../zjslib/zjslib.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class queue
{
	protected:
	public:
		virtual ~queue() {}
		virtual T &top() = 0;
		virtual T &back() = 0;
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual void push(const T &_element) = 0;
		virtual void pop() = 0;
};
template<typename T>
class arrqueue:	public queue<T>
{
	protected:
		int queuetop;
		int queueback;
		int arrlen;
		T *queue;
	public:
		arrqueue(int initial_arrlen = 10)
		{
			arrlen = initial_arrlen;
			queue = new T[arrlen];
			queuetop = 0;
			queueback = 0;
		}
		~arrqueue()
		{
			delete[] queue;
		}
		T &top()
		{
			return queue[(queuetop + 1) % arrlen];
		}
		T &back()
		{
			return queue[queueback];
		}
		bool empty() const
		{
			return queuetop == queueback;
		}
		int size() const
		{
			return (queueback - queuetop + arrlen) % arrlen;
		}
		void push(const T &_element)
		{
			if ((queueback + 1) % arrlen == queuetop)
			{
				T *newQueue = new T[2 * arrlen];
				int start = (queuetop + 1) % arrlen;
				if (start < 2)
					copy(queue + start, queue + start + arrlen - 1, newQueue);
				else
				{
					copy(queue + start, queue + arrlen, newQueue);
					copy(queue, queue + queueback + 1, newQueue + arrlen - start);
				}
				queuetop = 2 * arrlen - 1;
				queueback = arrlen - 2;
				arrlen *= 2;
				queue = newQueue;
			}
			queueback = (queueback + 1) % arrlen;
			queue[queueback] = _element;
		}
		void pop()
		{
			queuetop = (queuetop + 1) % arrlen;
			queue[queuetop].~T();
		}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
struct node
{
	T element;
	node<T> *left;
	node<T> *right;
	node<T>()
	{
		left = NULL;
		right = NULL;
	}
	node<T>(const T &_element)
		:element(_element)
	{
		left = NULL;
		right = NULL;
	}
	node<T>(const T &_element, node<T> *_left, node<T> *_right)
		:element(_element)
	{
		left = _left;
		right = _right;
	}
};
template<class T>
class chainbintree
{
	public:
		node<T> *root;
		int treesize;

		static void (*option)(node<T> *);
		static void preOrder(node<T> *t)
		{
			if (t != NULL)
			{
				chainbintree<T>::option(t);
				preOrder(t->left);
				preOrder(t->right);
			}
		}
		static void inOrder(node<T> *t)
		{
			if (t != NULL)
			{
				inOrder(t->left);
				chainbintree<T>::option(t);
				inOrder(t->right);
			}
		}
		static void postOrder(node<T> *t)
		{
			if (t != NULL)
			{
				postOrder(t->left);
				postOrder(t->right);
				chainbintree<T>::option(t);
			}
		}
		static int countnodes(node<T> *t)
		{
			option = addToCount;
			count = 0;
			preOrder(t);
		}
		static void dispose(node<T> *t)
		{
			delete t;
		}
		static void output(node<T> *t)
		{
			cout << t->element << ' ';
		}
		static void addToCount(node<T> *t)
		{
			count++;
		}
		static int height(node<T> *t)
		{
			if (t == NULL) return 0;
			int hl = height(t->left);
			int hr = height(t->right);
			if (hl > hr) return ++hl;
			else return ++hr;
		}
	public:
		static int count;
		chainbintree()
		{
			root = NULL;
			treesize = 0;
		}
		chainbintree(const T& _element)  	//root = _element.
		{
			root = new node<T>(_element);
			root->left = NULL;
			root->right = NULL;
			treesize = 1;
		}	//of course my diy...
		chainbintree(int n,T* arr)  //extended operation by zjs!
		//make the tree to a completed bintree by a array.
		{
			root = new node<T>[n];
			for(int i=0; i<n; i++)
				root[i].element = arr[i];   //first give the value to every node<T>.
			int j = 0;
			while(1)    //then link them...
			{
				if(2*j+1>=n) break;
				else root[j].left = &root[2*j+1];
				if(2*j+2>=n) break;
				else
				{
					root[j].right = &root[2*j+2];
					j++;
				}
			}
			treesize = n;
		}
		~chainbintree()
		{
			erase();
		};
		bool empty() const
		{
			return treesize == 0;
		}
		int size() const
		{
			return treesize;
		}
		T* rootElement() const
		{
			if (treesize == 0) return NULL;
			else return root->element;
		}
		////////////////////////////////////////////
		void preOrder(void(*_option)(node<T>*))
		{
			option = _option;
			preOrder(root);
		}
		void inOrder(void(*_option)(node<T>*))
		{
			option = _option;
			inOrder(root);
		}
		void postOrder(void(*_option)(node<T>*))
		{
			option = _option;
			postOrder(root);
		}
		void levelOrder(void(*_option)(node<T>*))
		{
			arrqueue<node<T>*> q;
			node<T>** arr = new node<T>*[treesize];
			int i = 0;
			node<T> *t = root;
			q.push(t);
			while (t != NULL)
			{
				arr[i] = q.top();
				q.pop();
				if (arr[i]->left != NULL)
					q.push(arr[i]->left);
				if (arr[i]->right != NULL)
					q.push(arr[i]->right);
				i++;
				if(q.empty()) break;
			}
			for(int i=0; i<treesize; i++)
			{
				_option(arr[i]);
			}
			//delete[] arr;
		}
		void levelOrderV2(void(*_option)(node<T>*))
		{
			arrqueue<node<T>*> q;
			node<T> *t = root;
			q.push(t);
			while (t != NULL)
			{
				t = q.top();
				_option(t);
				q.pop();
				if (t->left != NULL)
					q.push(t->left);
				if (t->right != NULL)
					q.push(t->right);
				if(q.empty()) break;
			}
		}
		node<T>* findElement(const T& target)
		{
			arrqueue<node<T>*> q;
			node<T>** arr = new node<T>*[treesize];
			int i = 0;
			node<T> *t = root;
			q.push(t);
			while (t != NULL)
			{
				arr[i] = q.top();
				q.pop();
				if (arr[i]->left != NULL)
					q.push(arr[i]->left);
				if (arr[i]->right != NULL)
					q.push(arr[i]->right);
				i++;
				if(q.empty()) break;
			}
			for(int i=0; i<treesize; i++)
			{
				if(arr[i]->element==target)
				{
					node<T>* _return = arr[i];
					delete[] arr;
					return _return;
				}
			}
		}
		node<T>* findElementV2(const T& target)
		{
			node<T>*t = root;
			if(t->element==target)	return t;
			if (t != NULL)
			{
				if(t->element==target)	return t;
				preOrder(t->left);
				if(t->element==target)	return t;
				preOrder(t->right);
				if(t->element==target)	return t;
			}
		}
		node<T>* findElementV3(const T& target)
		{
			arrqueue<node<T>*> q;
			node<T> *t = root;
			q.push(t);
			while (t != NULL)
			{
				t = q.top();
				if(t->element==target)	return t;
				q.pop();
				if (t->left != NULL)
					q.push(t->left);
				if (t->right != NULL)
					q.push(t->right);
				if(q.empty()) break;
			}
		}

		////////////////////////////////////////////
		void preOrderOutput()
		{
			preOrder(output);
			cout << endl;
		}
		void inOrderOutput()
		{
			inOrder(output);
			cout << endl;
		}
		void postOrderOutput()
		{
			postOrder(output);
			cout << endl;
		}
		void levelOrderOutput()
		{
			levelOrderV2(output);
			cout << endl;
		}
		void levelOrderOutputV2()
		{
			arrqueue<node<T>*> q;
			node<T> *t = root;
			q.push(t);
			while (t != NULL)
			{
				t = q.top();
				cout << t->element << ' ';
				q.pop();
				if (t->left != NULL)
					q.push(t->left);
				if (t->right != NULL)
					q.push(t->right);
				if(q.empty()) break;
			}
			cout << endl;
		}
		////////////////////////////////////////////
		void levelOrderCountnodes()
		{
			levelOrder(countnodes);
		}   //just for the exam.
		////////////////////////////////////////////
		void erase()
		{
			postOrder(dispose);
			root = NULL;
			treesize = 0;
		}
		int height() const
		{
			return height(root);
		}
		T rootvalue()
		{
			return root->element;
		}
		////////////////////////////////////////////
		void everyNum(int n)
		{
			int *p = new int[n];
			for (int i = 0; i < n; ++i)
				p[i] = 0;
			countnodes(root, p);
			for (int i = 0; i < n; ++i)
				cout << p[i] << " ";
		}

		int countnodes(node<T>*it, int *p)
		{
			if (it == NULL)
				return 0;
			else
			{
				int m=countnodes(it->left, p);
				int n=countnodes(it->right, p);
				return p[it->element - 1] = m + n + 1;
			}
		}
		void everyHeight(int n)
		{
			int *p = new int[n];
			height(root, p);
			for (int i = 0; i < n; ++i)
				cout << p[i] << " ";
			delete[]p;
		}
		int height(node<T> *it,int *p)
		{
			if (it == NULL)
				return 0;
			else
			{
				int m=height(it->left,p);
				int n=height(it->right,p);
				return p[it->element-1]=(m > n) ? m + 1 : n + 1;
			}
		}

};

//static varibles initialization!
template<typename T>
int chainbintree<T>::count=0;
template<typename T>
void (*chainbintree<T>::option)(node<T> *) = NULL;
////////////////////////////////////////////////

int main()
{
	int num_line = 0;
	cin >> num_line;
	int** in = new int*[num_line];
	for(int i=0; i<num_line; i++)
		in[i] = new int[2];
	for(int i=0; i<num_line; i++)
		cin >> in[i][0] >> in[i][1];
	//input formation.
	//memory is alright by now.
	chainbintree<int> zjs(1);
	node<int>* t = zjs.findElementV3(1);
	arrqueue<node<int>*> q;
	q.push(t);
	while (t != NULL)
	{
		t = q.top();
		int line = t->element - 1;
		if(in[line][0]!=-1)
		{
			t->left = new node<int>(in[line][0]);
			zjs.treesize++;
		}

		else t->left = NULL;
		if(in[line][1]!=-1)
		{
			t->right = new node<int>(in[line][1]);
			zjs.treesize++;
		}
		else t->right = NULL;
		q.pop();
		if (t->left != NULL)
			q.push(t->left);
		if (t->right != NULL)
			q.push(t->right);
		if(q.empty()) break;
	}
	//
	zjs.levelOrderOutputV2();
	//
//	int*out = new int[zjs.treesize];
//	t = zjs.root;
//	q.push(t);
//	while (t != NULL)
//	{
//		t = q.top();
//		int line = t->element - 1;
//		zjs.countnodes(t);
//		out[line] = chainbintree<int>::count;
//		q.pop();
//		if (t->left != NULL)
//			q.push(t->left);
//		if (t->right != NULL)
//			q.push(t->right);
//		if(q.empty()) break;
//	}
//	for(int i=0; i<zjs.treesize; i++)
//	{
//		cout << out[i] << ' ';
//	}
//	//
//	cout << endl;
//	//
//	t = zjs.root;
//	q.push(t);
//	while (t != NULL)
//	{
//		t = q.top();
//		int line = t->element - 1;
//		out[line] = zjs.height(t);
//		q.pop();
//		if (t->left != NULL)
//			q.push(t->left);
//		if (t->right != NULL)
//			q.push(t->right);
//		if(q.empty()) break;
//	}
//	for(int i=0; i<zjs.treesize; i++)
//	{
//		cout << out[i] << ' ';
//	}
	zjs.everyNum(zjs.treesize);
	cout << endl;
	zjs.everyHeight(zjs.treesize);
	//
	return 0;
}
