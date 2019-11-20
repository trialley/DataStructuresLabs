#include<iostream>
#include<cstring>
#define max(a,b) (a<b ? b:a)//���ڻ�ȡ���������������Ǹ�����
using namespace std;

/*queue
public:
	enum queue_err { queue_empty };  //�����Ĵ���
private:
	struct node;					//�������
	node* _head;					//ͷ���ָ��
	node* _end;						//β���ָ�룬ָ��NULL
	int _length;					//Ԫ�ظ���
public:
	queue ();						//���캯��
	~queue ();						//��������
	void push ( const T& in );		//�����
	T front ();						//�����Ԫ��
	void pop ();					//������Ԫ��
	bool empty ()const;			//�Ƿ�Ϊ��
	int size ()const;				//��ȡԪ�ظ���
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
	ostream& levelOut (ostream& out)						��¶�����Ĳ�α����ӿ�
	void setRoot (node* rootin)								���ø��ڵ�
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
			//ͨ�����д洢����ӡԪ�أ�����һ������ݻ�������һ��
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

/*����Ŀ�ڶ�����С����ĺ��ĺ���������ÿ���ڵ�Ϊ�������Ĳ�����ڵ���*/
void cal (btree<int>::node* rootin, int* sizes, int* deepthes) {
	//����������ֱ�ӷ���
	if (rootin) {
		//���ȵݹ����ڵ�Ϊ�������Ľڵ���������������ӽڵ�ȫ��������Ϻ��ټ��㵱ǰԪ��
		cal (rootin->left,sizes,deepthes);
		cal (rootin->right, sizes, deepthes);

		//���ڸýڵ�
		//����ǰԪ��û���ӽڵ㣬������Ϊ�������Ľڵ����������Ϊ1
		if (rootin->left == nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = 1;
			deepthes[rootin->data] = 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

		//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
		}else if (rootin->left != nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = sizes[rootin->left->data]+1;
			deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

		//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
		}else if (rootin->left == nullptr && rootin->right != nullptr) {
			sizes[rootin->data] =sizes[rootin->right->data]+1;
			deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "�Ҷ���\n";

		//����ǰԪ��������������������Ϊ�������Ľڵ��������Ϊ����������Ӧ��������ټ�1
		}else if (rootin->left != nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data]+ sizes[rootin->left->data]+1;
			deepthes[rootin->data] = max(deepthes[rootin->right->data], deepthes[rootin->left->data])+1;
			//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "���Ҷ���\n";
		}
	}
	return;
}



int main () {
	//#pragma warning(disable:4996)
	//	freopen ("input9.txt", "r", stdin);

	int num = 0;
	cin >> num;

	/*��ʼ���洢�ڵ��������������*/
	int* sizes = new int[num+1];
	memset (sizes, 0, num+1);
	int* deepthes = new int[num+1];
	memset (deepthes, 0, num+1);

	/*��ʼ���ڽڵ�*/
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
	
	/*����deepths��sizes*/
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
