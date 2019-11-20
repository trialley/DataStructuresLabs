/*二、实验内容
1、 创建二叉树类。二叉树的存储结构使用链表。提供操作:前序遍历、中序
遍历、后序遍历、层次遍历、计算二叉树结点数目、计算二叉树高度。
2、 对建立好的二叉树，执行上述各操作，输出各操作的结果。
3、 接收键盘录入的二叉树前序序列和中序序列(各元素各不相同)，输出该二
叉树的后序序列*/
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