/*****************************************************************************
*  permutations.cpp                                                          *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @brief    递归求全排列的测试程序                                            *
*  @author   TriAlley                                                        *
*  @email    lg139@139.com                                                   *
*  @version  1.0                                                             *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*  2019/09/11 | 1.0       | TriAlley       | Create file                     *
*****************************************************************************/
#include<iostream>
using namespace std;



/**
 * @brief 求全排列类
 * private:
 *     T* arr;									//元素数组
 *     int num;									//元素个数
 *     void lgswap(T& a, T& b);					//自行编写的交换函数
 *     void show();								//递归结束时显示全排列
 *
 * public:
 *     void calpermutation(int i=0);					//求全排列入口
 */
template<class T>
class permutation {
private:
	T* arr;
	int num;

	/*
	* 功能：显示函数，用于在递归尽头时打印一次结果
	* 输入：两个需要置换的元素
	* 返回：无
	* 特殊说明：iostream中有swap函数，在此使用自己编写的lgswap
	*/
	void lgswap(T& a, T& b) {
		T temp;
		temp = a;
		a = b;
		b = temp;
	}


	/*
	* 功能：显示函数，用于在递归尽头时打印一次结果
	* 输入：无
	* 返回：无
	*/
	void show() {
		for (int i = 0; i < num; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}
public:
	permutation(int inum, T* iarr) :num(inum), arr(iarr) {}

	/*
	* 功能：全排列递归主函数
	* 输入：
	* 	i：当前递归是第几层递归，也即排列到了第几个变量，默认为0
	* 返回：无
	*/
	void calpermutation(int i=0) {
		/*如果是最后一层，则说明这是集合的一个全排列，输出数组内容并返回到上一层*/
		if (i+1 == num) {
			show();
		}

		/*非最后一层的递归，将当前层与剩余各层进行置换，并进入下一层递归*/
		for (int j = i; j < num; j++) {
			lgswap(arr[j], arr[i]);
			calpermutation(i + 1);
			lgswap(arr[j], arr[i]);
		}
	}

};



int main() {
	/*获取输入，初始化数组*/
	cout << "请输入数组大小：";
	int num;
	cin >> num;
	cout << "请输入元素内容，空格分开：";

	int* arr = new int[num];
	for (int i = 0; i < num; i++) {
		cin >> arr[i];
	}

	/*构造类，传入数组大小与数组指针，调用全排列函数*/
	permutation<int> p(num,arr);
	p.calpermutation();

	/*谁申请谁释放，主函数释放数组*/
	delete[] arr;
	return 0;
}
