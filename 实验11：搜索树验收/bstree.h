#pragma once
#include<iostream>
using std::ostream;
using std::cout;


template<class T>
struct node {
	T data;
	int left_size;		//结点名次，实际上就是左子节点的元素数，一开始我想保存名次，但是名次一改俱该，比较麻烦
	node<T>* left;		//指向左子树的指针
	node<T>* right;		//指向右子树的指针

	//空构造函数
	node ()
		:left (nullptr), right (nullptr), left_size (0) {}

	//带子节点构造函数
	node (const T& data_in, node<T>* left_in, node<T>* right_in)
		:left_size (0), data (data_in), left (left_in), right (right_in) {}
	
	//有数据构造函数
	node (const T& data_in)
		:data (data_in), left (nullptr), right (nullptr), left_size (0) {}
	
	//拷贝构造函数
	node (const node* node_in)
		:data (node_in->data), left (node_in->left), right (node_in->right), left_size (node_in->left_size) {}
};

template<class T>
class bstree {
protected:
	node<T>* _root;								//根节点
	T _size;									//当前树的元素数目
	void _inOrder (node<T>* t, ostream& out);	//中序遍历递归函数
	void friend cal (node<int>* rootin, int* sizes, int* deepthes);
	int friend calF (bstree<int>& bst);			//使用之前二叉树的层次计算函数

public:
	int xor_result;								//保存对比过程中的异或和
	bstree () 
		:_root (nullptr), _size (0), xor_result(0){}//默认构造函数
	bool insert (T data_in);					//插入
	node<T>* search (T data_in);				//搜索
	bool erase (T data_in);						//删除
	node<T>* getPByIndex (int index);			//按照名次查询
	bool eraseByIndes (int index);				//按照名次删除
	ostream& inOrder (ostream& out);			//中序遍历，可以按照升序打印内容
};



template<class T>
void bstree<T>::_inOrder (node<T>* t, ostream& out) {
	if(t->left)_inOrder (t->left,out);
	out << t->data<<" ";
	if (t->right)_inOrder (t->right,out);
}

template<class T>
ostream& bstree<T>::inOrder (ostream& out) {
	_inOrder (_root,out);
	return out;

}
template<class T>
ostream& operator << (ostream& out, bstree<T> b) {
	b.inOrder(out);
	return out;
}

template<class T>
bool bstree<T>::insert (T data_in) {

	//检查目标结点是否存在
	//node<T>* temp = search (data_in);
	//if (temp != nullptr && temp->data == data_in) {
	//	//找不到则返回false
	//	return false;
	//}

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
		} else if (data_in > p->data) {
			p = p->right;
		} else {
			return false;
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
		if (data_in < p->data) {
			cout << "对比："<< data_in << " < " << p->data<<"\n";
			p = p->left;
		} else {
			if (data_in > p->data) {
				cout << "对比："<< data_in << " > " << p->data << "\n";
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
	if (index < 0 || index >= _size) {
		return nullptr;
	}

	xor_result = 0;
	node<T>* p = _root;
	while (p != nullptr) {
		xor_result = xor_result ^ p->data;
		if (p->left_size == index) {
			cout << "对比名次：" << p->left_size << " == " << index << "\n";
			return p;//直接返回
		} else {
			if (p->left_size > index) {
				cout << "对比名次："<< p->left_size << " > " <<  index << "\n";
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
			p->left_size--;//沿途的结点的左节点数量都要减少
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
		q->data = s->data;
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
/*本题目第二三个小任务的核心函数，计算每个节点为根的树的层数与节点数*/
#define max(a,b) (a<b ? b:a)//用于获取左右子树中最大的那个层数
void cal (node<int>* rootin, int* sizes, int* deepthes) {
	//如果传入空则直接返回
	if (rootin) {
		//首先递归计算节点为根的树的节点数与层数，所有子节点全部计算完毕后再计算当前元素
		cal (rootin->left, sizes, deepthes);
		cal (rootin->right, sizes, deepthes);

		//对于该节点
		//若当前元素没有子节点，则以其为根的树的节点数与层数均为1
		if (rootin->left == nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = 1;
			deepthes[rootin->data] = 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "都无\n";

		//若当前元素有左子树，则以其为根的树的节点数与层数为左子树相应数据加1
		} else if (rootin->left != nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "左有\n";

		//若当前元素有右子树，则以其为根的树的节点数与层数为右子树相应数据加1
		} else if (rootin->left == nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "右都有\n";

		//若当前元素有左右子树，则以其为根的树的节点数与层数为左右子树相应数据相加再加1
		} else if (rootin->left != nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = max (deepthes[rootin->right->data], deepthes[rootin->left->data]) + 1;
			//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "左右都有\n";
		}
	}
	return;
}

int calF (bstree<int>& bst) {
	/*初始化存储节点数与层数的数组*/
	int* sizes = new int[100 + 1];
	memset (sizes, 0, 100 + 1);
	int* deepthes = new int[100 + 1];
	memset (deepthes, 0, 100 + 1);
	cal (bst._root,sizes,deepthes);

	return deepthes[bst._root->data];
}