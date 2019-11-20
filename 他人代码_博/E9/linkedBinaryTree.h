
#ifndef chainbintree_
#define chainbintree_

using namespace std;
#include <iostream>

#include "booster.h"

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

template<class T>
class bintree
{
public:
    virtual ~bintree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*option) (T *)) = 0;	//����ָ���Լ��������͵��й�֪ʶ��12��
    virtual void inOrder(void (*option) (T *)) = 0;		//������ָ������Ϊoption�Ա�ʾҪ���еĲ�������.
    virtual void postOrder(void (*option) (T *)) = 0;
    virtual void levelOrder(void (*option) (T *)) = 0;
};

template<class T>
class chainbintree  //����ʹ����˽�����ڷ�װʽ�����������ڵ㣬�ʲ��ܼ̳�bintree.
{
private:
	struct node     //˽�����ڷ�װʽ�����������ڵ�
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
			:element(_element)  //��������Ϊ�˷�ֹT��һ����δ����������Ⱥŵ��Զ�������
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
protected:
    node *root;
    int treesize;   //size�Ǻ���
                    //����ǰ��Ҫ���޶��ʻ�
public:
    chainbintree()
    {
        root = NULL;
        treesize = 0;
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
	T* rootTlement() const
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
	}
    chainbintree<T>& removeLeftSubtree()
	{
	    if (treesize == 0) return;  //�˴�Ӧ�ü��쳣����
	    chainbintree<T> leftSubtree;
	    leftSubtree.root = root->left;
	    count = 0;  //count���������������ã����Ǳ�����countNodes������ú�����������.
	    leftSubtree.treesize = countNodes(leftSubtree.root);
	    root->left = NULL;
	    treesize -= leftSubtree.treesize;
	    return leftSubtree;
		//�����и�����ĵط���leftSubtree�Ǻ����ڴ������࣬����return��һ���ᱻ��������leftSubtree.root = root->left����������ִ��ʱ���Զ�����������delete����.
	}
    chainbintree<T>& removeRightSubtree()
	{
	    if (treesize == 0) return;  //�쳣����
	    chainbintree<T> rightSubtree;
	    rightSubtree.root = root->right;
	    count = 0;
	    rightSubtree.treesize = countNodes(rightSubtree.root);
	    root->right = NULL;
	    treesize -= rightSubtree.treesize;
	    return rightSubtree;
	}
    void preOrder(void(*_option)(node*))
    {
        option = _option;
        preOrder(root);
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
	    node *t = root;
	    while (t != NULL)
	    {
	        _option(t);

	        if (t->left != NULL)
	            q.push(t->left);
	        if (t->right != NULL)
	            q.push(t->right);
//	        try
//	        {
//	            t = q.front();
//	        }
//	        catch (queueEmpty)
//	        {
//	            return;
//	        }
			t = q.front();
			if(q.empty()) return;   //׾��ģ��
			//
	        q.pop();
	    }
	}
	//
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
protected:
    static void (*option)(node *);
    static int count;
    //
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
};
// the following should work but gives an internal compiler error
// template <class T> void (*chainbintree<T>::option)(node*);
// so the explicit declarations that follow are used for our purpose instead
//void (*chainbintree<int>::option)(node<int> *);
//void (*chainbintree<booster>::option)(node<booster> *);
//void (*chainbintree<pair<int, int> >::option)(node<pair<int, int> > *);
//void (*chainbintree<pair<const int, char> >::option)(node<pair<const int, char> > *);
//void (*chainbintree<pair<const int, int> >::option)(node<pair<const int, int> > *);     //��ȫû����

#endif
