//#include "queue"
//#include "stack"
//#include "vector"
//#include<iostream>
//using namespace std;
//
//#include<iostream>
//#include <string>
//using namespace std;
//class BiNode {
//public:
//	char data;
//	struct BiNode* lchild, * rchild;
//};
//
//class BiTree {
//private:
//	BiNode* root;
//	int height;
//	void pre_Order (BiNode* t);
//	void in_Order (BiNode* t);
//	void post_Order (BiNode* t);
//	BiNode* create (string& s, int& pos);
//	void get_Height (BiNode* t, int h);
//public:
//	BiTree () { root = NULL; height = 0; }
//	///����ǰ��������д���������
//	void createBiTree (string s);
//	///ǰ�����������
//	void preOrder ();
//	///�������������
//	void inOrder ();
//	///�������������(�ݹ鷽��)
//	void postOrder ();
//	///�������������(ʹ��ջ�ķǵݹ鷽��)
//	void postOrder1 ();
//	///�������������
//	void levelOrder ();
//	///�����ĸ߶�
//	int getHeight ();
//	///�������ڵ����󹫹�����
//	void ancestor (char A, char B);
//};
//
//
//BiNode* BiTree::create (string& s, int& pos) {
//	++pos;
//	BiNode* t;
//	if ((unsigned)pos >= s.size ())
//		return NULL;
//	else {
//		if (s[pos] == '#')
//			t = NULL;
//		else {
//			t = new BiNode;
//			t->data = s[pos];
//			t->lchild = create (s, pos);
//			t->rchild = create (s, pos);
//		}
//		return t;
//	}
//}
/////����ǰ��������д���������
//void BiTree::createBiTree (string s) {
//	int pos = -1;
//	root = create (s, pos);
//}
/////ǰ�����������
//void BiTree::preOrder () {
//	pre_Order (root);
//	cout << endl;
//}
//void BiTree::pre_Order (BiNode* t) {
//	if (t != NULL) {
//		cout << t->data << ' ';
//		pre_Order (t->lchild);
//		pre_Order (t->rchild);
//	}
//}
/////�������������
//void BiTree::inOrder () {
//	in_Order (root);
//	cout << endl;
//}
//void BiTree::in_Order (BiNode* t) {
//	if (t != NULL) {
//		in_Order (t->lchild);
//		cout << t->data << ' ';
//		in_Order (t->rchild);
//	}
//}
/////�������������(�ݹ鷽��)
//void BiTree::postOrder () {
//	post_Order (root);
//	cout << endl;
//}
//void BiTree::post_Order (BiNode* t) {
//	if (t != NULL) {
//		post_Order (t->lchild);
//		post_Order (t->rchild);
//		cout << t->data << ' ';
//	}
//}
/////�������������(ʹ��ջ�ķǵݹ鷽��)
/////���������ȱ������������ٱ��������������������ڵ�
/////����һ���ڵ���ԣ���һֱ����������ڵ�
/////Ȼ����r��¼�������Ƿ���������û�б����������������
//void BiTree::postOrder1 () {
//	///p��ʾ��ǰ���ڵ�ָ�룬
//	///r��ʾ������ʵ����ڵ�ָ��
//	BiNode* p, * r;
//	r = NULL;
//	p = root;
//	stack<BiNode*> my_stack;
//	while (p != NULL || !my_stack.empty ()) {
//		if (p) {
//			///һֱ�ߵ����������
//			my_stack.push (p);
//			p = p->lchild;
//		} else {
//			p = my_stack.top ();
//			///���������û�б���������������
//			if (p->rchild != NULL && p->rchild != r) {
//				p = p->rchild;
//				my_stack.push (p);
//				///ע��������Ҫ����ת����Ϊ���������ת��
//				///��������������ڵ�����
//				p = p->lchild;
//
//			}
//			///����������ڵ�
//			else {
//				p = my_stack.top ();
//				my_stack.pop ();
//				cout << p->data << ' ';
//				///������������Ľڵ�
//				r = p;
//				///��������Ľڵ���ΪNULL��������һ���ڵ�ı���
//				p = NULL;
//			}
//		}
//	}
//	cout << endl;
//}
/////ʹ�ö��н��в������������
//void BiTree::levelOrder () {
//	if (root == NULL)
//		return;
//	queue<BiNode*> q;
//	q.push (root);
//	while (!q.empty ()) {
//		BiNode* t;
//		t = q.front ();
//		q.pop ();
//		cout << t->data << ' ';
//		if (t->lchild != NULL)
//			q.push (t->lchild);
//		if (t->rchild != NULL)
//			q.push (t->rchild);
//	}
//	cout << endl;
//}
/////�����ĸ߶�
//int BiTree::getHeight () {
//	get_Height (root, 0);
//	return height;
//}
//void BiTree::get_Height (BiNode* t, int h) {
//	if (t != NULL) {
//		++h;
//		if (h > height)
//			height = h;
//		get_Height (t->lchild, h);
//		get_Height (t->rchild, h);
//	}
//}

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;

