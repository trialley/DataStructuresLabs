#include<iostream>
using namespace std;
#include"linktable.h"
#include<cstdlib>
#include<ctime>
#define lgrand(min,max) (rand()%(max-min+1))+min 
/*实验十四 分而治之
一、实验目的
掌握分而治之算法在排序和选择问题上的应用。
二、实验内容
1、编写一个归并排序程序，要求用链表来存储元素。输出结果为排序后的链
表。把函数作为单链表 chain 类的一个成员函数;
2、键盘输入 n, 随机生成 n 个 0~1000 之间的整数，建立单链表，输出 1 中
归并排序的过程。

*3、 修改选择问题的程序 18 – 9， 用循环来代替其中的递归调用； 键盘输入
n, 随机生成 n 个 0~1000 之间的整数，建立整数数组，输入 k, 输出该整数数
组中第 K 小的元素；输出所花的比较次数。*/
int main() {
	srand((int)time(0));//使用系统时间作为随机种子
	int num;
	cin >> num;

	
	chain<int> c;

	for (int i = 0; i < num;i++)c.push(lgrand(1,1000));

	c.ShowChain();
	c.callMergeSort();
	return 0;
}