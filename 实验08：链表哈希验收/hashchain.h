# pragma once
#include<iostream>

/*��Ӧ�����������͵Ĺ�ϣ�������˴�ֻдint�Ĺ�ϣ����*/
template <class K> class myhash;
template<>
class myhash<int> {
public:
	size_t operator()(const int keyin) const { return size_t (keyin); }
};

/*���ڴ洢��ֵ����*/
template <class K, class E>
class mypair {
public:
	K key;
	E data;
	mypair (K keyin, E datain) :key (keyin), data (datain) {}
};

/*���ڹ�������Ľ����*/
template <class K, class E>
struct mynode {
	mypair< K, E>  element;
	mynode< K, E>* next;
	mynode (mypair< K, E>  pairin) :element (pairin), next (nullptr) {}
	mynode (mypair< K, E>  pairin, mynode< K, E>* nextin) :element (pairin), next (nextin) {}
};

/*������
template<class K, class E>
class myChain {
protected:
	mynode<K, E>* _head;							//��������ͷ
	int _size;										//����Ԫ�ظ���
public:
	myChain ();										//���캯��
	~myChain ();									//��������
	bool empty () const;							//�����Ƿ�Ϊ��
	int size () const;								//����Ԫ����Ŀ
	mypair< K, E>* find (const K& keyin) const;		//����Ԫ�أ��Ҳ������ؿ�ָ��
	bool erase (const K& keyin);					//ɾ��Ԫ�أ��޴�Ԫ�ط���false��ɾ���ɹ�����true
	void insert (mypair< K, E>& pairin);			//���뺯�����ڲ���ʱȷ������
	void output (ostream& out) const;				//�������Ԫ��
*/
template<class K, class E>
class myChain {
public:
	typedef enum {empty_chain}err;
protected:
	mynode<K, E>* _head;
	int _size;
public:
	myChain () :_head (nullptr), _size (0) {}
	~myChain () {
		while (_head != nullptr) {
			mynode<K, E>* nextNode = _head->next;
			delete _head;
			_head = nextNode;
		}
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
	mypair< K, E>* find (const K& keyin) const {
		mynode<K, E>* c_node = _head;

		/*һֱѰ��ֱ���ҵ���ӦԪ��*/
		for (;;) {
			if (c_node == nullptr || c_node->element.key == keyin) {
				break;
			}
			c_node = c_node->next;
		}

		/*���ֵ��Ϊ�գ���*/
		if (c_node != nullptr && c_node->element.key == keyin) {
			return &c_node->element;
		} else {
			return nullptr;
		}
	}
	bool erase (const K& keyin) {
		mynode<K, E>* nodep = _head;
		mynode<K, E>* pre_nodep = nullptr;

		while (nodep != nullptr && nodep->element.key < keyin) {
			pre_nodep = nodep;
			nodep = nodep->next;
		}

		if (nodep != nullptr && nodep->element.key == keyin) {
			if (pre_nodep == nullptr) _head = nodep->next;
			else pre_nodep->next = nodep->next;
			delete nodep;
			_size--;
			return true;
		} else {
			return false;
		}
	}

	/*���뺯�����ڲ���ʱȷ������*/
	void insert (mypair< K, E>& thePair) {
		mynode<K, E>* nodep = _head;
		mynode<K, E>* pre_nodep = nullptr;
		while (nodep != nullptr && nodep->element.key < thePair.key) {
			pre_nodep = nodep;
			nodep = nodep->next;
		}
		/*�鿴�Ƿ����д�Ԫ��*/
		if (nodep != nullptr && nodep->element.key == thePair.key) {
			//������������޸ĸ�λ��Ԫ��
			nodep->element.data = thePair.data;
			return;
		} else {
			//���������Ԫ��
			mynode<K, E>* newNode = new mynode<K, E> (thePair, nodep);

			if (pre_nodep == nullptr) _head = newNode;
			else pre_nodep->next = newNode;

			_size++;
			return;
		}
	}
	/*�������Ԫ��*/
	void output (std::ostream& out) const {
		mynode<K, E>* c_node = _head;
		while (c_node != nullptr) {
			out << c_node->element.key << ":" << c_node->element.data << "  ";
			c_node = c_node->next;
		}
	}
};

/*�������Ԫ�ص����غ���*/
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const myChain<K, E>& in) {
	in.output (out);
	return out;
}

/*��ϣ������
template<class K, class E>
class myhashChains {
protected:
	myChain<K, E>* _chains;							//�ҵ�����
	myhash<K> _myhash;								//�Զ���Ĺ�ϣ����
	int _size;										//Ԫ�ظ���
	int _divisor;									//����������ĸ���
	int inline _getPosByKey (const K& keyin)const;	//��ȡ�ùؼ��ʵ�����λ�ã�ע��÷���ֵ��Ҫ������������зֱ����
public:
	myhashChains (int divisorin = 20);				//���캯��
	~myhashChains ();								//��������
	bool empty () const;							//�����Ƿ�Ϊ��
	int size () const;								//����Ԫ�ظ���
	E* find (const K& keyin) const;					//���ҹؼ��ʣ�����ֵ��ָ��
	bool insert (mypair<K, E> pairin);				//�����ֵ�ԣ����ز���ɹ�ʧ�����
	bool erase (const K& keyin);					//ɾ��Ԫ�صİ�װ
	void output (ostream& out) const;				//���Ԫ��
	int getLengthByKey (const K& keyin) const;		//ͨ���ؼ��ʻ�ȡ���ȣ�Ϊ��OJ������
*/

template<class K, class E>
class myhashChains {
public:
	typedef enum {  }err;
protected:
	myChain<K, E>* _chains;
	myhash<K> _myhash;
	int _size;
	int _divisor;
	int inline _getPosByKey (const K& keyin)const {
		return _myhash (keyin) % _divisor;
	}
public:
	myhashChains (int divisorin = 20) {
		_size = 0;
		_divisor = divisorin;
		_chains = new myChain<K, E>[_divisor];
	}
	~myhashChains () { delete[] _chains; }

	/*���ҹؼ��ʣ�����ֵ��ָ��*/
	E* find (const K& keyin) const {
		mypair< K, E>* temp = (_chains[_getPosByKey (keyin)].find (keyin));
		if (temp == nullptr) {
			return nullptr;
		} else {
			return &(temp->data);
		}
	}

	/*�����ֵ�ԣ����ز���ɹ�ʧ�����*/
	bool insert (mypair<K, E> pairin) {
		int pos = _getPosByKey (pairin.key);
		int old_size = _chains[pos].size ();
		_chains[pos].insert (pairin);

		/*����������˵�������ˣ�û������˵��������*/
		if (_chains[pos].size () > old_size) {
			_size++;
			return true;
		} else {
			return false;
		}
	}
	/*ɾ��Ԫ�صİ�װ*/
	bool erase (const K& keyin) { return _chains[_getPosByKey (keyin)].erase (keyin); }

	/*���Ԫ��*/
	void output (std::ostream& out) const {
		for (int i = 0; i < _divisor; i++) {
			if (_chains[i].size () == 0) {
				std::cout << "Chain" << i << ": nothing ";
			} else {
				std::cout << "Chain" << i << ": " << _chains[i] << " ";
			}
		}
	}
	/*ͨ���ؼ��ʻ�ȡ���ȣ�Ϊ��OJ������*/
	int getLengthByKey (const K& keyin) const {
		return _chains[_getPosByKey (keyin)].size ();
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
};
/*�������*/
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const myhashChains<K, E>& in) {
	in.output (out);
	return out;
}
