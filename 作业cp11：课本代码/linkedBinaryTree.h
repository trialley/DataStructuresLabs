
// linked binary tree using nodes of type binaryTreeNode
// derives from the abstract class binaryTree

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;


#include <iostream>
#include "binaryTree.h"
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include "booster.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> > {
public:
	linkedBinaryTree () { root = nullptr; treeSize = 0; }
	~linkedBinaryTree () { erase (); };
	bool empty () const { return treeSize == 0; }
	int size () const { return treeSize; }
	E* rootElement () const;
	void makeTree (const E& element,
		linkedBinaryTree<E>&, linkedBinaryTree<E>&);
	linkedBinaryTree<E>& removeLeftSubtree ();
	linkedBinaryTree<E>& removeRightSubtree ();
	void preOrder (void(*theVisit)(binaryTreeNode<E>*)) {
		visit = theVisit; preOrder (root);
	}
	void inOrder (void(*theVisit)(binaryTreeNode<E>*)) {
		visit = theVisit; inOrder (root);
	}
	void postOrder (void(*theVisit)(binaryTreeNode<E>*)) {
		visit = theVisit; postOrder (root);
	}
	void levelOrder (void(*)(binaryTreeNode<E>*)) {// Level-order traversal.
		arrayQueue<binaryTreeNode<E>*> q;
		binaryTreeNode<E>* t = root;
		while (t != nullptr) {
			theVisit (t);  // visit t

			// put t's children on queue
			if (t->left != nullptr)
				q.push (t->left);
			if (t->right != nullptr)
				q.push (t->right);

			// get next node to visit
			try { t = q.front (); } catch (queueEmpty) { return; }
			q.pop ();
		}
	}
	void preOrderOutput () { preOrder (&linkedBinaryTree<E>::output); cout << endl; }
	void inOrderOutput () { inOrder (&linkedBinaryTree<E>::output); cout << endl; }
	void postOrderOutput () { postOrder (&linkedBinaryTree<E>::output); cout << endl; }
	void levelOrderOutput () { levelOrder (&linkedBinaryTree<E>::output); cout << endl; }
	void erase () {
		postOrder (dispose);
		root = nullptr;
		treeSize = 0;
	}
	int height () const { return height (root); }
int getSizeByLevelOrder () {
	arrayQueue<binaryTreeNode<E>*> q;
	binaryTreeNode<E>* t = root;
	int size = 0;
	while (t != nullptr) {
		size++;

		if (t->left != nullptr)
			q.push (t->left);
		if (t->right != nullptr)
			q.push (t->right);

		if (q.empty ()) {
			return size;
		} else {
			t = q.front ();
			q.pop ();
		}
	}
}
protected:
	binaryTreeNode<E>* root;                // pointer to root
	int treeSize;                           // number of nodes in tree
	static void (*visit)(binaryTreeNode<E>*);      // visit function
	static int count;         // used to count nodes in a subtree
	static void preOrder (binaryTreeNode<E>* t);
	static void inOrder (binaryTreeNode<E>* t);
	static void postOrder (binaryTreeNode<E>* t);
	static void countNodes (binaryTreeNode<E>* t) {
		visit = addToCount;
		count = 0;
		preOrder (t);
	}
	static void dispose (binaryTreeNode<E>* t) { delete t; }
	static void output (binaryTreeNode<E>* t) {
		cout << t->element << ' ';
	}
	static void addToCount (binaryTreeNode<E>* t) {
		count++;
	}
	static int height (binaryTreeNode<E>* rootin) {// Return height of tree rooted at *t.
		if (rootin == nullptr) {
			return 0;
		}
		int lheight = height (rootin->left);  // height of left
		int rheight = height (rootin->right); // height of right
		return lheight > rheight ?++lheight : ++rheight ;
	}

};
// the following should work but gives an internal compiler error
// template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
void (*linkedBinaryTree<pair<int, int> >::visit)(binaryTreeNode<pair<int, int> >*);
void (*linkedBinaryTree<pair<const int, char> >::visit)(binaryTreeNode<pair<const int, char> >*);
void (*linkedBinaryTree<pair<const int, int> >::visit)(binaryTreeNode<pair<const int, int> >*);

