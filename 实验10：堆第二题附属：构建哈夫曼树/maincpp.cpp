#include <iostream>
using namespace std;
#include<iostream>
#include<cstring>
#define max(a,b) (a<b ? b:a)//���ڻ�ȡ���������������Ǹ�����
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
		//ͨ�����д洢����ӡԪ�أ�����һ������ݻ�������һ��
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
	void makeTree (T datai, btree& lefttreei, btree& righttreei) {
		_root = new node;
		_root->data = datai;
		_root->left = lefttreei._root;
		_root->right = righttreei._root;
		lefttreei._root = nullptr;
		righttreei._root = nullptr;
	}
};
template<class T>
/*�ֲ�ʽ����*/
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
	void initialize (T* arri,int sizei) {
		_clearAndInit ();
		for (int i = 0; i < sizei; i++) {
			push (arri[i]);
		}
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

		//���µ�ͷ��Ԫ����������ƶ��������ƶ������ӻ������ӣ�������Ҫ�ж�
		//������һ��������������Ҫ<=
		while (child_index <= _size) {
			//������ӱ����Ӵ����Ӧ�������ӽ�����ʹ�¸�С���������Ա�����С������
			//���������������sizeλ�ã�˵��û��������������Ѱ����������С��Ԫ��
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//������������Ӷ�С����ֱ���˳������ˣ������ٽ���
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
		//����Խ����
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//����Ԫ�صĸ�Ԫ�ز�С�ڲ���Ԫ�أ�˵����Ҫ����
			_head[insert_index] = _head[insert_index / 2]; //�ø�Ԫ�طŵ��ӽڵ�λ��
			insert_index /= 2;//�ӽڵ�λ��ָ��ԭ���ڵ�����ȥ��Ҳ���������ӽ�����ֻ������Ԫ�ػ�û�в���

			//����ѭ���鿴�µĸ��ڵ�
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
	bool operator <(huffmanNode& b) const { return weight < b.weight; }
	bool operator >(huffmanNode& b) const { return weight > b.weight; }
};


template <class T>
btree<int>* huffmanTree (T weight[], int n) {
	huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
	btree<int> emptyTree;
	for (int i = 1; i <= n; i++) {
		hNode[i].weight = weight[i];
		hNode[i].tree = new btree<int>;
		hNode[i].tree->makeTree (i, emptyTree, emptyTree);
	}

	// make node array into a min heap
	minHeap<huffmanNode<T> > heap (1);
	heap.initialize (hNode+1, n);

	// repeatedly combine trees from min heap
	// until only one tree remains
	huffmanNode<T> w, x, y;
	btree<int>* z;
	for (int i = 1; i < n; i++) {
		// remove two lightest trees from the min heap
		x = heap.top (); heap.pop ();
		y = heap.top (); heap.pop ();

		// combine into a single tree
		z = new btree<int>;
		z->makeTree (0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push (w);
		delete x.tree;
		delete y.tree;
	}

	// destructor for min heap deletes hNode
	return heap.top ().tree;
}

int main (void) {
	int str[10] = {9,9,9,9,9,9,9};
	btree<int>* x = huffmanTree (str, 2);
	x->levelOut (cout);
	return 0;
}
