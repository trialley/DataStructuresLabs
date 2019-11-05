# pragma once
#include<iostream>
using namespace std;

/*debug专用宏*/
#ifdef DEBUG
#define dprintf printf
#else
#define dprintf /\
/ printf
#endif

/*对应各种数据类型的哈希函数，此处只写int的哈希函数*/
template <class K> class myhash;
template<>
class myhash<int> {
public:
	size_t operator()(const int theKey) const {
		return size_t (theKey);
	}
};

template<class E, class K>
class myhashTable {
public:
	typedef struct pair {
		K key;
		E data;
		pair(K keyin,E datain):key(keyin),data(datain){}
	}pair;

protected:
	myhash<K> myhash;
	/*通过关键词寻找*/
	int _getPosByKey (const K& keyin) const {
		int i = myhash(keyin) % _divisor;
		int pos = i;
		do {
			if (_empty_table_head[pos] || _table_head[pos]->key == keyin) return pos;    //找到或者为空，则返回
			pos = (pos + 1) % _divisor;
		} while (pos != i);           //若又回到i，则退出循环
		return pos;
	}
	int _divisor;   //散列函数的除数
	pair** _table_head;     //散列数组
	bool* _empty_table_head;   //看是否为空的一维数组

public:
	myhashTable (int divisorin = 11):_divisor(divisorin){

		_table_head = new pair*[_divisor];
		for (int i = 0; i < _divisor; i++) {
			_table_head[i] = nullptr;
		}

		_empty_table_head = new bool[_divisor];
		for (int i = 0; i < _divisor; i++) {
			_empty_table_head[i] = true;
		}
	}
	~myhashTable (){
		dprintf ("调用析构函数:\n");
		for (int i = 0; i < _divisor; i++) {
			delete _table_head[i];
		}
		delete[] _table_head;
		delete[] _empty_table_head;
	}

	/*元素存在则返回-1，不出在则返回插入后的下标*/
	int  insertGetPos (const K& keyin,const E& datain) {
		dprintf ("调用插入函数：key：%d  data:%d\n", keyin, datain);
		int b = _getPosByKey (keyin);
		if (_empty_table_head[b]) {
			_empty_table_head[b] = false;
			_table_head[b] = new pair(keyin, datain);
			return b;
		}else {
			return -1;
		}
	}
	/*返回下标，不含有返回-1*/
	int  getPosByKey (const K& keyin) const {
		dprintf ("调用通过关键词获取位置函数：key：%d\n", keyin);
		int b = _getPosByKey (keyin);
		if (_empty_table_head[b] || _table_head[b]->key != keyin)
			return -1;
		else {
			return b;
		}
	}
	/*通过关键词删除键值对，返回移动次数或-1*/
	/*删除：先判断要删除的元素是否为空，若为空，则输出“Not Found“
不为空，判断是否为以下两种情况，其余情况则不需要移。先 将 i移到下一个，判断是否为空，若为空则break，不需要移动，否则
来判断这两种情况，进入if语句，进行移动，然后判断循环条件，while，下一个是否为空或者回到最初的位置b则结束
删除比较复杂，找到元素位置，删除，移动
首先判断目标位置是否为空，为空返回notfound
目标不为空
	循环开始----
	下一个元素是否为空
		为空说明当前元素没有后移，正常返回
		不为空，说明
			
*/
	int  deleteGetNum (const K& keyin) {
		dprintf ("调用删除元素，返回移动的数据：key：%d\n", keyin);
		int delete_pos = _getPosByKey (keyin);
		int move_count = 0;
		if (_empty_table_head[delete_pos]) {
			return -1;
		}else if (_table_head[delete_pos]->key == keyin) {

			_empty_table_head[delete_pos] = true;

			int current_pos = delete_pos;//当前元素当前的实际位置
			int last_pos = delete_pos;//
			int original_pos;//当前元素一般情况下本应该在的位置

			for (;;) {
				current_pos++;//将下一个元素设置为当前元素
				current_pos = current_pos % _divisor;   //当前元素的实际位置
				if (_empty_table_head[current_pos]) {    //当前桶为空或，为空说明前面的元素都在正确位置，直接分返回
					return move_count;
				} else {
					original_pos = myhash(_table_head[current_pos]->key) % _divisor;//下一个桶的元素本应该在哪里
					//cout << "original_pos的值为："<<original_pos << endl; //当前元素本应该在的位置
					if (
							(current_pos != original_pos && original_pos <= last_pos && current_pos > last_pos)||
							(current_pos != original_pos && current_pos < original_pos && last_pos < current_pos) || 
							(current_pos != original_pos && current_pos < original_pos && last_pos >= original_pos)
						) {
						_empty_table_head[last_pos] = false;
						_table_head[last_pos] = _table_head[current_pos];
						_empty_table_head[current_pos] = true;
						move_count++;
						last_pos = current_pos;
					} else {
						continue;
					}
				}
			};
		}
	}
};

int main (){
#pragma warning(disable:4996)
	freopen ( "input.txt", "r", stdin );
	int d, m, a, b,pos;
	cin >> d >> m;
	myhashTable<int, int> hashtable (d);

	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		switch (a){
		case 0:
			pos = hashtable.insertGetPos (b,b);
			if (pos==-1) {
				cout << "Existed\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 1:
			pos = hashtable.getPosByKey (b);
			if (pos == -1) {
				cout << -1<<"\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 2:
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
	}

	return 0;
}


