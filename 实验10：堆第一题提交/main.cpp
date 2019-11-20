#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
template<class T>
class minHeap {
private:
	int _headSize;
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
		_headSize = 0;
	}
	~minHeap () { /*delete[] _head;*/ }
	bool empty () const { return _headSize == 0; }
	int size () const {
		return _headSize;
	}
	const T& top () {
		if (_headSize == 0)
			throw min_head_empty;
		return _head[1];
	}
	void pop () {
		if (_headSize == 0)
			throw min_head_empty;
		_head[1].~T ();
		T lastElement = _head[_headSize--];
		int currentNode = 1,
			child = 2;     // child of currentNode
		while (child <= _headSize) {
			if (child < _headSize && _head[child] > _head[child + 1])
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
		if (_headSize == arrayLength - 1) {
			_extLength ();
			arrayLength *= 2;
		}
		int currentNode = ++_headSize;
		while (currentNode != 1 && _head[currentNode / 2] > theElement) {
			_head[currentNode] = _head[currentNode / 2]; // move element down
			currentNode /= 2;                          // move to parent
		}
		_head[currentNode] = theElement;
	}
	void initialize (T* theHeap, int theSize) {
		delete[] _head;
		_head = theHeap;
		_headSize = theSize;
		for (int root = _headSize / 2; root >= 1; root--) {
			T rootElement = _head[root];
			int child = 2 * root;
			while (child <= _headSize) {
				// _head[child] should be smaller sibling
				if (child < _headSize && _head[child] > _head[child + 1])
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
		_head = NULL; arrayLength = _headSize = 0;
	}
	void output (ostream& out)const {
		copy (_head + 1, _head + _headSize + 1, ostream_iterator<T> (cout, "  "));
	}
};

template <class T>
ostream& operator<<(ostream& out, const minHeap<T>& x) {
	x.output (out); return out;
}
int main (void) {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	minHeap<int> h (4);
	h.push (10);
	h.push (20);
	h.push (5);

	cout << "Heap size is " << h.size () << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	h.push (15);
	h.push (30);

	cout << "Heap size is " << h.size () << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	// test top and pop
	cout << "The min element is " << h.top () << endl;
	h.pop ();
	cout << "The min element is " << h.top () << endl;
	h.pop ();
	cout << "The min element is " << h.top () << endl;
	h.pop ();
	cout << "Heap size is " << h.size () << endl;
	cout << "Elements in array order are" << endl;
	cout << h << endl;

	int z[10];
	for (int i = 1; i < 10; i++)
		z[i] = 10 - i;
	h.initialize (z, 9);
	cout << "Elements in array order are" << endl;
	cout << h << endl;
	return 0;
}
