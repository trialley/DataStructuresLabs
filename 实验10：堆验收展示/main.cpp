#include"huffManTree.h"
#include<iostream>

using namespace std;
int main (void) {
	/*������OJ�ϵ�һ����Ŀ*/
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);

	minHeap<int> h;

	int size;
	cin >> size;
	for (int i = 0; i < size; i++) {
		int temp;
		cin >> temp;
		h.push (temp);
	}
	cout << h.top () << "\n";

	int times;
	cin >> times;
	for (int i = 0; i < times; i++) {
		int func_num;
		cin >> func_num;
		if (func_num == 1) {
			int temp;
			cin >> temp;
			h.push (temp);
			cout << h.top () << "\n";
		} else if (func_num == 2) {
			h.pop ();
			cout << h.top () << "\n";
		} else if (func_num == 3) {
			h._clearAndInit ();
			int size;
			cin >> size;
			for (int i = 0; i < size; i++) {
				int temp;
				cin >> temp;
				h.push (temp);
			}
			for (int i = 0; i < size; i++) {
				cout << h.top () << " ";
				h.pop ();
			}
		}
	}

	cout << "\n";

	/*�����ǹ�����������*/
	cout << "������������ṹ��\n";
	//���ȿճ�����ĵ�һ��Ԫ��
	int ws[10] = {0, 9,9,9,9,9,9,9 };
	char chars[10] = {'-', 'a','b','c','d','e' };

	//������������
	btree<char>* x = huffmanTree (ws,chars, 5);
	x->levelOut (cout);
	cout << "\n";



	/*������OJ�ڶ�����Ŀ*/
	cout << "������������볤�ȣ�\n";
	char str[10000];
	cin >> str;
	cout << calHlen (str);
	cout << "\n";

	return 0;
}
