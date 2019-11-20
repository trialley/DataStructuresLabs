#pragma once
#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "arrayQueue.h"

/*
接下来要做的事情是什么：
首先要写出层次遍历
然后开始写构造函数和析构函数
构造函数需要干什么？ 还是说像链表一样，仅仅对于初始的根节点附一个初值
然后写一个maketree函数
析构函数进行后序遍历visit是删除
所以还是先写一个disposal函数然后visit=disposal
对于disposal：
disposal是
构造函数可以如何进行设计
首先能够支持创建一个空树
支持创建有层次变量数组给出的树
支持创建满二叉树和完全二叉树
我还想搞一个图形化输出 怎么搞呢 就使用层次遍历的方法 再说吧有点麻烦

*/
template<class T>
class linkedBinaryTree :
	public binaryTree<T>
{
public:
	linkedBinaryTree() {
		root = NULL;
		Treesize = 0;

	}//madetree  可以把两个树进行合并  这个函数也要写  初始化创建一个树 现在的初始化应该支持通过一个序列生成一个树
	linkedBinaryTree(const T* element)//给出的层次遍历后形成的树 但是有一个问题这样形成的树不唯一 除非还有一种办法就是空位，但是好像还是有点复杂度
	{

	}//这些形成树的方法都有些奇怪不妨先试一下吧
	~linkedBinaryTree() {}//这个要写 
	void maketree(const T& element, binaryTree<T>& leftchild, binaryTree<T>& rightchild) {
		root = new binaryTreeNode<T>(element, leftchild.root, rightchild.root);
		Treesize = leftchild.size() + rightchild.size() + 1;
		//阻止访问旧树？为什么要阻止？
		leftchild.root = NULL;
		rightchild.root = NULL;
		leftchild.Treesize = 0;
		rightchild.Treesize = 0;
	}//可以直接通过这个函数来创建树
	bool empty()const {
		return Treesize == 0;
	}
	int size()const {
		return Treesize;
	}
	void preOutput() {
		preOrder(&linkedBinaryTree<T>::output);
		cout << endl;
	}
	void inOutput() {
		inOrder(&linkedBinaryTree<T>::output);
		cout << endl;
	}
	void postOutput() {
		postOrder(&linkedBinaryTree<T>::output);
		cout << endl;
	}
	void levelOutput() {
		levelOrder(&linkedBinaryTree<T>::output);
		cout << endl;
	}
	void preOrder(void(*thevisit)(binaryTreeNode<T>*)) {
		visit = thevisit;
		preOrder(root);
	}
	
	void inOrder(void(*thevisit)(binaryTreeNode<T>*)) {
		visit = thevisit;//Q:是否存在一些问题，不能静态的变量多次使用的时候是否会存在一些问题
		inOrder(root);
	}
	void postOrder(void(*thevisit)(binaryTreeNode<T>*)) {
		visit = thevisit;
		postOrder(root);
	}
	void levelOrder(void(*thevisit)(binaryTreeNode<T>*)) {
		visit = thevisit;
		levelOrder(root);
	}
	int height(binaryTreeNode<T>*t) {
		if (t != NULL) {
			int height_l = height(t->leftchild);
			int height_r = height(t->rightchild);
			if (height_l >= height_r)
				return height_l + 1;
			return height_r + 1;
		}
		return 0;
	}
	void madeTree_bypreandin(const T*pre, const T*in, int pre_s, int pre_e, int in_s, int in_e) {
		madeTree_bypreandin(pre, in, pre_s, pre_e, in_s, in_e, root);
	}
	void madeTree_bypreandin(const T* pre, const T* in, int pre_s, int pre_e, int in_s, int in_e, binaryTreeNode<T>* &t) {
		if (pre_s > pre_e || in_s > in_e) {
			return;
		}
		T middle = pre[pre_s];
		t = new binaryTreeNode<T>(middle);//在这个地方出现异常 如何解决这个异常？
		int pos = 0;
		for (int i = in_s; i <= in_e; i++) {
			if (in[i] == middle)
			{
				pos = i;
			}
		}
		madeTree_bypreandin(pre, in, pre_s + 1, pre_s + pos - in_s, in_s, pos - 1, t->leftChild);
		madeTree_bypreandin(pre, in, pre_s + 1 + pos - in_s, pre_e, pos + 1, in_e, t->rightChild);
	}//还是一个原则所有都是从0开始的
	void erase() {
		postOrder(linkedBinaryTree<T>::disposal);
		root = NULL;
		Treesize = 0;
	}

private:

	int Treesize = 0;
	binaryTreeNode<T>*root;
	static arrayQueue<binaryTreeNode<T>*> childqueue;
	static void(*visit)(binaryTreeNode<T>*);//为什么一定要作为静态的成员变量，有什么用处？如果作为非静态的成员变量的话好像也没什么问题
	static void disposal(binaryTreeNode<T>*t) {
		delete t;//这样不会出现问题吗？
	}
	static void output(binaryTreeNode<T>*t) {//为什么这样写是不行的 一定要把它作为static函数呢？
		cout << t->element << ' ';
	}
	static void preOrder(binaryTreeNode<T>*t) {
		if (t != NULL) {
			linkedBinaryTree<T>::visit(t);
			preOrder(t->leftChild);
			preOrder(t->rightChild);
		}
	}
	static void inOrder(binaryTreeNode<T>*t) {
		if (t != NULL) {
			inOrder(t->leftChild);
			linkedBinaryTree<T>::visit(t);
			inOrder(t->rightChild);
		}
	}
	static void postOrder(binaryTreeNode<T>*t) {
		if (t != NULL) {
			postOrder(t->leftChild);
			postOrder(t->rightChild);
			linkedBinaryTree<T>::visit(t);
		}
	}
	static void levelOrder(binaryTreeNode<T>*t) {
		if (t != NULL) {
			linkedBinaryTree<T>::visit(t);
			if (t->leftChild != NULL)
				childqueue.push(t->leftChild);
			if (t->rightChild != NULL)
				childqueue.push(t->rightChild);
			try {
				t = childqueue.front();
			}
			catch (queueEmpty c) {
				//c.outputMessage();
				return;
			}
			childqueue.pop();
			levelOrder(t);
		}
	}


};
void(*linkedBinaryTree<char>::visit)(binaryTreeNode<char>*);
void(*linkedBinaryTree<pair<int, int> >::visit)(binaryTreeNode<pair<int, int> >*);
void(*linkedBinaryTree<pair<const int, char> >::visit)(binaryTreeNode<pair<const int, char> >*);
void(*linkedBinaryTree<pair<const int, int> >::visit)(binaryTreeNode<pair<const int, int> >*);
arrayQueue<binaryTreeNode<char>*> linkedBinaryTree<char>::childqueue;
