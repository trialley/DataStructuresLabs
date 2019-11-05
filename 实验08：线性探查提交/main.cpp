# pragma once
#include<iostream>


using namespace std;

template<class E, class K>
class hashTable {
protected:
	+
private:
	int _getPosByKey (const K& k) const {
		int i = k % _divisor;   //找 k对应散列表的位置
		int j = i;
		do {
			if (_empty_table_head[j] || _table_head[j] == k) return j;    //找到或者为空，则返回
			j = (j + 1) % _divisor;

		} while (j != i);           //若又回到i，则退出循环
		return j;
	}
	int _divisor;   //散列函数的除数
	E* _table_head;     //散列数组
	bool* _empty_table_head;   //看是否为空的一维数组

public:
	hashTable (int divisorin = 11):_divisor(divisorin){

		_table_head = new E[_divisor];
		_empty_table_head = new bool[_divisor];

		for (int i = 0; i < _divisor; i++) {
			_empty_table_head[i] = true;
		}
	}
	~hashTable (){
		delete[]_table_head;
		delete[]_empty_table_head;
	}

	/*元素存在则返回-1，不出在则返回插入后的下标*/
	int  insertGetPos (const E& e) {
		K k = e;
		int b = _getPosByKey (k);
		if (_empty_table_head[b]) {
			_empty_table_head[b] = false;
			_table_head[b] = e;
			return b;
		}else {
			return -1;
		}
		//return *this;
	}
	/*返回下标，不含有返回-1*/
	int  getPosByKey (const K& k) const {
		int b = _getPosByKey (k);
		if (_empty_table_head[b] || _table_head[b] != k)
			return -1;
		else {
			return b;
		}
	}
	int  deleteGetNum (const E& e) {
		K k = e;
		int b = _getPosByKey (k);
		int Count = 0;
		if (_empty_table_head[b]) {
			//cout << "Not Found" << endl;
			return -1;
		}

		else if (_table_head[b] == k) {

			_empty_table_head[b] = true;
			int i = b;
			int z = b;
			int x;

			do {
				i = (i + 1) % _divisor;   //当前元素的实际位置
				if (_empty_table_head[i]) {    //看下一个是否为空
					break;
				}
				x = _table_head[i] % _divisor;
				//cout << "x的值为："<<x << endl; //当前元素本应该在的位置
				if (i != x && x <= z && i > z) {     //被挤走
					_empty_table_head[z] = false;
					_table_head[z] = _table_head[i];
					_empty_table_head[i] = true;
					Count++;
					z = i;
					//cout << "good" << endl;

				}
				else if ((i != x && i < x && z < i) || (i != x && i < x && z >= x)) {
					_empty_table_head[z] = false;
					_table_head[z] = _table_head[i];
					_empty_table_head[i] = true;
					Count++;
					z = i;
				}
			} while (!_empty_table_head[i + 1] && (i + 1) != b);

			return Count;
		}
	}
};

int main (){
#pragma warning(disable:4996)
	freopen ( "input.txt", "r", stdin );
	int d, m, a, b,pos;
	cin >> d >> m;
	hashTable<int, int> h (d);

	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		switch (a){
		case 0:
			pos = h.insertGetPos (b);
			if (pos==-1) {
				cout << "Existed\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 1:
			pos = h.getPosByKey (b);
			if (pos == -1) {
				cout << -1<<"\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 2:
			pos = h.deleteGetNum (b);
			if (pos == -1) {
				cout << "Not Found\n";
			}else {
				cout << pos << "\n";
			}
			break;
		default:
			break;
		}
	}

	return 0;
}


