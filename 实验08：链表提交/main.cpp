# pragma once
#include<iostream>
using namespace std;

/*对应各种数据类型的哈希函数，此处只写int的哈希函数*/
template <class K> class myhash;
template<>
class myhash<int> {
public:
	size_t operator()(const int theKey) const {
		return size_t (theKey);
	}
};
template <class K, class E>
class mypair {
public:
	K key;
	E data;
	mypair (K keyin, E datain) :key (keyin), data (datain) {}
};
template <class K, class E>
struct mynode {
	typedef mypair< K, E> mypairType;
	typedef mynode< K, E> mynodeType;
	mypairType element;
	mynodeType* next;

	mynode ( mypairType thePair) :element (thePair) {}
	mynode ( mypairType thePair, mynodeType* theNext) :element (thePair), next (theNext) {}
};
template<class K, class E>
class myChain {
protected:
	mynode<K, E>* _head;  // pointer to key mynode in chain
	int _size;                 // number of elements in dictionary
public:
	myChain () { _head = nullptr; _size = 0; }
	~myChain () {
		while (_head != nullptr) {
			mynode<K, E>* nextNode = _head->next;
			delete _head;
			_head = nextNode;
		}
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
	mypair< K, E>* find (const K& theKey) const {
		// Return pointer to matching mypair.
		 // Return nullptr if no matching mypair.
		mynode<K, E>* currentNode = _head;

		// search for match with theKey
		while (currentNode != nullptr && currentNode->element.key != theKey) {
			currentNode = currentNode->next;
		}

		// verify match
		if (currentNode != nullptr && currentNode->element.key == theKey)
			// yes, found match
			return &currentNode->element;

		// no match
		return nullptr;
	}
	bool erase (const K& theKey) {
		mynode<K, E>* p = _head;
		mynode<K, E>* tp = nullptr;

// search for match with theKey
		while (p != nullptr && p->element.key < theKey) {
			tp = p;
			p = p->next;
		}

		// verify match
		if (p != nullptr && p->element.key == theKey) {// found a match
		   // remove p from the chain
			if (tp == nullptr) _head = p->next;  // p is key mynode
			else tp->next = p->next;

			delete p;
			_size--;
			return true;
		}
		return false;
	}
	void insert ( mypair< K, E>& thePair) {
		// Insert thePair into the dictionary. Overwrite existing
		// mypair, if any, with same key.
		mynode<K, E>* p = _head;
		mynode<K, E>* tp = nullptr; // tp trails p

	// move tp so that thePair can be inserted after tp
		while (p != nullptr && p->element.key < thePair.key) {
			tp = p;
			p = p->next;
		}

		// check if there is a matching mypair
		if (p != nullptr && p->element.key == thePair.key) {// replace old value
			p->element.data = thePair.data;
			return;
		}

		// no match, set up mynode for thePair
		mynode<K, E>* newNode = new mynode<K, E> (thePair, p);

		// insert newNode just after tp
		if (tp == nullptr) _head = newNode;
		else tp->next = newNode;

		_size++;
		return;
	}
	void output (ostream& out) const {
		out << "  chain:  ";
		for (mynode<K, E>* currentNode = _head;
			currentNode != nullptr;
			currentNode = currentNode->next) {
			out << currentNode->element.key << " "<< currentNode->element.data << "  ";
		}

	}
};

template <class K, class E>
ostream& operator<<(ostream& out, const myChain<K, E>& x) {
	x.output (out);
	return out;
}

template<class K, class E>
class myhashChains {
protected:
	myChain<K, E>* _chains;  // myhash _chains
	myhash<K> _myhash;              // maps type K to nonnegative integer
	int _size;                 // number of elements in list
	int _divisor;               // myhash function _divisor
public:
	myhashChains (int divisorin = 11) {
		_size = 0;
		_divisor = divisorin;
		_chains = new myChain<K, E>[_divisor];
	}
	~myhashChains () { delete[] _chains; }
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
	E* find (const K& theKey) const {
		mypair< K, E>* temp = (_chains[_myhash (theKey) % _divisor].find (theKey));
		if (temp == nullptr) {
			return nullptr;
		} else {
			return &(temp->data);
		}
	}
	bool insert (mypair<K, E> thePair) {
		int homeBucket = (int)_myhash (thePair.key) % _divisor;
		int homeSize = _chains[homeBucket].size ();
		_chains[homeBucket].insert (thePair);
		if (_chains[homeBucket].size () > homeSize) {
			_size++;
			return true;//
		} else {
			return false;//这里的逻辑有待验证
		}
	}
	bool erase (const K& theKey) {
		return _chains[_myhash (theKey) % _divisor].erase (theKey);
	}

	void output (ostream& out) const {
		for (int i = 0; i < _divisor; i++)
			if (_chains[i].size () == 0) {
				cout << "  chain:  NULL ";
			} else {
				cout << _chains[i] << " ";
			}
	}
	int getLengthByKey (K keyin) {
		return _chains[_myhash (keyin) % _divisor].size ();
	}
};

template <class K, class E>
ostream& operator<<(ostream& out, const myhashChains<K, E>& x) {
	x.output (out); return out;
}

int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
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