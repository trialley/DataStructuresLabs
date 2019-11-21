#include<iostream>
#include<cstring>
#define max(a,b) (a<b ? b:a)//用于获取左右子树中最大的那个层数
using namespace std;

template<typename T>
class queue {
public:
	enum queue_err { queue_empty };
private:
	typedef struct node {
		T data;
		node* next;
		node () { next = nullptr; }
	}node;
	node* _head;
	node* _end;
	int _length;
public:
	queue () {
		_head = new node;
		_end = _head;
		_length = 0;
	}
	~queue () {
		while (_head->next != nullptr) {
			node* temp = _head;
			_head = _head->next;
			delete temp;
		}
		delete _head;
	}

	void push (const T& in) {
		_length++;
		node* n_end = new node;
		n_end->data = in;
		n_end->next = nullptr;

		_end->next = n_end;
		_end = n_end;
	}
	T front () {
		if (empty ()) {
			throw queue_empty;
		}
		return _head->next->data;
	}
	void pop () {
		if (empty ()) {
			throw queue_empty;
		}
		node* n_head = _head->next;
		delete _head;

		_head = n_head;

		_length--;
		return;
	}


	bool empty ()const { return _head == _end; }
	int size ()const { return _length; }
};
/*用于存储键值的类*/
template <class K, class E>
class mypair {
public:
	K key;
	E data;
	mypair (K keyin, E datain) :key (keyin), data (datain) {}
};
template<class T>
class btree {
public:
	typedef enum {} err;
	typedef struct node {
		T data;
		node* left;
		node* right;
		node (T data, node* left, node* right)
			:data (data), left (left), right (right) {}
		node ()
			:left (nullptr), right (nullptr) {}

	} node;
protected:
	node* _root;
	int _size;

	void deleteNodes (node* root) {
		if (root) {
			//cout << "delete" << root->data << "\n";
			if (root->left)deleteNodes (root->left);
			if (root->right)deleteNodes (root->right);
			delete root;
		}
	}

	ostream& _preOut (ostream& out, node* rootin) {
		if (rootin == nullptr) {
			return out;
		} else {
			out << rootin->data << " ";
			_preOut (out, rootin->left);
			_preOut (out, rootin->right);
			return out;
		}
	}
	ostream& _postOut (ostream& out, node* rootin) {
		if (rootin == nullptr) {
			return out;
		} else {
			_postOut (out, rootin->left);
			_postOut (out, rootin->right);
			out << rootin->data << " ";
			return out;
		}
	}
public:
	btree () {
		_root = nullptr;
	}
	~btree () {
		//cout << "dis\n";
		if (_root) {
			if (_root->left)deleteNodes (_root->left);
			if (_root->right)deleteNodes (_root->right);
			delete _root;
		}
	}
	void clear () {
		if (_root) {
			if (_root->left)deleteNodes (_root->left);
			if (_root->right)deleteNodes (_root->right);
			delete _root;
		}
	}

	ostream& preOut (ostream& out) {
		if (_root == nullptr) {
			return out;
		} else {
			out << _root->data << " ";
			_preOut (out, _root->left);
			_preOut (out, _root->right);
			return out;
		}

	}
	ostream& postOut (ostream& out) {
		if (_root == nullptr) {
			return out;
		} else {
			_postOut (out, _root->left);
			_postOut (out, _root->right);
			out << _root->data << " ";
			return out;
		}
	}
	ostream& levelOut (ostream& out) {
		queue<node* > q;
		node* t = _root;
		q.push (t);
		//通过队列存储待打印元素，这样一层的数据会相邻在一起
		while (!q.empty ()) {
			t = q.front ();
			q.pop ();
			out << t->data << " ";
			if (t->left != nullptr) {
				q.push (t->left);
			}
			if (t->right != nullptr) {
				q.push (t->right);
			}
		}
		return out;
	}
	void setRoot (node* rootin) {
		clear ();
		_root = rootin;
		return;
	}
};