const int MAX = 1000000000;
typedef struct BSTNode {
	int data;   //����
	int num;  //����
	BSTNode* left;
	BSTNode* right;
}Node, * pointer;

//  const���εĺ��� �������ڲ��ܶԳ�Ա�������κθĶ�
class BinarySearchTree {
private:
	pointer Root;
	pointer Empty (pointer node) {
		if (node) {
			Empty (node->left);
			Empty (node->right);
			free (node);
		}
		return NULL;
	}
	pointer Search (pointer node, int key) const {
		if (node == NULL)
			return NULL;
		if (key < node->data)
			return Search (node->left, key);
		else if (key > node->data)
			return Search (node->right, key);
		else
			return node;
	} //�ڲ�����
	pointer SearchMin (pointer node) const {
		if (node == NULL)
			return NULL;
		else if (node->left == NULL)
			return node;
		else
			return SearchMin (node->left);
	}//�ڲ�����
	pointer Insert (pointer node, int key) {
		if (node == NULL) {
			node = (pointer)malloc (sizeof (Node));
			if (node == NULL) {
				perror ("Allocate dynamic memory");   //����������
				return node;
			}
			node->data = key;
			node->num = 1;
			node->left = node->right = NULL;

			if (Root == NULL)   //��һ�������� �����ָ�������һ����������������ı�ԭָ��ĵ�ַ��ֵ�����ǿ��ܻ�ı�ԭָ����ָ���ڴ�������
				Root = node;
		} else if (key < node->data)
			node->left = Insert (node->left, key);
		else if (key > node->data)
			node->right = Insert (node->right, key);
		else
			node->num++;
		return node;
	} //�ڲ�����
	pointer Delete (pointer node, int key); //�ڲ�ɾ��
	pointer DeleteMin (pointer node);   //ɾ����Сֵ
	void PreOrder (pointer node) const;  //����
	void InOrder (pointer node) const;  //����
	void PostOrder (pointer node) const; //����
	void PrintNode (pointer node) const; //����ڵ���Ϣ

public:
	BinarySearchTree () {
		Root = NULL;
	}
	~BinarySearchTree () //���������ڶ����������������� ���ں���fun�ڴ���node����A�����͵���
	{
		Empty (Root);
	}

	bool Search (int key) const {
		if (Search (Root, key))
			return true;
		return false;
	}     //�ⲿ����
	int SearchMin () const {
		pointer T = Root;
		if (T != NULL)
			while (T->left != NULL)
				T = T->left;
		if (T)
			return T->data;
		else
			return MAX;
	}   //������Сֵ
	bool Insert (int key) {
		if (Insert (Root, key))
			return true;
		return false;
	}
	//�ⲿ����
	bool Delete (int key);   //ɾ��
	void PreOrder () const;  //����
	void InOrder () const;  //����
	void PostOrder () const; //����
	void LeverOrder () const {
		if (Root == NULL) {
			printf ("Empty Tree\n");
			return;
		}

		printf ("LevelOrder: ");
		pointer temp;
		queue<pointer> q;
		q.push (Root);
		while (!q.empty ()) {
			temp = q.front ();
			q.pop ();
			PrintNode (temp);
			if (temp->left)
				q.push (temp->left);
			if (temp->right)
				q.push (temp->right);
		}
		printf ("\n");
	}
};

