#include<iostream>
using namespace std;

#define fori(i,n) for(int i=0;i<(int)(n);i++)


template<class T>
struct node {
	T data;
	int left_size;		//结点名次，实际上就是左子节点的元素数
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

};

template<class T>
class bsTree {
protected:
	node<T>* _root;
	T _size;
	void _preOrder (node<T>* t, ostream& out);
public:
	int xor_result;
	bsTree ():_root(nullptr), _size(0){ }
	bool push (T data_in);
	node<T>* search (T data_in);
	node<T>* getByIndex (int index);//索引从零开始
	bool erase (T data_in);
	bool eraseByIndes (int index);
	ostream& preOrder (ostream& out);
};
template<class T>
bool bsTree<T>::push (T data_in) {

	//检查目标结点是否存在
	node<T>* temp = search (data_in);
	if (temp != nullptr && temp->data == data_in){
		//找不到则返回false
		return false;
	}

	xor_result = 0;				//初始化异或值
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
node<T>* bsTree<T>::search (T data_in) {
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
node<T>* bsTree<T>::getByIndex (int index) {
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

/*前序遍历两函数*/
template<class T>
void bsTree<T>::_preOrder (node<T>* t,ostream& out){
	if (t == nullptr) {
		return;
	}
	out << t->data << " " << t->left_size << endl;
	_preOrder (t->left);
	_preOrder (t->right);
}
template<class T>
ostream& bsTree<T>::preOrder (ostream& out) {
	_preOrder (_root, out);
}


template<class T>
bool bsTree<T>::erase (T data_in){
	/*寻找元素*/
	node<T>* temp = search (data_in);
	if (temp == nullptr){
		return false;
	}

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
		return false;             //不存在与关键字匹配的数对
	}

	if (p->left != nullptr && p->right != nullptr) {
		node<T>* s = p->right,
			* ps = p;  // parent of s
		while (s->left != nullptr) {// move to larger data

			ps = s;
			s->left_size--;
			s = s->left;
		}
		node<T>* q = new node<T> (s->data, p->left, p->right);
		q->left_size = p->left_size;//将s元素的值赋给p，后将s元素删除 
		if (pp == nullptr)
			_root = q;
		else if (p == pp->left)
			pp->left = q;
		else
			pp->right = q;
		if (ps == p) pp = q;
		else pp = ps;
		delete p;
		p = s;
	}
	node<T>* c = nullptr;
	if (p->left != nullptr) { c = p->left; } else { c = p->right; }
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
bool bsTree<T>::eraseByIndes (int index) {
	//xor_result = 0;
	if (index < 0 || index >= _size)//索引越界
	{
		//cout << "0" << endl;
		return false;
	}
	xor_result = 0;
	node<T>* temp = getByIndex (index);
	if (temp == nullptr) {
		return false;
	}
	erase (temp->data);
	return true;
}

int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	int n;
	cin >> n;

	int a, b;
	bsTree<int> m;
	node<int>* x;
	fori (i, n) {
		cin >> a;
		switch (a) {
		case 0:
			cin >> b;
			if (m.push (b)) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}

			break;
		case 1:

			cin >> b;
			x = m.search (b);
			if (x != nullptr) {
				//确实存在
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}
			break;
		case 2:

			cin >> b;
			if (m.erase (b)) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}
			break;
		case 3:
			cin >> b;
			b--;
			x = m.getByIndex (b);
			if (x != nullptr) {
				cout << m.xor_result << endl;
			} else {
				cout << "0" << endl;
			}

			break;
		case 4:
			cin >> b;
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