template<class K, class E>
class binarySearchTree : public bsTree<K, E>,
	public btree<pair<const K, E> > {
public:
	// methods of dictionary
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
	pair<const K, E>* find (const K& theKey) const;
	void insert (const pair<const K, E>& thePair);
	void erase (const K& theKey);

	// additional method of bsTree
	void ascend () { inOrderOutput (); }
void deleteMax () {
	node* troot = _root;//指向要删除的节点
	node* troot_f = _root;//指向要删除的元素的父节点

	//判断两种特殊情况
	if (_root == nullptr) {
		return
	}
	if (_root->right == nullptr) {
		troot = _root;
		_root = _root->left;
		delete troot;
		return;
	}

	//找到最右的右子树
	while (troot->right != nullptr) {
		troot_f = troot;
		troot = troot->right;
	}
	//如果最右子节点还有左子树，则该左子树变成最右子节点的父节点的右子树
	if (troot->left != nullptr) {
		troot_f->right = troot->left;
	}
	//删除右子树
	delete troot;
	return;
}

void insertArray (T* arru, int len) {
	_root = new node;

	for (int i = 0; i < len; i++) {
		node* p = _root;
		node* pp = nullptr;
		while (p != nullptr) {
			pp = p;
			if (i < p->element.key)
				p = p->left;
			else
				p = p->right;
		}

		node* newNode= new node(i,arri[i]);
		if (root != nullptr) {
			if (i < pp->element.key)pp->left = newNode;
			else pp->right = newNode;
		} else {
			_root = newNode;
		}

		_size++;
	}
}

void inOrderToArr (node* t,E* position) {
	if (t != nullptr) {
		inOrderToArr (t->leftChild,position);
		position[0]=t->key;
		position++;
		inOrderToArr (t->leftChild,position);
		return;
	} else {
		return;
	}
}
};

template<class K, class E>
pair<const K, E>* binarySearchTree<K, E>::find (const K& theKey) const {// Return pointer to matching pair.
 // Return nullptr if no matching pair.
   // p starts at the root and moves through
   // the tree looking for an element with key theKey
	node<pair<const K, E> >* p = root;
	while (p != nullptr)
		// examine p->element
		if (theKey < p->element.key)
			p = p->leftChild;
		else
			if (theKey > p->element.key)
				p = p->rightChild;
			else // found matching pair
				return &p->element;

	// no matching pair
	return nullptr;
}

template<class K, class E>
void binarySearchTree<K, E>::insert (const pair<const K, E>& thePair) {// Insert thePair into the tree. Overwrite existing
 // pair, if any, with same key.
   // find place to insert
	node* p = root;
	node* pp = nullptr;
	while (p != nullptr) {// examine p->element
		pp = p;
		// move p to a child
		if (thePair.key < p->element.key)
			p = p->leftChild;
		else
			if (thePair.key > p->element.key)
				p = p->rightChild;
			else {// replace old value
				p->element.second = thePair.second;
				return;
			}
	}

	// get a node for thePair and attach to pp
	node<pair<const K, E> >* newNode
		= new node<pair<const K, E> > (thePair);
	if (root != nullptr) // the tree is not empty
		if (thePair.key < pp->element.key)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	else
		root = newNode; // insertion into empty tree
	_size++;
}

template<class K, class E>
void binarySearchTree<K, E>::erase (const K& theKey) {// Delete the pair, if any, whose key equals theKey.

   // search for node with key theKey
	node<pair<const K, E> >* p = root,
		* pp = nullptr;
	while (p != nullptr && p->element.key != theKey) {// move to a child of p
		pp = p;
		if (theKey < p->element.key)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == nullptr)
		return; // no pair with key theKey

	 // restructure tree
	 // handle case when p has two children
	if (p->leftChild != nullptr && p->rightChild != nullptr) {// two children
	   // convert to zero or one child case
	   // find largest element in left subtree of p
		node<pair<const K, E> >* s = p->leftChild,
			* ps = p;  // parent of s
		while (s->rightChild != nullptr) {// move to larger element
			ps = s;
			s = s->rightChild;
		}

		// move largest from s to p, can't do a simple move
		// p->element = s->element as key is const
		node<pair<const K, E> >* q =
			new node<pair<const K, E> >
			(s->element, p->leftChild, p->rightChild);
		if (pp == nullptr)
			root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p) pp = q;
		else pp = ps;
		delete p;
		p = s;
	}

	// p has at most one child
	// save child pointer in c
	node<pair<const K, E> >* c;
	if (p->leftChild != nullptr)
		c = p->leftChild;
	else
		c = p->rightChild;

	// delete p
	if (p == root)
		root = c;
	else {// is p left or right child of pp?
		if (p == pp->leftChild)
			pp->leftChild = c;
		else pp->rightChild = c;
	}
	_size--;
	delete p;
}

template <class K, class E>
ostream& operator<<(ostream& out, const pair<K, E>& x) {
	out << x.key << ' ' << x.second; return out;
}
