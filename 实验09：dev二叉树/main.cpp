#include<iostream>
using namespace std;
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
	//前序遍历第一个元素就是当前子树的根节点
	//再从中序遍历中找到该节点的位置，其左右两侧的序列就是左右子树的前序遍历
	//此时前序遍历第一个元素之后的若干元素与中序遍历左侧序列对应，前序遍历末尾若干元素与中序遍历右侧序列对应
	//将对应子序列再次作为新的前序与中序序列进行树的构建，不断递归到序列为空。则完成树的构建
	node* _makeNodeFromPreIn (T* pre, T* in, int in_length) {
		node* new_node;

		//如果该子序列为0，则说明此节点为空
		if (in_length == 0) {
			//cout << "leaf node\n";
			return nullptr;
		} else {
		//如果子序列不为零，说明此处有节点
			new_node = new node;

			//获取len，len是左子序列的长度，也就是左子树元素数；通过len也可以求出右子序列长度
			int len = 0;
			while (pre[0] != in[len]) {
				len++;
			}
			new_node->data = pre[0];
			//cout << pre[0] << "make in \n";
			
			//将前序与中序的子序列起始位置与长度计算出来，传入递归函数

			//左子树前序序列为当前前序首节点之后的len个元素
			//中序序列为当前中序根节点左侧的len个元素
			new_node->left = _makeNodeFromPreIn (pre + 1, in, len);

			//右子树前序序列为当前前序序列len个元素之后的所有元素
			//中序序列为当前中序根节点右侧的length-len-1个元素
			new_node->right = _makeNodeFromPreIn (pre + len + 1, in + len + 1, in_length - len - 1);
			return new_node;
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
		~btree ();
	}
	void buildFromPreIn (T* pre_head_in, T* in_head_in, int length_in) {
		_root = _makeNodeFromPreIn (pre_head_in, in_head_in, length_in);
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
};



int main () {
//#pragma warning(disable:4996)
//	freopen ("input.txt", "r", stdin);
	int*  pre;
	int*  in;

	btree<int> b;

	int length = 0;
	cin >> length;

	/*初始化两个前序遍历与中序遍历序列*/
	pre = new int[length];
	in = new int[length];
	for (int i = 0; i < length; i++) {
		cin >> pre[i];
	}
	for (int i = 0; i < length; i++) {
		cin >> in[i];
	}


	b.buildFromPreIn (pre, in, length);
	b.postOut (cout);
	return 0;
}
