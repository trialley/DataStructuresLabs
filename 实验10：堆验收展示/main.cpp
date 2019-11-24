#include"huffManTree.h"
#include<iostream>
using namespace std;



/*1、创建最小堆类。最小堆的存储结构使用数组。提供操作:插入、删除、初始化。
2、接收键盘录入的一系列整数，以文本形式输出其对应的最小堆；
3、对建立好的最小堆，键盘输入插入元素，输出插入操作完成后的堆（可以文本形式表示）；键盘输入删除元素，输出删除操作完成后的堆；
4、键盘输入n, 随机生成n个0~1000之间的整数；输出堆排序的排序过程。
5、键盘输入字符个数n, 以（c，w）形式依次字符和字符出现的频率，字符互不相同，输出Huffman树（可用文本形式）和每个字符的Huffman编码。
*/
int main (void) {
	/*这里是OJ上第一个题目*/
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);

	minHeap<int> h;

	int size;
	cin >> size;
	for (int i = 0; i < size; i++) {
		int temp;
		cin >> temp;
		h.push (temp);
	}
	cout << h.top () << "\n";

	int times;
	cin >> times;
	for (int i = 0; i < times; i++) {
		int func_num;
		cin >> func_num;
		if (func_num == 1) {
			int temp;
			cin >> temp;
			h.push (temp);
			cout << h.top () << "\n";
		} else if (func_num == 2) {
			h.pop ();
			cout << h.top () << "\n";
		} else if (func_num == 3) {
			h._clearAndInit ();
			int size;
			cin >> size;
			for (int i = 0; i < size; i++) {
				int temp;
				cin >> temp;
				h.push (temp);
			}
			for (int i = 0; i < size; i++) {
				cout << h.top () << " ";
				h.pop ();
			}
		}
	}

	cout << "\n";

	/*这里是构建哈夫曼树*/
	cout << "输出霍夫曼树结构：\n";
	//首先空出数组的第一个元素
	int ws[10] = {0, 9,9,9,9,9,9,9 };
	char chars[10] = {'-', 'a','b','c','d','e' };

	//构建哈夫曼树
	btree<char>* x = huffmanTree (ws,chars, 5);
	x->levelOut (cout);
	cout << "\n";



	/*这里是OJ第二个题目*/
	cout << "输出霍夫曼编码长度：\n";
	char str[10000];
	cin >> str;
	cout << calHlen (str);
	cout << "\n";

	return 0;
}
