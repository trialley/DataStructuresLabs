#include<iostream>
#include<math.h>
#include<stack>
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
	mypair<E>* _head;
	int _maxlength;
	int _maxdeepth;
	int _size;
public:
	arrtree (int deepth = 5) {
		//_maxdeepth = deepth;
		//_maxlength = (int)pow (2, deepth) - 1;
		//_size = 0;
		//_head = new mypair<E>[_maxlength];
		//for (int i = 0; i < _maxlength; i++) {
		//	_head[i].;
		//}
	}
	arrtree (E* IN, int deepth) {
		_maxdeepth = deepth;
		_maxlength = (int)pow (2, deepth) - 1;
		_size = 0;
		_head =new  mypair<E>[_maxlength];
		for (int i = 0; i < _maxlength; i++) {
			_head[i].first = true;
			_head[i].second=IN[i];

		}
	}
	~arrtree () {
		//for (int i = 0; i < _maxlength; i++) {
		//	if(_head[i] != nullptr) {
		//		delete _head[i];
		//	}
		//}
		delete[] _head;
	}
	E* getByPos (int level,int pos) {
		int prenum = (int)pow (2, level);
		int index = prenum - 1 + pos;
		if (_head[index].first) {
			return &_head[index].second;
		} else {
			return nullptr;
		}
	}
	//void preOrder () {
	//	for (int level = 0; level < _maxdeepth; level++) {
	//		int prenum = (int)pow (2, level);
	//		for (int j = 0; j < ; j++) {
	//			int index = prenum - 1 + j;
	//			if (_head[index].first) {
	//				cout << _head[index].second << "  ";
	//			}
	//		}
	//	}
	//}
	void preOrder (int rootindex=1) {
		if (rootindex > _maxlength) {
			return;
		}
		//注意用于递归的索引和用于获取值的索引不一样
		if (_head[rootindex-1].first) {
			cout << _head[rootindex-1].second << "  ";
			//索引为rootindex的节点，其左孩子为（2*rootindex） 右孩子为（ 2*rootindex+1
			preOrder (2 * rootindex);
			preOrder (2 * rootindex + 1);
		} else {
			return;
		}

	}
	void levelOrder () {
		for(int level=0; level <_maxdeepth; level++){
			int prenum = (int)pow (2, level);
			for (int j = 0; j < prenum;j++) {
				int index = prenum - 1 + j;
				if (_head[index].first) {
					cout << _head[index].second << "  ";
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