/*����ʵ������
1�� �����������ࡣ�������Ĵ洢�ṹʹ�������ṩ����:ǰ�����������
�����������������α�������������������Ŀ������������߶ȡ�
2�� �Խ����õĶ�������ִ������������������������Ľ����
3�� ���ռ���¼��Ķ�����ǰ�����к���������(��Ԫ�ظ�����ͬ)������ö�
�����ĺ�������*/
#include"BinaryTree.h"
#include<iostream>
using namespace std;

int main() {

	BinaryTree<int> b;
	
	b.ChangeRoot(
		1,
		b.MakeNode(2,
			b.MakeNode(4),
			b.MakeNode(5),
		),
		b.MakeNode(
			3,
			b.MakeNode(6),
			b.MakeNode(7),
		)
	);


	int n;
	cin >> n;

	return 0;
}