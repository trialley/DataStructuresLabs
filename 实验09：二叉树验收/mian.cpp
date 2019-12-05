#include<iostream>
#include"btree.h"
#define max(a,b) (a<b ? b:a)//���ڻ�ȡ���������������Ǹ�����
using namespace std;
/*ʵ���  ����������
1.�������Ĵ洢�ṹʹ������
2.�ṩ����:ǰ���������������������������α���
3.��������������Ŀ������������߶ȡ�
4.���ռ���¼��Ķ�����ǰ�����к���������(��Ԫ�ظ�����ͬ)������ö������ĺ������С�*/

/*����Ŀ�ڶ�����С����ĺ��ĺ���������ÿ���ڵ�Ϊ�������Ĳ�����ڵ���*/
void cal (btree<int>::node* rootin, int* sizes, int* deepthes) {
	//����������ֱ�ӷ���
	if (rootin) {
		//���ȵݹ����ڵ�Ϊ�������Ľڵ���������������ӽڵ�ȫ��������Ϻ��ټ��㵱ǰԪ��
		cal (rootin->left, sizes, deepthes);
		cal (rootin->right, sizes, deepthes);

		//���ڸýڵ�
		//����ǰԪ��û���ӽڵ㣬������Ϊ�������Ľڵ����������Ϊ1
		if (rootin->left == nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = 1;
			deepthes[rootin->data] = 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

		//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
		} else if (rootin->left != nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

		//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
		} else if (rootin->left == nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "�Ҷ���\n";

		//����ǰԪ��������������������Ϊ�������Ľڵ��������Ϊ����������Ӧ��������ټ�1
		} else if (rootin->left != nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = max (deepthes[rootin->right->data], deepthes[rootin->left->data]) + 1;
			//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "���Ҷ���\n";
		}
	}
	return;
}


int main () {

	cout << "\nbuild tree and print\n";
	#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);

	int num = 0;
	cin >> num;

	/*��ʼ���洢�ڵ��������������*/
	int* sizes = new int[num + 1];
	memset (sizes, 0, num + 1);
	int* deepthes = new int[num + 1];
	memset (deepthes, 0, num + 1);

	/*��ʼ���ڽڵ�*/
	btree<int> a;
	btree<int>::node** nodes = new btree<int>::node * [num + 1];
	for (int i = 1; i <= num; i++) {
		nodes[i] = new  btree<int>::node;
	}
	for (int i = 1; i <= num; i++) {
		int l = 0;
		int r = 0;
		cin >> l >> r;
		nodes[i]->data = i;
		nodes[i]->left = l == -1 ? nullptr : nodes[l];
		nodes[i]->right = r == -1 ? nullptr : nodes[r];

		sizes[i] = 1;
		deepthes[i] = 1;
	}
	a.setRoot (nodes[1]);
	cout << "inout:";
	a.midOut (cout);
	cout << "\npreout:";
	a.preOut (cout);
	cout << "\npostout:";
	a.postOut (cout);
	cout << "\nlevelout:";
	a.levelOut (cout);
	cout << "\n";

	/*����deepths��sizes*/
	cal (nodes[1], sizes, deepthes);
	cout << "size:";
	for (int i = 1; i <= num; i++) {
		cout << sizes[i] << " ";
	}
	cout << "\n";
	cout << "deepth:";
	for (int i = 1; i <= num; i++) {
		cout << deepthes[i] << " ";
	}
	cout << "\n";


	cout << "\nmake tree from pre and in\n";
	char  pre[] = { 'a','b','c','d','e','f','g','h','\0' };
	char in[] = { 'c','d','b','a','g','f','e','h','\0' };

	btree<char> b;

	b.buildFromPreIn (pre, in, 8);


	cout <<"pre:"<< pre << endl;
	cout <<"in:"<< in << endl;
	cout << "post:";
	b.postOut (cout);
	return 0;
	return 0;
}
