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
	mypairType element;
	mynode<K, E>* next;

	mynode ( mypairType thePair) :element (thePair) {}
	mynode ( mypairType thePair, mynode<K, E>* theNext) :element (thePair), next (theNext) {}
};
template<class K, class E>
class sortedChain {
protected:
	mynode<K, E>* _key_mynode;  // pointer to key mynode in chain
	int _size;                 // number of elements in dictionary
public:
	sortedChain () { _key_mynode = nullptr; _size = 0; }
	~sortedChain () {
		// Destructor.  Delete all mynodes.
		while (_key_mynode != nullptr) {// delete _key_mynode
			mynode<K, E>* nextNode = _key_mynode->next;
			delete _key_mynode;
			_key_mynode = nextNode;
		}
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
	mypair< K, E>* find (const K& theKey) const {
		// Return pointer to matching mypair.
		 // Return nullptr if no matching mypair.
		mynode<K, E>* currentNode = _key_mynode;

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
	void erase (const K& theKey) {
		// Delete the mypair, if any, whose key equals theKey.
		mynode<K, E>* p = _key_mynode,
			* tp = nullptr; // tp trails p

// search for match with theKey
		while (p != nullptr && p->element.key < theKey) {
			tp = p;
			p = p->next;
		}

		// verify match
		if (p != nullptr && p->element.key == theKey) {// found a match
		   // remove p from the chain
			if (tp == nullptr) _key_mynode = p->next;  // p is key mynode
			else tp->next = p->next;

			delete p;
			_size--;
		}
	}
	void insert ( mypair< K, E>& thePair) {
		// Insert thePair into the dictionary. Overwrite existing
		// mypair, if any, with same key.
		mynode<K, E>* p = _key_mynode;
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
		if (tp == nullptr) _key_mynode = newNode;
		else tp->next = newNode;

		_size++;
		return;
	}
	void output (ostream& out) const {// Insert the chain elements into the stream out.
		out << "  chain:  ";
		for (mynode<K, E>* currentNode = _key_mynode;
			currentNode != nullptr;
			currentNode = currentNode->next)
			out << currentNode->element.key << " "
			<< currentNode->element.data << "  ";
	}
};

template <class K, class E>
ostream& operator<<(ostream& out, const sortedChain<K, E>& x) {
	x.output (out);
	return out;
}

template<class K, class E>
class myhashChains {
public:



public:
	myhashChains (int theDivisor = 11) {
		divisor = theDivisor;
		dSize = 0;

		table = new sortedChain<K, E>[divisor];
	}
	~myhashChains () { delete[] table; }
	bool empty () const { return dSize == 0; }
	int size () const { return dSize; }
	E find (const K& theKey) const {
		mypair< K, E>* temp = (table[myhash (theKey) % divisor].find (theKey));
		if (temp == nullptr) {
			return (E)0;
		} else {
			return temp->data;
		}
	}
	void insert (mypair<K, E> thePair) {
		int homeBucket = (int)myhash (thePair.key) % divisor;
		int homeSize = table[homeBucket].size ();
		table[homeBucket].insert (thePair);
		if (table[homeBucket].size () > homeSize)
			dSize++;
	}
	void erase (const K& theKey) {
		table[myhash (theKey) % divisor].erase (theKey);
	}

	void output (ostream& out) const {
		for (int i = 0; i < divisor; i++)
			if (table[i].size () == 0)
				cout << "  chain:  NULL " ;
			else
				cout << table[i]<<" ";
	}
protected:
	sortedChain<K, E>* table;  // myhash table
	myhash<K> myhash;              // maps type K to nonnegative integer
	int dSize;                 // number of elements in list
	int divisor;               // myhash function divisor
};

template <class K, class E>
ostream& operator<<(ostream& out, const myhashChains<K, E>& x) {
	x.output (out); return out;
}

int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	int d, m, a, b, pos=0;
	cin >> d >> m;
	myhashChains<int, int> myhashChain (d);

	for (int i = 1; i <= m; i++) {
		//cout << "第n次循环" << i<<endl;
		cin >> a >> b;
		switch (a) {
		case 0:
			cout << "插入" << b << endl;
			myhashChain.insert (mypair<int,int>(b, b));
			if (pos == -1) {
				cout << "Existed\n";
			} else {
				cout << pos << "\n";
			}
			break;
		case 1:
			cout << "查找" << b << endl;

			pos = myhashChain.find(b);
			if (pos == -1) {
				cout << -1 << "\n";
			} else {
				cout << pos << "\n";
			}
			break;
		case 2:
			cout << "删除" << b << endl;

			myhashChain.erase (b);
			if (pos == -1) {
				cout << "Delete Failed\n";
			} else {
			//	cout << myhashChain.getSize () << "\n";
			}
			break;
		default:
			break;
		}
		cout << endl << endl << myhashChain << endl << endl;

	}

	return 0;
}