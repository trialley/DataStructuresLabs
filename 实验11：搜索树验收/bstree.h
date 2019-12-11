#pragma once
#include<iostream>
using std::ostream;
using std::cout;


template<class T>
struct node {
	T data;
	int left_size;		//������Σ�ʵ���Ͼ������ӽڵ��Ԫ������һ��ʼ���뱣�����Σ���������һ�ľ�ã��Ƚ��鷳
	node<T>* left;		//ָ����������ָ��
	node<T>* right;		//ָ����������ָ��

	//�չ��캯��
	node ()
		:left (nullptr), right (nullptr), left_size (0) {}

	//���ӽڵ㹹�캯��
	node (const T& data_in, node<T>* left_in, node<T>* right_in)
		:left_size (0), data (data_in), left (left_in), right (right_in) {}
	
	//�����ݹ��캯��
	node (const T& data_in)
		:data (data_in), left (nullptr), right (nullptr), left_size (0) {}
	
	//�������캯��
	node (const node* node_in)
		:data (node_in->data), left (node_in->left), right (node_in->right), left_size (node_in->left_size) {}
};

template<class T>
class bstree {
protected:
	node<T>* _root;								//���ڵ�
	T _size;									//��ǰ����Ԫ����Ŀ
	void _inOrder (node<T>* t, ostream& out);	//��������ݹ麯��
	void friend cal (node<int>* rootin, int* sizes, int* deepthes);
	int friend calF (bstree<int>& bst);			//ʹ��֮ǰ�������Ĳ�μ��㺯��

public:
	int xor_result;								//����Աȹ����е�����
	bstree () 
		:_root (nullptr), _size (0), xor_result(0){}//Ĭ�Ϲ��캯��
	bool insert (T data_in);					//����
	node<T>* search (T data_in);				//����
	bool erase (T data_in);						//ɾ��
	node<T>* getPByIndex (int index);			//�������β�ѯ
	bool eraseByIndes (int index);				//��������ɾ��
	ostream& inOrder (ostream& out);			//������������԰��������ӡ����
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

	//���Ŀ�����Ƿ����
	//node<T>* temp = search (data_in);
	//if (temp != nullptr && temp->data == data_in) {
	//	//�Ҳ����򷵻�false
	//	return false;
	//}

	xor_result = 0;				//��ʼ�����ֵ
	node<T>* p = _root;		//p������Ѱ��Ŀ��λ�õ�ָ��
	node<T>* pp = nullptr;	//pp��Ϊ�˱���pָ���Ҷ�ӽ������Ŀ�궪ʧ

	/*ѭ��Ѱ��Ŀ��λ��*/
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

	node<T>* new_node = new node<T> (data_in);	//�����µĽ��
	if (_root != nullptr) {						//������Ϊ������뵽����λ��
		if (data_in < pp->data) {
			pp->left = new_node;
		} else {
			pp->right = new_node;
		}
	} else {									//����Ϊ����ֱ�Ӵ���root
		_root = new_node;
	}
	_size++;
	return true;
}

/*Ѱ��Ŀ��ֵԪ�أ�����ָ��*/
template<class T>
node<T>* bstree<T>::search (T data_in) {
	xor_result = 0;
	node<T>* p = _root;

	while (p != nullptr) {
		xor_result = xor_result ^ p->data;
		if (data_in < p->data) {
			cout << "�Աȣ�"<< data_in << " < " << p->data<<"\n";
			p = p->left;
		} else {
			if (data_in > p->data) {
				cout << "�Աȣ�"<< data_in << " > " << p->data << "\n";
				p = p->right;
			} else {
				return p;//�ҵ�Ŀ��㷵��
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
			cout << "�Ա����Σ�" << p->left_size << " == " << index << "\n";
			return p;//ֱ�ӷ���
		} else {
			if (p->left_size > index) {
				cout << "�Ա����Σ�"<< p->left_size << " > " <<  index << "\n";
				p = p->left;
			} else {
				index = index - p->left_size - 1;//����ע�⣬�����·�Ѱ��ʱ�ǵ��޸�Ŀ������ֵ
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


	//p��Ŀ��Ԫ�أ�pp���丸Ԫ��
	xor_result = 0;
	node<T>* p = _root;
	node<T>* pp = nullptr;
	while (p->data != data_in && p != nullptr) {
		xor_result = xor_result ^ p->data;
		pp = p;
		if (data_in < p->data) {
			p->left_size--;//��;�Ľ�����ڵ�������Ҫ����
			p = p->left;
		} else {
			p = p->right;
		}

	}
	xor_result = xor_result ^ data_in;
	if (p == nullptr) {
		return false;
	}

	//Ѱ�ҿɴ���p��s���
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
/*����Ŀ�ڶ�����С����ĺ��ĺ���������ÿ���ڵ�Ϊ�������Ĳ�����ڵ���*/
#define max(a,b) (a<b ? b:a)//���ڻ�ȡ���������������Ǹ�����
void cal (node<int>* rootin, int* sizes, int* deepthes) {
	//����������ֱ�ӷ���
	if (rootin) {
		//���ȵݹ����ڵ�Ϊ�������Ľڵ���������������ӽڵ�ȫ��������Ϻ��ټ��㵱ǰԪ��
		cal (rootin->left, sizes, deepthes);
		cal (rootin->right, sizes, deepthes);

		//���ڸýڵ�
		//����ǰԪ��û���ӽڵ㣬������Ϊ�������Ľڵ����������Ϊ1
		if (rootin->left == nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = 1;
			deepthes[rootin->data] = 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

		//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
		} else if (rootin->left != nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

		//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
		} else if (rootin->left == nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "�Ҷ���\n";

		//����ǰԪ��������������������Ϊ�������Ľڵ��������Ϊ����������Ӧ��������ټ�1
		} else if (rootin->left != nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = max (deepthes[rootin->right->data], deepthes[rootin->left->data]) + 1;
			//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "���Ҷ���\n";
		}
	}
	return;
}

int calF (bstree<int>& bst) {
	/*��ʼ���洢�ڵ��������������*/
	int* sizes = new int[100 + 1];
	memset (sizes, 0, 100 + 1);
	int* deepthes = new int[100 + 1];
	memset (deepthes, 0, 100 + 1);
	cal (bst._root,sizes,deepthes);

	return deepthes[bst._root->data];
}