//ɾ��
bool BinarySearchTree::Delete (int key) {
	if (Delete (Root, key))
		return true;
	return false;
}

pointer BinarySearchTree::DeleteMin (pointer node) {
	pointer current = node;
	pointer parent = node;
	node = node->right;
	if (node->left == NULL)            //���������û�������� ��ô��ֱ�����
	{
		current->data = node->data;
		current->right = node->right;      //����������Ϊ��Ҳ����ֱ��NULL
	} else {
		while (node->left != NULL)            //�ҵ�����������С����
		{
			parent = node;
			node = node->left;
		}
		current->data = node->data;
		parent->left = node->right;
	}
	free (node);
	return current;
}

pointer BinarySearchTree::Delete (pointer node, int key) {
	if (node == NULL)
		return NULL;
	else if (key < node->data)
		node->left = Delete (node->left, key);
	else if (key > node->data)
		node->right = Delete (node->right, key);
	else if (node->left && node->right)           //2�����Ӷ���
	{
		//ֱ���ڲ��ҵ�ʱ���ɾ����
		node = DeleteMin (node);
	} else            //һ������0������
	{
		pointer temp = node;
		if (node->left == NULL)
			node = node->right;
		else if (node->right == NULL)
			node = node->left;
		if (temp->data == Root->data)          //�����ɾ���� RootҪ�ض���һ��
			Root = node;
		free (temp);
	}
	return node;
}

//����
void BinarySearchTree::PrintNode (pointer node) const {
	printf ("%d ", node->data);
	//printf("data: %d num: %d\n", node->data, node->num);
}

//����
void BinarySearchTree::PreOrder () const {
	if (Root) {
		printf ("PreOrder: ");
		PreOrder (Root);
		printf ("\n");
	} else
		printf ("Empty Tree\n");
}

void BinarySearchTree::PreOrder (pointer node) const {
	if (node != NULL) {
		PrintNode (node);
		PreOrder (node->left);
		PreOrder (node->right);
	}
}

//����
void BinarySearchTree::InOrder () const {
	if (Root) {
		printf ("InOrder: ");
		InOrder (Root);
		printf ("\n");
	} else
		printf ("Empty Tree\n");
}

void BinarySearchTree::InOrder (pointer node) const {
	if (node != NULL) {
		InOrder (node->left);
		PrintNode (node);
		InOrder (node->right);
	}
}

//����
void BinarySearchTree::PostOrder () const {
	if (Root) {
		printf ("PostOrder: ");
		PostOrder (Root);
		printf ("\n");
	} else
		printf ("Empty Tree\n");
}

void BinarySearchTree::PostOrder (pointer node) const {
	if (node != NULL) {
		PostOrder (node->left);
		PostOrder (node->right);
		PrintNode (node);
	}
}

//��α��� �ö���
void BinarySearchTree::LeverOrder () const 

#include<iostream>
using namespace std;

int main () {
	BinarySearchTree Tree;
	Tree.Insert (12);
	Tree.Insert (6);
	Tree.Insert (2);
	Tree.Insert (10);
	Tree.Insert (11);
	Tree.Insert (9);
	Tree.Insert (7);
	Tree.Insert (8);
	Tree.Insert (14);
	Tree.Delete (6);
	Tree.Delete (2);
	Tree.PreOrder ();
	Tree.InOrder ();
	Tree.PostOrder ();
	Tree.LeverOrder ();
	return 0;
}