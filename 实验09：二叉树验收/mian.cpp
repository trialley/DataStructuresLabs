#include<iostream>
#include"btree.h"
#define max(a,b) (a<b ? b:a)//用于获取左右子树中最大的那个层数
using namespace std;
/*实验九  二叉树操作
1.二叉树的存储结构使用链表。
2.提供操作:前序遍历、中序遍历、后序遍历、层次遍历
3.计算二叉树结点数目、计算二叉树高度。
4.接收键盘录入的二叉树前序序列和中序序列(各元素各不相同)，输出该二叉树的后序序列。*/

/*本题目第二三个小任务的核心函数，计算每个节点为根的树的层数与节点数*/
void cal (btree<int>::node* rootin, int* sizes, int* deepthes) {
	//如果传入空则直接返回
	if (rootin) {
		//首先递归计算节点为根的树的节点数与层数，所有子节点全部计算完毕后再计算当前元素
		cal (rootin->left, sizes, deepthes);
		cal (rootin->right, sizes, deepthes);

		//对于该节点
		//若当前元素没有子节点，则以其为根的树的节点数与层数均为1
		if (rootin->left == nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = 1;
			deepthes[rootin->data] = 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "都无\n";

		//若当前元素有左子树，则以其为根的树的节点数与层数为左子树相应数据加1
		} else if (rootin->left != nullptr && rootin->right == nullptr) {
			sizes[rootin->data] = sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "左有\n";

		//若当前元素有右子树，则以其为根的树的节点数与层数为右子树相应数据加1
		} else if (rootin->left == nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + 1;
			deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
			//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "右都有\n";

		//若当前元素有左右子树，则以其为根的树的节点数与层数为左右子树相应数据相加再加1
		} else if (rootin->left != nullptr && rootin->right != nullptr) {
			sizes[rootin->data] = sizes[rootin->right->data] + sizes[rootin->left->data] + 1;
			deepthes[rootin->data] = max (deepthes[rootin->right->data], deepthes[rootin->left->data]) + 1;
			//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "左右都有\n";
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

	/*初始化存储节点数与层数的数组*/
	int* sizes = new int[num + 1];
	memset (sizes, 0, num + 1);
	int* deepthes = new int[num + 1];
	memset (deepthes, 0, num + 1);

	/*初始化众节点*/
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

	/*计算deepths与sizes*/
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
