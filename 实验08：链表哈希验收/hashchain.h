# pragma once
#include<iostream>

/*对应各种数据类型的哈希函数，此处只写int的哈希函数*/
template <class K> class myhash;
template<>
class myhash<int> {
public:
	size_t operator()(const int keyin) const { return size_t (keyin); }
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
	mypair< K, E>  element;
	mynode< K, E>* next;
	mynode (mypair< K, E>  pairin) :element (pairin), next (nullptr) {}
	mynode (mypair< K, E>  pairin, mynode< K, E>* nextin) :element (pairin), next (nextin) {}
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

		/*一直寻找直到找到对应元素*/
		for (;;) {
			if (c_node == nullptr || c_node->element.key == keyin) {
				break;
			}
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
	void output (std::ostream& out) const {
		mynode<K, E>* c_node = _head;
		while (c_node != nullptr) {
			out << c_node->element.key << ":" << c_node->element.data << "  ";
			c_node = c_node->next;
		}
	}
};

/*输出链表元素的重载函数*/
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const myChain<K, E>& in) {
	in.output (out);
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
		int old_size = _chains[pos].size ();
		_chains[pos].insert (pairin);

		/*链表长度扩大说明插入了，没有扩大说明覆盖了*/
		if (_chains[pos].size () > old_size) {
			_size++;
			return true;
		} else {
			return false;
		}
	}
	/*删除元素的包装*/
	bool erase (const K& keyin) { return _chains[_getPosByKey (keyin)].erase (keyin); }

	/*输出元素*/
	void output (std::ostream& out) const {
		for (int i = 0; i < _divisor; i++) {
			if (_chains[i].size () == 0) {
				std::cout << "Chain" << i << ": nothing ";
			} else {
				std::cout << "Chain" << i << ": " << _chains[i] << " ";
			}
		}
	}
	/*通过关键词获取长度，为了OJ而增加*/
	int getLengthByKey (const K& keyin) const {
		return _chains[_getPosByKey (keyin)].size ();
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
};
/*输出重载*/
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const myhashChains<K, E>& in) {
	in.output (out);
	return out;
}
