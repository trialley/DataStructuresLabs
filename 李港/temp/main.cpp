#include <iostream>
#include "BinaryTree.h"
#include <math.h>

using namespace std;

int lgcount = 0;

BinaryTree<int> a, x, y, z, h;

void ct(BinaryTreeNode<int>* t) { lgcount++; }

int main(int argc, char* argv[])
{
	y.MakeTree(1, a, a);
	z.MakeTree(2, a, a);
	x.MakeTree(3, y, z);
	h.MakeTree(5, a, a);
	y.MakeTree(4, x, h);

	cout << "ǰ��";
	y.PreOutput();
	cout << "����";
	y.InOutput();
	cout << "����";
	y.PostOutput();
	cout << "���";
	y.LevelOutput();

	int hight = y.getHight();
	cout << "�߶�" << hight << endl;

	y.PreOrder(ct);
	cout << "Node��Ŀ" << lgcount << endl;
	lgcount = 0;

	cout << "ɾ��Ԫ��3" << endl;
	int delement = 3;
	int temp = 0;
	y.Delete(3, temp);
	cout << "ɾ��Ԫ��3��ǰ�����" << endl;
	y.PreOutput();

	//-----------------------------------------------------------------
	//���ܼ�������
	cout << "����ڵ����" << endl;
	int Number = 0;
	cin >> Number;
	cout << "����ǰ�������˳��" << endl;
	int* Pre = new int[Number];
	for (int i = 0; i < Number; i++)
		cin >> Pre[i];

	cout << "�������������˳��" << endl;
	int* In = new int[Number];
	for (int i = 0; i < Number; i++)
		cin >> In[i];

	BinaryTree<int> g;
	g.PreInMakeTree(Pre, In, Number);
	g.PostOutput();

	system("pause");
	cout << "" << endl;
	return 0;
}