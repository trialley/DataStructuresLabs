#include<iostream>
using namespace std;
#define fori(i,n) for(int i=0;i<(int)(n);i++)


template<class T>
struct node {
	T data;
	int left_size;		//代表结点在以自己为根的树中的名次
	node<T>* left;		//指向左子树的指针
	node<T>* right;		//指向右子树的指针

	//空构造函数
	node ()
		:left(nullptr),right(nullptr), left_size(0){}
	//带子节点构造函数
	node (const T& data_in, node<T>* left_in, node<T>* right_in)
		:left_size (0), data (data_in), left (left_in), right (right_in) {}
	//有数据构造函数
	node (const T& data_in) 
		:data (data_in),left (nullptr),right ( nullptr), left_size (0) { }
	node (const node* node_in)
		:data (node_in->data), left (node_in->left), right (node_in->right), left_size (node_in->left_size) {}
};

template<class T>
class bstree {
protected:
	node<T>* _root;
	T _size;
	void _preOrder (node<T>* t, ostream& out);
public:
	int xor_result;
	bstree ():_root(nullptr), _size(0){ }
	bool insert (T data_in);
	node<T>* search (T data_in);
	node<T>* getPByIndex (int index);//索引从零开始
	bool erase (T data_in);
	bool eraseByIndes (int index);
	ostream& preOrder (ostream& out);
};
template<class T>
bool bstree<T>::insert (T data_in) {

	//检查目标结点是否存在
	node<T>* temp = search (data_in);
	if (temp != nullptr && temp->data == data_in){
		//找不到则返回false
		return false;
	}

	xor_result = 0;			//初始化异或值
	node<T>* p = _root;		//p是用来寻找目标位置的指针
	node<T>* pp = nullptr;	//pp是为了避免p指向空叶子结点而造成目标丢失

	/*循环寻找目标位置*/
	while (p != nullptr) {
		pp = p;
		xor_result = xor_result ^ p->data;
		if (data_in < p->data) {
			p->left_size++;
			p = p->left;
		} else {
			p = p->right;
		}
	}

	node<T>* new_node = new node<T> (data_in);	//构造新的结点
	if (_root != nullptr) {						//若树不为空则插入到合适位置
		if (data_in < pp->data) {
			pp->left = new_node; 
		} else {
			pp->right = new_node;
		}
	} else {									//若树为空则直接代替root
		_root = new_node;
	}
	_size++;
	return true;
}

/*寻找目标值元素，返回指针*/
template<class T>
node<T>* bstree<T>::search (T data_in) {
	xor_result = 0;
	node<T>* p = _root;

	while (p != nullptr) {
		xor_result = xor_result ^ p->data;
		if (data_in < p->data){
			p = p->left;
		} else {
			if (data_in > p->data) {
				p = p->right;
			} else {
				return p;//找到目标便返回
			}
		}
	}
	
	return nullptr;
}

template<class T>
node<T>* bstree<T>::getPByIndex (int index) {
	if (index < 0 || index >= _size){
		return nullptr;
	}

	xor_result = 0;
	node<T>* p = _root;
	while (p != nullptr) {
		xor_result = xor_result ^ p->data;
		if (p->left_size == index) {
			return p;//直接返回
		} else {
			if (p->left_size > index){
				p = p->left;
			} else {
				index = index - p->left_size - 1;//这里注意，向右下方寻找时记得修改目标索引值
				p = p->right;
			}
		}
	}

	return nullptr;
}
template<class T>
bool bstree<T>::erase (T data_in) {
	node<T>* temp = search (data_in);
	if (temp == nullptr) {
		return false;
	}


	//p是目标元素，pp是其父元素
	xor_result = 0;
	node<T>* p = _root;
	node<T>* pp = nullptr;
	while (p->data != data_in && p != nullptr) {
		xor_result = xor_result ^ p->data;
		pp = p;
		if (data_in < p->data) {
			p->left_size--;
			p = p->left;
		} else {
			p = p->right;
		}
	}
	xor_result = xor_result ^ data_in;
	if (p == nullptr) {
		return false;
	}

	//寻找可代替p的s结点
	if (p->left != nullptr && p->right != nullptr) {
		node<T>* s = p->right;
		node <T>* ps = p;
		while (s->left != nullptr) {
			ps = s;
			s->left_size--;
			s = s->left;
		}
		node<T>* q = new node<T> (p);
		q->data=s->data;
		if (pp == nullptr) {
			_root = q;
		} else if (p == pp->left) {
			pp->left = q;
		} else {
			pp->right = q;
		}
		if (ps == p) {
			pp = q;
		} else {
			pp = ps;
		}
		delete p;
		p = s;
	}
	node<T>* c = nullptr;
	if (p->left != nullptr) {
		c = p->left;
	} else {
		c = p->right;
	}
	if (p == _root) { _root = c; } else {
		if (p == pp->left) {
			pp->left = c;
		} else {
			pp->right = c;
		}
	}
	_size--;
	delete p;
	return true;
}

template<class T>
bool bstree<T>::eraseByIndes (int index) {
	if (index < 0 || index >= _size) {
		return false;
	}
	xor_result = 0;
	node<T>* temp = getPByIndex (index);
	if (temp == nullptr) {
		return false;
	}
	erase (temp->data);
	return true;
}

int main () {
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);
	int n;
	cin >> n;

	int a, b;
	bstree<int> m;
	node<int>* x;
	fori (i, n) {
		cin >> a>>b;
		switch (a) {
		case 0:
			if (m.insert (b)) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}

			break;
		case 1:
			x = m.search (b);
			if (x != nullptr) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}
			break;
		case 2:
			if (m.erase (b)) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}
			break;
		case 3:
			b--;
			x = m.getPByIndex (b);
			if (x != nullptr) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}

			break;
		case 4:
			b--;
			if (m.eraseByIndes (b)) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}
			break;
		default:
			break;
		}
	}
}
