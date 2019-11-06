# pragma once
#include<iostream>
using namespace std;

/*对应各种数据类型的哈希函数，此处只写int的哈希函数*/
template <class K> class myhash;

template<>
class myhash<int> {
public:
	size_t operator()(const int keyin) const {return size_t(keyin);}
};


/*用于存储键值的类*/
template <class K, class E>
class mypair {
public:
	K key;
	E data;
	mypair (K keyin, E datain) :key (keyin), data (datain) {}
};

/*用于构成链表的结点类*/
template <class K, class E>
struct mynode {
	typedef mypair< K, E> mypairType;
	typedef mynode< K, E> mynodeType;
	mypairType element;
	mynodeType* next;

	mynode ( mypairType pairin) :element (pairin),next(nullptr) {}
	mynode ( mypairType pairin, mynodeType* nextin) :element (pairin), next (nextin) {}
};


/*链表类
template<class K, class E>
class myChain {
protected:
	mynode<K, E>* _head;							//保存链表头
	int _size;										//保存元素个数
public:
	myChain ();										//构造函数
	~myChain ();									//析构函数
	bool empty () const;							//返回是否为空
	int size () const;								//返回元素数目
	mypair< K, E>* find (const K& keyin) const;		//查找元素，找不到返回空指针
	bool erase (const K& keyin);					//删除元素，无此元素返回false，删除成功返回true
	void insert (mypair< K, E>& pairin);			//插入函数，在插入时确保有序
	void output (ostream& out) const;				//输出链表元素
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

		/*一直寻找直到找到对应元素*/
		while (c_node != nullptr && c_node->element.key != keyin) {
			c_node = c_node->next;
		}

		/*如果值不为空，则*/
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

	/*插入函数，在插入时确保有序*/
	void insert (mypair< K, E>& thePair) {
		mynode<K, E>* nodep = _head;
		mynode<K, E>* pre_nodep = nullptr;
		while (nodep != nullptr && nodep->element.key < thePair.key) {
			pre_nodep = nodep;
			nodep = nodep->next;
		}
		/*查看是否已有此元素*/
		if (nodep != nullptr && nodep->element.key == thePair.key) {
			//已有则插入则修改该位置元素
			nodep->element.data = thePair.data;
			return;
		} else {
			//无则插入新元素
			mynode<K, E>* newNode = new mynode<K, E> (thePair, nodep);

			if (pre_nodep == nullptr) _head = newNode;
			else pre_nodep->next = newNode;

			_size++;
			return;
		}

	}
	/*输出链表元素*/
	void output (ostream& out) const {
		for (mynode<K, E>* c_node = _head;
			c_node != nullptr;
			c_node = c_node->next) {
			out << c_node->element.key << ":"<< c_node->element.data << "  ";
		}
	}
};

/*输出链表元素的重载函数*/
template <class K, class E>
ostream& operator<<(ostream& out, const myChain<K, E>& x) {
	x.output (out);
	return out;
}

/*哈希链表类
template<class K, class E>
class myhashChains {
protected:
	myChain<K, E>* _chains;							//我的链表
	myhash<K> _myhash;								//自定义的哈希函数
	int _size;										//元素个数
	int _divisor;									//除数，链表的个数
	int inline _getPosByKey (const K& keyin)const;	//获取该关键词的理论位置，注意该返回值需要配个各函数进行分别分析
public:
	myhashChains (int divisorin = 20);				//构造函数
	~myhashChains ();								//析构函数
	bool empty () const;							//返回是否为空
	int size () const;								//返回元素个数
	E* find (const K& keyin) const;					//查找关键词，返回值的指针
	bool insert (mypair<K, E> pairin);				//插入键值对，返回插入成功失败与否
	bool erase (const K& keyin);					//删除元素的包装
	void output (ostream& out) const;				//输出元素
	int getLengthByKey (const K& keyin) const;		//通过关键词获取长度，为了OJ而增加
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

	/*查找关键词，返回值的指针*/
	E* find (const K& keyin) const {
		mypair< K, E>* temp = (_chains[_getPosByKey (keyin)].find (keyin));
		if (temp == nullptr) {
			return nullptr;
		} else {
			return &(temp->data);
		}
	}

	/*插入键值对，返回插入成功失败与否*/
	bool insert (mypair<K, E> pairin) {
		int pos = _getPosByKey (pairin.key);
		int size = _chains[pos].size ();
		_chains[pos].insert (pairin);

		/*链表长度扩大说明插入了，没有扩大说明覆盖了*/
		if (_chains[pos].size () > size) {
			_size++;
			return true;
		} else {
			return false;
		}
	}
	/*删除元素的包装*/
	bool erase (const K& keyin) {return _chains[_getPosByKey(keyin)].erase (keyin);}

	/*输出元素*/
	void output (ostream& out) const {
		for (int i = 0; i < _divisor; i++) {
			if (_chains[i].size () == 0) {
				cout << "Chain" << i << ": NULL ";
			} else {
				cout << "Chain" << i << ":" << _chains[i] << " ";
			}
		}
	}
	/*通过关键词获取长度，为了OJ而增加*/
	int getLengthByKey (const K& keyin) const {
		return _chains[_getPosByKey (keyin)].size ();
	}
};
/*输出重载*/
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
		//cout << "第n次循环" << i<<endl;
		cin >> a >> b;
		switch (a) {
		case 0:
			//cout << "插入" << b << endl;
			if (myhashChain.insert (mypair<int, int> (b, b))) {
			
			} else {
				cout << "Existed\n";
			}
			break;
		case 1:
			//cout << "查找" << b << endl;

			pos = myhashChain.find(b);
			if (pos == nullptr) {
				cout << "Not Found" << "\n";
			} else {
				length = myhashChain.getLengthByKey (b);
				cout << length << "\n";
			}
			break;
		case 2:
			//cout << "删除" << b << endl;

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