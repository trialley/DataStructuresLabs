#include<iostream>
#include"bstree.h"
using namespace std;
#define fori(i,n) for(int i=0;i<(int)(n);i++)
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )




int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);

	//#pragma warning(disable:4996)
	//	freopen ("input.txt", "r", stdin);
	bstree<int> b;
	int num = 10;
	int nums[] = { 6, 8, 9, 7,1, 5, 4,  3,11,15};
	//初始化二叉搜索树，随机1-100
	fori (i,num) {
		b.insert (nums[i]);
	}
	cout << "树内容为：" << b;
	cout << "树高度为：" << calF (b)<<"\n";


	cout << "\n\n测试各种操作：插入、删除、按名次删除、查找、按名次查找\n";
	cout << "\n\n测试插入 99\n";
	b.insert (99);
	cout << "树内容为：" << b;

	cout << "\n\n测试删除 99\n";
	b.erase (99);
	cout << "树内容为：" << b;

	cout << "\n\n测试按名次删除 1\n";
	b.eraseByIndes (1);
	cout << "树内容为：" << b;

	cout << "\n\n测试查找 99 7\n";
	cout << b.search (99)<<"\n\n";
	cout << b.search (7);

	cout << "\n\n测试按名次查找 b[4]==7\n";
	cout<<b.getPByIndex (4);

}
