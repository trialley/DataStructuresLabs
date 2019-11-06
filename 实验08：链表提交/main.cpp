# pragma once
#include<iostream>
using namespace std;

/*��Ӧ�����������͵Ĺ�ϣ�������˴�ֻдint�Ĺ�ϣ����*/
template <class K> class myhash;

template<>
class myhash<int> {
public:
	size_t operator()(const int keyin) const {return size_t(keyin);}
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
	typedef mypair< K, E> mypairType;
	typedef mynode< K, E> mynodeType;
	mypairType element;
	mynodeType* next;

	mynode ( mypairType pairin) :element (pairin),next(nullptr) {}
	mynode ( mypairType pairin, mynodeType* nextin) :element (pairin), next (nextin) {}
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

protected:
	mynode<K, E>* _head;
	int _size;
public:
	myChain ():_head(nullptr), _size(0){}
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
		while (c_node != nullptr && c_node->element.key != keyin) {
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
		mynode<K, E>* p = _head;
		mynode<K, E>* tp = nullptr;

		while (p != nullptr && p->element.key < keyin) {
			tp = p;
			p = p->next;
		}

		if (p != nullptr && p->element.key == keyin) {
			if (tp == nullptr) _head = p->next;
			else tp->next = p->next;
			delete p;
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
	void output (ostream& out) const {
		for (mynode<K, E>* c_node = _head;
			c_node != nullptr;
			c_node = c_node->next) {
			out << c_node->element.key << ":"<< c_node->element.data << "  ";
		}
	}
};

/*�������Ԫ�ص����غ���*/
template <class K, class E>
ostream& operator<<(ostream& out, const myChain<K, E>& x) {
	x.output (out);
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
	bool empty () const { return _size == 0; }
	int size () const { return _size; }

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
		int size = _chains[pos].size ();
		_chains[pos].insert (pairin);

		/*����������˵�������ˣ�û������˵��������*/
		if (_chains[pos].size () > size) {
			_size++;
			return true;
		} else {
			return false;
		}
	}
	/*ɾ��Ԫ�صİ�װ*/
	bool erase (const K& keyin) {return _chains[_getPosByKey(keyin)].erase (keyin);}

	/*���Ԫ��*/
	void output (ostream& out) const {
		for (int i = 0; i < _divisor; i++) {
			if (_chains[i].size () == 0) {
				cout << "Chain" << i << ": NULL ";
			} else {
				cout << "Chain" << i << ":" << _chains[i] << " ";
			}
		}
	}
	/*ͨ���ؼ��ʻ�ȡ���ȣ�Ϊ��OJ������*/
	int getLengthByKey (const K& keyin) const {
		return _chains[_getPosByKey (keyin)].size ();
	}
};
/*�������*/
template <class K, class E>
ostream& operator<<(ostream& out, const myhashChains<K, E>& in) {
	in.output (out); return out;
}


int main () {
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);
	int d, m, a, b;
	int* pos =nullptr;
	int length = 0;
	cin >> d >> m;
	myhashChains<int, int> myhashChain (d);

	for (int i = 1; i <= m; i++) {
		//cout << "��n��ѭ��" << i<<endl;
		cin >> a >> b;
		switch (a) {
		case 0:
			//cout << "����" << b << endl;
			if (myhashChain.insert (mypair<int, int> (b, b))) {
			
			} else {
				cout << "Existed\n";
			}
			break;
		case 1:
			//cout << "����" << b << endl;

			pos = myhashChain.find(b);
			if (pos == nullptr) {
				cout << "Not Found" << "\n";
			} else {
				length = myhashChain.getLengthByKey (b);
				cout << length << "\n";
			}
			break;
		case 2:
			//cout << "ɾ��" << b << endl;

			length = myhashChain.getLengthByKey (b);
			if (myhashChain.erase (b)) {
				cout <<--length<< "\n";
			} else {
				cout << "Delete Failed\n";
			}
			break;
		default:
			break;
		}
		//cout << endl << endl << myhashChain << endl << endl;

	}

	return 0;
}