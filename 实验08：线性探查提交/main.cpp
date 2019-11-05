# pragma once
#include<iostream>
using namespace std;

/*debugר�ú�*/
#ifdef DEBUG
#define dprintf printf
#else
#define dprintf /\
/ printf
#endif

/*��Ӧ�����������͵Ĺ�ϣ�������˴�ֻдint�Ĺ�ϣ����*/
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
	/*ͨ���ؼ���Ѱ��*/
	int _getPosByKey (const K& keyin) const {
		int i = myhash(keyin) % _divisor;
		int pos = i;
		do {
			if (_empty_table_head[pos] || _table_head[pos]->key == keyin) return pos;    //�ҵ�����Ϊ�գ��򷵻�
			pos = (pos + 1) % _divisor;
		} while (pos != i);           //���ֻص�i�����˳�ѭ��
		return pos;
	}
	int _divisor;   //ɢ�к����ĳ���
	pair** _table_head;     //ɢ������
	bool* _empty_table_head;   //���Ƿ�Ϊ�յ�һά����

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
		dprintf ("������������:\n");
		for (int i = 0; i < _divisor; i++) {
			delete _table_head[i];
		}
		delete[] _table_head;
		delete[] _empty_table_head;
	}

	/*Ԫ�ش����򷵻�-1���������򷵻ز������±�*/
	int  insertGetPos (const K& keyin,const E& datain) {
		dprintf ("���ò��뺯����key��%d  data:%d\n", keyin, datain);
		int b = _getPosByKey (keyin);
		if (_empty_table_head[b]) {
			_empty_table_head[b] = false;
			_table_head[b] = new pair(keyin, datain);
			return b;
		}else {
			return -1;
		}
	}
	/*�����±꣬�����з���-1*/
	int  getPosByKey (const K& keyin) const {
		dprintf ("����ͨ���ؼ��ʻ�ȡλ�ú�����key��%d\n", keyin);
		int b = _getPosByKey (keyin);
		if (_empty_table_head[b] || _table_head[b]->key != keyin)
			return -1;
		else {
			return b;
		}
	}
	/*ͨ���ؼ���ɾ����ֵ�ԣ������ƶ�������-1*/
	/*ɾ�������ж�Ҫɾ����Ԫ���Ƿ�Ϊ�գ���Ϊ�գ��������Not Found��
��Ϊ�գ��ж��Ƿ�Ϊ������������������������Ҫ�ơ��� �� i�Ƶ���һ�����ж��Ƿ�Ϊ�գ���Ϊ����break������Ҫ�ƶ�������
���ж����������������if��䣬�����ƶ���Ȼ���ж�ѭ��������while����һ���Ƿ�Ϊ�ջ��߻ص������λ��b�����
ɾ���Ƚϸ��ӣ��ҵ�Ԫ��λ�ã�ɾ�����ƶ�
�����ж�Ŀ��λ���Ƿ�Ϊ�գ�Ϊ�շ���notfound
Ŀ�겻Ϊ��
	ѭ����ʼ----
	��һ��Ԫ���Ƿ�Ϊ��
		Ϊ��˵����ǰԪ��û�к��ƣ���������
		��Ϊ�գ�˵��
			
*/
	int  deleteGetNum (const K& keyin) {
		dprintf ("����ɾ��Ԫ�أ������ƶ������ݣ�key��%d\n", keyin);
		int delete_pos = _getPosByKey (keyin);
		int move_count = 0;
		if (_empty_table_head[delete_pos]) {
			return -1;
		}else if (_table_head[delete_pos]->key == keyin) {

			_empty_table_head[delete_pos] = true;

			int current_pos = delete_pos;//��ǰԪ�ص�ǰ��ʵ��λ��
			int last_pos = delete_pos;//
			int original_pos;//��ǰԪ��һ������±�Ӧ���ڵ�λ��

			for (;;) {
				current_pos++;//����һ��Ԫ������Ϊ��ǰԪ��
				current_pos = current_pos % _divisor;   //��ǰԪ�ص�ʵ��λ��
				if (_empty_table_head[current_pos]) {    //��ǰͰΪ�ջ�Ϊ��˵��ǰ���Ԫ�ض�����ȷλ�ã�ֱ�ӷַ���
					return move_count;
				} else {
					original_pos = myhash(_table_head[current_pos]->key) % _divisor;//��һ��Ͱ��Ԫ�ر�Ӧ��������
					//cout << "original_pos��ֵΪ��"<<original_pos << endl; //��ǰԪ�ر�Ӧ���ڵ�λ��
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


