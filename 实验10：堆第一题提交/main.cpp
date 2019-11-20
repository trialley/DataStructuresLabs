#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
template<class T>
class minHeap {
private:
	int _size;
	int arrayLength;
	T* _head;
	void _extLength () {
		T* temp = new T[arrayLength * 2];
		copy (_head, _head + arrayLength, temp);
		delete[] _head;
		_head = temp;
	}
public:
	typedef enum { min_head_empty }err;
	minHeap (int initialCapacity = 10) {
		arrayLength = initialCapacity + 1;
		_head = new T[arrayLength];
		_size = 0;
	}
	void clear () {
 /*delete[] _head;*/
	}
	~minHeap () { clear (); }
	void clearAndInit () {
		clear ();
		arrayLength = 10;
		_head = new T[10];
		_size = 0;
	}
	bool empty () const { return _size == 0; }
	int size () const {
		return _size;
	}
	const T& top () {
		if (_size == 0)
			throw min_head_empty;
		return _head[1];
	}
	void pop () {
		if (_size == 0)
			throw min_head_empty;
		_head[1].~T ();
		T lastElement = _head[_size--];
		int currentNode = 1,
			child = 2;     // child of currentNode
		while (child <= _size) {
			if (child < _size && _head[child] > _head[child + 1])
				child++;
			if (lastElement <= _head[child])
				break;   // yes
			_head[currentNode] = _head[child]; // move child up
			currentNode = child;             // move down a level
			child *= 2;
		}
		_head[currentNode] = lastElement;
	}
	void push (const T& theElement) {
		if (_size == arrayLength - 1) {
			_extLength ();
			arrayLength *= 2;
		}
		int currentNode = ++_size;
		while (currentNode != 1 && _head[currentNode / 2] > theElement) {
			_head[currentNode] = _head[currentNode / 2]; // move element down
			currentNode /= 2;                          // move to parent
		}
		_head[currentNode] = theElement;
	}
	void initialize (T* theHeap, int theSize) {
		//delete[] _head;
		_head = theHeap;
		_size = theSize;
		for (int root = _size / 2; root >= 1; root--) {
			T rootElement = _head[root];
			int child = 2 * root;
			while (child <= _size) {
				// _head[child] should be smaller sibling
				if (child < _size && _head[child] > _head[child + 1])
					child++;

				// can we put rootElement in _head[child/2]?
				if (rootElement <= _head[child])
					break;  // yes

				 // no
				_head[child / 2] = _head[child]; // move child up
				child *= 2;                    // move down a level
			}
			_head[child / 2] = rootElement;
		}
	}
	void deactivateArray () {
		_head = NULL; arrayLength = _size = 0;
	}
	void output (ostream& out)const {
		copy (_head + 1, _head + _size + 1, ostream_iterator<T> (cout, "  "));
	}
};

template <class T>
ostream& operator<<(ostream& out, const minHeap<T>& x) {
	x.output (out); return out;
}
int main (void) {
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);

	minHeap<int> h;

	int size;
	cin >> size;
	for (int i = 0; i < size; i++) {
		int temp;
		cin >> temp;
		h.push (temp);
	}
	cout << h.top ()<<"\n";
	
	int times;
	cin >> times;
	for (int i = 0; i < times; i++) {
		int func_num;
		cin >> func_num;
		if (func_num == 1) {
			int temp;
			cin >> temp;
			h.push (temp);
			cout << h.top () << "\n";
		} else if (func_num == 2) {
			h.pop ();
			cout << h.top () << "\n";
		} else if (func_num == 3) {
			h.clearAndInit ();
			int size;
			cin >> size;
			for (int i = 0; i < size;i++) {
				int temp;
				cin >> temp;
				h.push (temp);
			}
			for (int i = 0; i < size; i++) {
				cout<<h.top ()<<" ";
				h.pop ();
			}
		}
	}
	return 0;
}
