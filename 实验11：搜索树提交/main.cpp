/*ʵ��ʮһ  ������
һ��ʵ��Ŀ��
���ն����������ṹ�Ķ��塢��������������ʵ�֡�
����ʵ������
1�������������Ķ����������ࡣ�洢�ṹʹ�������ṩ����:���롢ɾ����������ɾ�������ҡ������β��ҡ������������Ԫ�ء�
2�����ռ���¼���һϵ��������������Ӧ�Ķ�������������ʹ���ı���ʽ��������Լ�///�����������ĸ߶ȡ�
3���Խ����õĶ�����������ִ������������������������⣩������������Ľ�������롢ɾ�����������ɺ�Ķ�����������
	���Ҳ���������ҹ��������αȽϵ�Ԫ�أ���
*/
#include<string>
#include<iostream>
#include"bstree.h"

#define debug
#ifndef debug
#define dprintf /\
/
#else
#define dprintf printf
#endif

int main () {
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);
	bstree<int, int> bst;

	int m= 0;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		int result;
		cin >> a >> b;
		switch (a) {
		case 0://����b���Ѵ��ڷ���0�����뷵�����ֵ
			dprintf ("f0;\n");
			result = bst.insertGetXor (mypair<int, int> (b, b));;
			printf ("%d\n", result);
			break;
		case 1://����b,�ҵ���������Ҳ�������0
			dprintf ("f1;\n");
			result = bst.findGetXor (b);;
			printf ("%d\n", result);
			break;
		case 2://ɾ��b
			dprintf ("f2;\n");

			break;
		case 3://������b��
			dprintf ("f3;\n");

			break;
		case 4://ɾ����b��
			dprintf ("f4;\n");

			break;
		default:
			dprintf ("no func;\n");
			break;
		}
	}


	return 0;
}