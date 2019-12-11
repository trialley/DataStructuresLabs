#include<iostream>
#include"bstree.h"
using namespace std;
#define fori(i,n) for(int i=0;i<(int)(n);i++)
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )




int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);

	//#pragma warning(disable:4996)
	//	freopen ("input.txt", "r", stdin);
	bstree<int> b;
	int num = 10;
	int nums[] = { 6, 8, 9, 7,1, 5, 4,  3,11,15};
	//��ʼ�����������������1-100
	fori (i,num) {
		b.insert (nums[i]);
	}
	cout << "������Ϊ��" << b;
	cout << "���߶�Ϊ��" << calF (b)<<"\n";


	cout << "\n\n���Ը��ֲ��������롢ɾ����������ɾ�������ҡ������β���\n";
	cout << "\n\n���Բ��� 99\n";
	b.insert (99);
	cout << "������Ϊ��" << b;

	cout << "\n\n����ɾ�� 99\n";
	b.erase (99);
	cout << "������Ϊ��" << b;

	cout << "\n\n���԰�����ɾ�� 1\n";
	b.eraseByIndes (1);
	cout << "������Ϊ��" << b;

	cout << "\n\n���Բ��� 99 7\n";
	cout << b.search (99)<<"\n\n";
	cout << b.search (7);

	cout << "\n\n���԰����β��� b[4]==7\n";
	cout<<b.getPByIndex (4);

}
