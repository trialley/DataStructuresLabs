#include<iostream>
#include<math.h>
using namespace std;
template<class E>
class mypair {
public:
	bool first;
	E second;
	mypair () :first (false) {}
	mypair(E in):first(true),second(in){}

};

template<class E>
class arrtree {
protected:
	E** _head;
	int _maxlength;
	int _maxdeepth;
	int _size;
public:
	arrtree (int deepth = 5) {
		_maxdeepth = deepth;
		_maxlength = (int)pow (2, deepth) - 1;
		_size = 0;
		_head = new E * [_maxlength];
		for (int i = 0; i < _maxlength; i++) {
			_head[i] = nullptr;
		}
	}
	arrtree (E* IN, int deepth) {
		_maxdeepth = deepth;
		_maxlength = (int)pow (2, deepth) - 1;
		_size = 0;
		_head = new E * [_maxlength];
		for (int i = 0; i < _maxlength; i++) {
			_head[i] = new E(IN[i]);
		}
	}
	~arrtree () {
		for (int i = 0; i < _maxlength; i++) {
			if(_head[i] != nullptr) {
				delete _head[i];
			}
		}
		delete[] _head;
	}
	void preOrder () {
		for(int level=0; level <_maxdeepth; level++){
			for (int j = 0; j < (int)pow (2, level);j++) {
				int index = (int)pow (2, level) - 1 + j;
				if (_head[index] != nullptr) {
					cout << *_head[index] << "  ";
				}
			}
		}
	}
};

int main(){
	int* a =new int[7];
	for (int i = 0; i < 7; i++) {
		a[i] = i;
	}
	arrtree<int> arr (a,3);
	arr.preOrder ();
	//return 0;
}