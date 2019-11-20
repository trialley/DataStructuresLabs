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
				 out<<t->data<<" ";
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

/*本题目第二三个小任务的核心函数，计算每个节点为根的树的层数与节点数*/
void cal (btree<int>::node* rootin, int* sizes, int* deepthes) {
	//如果传入空则直接返回
	if (rootin) {
		//首先递归计算节点为根的树的节点数与层数，所有子节点全部计算完毕后再计算当前元素
		cal (rootin->left,sizes,deepthes);
		cal (rootin->right, sizes, deepthes);

		//对于该节点
		//若当前元素没有子节点，则以其为根的树的节点数与层数均为1
		if (rootin->left == nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = 1;
			deepthes[rootin->data] = 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "都无\n";

		//若当前元素有左子树，则以其为根的树的节点数与层数为左子树相应数据加1
		}else if (rootin->left != nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = sizes[rootin->left->data]+1;
			deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "左有\n";

		//若当前元素有右子树，则以其为根的树的节点数与层数为右子树相应数据加1
		}else if (rootin->left == nullptr && rootin->right != nullptr) {
			sizes[rootin->data] =sizes[rootin->right->data]+1;
			deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "右都有\n";

		//若当前元素有左右子树，则以其为根的树的节点数与层数为左右子树相应数据相加再加1
		}else if (rootin->left != nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data]+ sizes[rootin->left->data]+1;
			deepthes[rootin->data] = max(deepthes[rootin->right->data], deepthes[rootin->left->data])+1;
			//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "左右都有\n";
		}
	}
	return;
}



int main () {
	//#pragma warning(disable:4996)
	//	freopen ("input9.txt", "r", stdin);

	int num = 0;
	cin >> num;

	/*初始化存储节点数与层数的数组*/
	int* sizes = new int[num+1];
	memset (sizes, 0, num+1);
	int* deepthes = new int[num+1];
	memset (deepthes, 0, num+1);

	/*初始化众节点*/
	btree<int> b;
	btree<int>::node** nodes=new btree<int>::node*[num+1];
	for (int i = 1; i <= num; i++) {
		nodes[i] = new  btree<int>::node;
	}
	for (int i = 1; i <= num; i++) {
		int l = 0;
		int r = 0;
		cin >> l >> r;
		nodes[i]->data = i;
		nodes[i]->left = l==-1? nullptr: nodes[l];
		nodes[i]->right = r==-1 ? nullptr : nodes[r];

		sizes[i]= 1;
		deepthes[i]=1;
	}
	b.setRoot (nodes[1]);
	b.levelOut (cout);
	cout << "\n";
	
	/*计算deepths与sizes*/
	cal (nodes[1],sizes,deepthes);

	for (int i = 1; i <= num; i++) {
		cout << sizes[i] << " ";
	}
	cout << "\n";
	for (int i = 1; i <= num; i++) {
		cout << deepthes[i] << " ";
	}
	cout << "\n";

	return 0;
}