template<class E>
E* linkedBinaryTree<E>::rootElement () const {// Return nullptr if no root. Otherwise, return pointer to root element.
	if (treeSize == 0)
		return nullptr;  // no root
	else
		return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree (const E& element,
	linkedBinaryTree<E>& left, linkedBinaryTree<E>& right) {// Combine left, right, and element to make new tree.
// left, right, and this must be different trees.
  // create combined tree
	root = new binaryTreeNode<E> (element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;

	// deny access from trees left and right
	left.root = right.root = nullptr;
	left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree () {// Remove and return the left subtree.
   // check if empty
	if (treeSize == 0)
		throw "emptyTree()";

	// detach left subtree and save in leftSubtree
	linkedBinaryTree<E> leftSubtree;
	leftSubtree.root = root->left;
	count = 0;
	leftSubtree.treeSize = countNodes (leftSubtree.root);
	root->left = nullptr;
	treeSize -= leftSubtree.treeSize;

	return leftSubtree;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree () {// Remove and return the right subtree.
   // check if empty
	if (treeSize == 0)
		throw "emptyTree()";

	// detach right subtree and save in rightSubtree
	linkedBinaryTree<E> rightSubtree;
	rightSubtree.root = root->right;
	count = 0;
	rightSubtree.treeSize = countNodes (rightSubtree.root);
	root->right = nullptr;
	treeSize -= rightSubtree.treeSize;

	return rightSubtree;
}

template<class E>
void linkedBinaryTree<E>::preOrder (binaryTreeNode<E>* t) {// Preorder traversal.
	if (t != nullptr) {
		linkedBinaryTree<E>::visit (t);
		preOrder (t->left);
		preOrder (t->right);
	}
}

template<class E>
void linkedBinaryTree<E>::inOrder (binaryTreeNode<E>* t) {// Inorder traversal.
	if (t != nullptr) {
		inOrder (t->left);
		linkedBinaryTree<E>::visit (t);
		inOrder (t->right);
	}
}

template<class E>
void linkedBinaryTree<E>::postOrder (binaryTreeNode<E>* t) {// Postorder traversal.
	if (t != nullptr) {
		postOrder (t->left);
		postOrder (t->right);
		linkedBinaryTree<E>::visit (t);
	}
}


#endif
int WidthNR (BT root){
	int i, j, w, index;
	int count[20], width[20];//count array stores the total amounts of nodes before a level(including itself);
	//width array stores every level's amount of nodes.
	BT queue[20];//queue array stores the nodes' pointers.
	for (i = 0; i < 20; i++) {
		count[i] = 0;
		width[i] = 0;
		queue[i] = NULL;
	}
	i = 0;
	j = 0;
	if (!root)w = 0;
	else {
		queue[0] = root;
		count[0] = 1;
		count[1] = 1;
		index = 1;
		while (queue[i]) {
			if (queue[i]->lchild) {
				j++;
				queue[j] = queue[i]->lchild;
				count[index]++;
			}
			if (queue[i]->rchild) {
				j++;
				queue[j] = queue[i]->rchild;
				count[index]++;
			}
			i++;
			if (i >= count[index - 1])index++;//if the head of queue exeeds the level's total amount then it indictates it's a node in next level.
			if (count[index] == 0)count[index] += count[index - 1];//the next level's amount of nodes is the sum of itself's and the amount of nodes whose level are before it.

		}
	}
	width[0] = 1;
	w = width[0];
	i = 1;
	while (count[i]) {
		width[i] = count[i] - count[i - 1];
		if (width[i] > w)w = width[i];
		i++;
	}
	return w;
}

// Function to find the maximum width of the tree
// using level order traversal

int getMaxWidth () {
	//如果树为空，则宽度为0
	if (root == nullptr) {
		return 0;
	}

	int result = 0;

	queue<binaryTreeNode<E>*> q;
	q.push (root);
	while (!q.empty ()) {
		int count = q.size ();//当前层的宽度
		result = max (count, result);//获取最大宽度
		while (count--) {//获取下一层元素
			binaryTreeNode<E>* temp = q.front ();
			q.pop ();

			if (temp->left != nullptr) {
				q.push (temp->left);
			}
			if (temp->right != nullptr) {
				q.push (temp->right);
			}
		}
	}

	return result;
}
template<class E>
binaryTreeNode<E>* getTreeByPreAndIn (binaryTreeNode<E>* preorder, binaryTreeNode<E>* inorder,int length) {
	//递归结束条件
	if (length == 0) {
		return nullptr;
	}
	binaryTreeNode<E>* root = new binaryTreeNode<E>(preorder[0]);//当前根节点

	//找到中序遍历根节点的位置
	int index;
	for (index = 0; inorder[index] != preorder[0]; index++) {}

	//构建左右子树
	root->left = getTreeByPreAndIn (preorder + 1, inorder, index);
	root->right = getTreeByPreAndIn (preorder + 1 + index, inorder + 1 + index, length - 1 - index);

	return root;//返回当前根节点
}