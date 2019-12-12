#include<iostream>
using namespace std;
template<class T>
struct node {
	T data;
	T weight;
	node* next = nullptr;

	node (T ele, T w, node* p = nullptr) :data (ele), weight (w), next (p) {}
	node () {}
	node& operator=(node& A) {//��㸳ֵ 
		data = A.data;
		weight = A.weight;
		next = A.next;
		return *this;
	}
};

template<class T>
class chain {
public:
	chain () {
		_head = nullptr;
		_size = 0;
	}
	chain (int initialCapacity, T A[]) {
		if (initialCapacity > 0) {
			_head = new node<T>;
			_head->data = A[0];
			node<T>* p1 = _head, * p2;
			for (int i = 1; i < initialCapacity; i++){  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			_size = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "��ʼ���ȹ�С��" << endl;
	}
	chain (const chain<T>& A) {
		_size = A._size;
		if (_size == 0) {//�˱�Ϊ�� 
			_head = nullptr;
		} else {//TargetNodeָ��A�Ľڵ㣬SourceNodeָ�������Ľڵ�
				//ֱ�ӽڵ㸳ֵ����ǳ���ƣ�ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			_head = SourceNode;
			TargetNode = A._head;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < _size; i++) {  //����1�Ļ�ǰ���Ѿ���������һ���ڵ�
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //�����pre_node������һ���¿ռ䲢��ʼ�� 
				SourceNode->next = pre_node;
				SourceNode = pre_node;
			}
		}
	}
	~chain () {
		while (_head != nullptr) {
			node<T>* nextnode = _head->next;
			delete _head;
			_head = nextnode;
		}
	}
	bool empty () const {return _size == 0;}
	int size () const {return _size;}
	T& get (int theIndex) const {//����������theIndex�ڵ��data���� 
		checkIndex (theIndex);
		node<T>* cur_node = _head;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T get_Weight (int ele) const {//����Ԫ����ele�ڵ��weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = _head; cur_node != nullptr; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//���ؽڵ�Ԫ��������theElement�Ľڵ���������δ�ҵ��򷵻�-1 
		node<T>* cur_node = _head;
		for (int i = 0; i < _size; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseElement (int theVertex) {//�����������Ҷ������theVertex��Ԫ�أ����ҵ���ɾ�������������Ԫ�ص�ָ�� 
		node<T>* p = _head, * tp = nullptr;
		while (p != nullptr) {
			if (p->data == theVertex) {
				if (p == _head) //ɾͷ��� 
					_head = _head->next;
				else {
					tp->next = p->next;
					delete p;
					return p;
				}
			} else {//Ԫ�ز�����theVertex 
				tp = p;
				p = p->next;
			}
		}
		return nullptr;  //�Ҳ����Ļ�����nullptr 
	}

	void erase (int theIndex) {//��������ɾ������ΪtheIndex�Ľڵ� 
		checkIndex (theIndex);
		node<T>* deletenode;
		if (theIndex == 0) {//ɾ��ͷ��� 
			deletenode = _head;
			_head = _head->next;
		} else {
			node<T>* p = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫɾ���Ľ���ǰ���ڵ� 
			deletenode = p->next;
			p->next = p->next->next;
		}
		_size--;
		delete deletenode;
	}
	void insert (int theIndex, const T& ele, T weight) {//��eleԪ�ز�������ΪtheIndexλ�õ��½ڵ� 
		checkIndex (theIndex);
		if (theIndex == 0) {//����ͷ�ڵ� 
			node<T>* p = new node<T> (ele, weight, _head);
			_head = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//������ڵ�
			node<T>* cur_node = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫ����Ľ���ǰ���ڵ� 
			p->next = cur_node->next;
			cur_node->next = p;
		}
		_size++;
	}
	void output () const {
		if (_size == 0) { cout << "null" << endl;  return; } else {
			node<T>* p = _head;
			for (int i = 0; i < _size; i++) {
				cout << "vertex=" << p->data << ",weight=" << p->weight << "   ";
				p = p->next;
			}
		}
	}
	void i_print () const {//ʹ�õ�������� 
		if (_size == 0) { cout << "null" << endl;  return; } else {
			iteragetTor I (_head);
			for (int i = 0; i < _size; i++) {
				cout << (*I) << " ";
				I++;
			}
		}
	}

	void clear () {//������ 
		node<T>* deletenode, * p = _head;
		for (int i = 0; i < _size; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		_head = nullptr;
		_size = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//����Ҫ���ø��ƹ��캯�� 
		if (A._size == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A._head;
			for (int i = 0; i < A._size; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iteragetTor {//���캯����*&��ǰ���Լӡ���=��== 
	protected:
		node<T>* _node = nullptr;
	public:
		iteragetTor (node<T>* theNode) {
			_node = theNode;
		}
		iteragetTor () {}

		T& operator*() { return _node->data; }  //ȡ�������������Ϊ���÷��� 
		T* operator->() { return &(_node->data); }  //ȡ��ַ���������Ϊָ�뷵�� 
		iteragetTor& operator++() {//ǰ�� 
			_node = _node->next;
			return *this;
		}
		iteragetTor operator++(int) {//��� 
			iteragetTor temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iteragetTor I)const {
			if (_node == I._node) return false;  //������û�ж���_node��==��Ϊʲôû�б��� 
			else return true;
		}
		bool operator==(const iteragetTor I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void checkIndex (int theIndex) const {//ȷ����������Ч�ԣ���ֹԽ��
		if (theIndex<0 || theIndex>_size) {
			cerr << "index=" << theIndex << ",listSize=" << _size << "������������Ч�ԣ�" << endl;
		}
	}
	node<T>* _head;          //ָ�������һ��Ԫ�ص�ָ�� 
	int _size;                     //�����Ԫ�ظ��� 	               
};
