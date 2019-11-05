# pragma once
#include<iostream>


using namespace std;

template<class E, class K>
class HashTable {
public:
	HashTable (int divisor = 11);
	~HashTable ()
	{
		delete[]ht;
		delete[]empty;
	}

	/*Ԫ�ش����򷵻�-1���������򷵻ز������±�*/
	int  Insert (const E& e) {
		K k = e;
		int b = hSearch (k);
		if (empty[b]) {
			empty[b] = false;
			ht[b] = e;
			return b;
		}
		else {
			return -1;
		}
		//return *this;
	}
	/*�����±꣬�����з���-1*/
	int  NewSearch (const K& k) const {
		int b = hSearch (k);
		if (empty[b] || ht[b] != k)
			return -1;          //Ϊ�ջ����ҵ�����ʼͰ��hSearch��i��λ��
		else {
			return b;
		}
	}
	int  Delete (const E& e) {
		K k = e;
		int b = hSearch (k);
		int Count = 0;
		if (empty[b]) {
			//cout << "Not Found" << endl;
			return -1;
		}

		else if (ht[b] == k) {

			empty[b] = true;
			int i = b;
			int z = b;
			int x;

			do {
				i = (i + 1) % D;   //��ǰԪ�ص�ʵ��λ��
				if (empty[i]) {    //����һ���Ƿ�Ϊ��
					break;
				}
				x = ht[i] % D;
				//cout << "x��ֵΪ��"<<x << endl; //��ǰԪ�ر�Ӧ���ڵ�λ��
				if (i != x && x <= z && i > z) {     //������
					empty[z] = false;
					ht[z] = ht[i];
					empty[i] = true;
					Count++;
					z = i;
					//cout << "good" << endl;

				}
				else if ((i != x && i < x && z < i) || (i != x && i < x && z >= x)) {
					empty[z] = false;
					ht[z] = ht[i];
					empty[i] = true;
					Count++;
					z = i;
				}
			} while (!empty[i + 1] && (i + 1) != b);

			return Count;
			//cout << Count << endl;
		}
	}
private:
	int hSearch (const K& k) const {
		int i = k % D;   //�� k��Ӧɢ�б��λ��
		int j = i;
		do {
			if (empty[j] || ht[j] == k) return j;    //�ҵ�����Ϊ�գ��򷵻�
			j = (j + 1) % D;

		} while (j != i);           //���ֻص�i�����˳�ѭ��
		return j;
	}
	int D;   //ɢ�к����ĳ���
	E* ht;     //ɢ������
	bool* empty;   //���Ƿ�Ϊ�յ�һά����
};
template<class E, class K>
HashTable<E, K>::HashTable (int divisor) {
	D = divisor;

	ht = new E[D];
	empty = new bool[D];

	for (int i = 0; i < D; i++) {
		empty[i] = true;
	}
}

int main (){
#pragma warning(disable:4996)
	freopen ( "input.txt", "r", stdin );
	int d, m, a, b,pos;
	cin >> d >> m;
	HashTable<int, int> h (d);

	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		switch (a){
		case 0:
			pos = h.Insert (b);
			if (pos==-1) {
				cout << "Existed\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 1:
			pos = h.NewSearch (b);
			if (pos == -1) {
				cout << -1<<"\n";
			}else {
				cout << pos << "\n";
			}
			break;
		case 2:
			pos = h.Delete (b);
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


