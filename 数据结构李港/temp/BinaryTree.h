#pragma once
#include "LinkedQueue.h"
#include <iostream>

using namespace std;

template <class T>
class BinaryTree;

template <class T>
class BinaryTreeNode
{
	friend BinaryTree<T>;
public:
	BinaryTreeNode(void) { LeftChild = RightChild = 0; }
	BinaryTreeNode(const int& e) { data = e; LeftChild = RightChild = 0; }
	BinaryTreeNode(const int& e, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r) { data = e; LeftChild = l; RightChild = r; }
	~BinaryTreeNode() {};
private:
	T data;
	BinaryTreeNode<T>* LeftChild, * RightChild;
};

template <class T>
class BinaryTree
{
public:
	BinaryTree(void) { root = 0; }
	~BinaryTree();
	bool IsEmpty()const { return ((root) ? false : true); }
	bool Root(int& t)const;
	void MakeTree(const int& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void BreakTree(int& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void PreOrder(void (*Visit)(BinaryTreeNode<T>* u)) { PreOrder(Visit, root); }
	void InOrder(void (*Visit)(BinaryTreeNode<T>* u)) { InOrder(Visit, root); }
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u)) { PostOrder(Visit, root); }
	void LevelOrder(void(*Visit)(BinaryTreeNode<T>* u));
	int getHight() const { return Height(root); }
	void PreOutput() { PreOrder(Output, root); cout << endl; }
	void InOutput() { InOrder(Output, root); cout << endl; }
	void PostOutput() { PostOrder(Output, root); cout << endl; }
	void LevelOutput() { LevelOrder(Output); cout << endl; }
	BinaryTree<T>& Delete(const T& k, T e);
	int GetLR(T* Pre, T* In, int i, T data);
	void AddTreeNode(BinaryTreeNode<T>** root, T* PreOrder, T* InOrder, int i);
	void PreInMakeTree(T* PreOrder, T* InOrder, int length)
	{
		for (int i = 0; i < length; i++)
			AddTreeNode(&root, PreOrder, InOrder, i);
	}
private:
	BinaryTreeNode<T>* root;
	void PreOrder(void (*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	void InOrder(void (*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	int Height(BinaryTreeNode<T>* t)const;
	static void Output(BinaryTreeNode<T>* t) { cout << t->data << ""; }
};

template <class T>
BinaryTree<T>::~BinaryTree()
{
}

template <class T>
bool BinaryTree<T>::Root(int& x)const
{
	if (root)
	{
		x = root->data;
		return true;
	}
	else
		return false;
}

template <class T>
void BinaryTree<T>::MakeTree(const int& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	root = new BinaryTreeNode<T>(element, left.root, right.root);
	left.root = right.root = 0;
}

template <class T>
void BinaryTree<T>::BreakTree(int& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	if (!root)
		throw "badiput";
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;
	delete root;
	root = 0;
}

template <class T>
void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		Visit(t);
		PreOrder(Visit, t->LeftChild);
		PreOrder(Visit, t->RightChild);
	}
}

template <class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		InOrder(Visit, t->LeftChild);
		Visit(t);
		InOrder(Visit, t->RightChild);
	}
}

template <class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		PostOrder(Visit, t->LeftChild);
		PostOrder(Visit, t->RightChild);
		Visit(t);
	}
}

template <class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>* u))
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T>* t;
	t = root;
	while (t)
	{
		Visit(t);
		if (t->LeftChild)
			Q.Add(t->LeftChild);
		if (t->RightChild)
			Q.Add(t->RightChild);
		try
		{
			Q.Delele(t);
		}
		catch (char* ch)
		{
			return;
		}
	}
}

template <class T>
int BinaryTree<T>::Height(BinaryTreeNode<T>* t)const
{
	if (!t)
		return 0;
	int hl = Height(t->LeftChild);
	int hr = Height(t->RightChild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

template<class T>
BinaryTree<T>& BinaryTree<T>::Delete(const T& k, T e)
{
	BinaryTreeNode<T>* p = root, * pp = 0;
	while (p && p->data != k)
	{
		pp = p;
		if (k < p->data) p = p->LeftChild;
		else  p = p->RightChild;
	}
	if (!p) throw "wrong";
	e = p->data;

	//将删除元素左子树的中最大元素放到p
	if (p->LeftChild && p->RightChild)
	{
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}

		p->data = s->data;
		p = s;
		pp = ps;
	}

	//p只有一个子树的时候
	BinaryTreeNode<T>* c;
	if (p->LeftChild) c = p->LeftChild;
	else c = p->RightChild;

	if (p == root) root = c;
	else
	{
		if (p == pp->LeftChild) pp->LeftChild = c;
		else pp->RightChild = c;
	}
	delete p;

	return *this;
}

template <class T>
int BinaryTree<T>::GetLR(T* Pre, T* In, int i, T data)
{
	int j = 0, k = 0;
	while (Pre[i] != In[j])
		j++;
	while (data != In[k])
		k++;
	if (j < k)
		return 1;
	else
		return 0;
}

template <class T>
void BinaryTree<T>::AddTreeNode(BinaryTreeNode<T>** root, T* PreOrder, T* InOrder, int i)
{
	if (NULL == *root)
	{
		*root = new BinaryTreeNode<T>(PreOrder[i]);
		/*cout << root->data << endl ;*/
	}
	else
		if (GetLR(PreOrder, InOrder, i, (**root).data))
			AddTreeNode(&(**root).LeftChild, PreOrder, InOrder, i);
		else
			AddTreeNode(&(**root).RightChild, PreOrder, InOrder, i);
}