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

	cout << "前序";
	y.PreOutput();
	cout << "中序";
	y.InOutput();
	cout << "后序";
	y.PostOutput();
	cout << "逐层";
	y.LevelOutput();

	int hight = y.getHight();
	cout << "高度" << hight << endl;

	y.PreOrder(ct);
	cout << "Node数目" << lgcount << endl;
	lgcount = 0;

	cout << "删除元素3" << endl;
	int delement = 3;
	int temp = 0;
	y.Delete(3, temp);
	cout << "删除元素3后前序输出" << endl;
	y.PreOutput();

	//-----------------------------------------------------------------
	//接受键盘输入
	cout << "输入节点个数" << endl;
	int Number = 0;
	cin >> Number;
	cout << "输入前序遍历的顺序" << endl;
	int* Pre = new int[Number];
	for (int i = 0; i < Number; i++)
		cin >> Pre[i];

	cout << "输入中序遍历的顺序" << endl;
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