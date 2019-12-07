/*实验十一  搜索树
一、实验目的
掌握二叉搜索树结构的定义、描述方法、操作实现。
二、实验内容
1、创建带索引的二叉搜索树类。存储结构使用链表，提供操作:插入、删除、按名次删除、查找、按名次查找、升序输出所有元素。
2、接收键盘录入的一系列整数，输出其对应的二叉搜索树（可使用文本形式输出），以及///二叉搜索树的高度。
3、对建立好的二叉搜索树，执行上述各操作（插入操作除外），输出各操作的结果（插入、删除操作输出完成后的二叉搜索树；
	查找操作输出查找过程中依次比较的元素）。
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
		case 0://插入b，已存在返回0，插入返回异或值
			dprintf ("f0;\n");
			result = bst.insertGetXor (mypair<int, int> (b, b));;
			printf ("%d\n", result);
			break;
		case 1://查找b,找到返回异或，找不到返回0
			dprintf ("f1;\n");
			result = bst.findGetXor (b);;
			printf ("%d\n", result);
			break;
		case 2://删除b
			dprintf ("f2;\n");

			break;
		case 3://搜索第b名
			dprintf ("f3;\n");

			break;
		case 4://删除第b名
			dprintf ("f4;\n");

			break;
		default:
			dprintf ("no func;\n");
			break;
		}
	}


	return 0;
}