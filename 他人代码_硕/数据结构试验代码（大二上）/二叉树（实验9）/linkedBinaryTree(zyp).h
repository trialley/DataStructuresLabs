#pragma once
#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "arrayQueue.h"

/*
������Ҫ����������ʲô��
����Ҫд����α���
Ȼ��ʼд���캯������������
���캯����Ҫ��ʲô�� ����˵������һ�����������ڳ�ʼ�ĸ��ڵ㸽һ����ֵ
Ȼ��дһ��maketree����
�����������к������visit��ɾ��
���Ի�����дһ��disposal����Ȼ��visit=disposal
����disposal��
disposal��
���캯��������ν������
�����ܹ�֧�ִ���һ������
֧�ִ����в�α��������������
֧�ִ���������������ȫ������
�һ����һ��ͼ�λ���� ��ô���� ��ʹ�ò�α����ķ��� ��˵���е��鷳

*/
template<class T>
class linkedBinaryTree :
	public binaryTree<T>
{
public:
	linkedBinaryTree() {
		root = NULL;
		Treesize = 0;

	}//madetree  ���԰����������кϲ�  �������ҲҪд  ��ʼ������һ���� ���ڵĳ�ʼ��Ӧ��֧��ͨ��һ����������һ����
	linkedBinaryTree(const T* element)//�����Ĳ�α������γɵ��� ������һ�����������γɵ�����Ψһ ���ǻ���һ�ְ취���ǿ�λ�����Ǻ������е㸴�Ӷ�
	{

	}//��Щ�γ����ķ�������Щ��ֲ�������һ�°�
	~linkedBinaryTree() {}//���Ҫд 
	void maketree(const T& element, binaryTree<T>& leftchild, binaryTree<T>& rightchild) {
		root = new binaryTreeNode<T>(element, leftchild.root, rightchild.root);
		Treesize = leftchild.size() + rightchild.size() + 1;
		//��ֹ���ʾ�����ΪʲôҪ��ֹ��
		leftchild.root = NULL;
		rightchild.root = NULL;
		leftchild.Treesize = 0;
		rightchild.Treesize = 0;
	}//����ֱ��ͨ�����������������
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
		visit = thevisit;//Q:�Ƿ����һЩ���⣬���ܾ�̬�ı������ʹ�õ�ʱ���Ƿ�����һЩ����
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
		t = new binaryTreeNode<T>(middle);//������ط������쳣 ��ν������쳣��
		int pos = 0;
		for (int i = in_s; i <= in_e; i++) {
			if (in[i] == middle)
			{
				pos = i;
			}
		}
		madeTree_bypreandin(pre, in, pre_s + 1, pre_s + pos - in_s, in_s, pos - 1, t->leftChild);
		madeTree_bypreandin(pre, in, pre_s + 1 + pos - in_s, pre_e, pos + 1, in_e, t->rightChild);
	}//����һ��ԭ�����ж��Ǵ�0��ʼ��
	void erase() {
		postOrder(linkedBinaryTree<T>::disposal);
		root = NULL;
		Treesize = 0;
	}

private:

	int Treesize = 0;
	binaryTreeNode<T>*root;
	static arrayQueue<binaryTreeNode<T>*> childqueue;
	static void(*visit)(binaryTreeNode<T>*);//Ϊʲôһ��Ҫ��Ϊ��̬�ĳ�Ա��������ʲô�ô��������Ϊ�Ǿ�̬�ĳ�Ա�����Ļ�����Ҳûʲô����
	static void disposal(binaryTreeNode<T>*t) {
		delete t;//�����������������
	}
	static void output(binaryTreeNode<T>*t) {//Ϊʲô����д�ǲ��е� һ��Ҫ������Ϊstatic�����أ�
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
