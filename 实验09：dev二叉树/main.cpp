#include<iostream>
using namespace std;
/*class btree
public:
	enum err;			��������
	struct node			�ڵ�ṹ��
protected:
	node* _root;		����ָ��
	int _size;			���ڵ�����

	void deleteNodes (node* root)							ɾ���Դ���ڵ�Ϊ������
	node* _makeNodeFromPreIn (T* pre, T* in, int in_length)	�������ǰ�����������еݹ�����һ����
	ostream& _preOut (ostream& out, node* rootin)			ǰ�����
	ostream& _postOut (ostream& out, node* rootin)			��������
public:
	btree ()												���캯��
	~btree ()												�����������ݹ�ɾ�����нڵ�
	void clear ()											��մ��������ڵ���Ϊ��
	void buildFromPreIn (T* pre_head_in, T* in_head_in, int length_in)��¶���ⲿ�ĸ���ǰ�������������������ĺ���
	ostream& preOut (ostream& out)							��¶������ǰ������ӿ�
	ostream& postOut (ostream& out)							��¶�����ĺ�������ӿ�
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
	//ǰ�������һ��Ԫ�ؾ��ǵ�ǰ�����ĸ��ڵ�
	//�ٴ�����������ҵ��ýڵ��λ�ã���������������о�������������ǰ�����
	//��ʱǰ�������һ��Ԫ��֮�������Ԫ�����������������ж�Ӧ��ǰ�����ĩβ����Ԫ������������Ҳ����ж�Ӧ
	//����Ӧ�������ٴ���Ϊ�µ�ǰ�����������н������Ĺ��������ϵݹ鵽����Ϊ�ա���������Ĺ���
	node* _makeNodeFromPreIn (T* pre, T* in, int in_length) {
		node* new_node;

		//�����������Ϊ0����˵���˽ڵ�Ϊ��
		if (in_length == 0) {
			//cout << "leaf node\n";
			return nullptr;
		} else {
		//��������в�Ϊ�㣬˵���˴��нڵ�
			new_node = new node;

			//��ȡlen��len���������еĳ��ȣ�Ҳ����������Ԫ������ͨ��lenҲ��������������г���
			int len = 0;
			while (pre[0] != in[len]) {
				len++;
			}
			new_node->data = pre[0];
			//cout << pre[0] << "make in \n";
			
			//��ǰ�����������������ʼλ���볤�ȼ������������ݹ麯��

			//������ǰ������Ϊ��ǰǰ���׽ڵ�֮���len��Ԫ��
			//��������Ϊ��ǰ������ڵ�����len��Ԫ��
			new_node->left = _makeNodeFromPreIn (pre + 1, in, len);

			//������ǰ������Ϊ��ǰǰ������len��Ԫ��֮�������Ԫ��
			//��������Ϊ��ǰ������ڵ��Ҳ��length-len-1��Ԫ��
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

	/*��ʼ������ǰ������������������*/
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
