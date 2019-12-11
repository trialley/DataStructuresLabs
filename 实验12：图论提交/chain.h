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
		firstnode = nullptr;
		listSize = 0;
	}
	chain (int initialCapacity, T A[]) {
		if (initialCapacity > 0) {
			firstnode = new node<T>;
			firstnode->data = A[0];
			node<T>* p1 = firstnode, * p2;
			for (int i = 1; i < initialCapacity; i++)  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
			{
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			listSize = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "��ʼ���ȹ�С��" << endl;
	}
	chain (int initialCapacity) //�൱��Ĭ�Ϲ��캯�� 
	{//����ֻ���ٽڵ㲻�����Ǹ�ֵ 
		if (initialCapacity >= 0) {
			firstnode = new node<T>;
			node<T>* p1 = firstnode, * p2;
			for (int i = 1; i < initialCapacity; i++) {
				p2 = new node<T>;
				p1->next = p2;
				p1 = p2;
			}
			listSize = initialCapacity;
		}
		if (initialCapacity < 0) cerr << "��ʼ���ȹ�С��" << endl;
	}
	chain (const chain<T>& A) {
		listSize = A.listSize;
		if (listSize == 0) {//�˱�Ϊ�� 
			firstnode = nullptr;
		} else {//TargetNodeָ��A�Ľڵ㣬SourceNodeָ�������Ľڵ�
		//ֱ�ӽڵ㸳ֵ����ǳ���ƣ�ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			firstnode = SourceNode;
			TargetNode = A.firstnode;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < listSize; i++)  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
			{
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //�����pre_node������һ���¿ռ䲢��ʼ�� 
				SourceNode->next = pre_node;
				SourceNode = pre_node;
			}
		}


	}
	~chain () {
		while (firstnode != nullptr) {
			node<T>* nextnode = firstnode->next;
			delete firstnode;
			firstnode = nextnode;
		}
	}
	bool empty () const {
		return listSize == 0;
	}
	int size () const {
		return listSize;
	}
	T& get (int theIndex) const {//����������theIndex�ڵ��data���� 
		checkIndex (theIndex);
		node<T>* cur_node = firstnode;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T get_Weight (int ele) const {//����Ԫ����ele�ڵ��weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = firstnode; cur_node != nullptr; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//���ؽڵ�Ԫ��������theElement�Ľڵ���������δ�ҵ��򷵻�-1 
		node<T>* cur_node = firstnode;
		for (int i = 0; i < listSize; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseElement (int theVertex) {//�����������Ҷ������theVertex��Ԫ�أ����ҵ���ɾ�������������Ԫ�ص�ָ�� 
		node<T>* p = firstnode, * tp = nullptr;
		while (p != nullptr) {
			if (p->data == theVertex) {
				if (p == firstnode) //ɾͷ��� 
					firstnode = firstnode->next;
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
			deletenode = firstnode;
			firstnode = firstnode->next;
		} else {
			node<T>* p = firstnode;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫɾ���Ľ���ǰ���ڵ� 
			deletenode = p->next;
			p->next = p->next->next;
		}
		listSize--;
		delete deletenode;
	}
	void insert (int theIndex, const T& ele, T weight) {//��eleԪ�ز�������ΪtheIndexλ�õ��½ڵ� 
		checkIndex (theIndex);
		if (theIndex == 0) {//����ͷ�ڵ� 
			node<T>* p = new node<T> (ele, weight, firstnode);
			firstnode = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//������ڵ�
			node<T>* cur_node = firstnode;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫ����Ľ���ǰ���ڵ� 
			p->next = cur_node->next;
			cur_node->next = p;
		}
		listSize++;
	}
	void output () const {
		if (listSize == 0) { cout << "null" << endl;  return; } else {
			node<T>* p = firstnode;
			for (int i = 0; i < listSize; i++) {
				cout << "vertex=" << p->data << ",weight=" << p->weight << "   ";
				p = p->next;
			}
		}
	}
	void i_print () const {//ʹ�õ�������� 
		if (listSize == 0) { cout << "null" << endl;  return; } else {
			iterator I (firstnode);
			for (int i = 0; i < listSize; i++) {
				cout << (*I) << " ";
				I++;
			}
		}
	}

	void clear () {//������ 
		node<T>* deletenode, * p = firstnode;
		for (int i = 0; i < listSize; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		firstnode = nullptr;
		listSize = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//����Ҫ���ø��ƹ��캯�� 
		if (A.listSize == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A.firstnode;
			for (int i = 0; i < A.listSize; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iterator {//���캯����*&��ǰ���Լӡ���=��== 
	protected:
		node<T>* _node = nullptr;
	public:
		iterator (node<T>* theNode) {
			_node = theNode;
		}
		iterator () {}

		T& operator*() { return _node->data; }  //ȡ�������������Ϊ���÷��� 
		T* operator->() { return &(_node->data); }  //ȡ��ַ���������Ϊָ�뷵�� 
		iterator& operator++() {//ǰ�� 
			_node = _node->next;
			return *this;
		}
		iterator operator++(int) {//��� 
			iterator temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iterator I)const {
			if (_node == I._node) return false;  //������û�ж���_node��==��Ϊʲôû�б��� 
			else return true;
		}
		bool operator==(const iterator I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void checkIndex (int theIndex) const {//ȷ����������Ч�ԣ���ֹԽ��
		if (theIndex<0 || theIndex>listSize) {
			cerr << "index=" << theIndex << ",listSize=" << listSize << "������������Ч�ԣ�" << endl;
		}
	}
	node<T>* firstnode;          //ָ�������һ��Ԫ�ص�ָ�� 
	int listSize;                     //�����Ԫ�ظ��� 	               
};
