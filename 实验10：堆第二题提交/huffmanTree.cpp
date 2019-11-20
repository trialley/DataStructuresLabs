#include <iostream>
using namespace std;
#include<iostream>
#include<cstring>
#define max(a,b) (a<b ? b:a)//用于获取左右子树中最大的那个层数
using namespace std;

/*queue
public:
	enum queue_err { queue_empty };  //常见的错误
private:
	struct node;					//结点类型
	node* _head;					//头结点指针
	node* _end;						//尾结点指针，指向NULL
	int _length;					//元素个数
public:
	queue ();						//构造函数
	~queue ();						//析构函数
	void push ( const T& in );		//入队列
	T front ();						//获得首元素
	void pop ();					//弹出首元素
	bool empty ()const;			//是否为空
	int size ()const;				//获取元素个数
*/
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
		while (_head->next != NULL) {
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
		n_end->next = NULL;

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

/*class btree
public:
	enum err;			常见错误
	struct node			节点结构体
protected:
	node* _root;		树根指针
	int _size;			树节点数量

	void deleteNodes (node* root)							删除以传入节点为根的树
	node* _makeNodeFromPreIn (T* pre, T* in, int in_length)	以输入的前序与中序序列递归生成一颗树
	ostream& _preOut (ostream& out, node* rootin)			前序遍历
	ostream& _postOut (ostream& out, node* rootin)			后续遍历
public:
	btree ()												构造函数
	~btree ()												析构函数，递归删除所有节点
	void clear ()											清空此树，根节点置为空
	void buildFromPreIn (T* pre_head_in, T* in_head_in, int length_in)暴露给外部的根据前序与中序序列生成树的函数
	ostream& preOut (ostream& out)							暴露给外界的前序遍历接口
	ostream& postOut (ostream& out)							暴露给外界的后序遍历接口
	ostream& levelOut (ostream& out)						暴露给外界的层次遍历接口
	void setRoot (node* rootin)								设置根节点
*/
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
	void makeTree (T datai,btree* lefttreei,btree* righttreei) {
		_root = new node;
		_root->data = datai;
		_root->left = lefttreei->_root;
		_root->right = righttreei->_root;
		lefttreei->_root = nullptr;
		righttreei->_root = nullptr;
	}
};
template<class T>
/*分布式排序*/
class minHeap {
public:
	typedef enum { min_head_empty }err;
private:
	int _size;
	int _length;
	T* _head;
	void _extLength () {
		T* temp = new T[_length * 2];
		copy (_head, _head + _length, temp);
		delete[] _head;
		_length *= 2;
		_head = temp;
	}
	void _clear () {
		/*delete[] _head;*/
	}
public:
	minHeap (int lengthi = 10) {
		_length = lengthi + 1;
		_head = new T[_length];
		_size = 0;
	}
	~minHeap () { _clear (); }
	void _clearAndInit () {
		_clear ();
		_length = 11;
		_head = new T[11];
		_size = 0;
	}
	const T& top () {
		if (_size == 0)
			throw min_head_empty;
		return _head[1];
	}
	void pop () {
		if (_size == 0) {
			throw min_head_empty;
		}
		_head[1].~T ();
		T to_be_insert = _head[_size--];
		int insert_index = 1,
			child_index = 2;     // child_index of current_node

		//将新的头部元素逐层向下移动，向下移动到左子还是右子？这里需要判断
		//起码有一个左子树，所以要<=
		while (child_index <= _size) {
			//如果左子比右子大，则根应当与右子交换，使新根小，这样可以保持最小堆特性
			//如果左子树卡到了size位置，说明没有右子树，不必寻找左右中最小的元素
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//如果根比两个子都小，那直接退出就行了，不必再交换
			if (to_be_insert <= _head[child_index]) {
				break;
			}
			_head[insert_index] = _head[child_index];
			insert_index = child_index;
			child_index *= 2;
		}
		_head[insert_index] = to_be_insert;
	}
	void push (const T& datai) {
		//进行越界检查
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//插入元素的父元素不小于插入元素，说明需要调整
			_head[insert_index] = _head[insert_index / 2]; //该父元素放到子节点位置
			insert_index /= 2;//子节点位置指向原父节点那里去，也即发生父子交换，只不过子元素还没有插入

			//继续循环查看新的父节点
		}

		_head[insert_index] = datai;
	}

	bool empty () const { return _size == 0; }
	int size () const { return _size; }
};
template<class T>
struct huffmanNode {
	btree<int>* tree;
	T weight;

	operator T () const { return weight; }
};

template <class T>
btree<int>* huffmanTree(T weight[], int n)
{// Generate Huffman tree with weights weight[1:n], n >= 1.
   // create an array of single node trees
   huffmanNode<T> *hNode = new huffmanNode<T> [n + 1];
   btree<int> emptyTree;
   for (int i = 1; i <= n; i++)
   {
      hNode[i].weight = weight[i];
      hNode[i].tree = new btree<int>;
      hNode[i].tree->makeTree(i, emptyTree, emptyTree);
   }

   // make node array into a min heap
   minHeap<huffmanNode<T> > heap;
   heap.initialize(hNode, n);

   // repeatedly combine trees from min heap
   // until only one tree remains
   huffmanNode<T> w, x, y;
   linkedBinaryTree<int> *z;
   for (i = 1; i < n; i++){
      // remove two lightest trees from the min heap
      x = heap.top(); heap.pop();
      y = heap.top(); heap.pop();

      // combine into a single tree
      z = new linkedBinaryTree<int>;
      z->makeTree(0, *x.tree, *y.tree);
      w.weight = x.weight + y.weight;
      w.tree = z;
      heap.push(w);
      delete x.tree;
      delete y.tree;
   }

   // destructor for min heap deletes hNode
   return heap.top().tree;
}

int main(void){
   int a[11];
   int n = 10;
   for (int i = 1; i <= n; i++)
      a[i] = 2 * i;
   linkedBinaryTree<int> *x = huffmanTree(a, n);
   x->postOrderOutput();
   return 0;
}
