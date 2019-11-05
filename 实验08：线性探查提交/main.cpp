# pragma once
#include<iostream>


using namespace std;

template<class E, class K>
class hashTable {
protected:
	+
private:
	int _getPosByKey (const K& k) const {
		int i = k % _divisor;   //�� k��Ӧɢ�б��λ��
		int j = i;
		do {
			if (_empty_table_head[j] || _table_head[j] == k) return j;    //�ҵ�����Ϊ�գ��򷵻�
			j = (j + 1) % _divisor;

		} while (j != i);           //���ֻص�i�����˳�ѭ��
		return j;
	}
	int _divisor;   //ɢ�к����ĳ���
	E* _table_head;     //ɢ������
	bool* _empty_table_head;   //���Ƿ�Ϊ�յ�һά����

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

	/*Ԫ�ش����򷵻�-1���������򷵻ز������±�*/
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
	/*�����±꣬�����з���-1*/
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
				i = (i + 1) % _divisor;   //��ǰԪ�ص�ʵ��λ��
				if (_empty_table_head[i]) {    //����һ���Ƿ�Ϊ��
					break;
				}
				x = _table_head[i] % _divisor;
				//cout << "x��ֵΪ��"<<x << endl; //��ǰԪ�ر�Ӧ���ڵ�λ��
				if (i != x && x <= z && i > z) {     //������
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


