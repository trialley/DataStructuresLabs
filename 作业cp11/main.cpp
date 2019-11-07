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
//	///按照前序遍历序列创建二叉树
//	void createBiTree (string s);
//	///前序遍历二叉树
//	void preOrder ();
//	///中序遍历二叉树
//	void inOrder ();
//	///后序遍历二叉树(递归方法)
//	void postOrder ();
//	///后序遍历二叉树(使用栈的非递归方法)
//	void postOrder1 ();
//	///层序遍历二叉树
//	void levelOrder ();
//	///求树的高度
//	int getHeight ();
//	///求两个节点的最大公共祖先
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
/////按照前序遍历序列创建二叉树
//void BiTree::createBiTree (string s) {
//	int pos = -1;
//	root = create (s, pos);
//}
/////前序遍历二叉树
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
/////中序遍历二叉树
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
/////后序遍历二叉树(递归方法)
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
/////后序遍历二叉树(使用栈的非递归方法)
/////后续遍历先遍历左子树，再遍历右子树，最后遍历根节点
/////对于一个节点而言，先一直遍历到最左节点
/////然后用r记录右子树是否遍历，如果没有遍历，则遍历右子树
//void BiTree::postOrder1 () {
//	///p表示当前树节点指针，
//	///r表示最近访问的树节点指针
//	BiNode* p, * r;
//	r = NULL;
//	p = root;
//	stack<BiNode*> my_stack;
//	while (p != NULL || !my_stack.empty ()) {
//		if (p) {
//			///一直走到树的最左边
//			my_stack.push (p);
//			p = p->lchild;
//		} else {
//			p = my_stack.top ();
//			///如果右子树没有遍历，遍历右子树
//			if (p->rchild != NULL && p->rchild != r) {
//				p = p->rchild;
//				my_stack.push (p);
//				///注意这里需要向左转，因为如果不向左转，
//				///将会遍历右子树节点两边
//				p = p->lchild;
//
//			}
//			///否则遍历根节点
//			else {
//				p = my_stack.top ();
//				my_stack.pop ();
//				cout << p->data << ' ';
//				///更新最近遍历的节点
//				r = p;
//				///将遍历后的节点设为NULL，进行下一个节点的遍历
//				p = NULL;
//			}
//		}
//	}
//	cout << endl;
//}
/////使用队列进行层序遍历二叉树
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
/////求树的高度
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
	int data;   //数据
	int num;  //数量
	BSTNode* left;
	BSTNode* right;
}Node, * pointer;

//  const修饰的函数 函数体内不能对成员数据做任何改动
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
	} //内部查找
	pointer SearchMin (pointer node) const {
		if (node == NULL)
			return NULL;
		else if (node->left == NULL)
			return node;
		else
			return SearchMin (node->left);
	}//内部查找
	pointer Insert (pointer node, int key) {
		if (node == NULL) {
			node = (pointer)malloc (sizeof (Node));
			if (node == NULL) {
				perror ("Allocate dynamic memory");   //错误输出语句
				return node;
			}
			node->data = key;
			node->num = 1;
			node->left = node->right = NULL;

			if (Root == NULL)   //这一步必须有 传入的指针仅仅是一个拷贝，方法不会改变原指针的地址、值，但是可能会改变原指针所指向内存块的数据
				Root = node;
		} else if (key < node->data)
			node->left = Insert (node->left, key);
		else if (key > node->data)
			node->right = Insert (node->right, key);
		else
			node->num++;
		return node;
	} //内部插入
	pointer Delete (pointer node, int key); //内部删除
	pointer DeleteMin (pointer node);   //删除最小值
	void PreOrder (pointer node) const;  //先序
	void InOrder (pointer node) const;  //中序
	void PostOrder (pointer node) const; //后序
	void PrintNode (pointer node) const; //输出节点信息

public:
	BinarySearchTree () {
		Root = NULL;
	}
	~BinarySearchTree () //析构函数在对象作用域结束后调用 如在函数fun内创建node，则A结束就调用
	{
		Empty (Root);
	}

	bool Search (int key) const {
		if (Search (Root, key))
			return true;
		return false;
	}     //外部查找
	int SearchMin () const {
		pointer T = Root;
		if (T != NULL)
			while (T->left != NULL)
				T = T->left;
		if (T)
			return T->data;
		else
			return MAX;
	}   //查找最小值
	bool Insert (int key) {
		if (Insert (Root, key))
			return true;
		return false;
	}
	//外部插入
	bool Delete (int key);   //删除
	void PreOrder () const;  //先序
	void InOrder () const;  //中序
	void PostOrder () const; //后序
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

//删除
bool BinarySearchTree::Delete (int key) {
	if (Delete (Root, key))
		return true;
	return false;
}

pointer BinarySearchTree::DeleteMin (pointer node) {
	pointer current = node;
	pointer parent = node;
	node = node->right;
	if (node->left == NULL)            //如果右子树没有左子树 那么它直接替代
	{
		current->data = node->data;
		current->right = node->right;      //就算右子树为空也可以直接NULL
	} else {
		while (node->left != NULL)            //找到右子树的最小子树
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
	else if (node->left && node->right)           //2个儿子都有
	{
		//直接在查找的时候就删除了
		node = DeleteMin (node);
	} else            //一个或者0个儿子
	{
		pointer temp = node;
		if (node->left == NULL)
			node = node->right;
		else if (node->right == NULL)
			node = node->left;
		if (temp->data == Root->data)          //如果是删除根 Root要重定向一下
			Root = node;
		free (temp);
	}
	return node;
}

//遍历
void BinarySearchTree::PrintNode (pointer node) const {
	printf ("%d ", node->data);
	//printf("data: %d num: %d\n", node->data, node->num);
}

//先序
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

//中序
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

//后序
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

//层次遍历 用队列
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