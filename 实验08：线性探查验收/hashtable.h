# pragma once
#include<iostream>

/*对应各种数据类型的哈希函数，此处只写int的哈希函数*/
template <class K> class myhash;
template<>
class myhash<int> {
public:
	size_t operator()(const int theKey) const {
		return size_t (theKey);
	}
};


/*用于存储键值的类*/
template <class K, class E>
class mypair {
public:
	K key;
	E data;
	mypair (K keyin, E datain) :key (keyin), data (datain) {}
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
	friend std::ostream& operator << (std::ostream& out, myhashTable& in)
	int getPosByKey (const K& keyin) const;				//通过关键词获取该元素的理论位置
*/
template<class E, class K>
class myhashTable {
//public:
//	typedef struct mypair<K,E> {
//		K key;
//		E data;
//		mypair<K,E> (K keyin, E datain) :key (keyin), data (datain) {}
//	}mypair<K,E>;

protected:
	myhash<K> myhashf;
	int _divisor;   //散列函数的除数
	mypair<K,E>** _table_head;     //散列数组
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
	E* find (K& keyin) {
		int temp = getPosByKey (keyin);
		if (temp== -1) {
			return nullptr;
		} else {
			return &(_table_head[temp]->data);
		}

	}
	myhashTable (int divisorin = 20) :_divisor (divisorin) {
		_table_head = new mypair<K,E> * [_divisor];
		for (int i = 0; i < _divisor; i++) {
			_table_head[i] = nullptr;
		}
	}
	~myhashTable () {
		for (int i = 0; i < _divisor; i++) {

		}
		delete[] _table_head;
	}
	int erase (const K& keyin) {
		return deleteGetNum (keyin);
	}
	/*通过关键词删除键值对，返回移动次数或-1*/
	int  deleteGetNum (const K& keyin) {
		int delete_pos = _getPosByKey (keyin);
		if (_table_head[delete_pos] == nullptr) {
			return -1;
		} else if (_table_head[delete_pos]->key == keyin) {
			_table_head[delete_pos] = nullptr;//内存溢出

			int current_pos = delete_pos;//当前元素当前的实际位置
			int last_pos = delete_pos;//
			int original_pos;//当前元素一般情况下本应该在的位置

			int move_count = 0;
			for (;;) {
				current_pos++;//将下一个元素设置为当前元素
				current_pos = current_pos % _divisor;   //当前元素的实际位置
				if (_table_head[current_pos] == nullptr) {    //当前桶为空或，为空说明前面的元素都在正确位置，直接删除并返回
					return move_count;
				} else {
					//original_pos = myhashf (_table_head[current_pos]->key) % _divisor;//当前元素本应该在哪里
					if (current_pos != _getPosByKey (_table_head[current_pos]->key)) {
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
	int  insertGetPos (const K& keyin, const E& datain) {
		int b = _getPosByKey (keyin);
		if (_table_head[b] == nullptr) {
			_table_head[b] = new mypair<K,E> (keyin, datain);
			return b;
		} else {
			return -1;
		}
	}
	int insert (mypair<K,E>& pairin) {
		return insertGetPos (pairin.key, pairin.data);
	}
	friend std::ostream& operator << (std::ostream& out, myhashTable& in) {
		for (int i = 0; i < in._divisor; i++) {
			if (in._table_head[i] == nullptr) {
				out << "null" << " ";
			} else {
				out << in._table_head[i]->key << ":" << in._table_head[i]->data<<" ";
			}
		}
		return  out;
	}
};