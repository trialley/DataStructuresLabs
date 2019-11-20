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
class chainbintree  
{
private:
	struct node
	{
	    T element;
	    node *left;
		node *right;
	    node()
	    {
	        left = NULL;
			right = NULL;
	    }
	    node(const T &_element)
			:element(_element)  
	    {
	        left = NULL;
			right = NULL;
	    }
	    node(const T &_element, node *_left, node *_right)
	        :element(_element)
	    {
	        left = _left;
	        right = _right;
	    }
	};
public:
    node *root;
    int treesize;   

    static void (*option)(node *);
    static void preOrder(node *t)
	{
	    if (t != NULL)
	    {
	        chainbintree<T>::option(t);
	        preOrder(t->left);
	        preOrder(t->right);
	    }
	}
	static void inOrder(node *t)
	{
	    if (t != NULL)
	    {
	        inOrder(t->left);
	        chainbintree<T>::option(t);
	        inOrder(t->right);
	    }
	}
	static void postOrder(node *t)
	{
	    if (t != NULL)
	    {
	        postOrder(t->left);
	        postOrder(t->right);
	        chainbintree<T>::option(t);
	    }
	}
    static void countNodes(node *t)
	{
        option = addToCount;
        count = 0;
        preOrder(t);
        cout << count << " ";   //this is just for E9,because it needs an output for each element;
    }
    static void dispose(node *t)
    {
        delete t;
    }
    static void output(node *t)
    {
        cout << t->element << ' ';
    }
    static void addToCount(node *t)
    {
        count++;
    }
    static int height(node *t)
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
    chainbintree(const T& _element)
    {
    	root = new node(_element);
		root->left = NULL;
		root->right = NULL;
		treesize = 1;
    }
//    ~chainbintree()
//    {
//        erase();
//    };
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
	void makeTree(const T &element, chainbintree<T> &left, chainbintree<T> &right)
	{
	    root = new node (element, left.root, right.root);
	    treesize = left.treesize + right.treesize + 1;
	    left.root = right.root = NULL;
	    left.treesize = right.treesize = 0;
	}   // I dont think this is a good function.
	//So I code this one below.
	void linktree()
	{
		
	}
    chainbintree<T>& removeLeftSubtree()
	{
	    if (treesize == 0) return;
	    chainbintree<T> leftSubtree;
	    leftSubtree.root = root->left;
	    count = 0;
	    leftSubtree.treesize = countNodes(leftSubtree.root);
	    root->left = NULL;
	    treesize -= leftSubtree.treesize;
	    return leftSubtree;
	}
    chainbintree<T>& removeRightSubtree()
	{
	    if (treesize == 0) return;
	    chainbintree<T> rightSubtree;
	    rightSubtree.root = root->right;
	    count = 0;
	    rightSubtree.treesize = countNodes(rightSubtree.root);
	    root->right = NULL;
	    treesize -= rightSubtree.treesize;
	    return rightSubtree;
	}
	////////////////////////////////////////////
    void preOrder(void(*_option)(node*))
    {
        option = _option;
        preOrder(root);		//default from root node.
    }
    void inOrder(void(*_option)(node*))
    {
        option = _option;
        inOrder(root);
    }
    void postOrder(void(*_option)(node*))
    {
        option = _option;
        postOrder(root);
    }
    void levelOrder(void(*_option)(node*))
	{
	    arrqueue<node*> q;
	    node** arr = new node*[treesize];
	    int i = 0;
	    node *t = root;
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
	    for(int i=0;i<treesize;i++)
	    {
	    	_option(arr[i]);
	    }
	}	//My DIY levelOrder. 
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
        levelOrder(output);
        cout << endl;
    }
    ////////////////////////////////////////////
    void levelOrderCountnodes()
    {
        levelOrder(countNodes);
    }   //just for the exam.	//output num_nodes for each nodes in tree in levelOrder.
    ////////////////////////////////////////////
    void erase()
    {
        postOrder(dispose);
        root = NULL;
        treesize = 0;
    }	//clean up the whole tree;
    int height() const
    {
        return height(root);
    }
    T rootvalue()
    {
    	return root->element;
    }
    ////////////////////////////////////////////
};

//static varibles initialization!
template<typename T>
int chainbintree<T>::count=0;
template<typename T>
void (*chainbintree<T>::option)(node *) = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	chainbintree<int>* zjs = new chainbintree<int>(1);
	chainbintree<int>* p = zjs;
	chainbintree<int>* q = zjs;
	int n = 0;
	scanf("%d",&n);
	chainbintree<int>** arr = new chainbintree<int>*[2*n];
	for(int i=0;i<2*n;i++)
	{
		int temp = 0;
		scanf("%d",&temp);
		arr[i] = new chainbintree<int>(temp);
	}
	zjs->linktree(*arr[0],*arr[1]);
	p = p->root->left;
	int num = p->rootvalue();
	int rank = 2*num-2;
	p->linktree(*arr[rank],*arr[rank+1]);

	p = q;

	p = p->root->right;
	int num = p->rootvalue();
	int rank = 2*num-2;
	p->linktree(*arr[rank],*arr[rank+1]);


	for(int i=0;i<n;i++)
	{
		p->linktree(*arr[i],*arr[i++]);
		p = p->left;
	}
    return 0;
}
