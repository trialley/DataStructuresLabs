/* 实验八  散列表
一、实验目的
1、掌握散列表结构的定义和实现。
2、掌握散列表结构的应用。
二、实验内容
1、分别使用 线性开型寻址 和 链表散列 解决溢出，创建散列表类；
2、使用散列表设计实现一个字典，假设关键字为整数且D为961，在字典中插入随机产生的500个不同的整数，实现字典的建立和搜索操作。*实现字典的删除。*/



#include"hashtable.h"
#include<iostream>
using namespace std;

int main () {

	hashtable<int, int> h;
	h.insert ( hashtable<int, int>::makepair ( 1, 10 ) );
	int i = 1;
	cout << h.find ( i );

}