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


/*template<class E, class K>
class myhashTable {
public:
	struct pair;
protected:
	myhash<K> myhashf;
	int _divisor;										//散列函数的除数
	pair** _table_head;									//散列数组
	int  _getPosByKey (const K& keyin) const;			//返回下标，不含有返回-1
public:
	myhashTable (int divisorin = 20);					//
	int  insertGetPos (const K& keyin, const E& datain);//元素存在则返回-1，不出在则返回插入后的下标
	int  deleteGetNum (const K& keyin);					//通过关键词删除键值对，返回移动次数或-1*
	friend ostream& operator << (ostream& out, myhashTable& in)
	int getPosByKey (const K& keyin) const;				//通过关键词获取该元素的理论位置
*/
template<class E, class K>
class myhashTable {
public:
	typedef struct pair {
		K key;
		E data;
		pair(K keyin,E datain):key(keyin),data(datain){}
	}pair;

protected:
	myhash<K> myhashf;
	int _divisor;   //散列函数的除数
	pair** _table_head;     //散列数组
		/*返回下标，不含有返回-1*/
	int  _getPosByKey (const K& keyin) const {
		int i = keyin % _divisor;   //找 k对应散列表的位置
		int j = i;
		do {
			if (!(_table_head[j] != nullptr && _table_head[j]->key != keyin)) return j;    //找到或者为空，则返回
			j = (j + 1) % _divisor;

		} while (j != i);           //若又回到i，则退出循环
		return j;
	}

public:
	int getPosByKey (const K& keyin) const {
		int pos = _getPosByKey (keyin);
		if (_table_head[pos] == nullptr) {
			return -1;
		} else {
			return pos;
		}
	}
	myhashTable (int divisorin = 20):_divisor(divisorin){
		_table_head = new pair*[_divisor];
		for (int i = 0; i < _divisor; i++) {
			_table_head[i] = nullptr;
		}
	}
	~myhashTable (){
		for (int i = 0; i < _divisor; i++) {

		}
		delete[] _table_head;
	}

	/*通过关键词删除键值对，返回移动次数或-1*/
	int  deleteGetNum (const K& keyin) {
		int delete_pos = _getPosByKey (keyin);
		if (_table_head[delete_pos]==nullptr) {
			return -1;
		}else if (_table_head[delete_pos]->key == keyin) {
			_table_head[delete_pos] = nullptr;//内存溢出

			int current_pos = delete_pos;//当前元素当前的实际位置
			int last_pos = delete_pos;//
			int original_pos;//当前元素一般情况下本应该在的位置

			int move_count = 0;
			for (;;) {
				current_pos++;//将下一个元素设置为当前元素
				current_pos = current_pos % _divisor;   //当前元素的实际位置
				if (_table_head[current_pos]==nullptr) {    //当前桶为空或，为空说明前面的元素都在正确位置，直接删除并返回
					return move_count;
				} else {
					original_pos = myhashf(_table_head[current_pos]->key) % _divisor;//当前元素本应该在哪里
					if (current_pos!= _getPosByKey(_table_head[current_pos]->key)) {
						_table_head[last_pos] = _table_head[current_pos];//移动指针，无需delete
						_table_head[current_pos] = nullptr;//内存溢出
						move_count++;
						last_pos = current_pos;
					} else {
						continue;
					}
				}
			};
		}
	}

	/*元素存在则返回-1，不出在则返回插入后的下标*/
	int  insertGetPos (const K& keyin,const E& datain) {
		int b = _getPosByKey (keyin);
		if (_table_head[b] == nullptr) {
			_table_head[b] = new pair(keyin, datain);
			return b;
		}else {
			return -1;
		}
	}

	friend ostream& operator << (ostream& out, myhashTable& in) {
		for (int i = 0; i < in._divisor; i++) {
			if (in._table_head[i] == nullptr) {
				out << "np" << " ";
			} else {
				out << in._table_head[i]->key << " ";
			}
		}
		return  out;
	}
};

int main (){
#pragma warning(disable:4996)
	//freopen ( "input.txt", "r", stdin );
	int d, m, a, b,pos;
	cin >> d >> m;
	myhashTable<int, int> hashtable (d);

	for (int i = 1; i <= m; i++) {
		//cout << "第n次循环" << i<<endl;
		cin >> a >> b;
		switch (a){
		case 0:
			//cout << "插入" << b << endl;
			pos = hashtable.insertGetPos (b,b);
			if (pos==-1) {
				cout << "Existed\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 1:
			//cout << "查找" << b << endl;

			pos = hashtable.getPosByKey (b);
			if (pos == -1) {
				cout << -1<<"\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 2:
			//cout << "删除" << b << endl;

			pos = hashtable.deleteGetNum (b);
			if (pos == -1) {
				cout << "Not Found\n";
			}else {
				cout << pos << "\n";
			}
			break;
		default:
			break;
		}

		//cout << endl << endl << hashtable << endl << endl;
	}

	return 0;
}