/*****************************************************************************
*  permutations_test.cpp                                                     *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @file     permutations_test.cpp                                           *
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
#include<iostream>

/**
 * @brief 求全排列类
 * private:
 *     T* arr;									//元素数组
 *     int n;									//元素个数
 *     void lgswap(T& a, T& b);					//自行编写的交换函数
 *     void show();								//递归结束时显示全排列
 *     void ipermutation(int i)					//求全排列主体函数
 *
 * public:
 *     permutation(T* iarr, int in);			//构造函数
 *     void calpermutation()					//求全排列入口
 */
template<class T>
class permutation {
private:
	T* arr;
	int n;
	unsigned int value;
	/**
	* @brief iostream中有swap函数，在此使用自己编写的lgswap
	*/
	void lgswap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	/**
	* @brief 全排列计算的显示函数
	*/
	void cal() {
		unsigned int temp=0;
		for (unsigned int i = 0; i < n; i++){
			temp += (i+1)^(unsigned int)arr[i];
		}
		value=value | temp;
	}

	/**
	* @brief 全排列计算的主体函数
	*/
	void ipermutation(int i) {

		/*如果是最后一层，则说明这是集合的一个全排列，输出数组内容并返回到上一层*/
		if (i + 1 == n) {
			cal();
			return;
		}

		/*非最后一层的递归，将当前层与剩余各层进行置换，并进入下一层递归*/
		for (int j = i; j < n; j++) {
			lgswap(arr[j], arr[i]);
			ipermutation(i + 1);
			lgswap(arr[j], arr[i]);
		}
	}
public:
	/**
	* @brief 构造函数
	*/
	permutation(T* iarr, int in) :arr(iarr), n(in) {
		value = 0;
	}
	//~permutation() {}

	/**
	* @brief 全排列计算的入口
	*/
	void calpermutation() {
		/*非最后一层的递归，将当前层与剩余各层进行置换，并进入下一层递归*/
		ipermutation(0);
	}
	unsigned int getvalue() { return value; }
	//int getlength()const { return n; }
	//T& getvalue(int i)const { return arr[i]; }

};

int main() {
	int num;
	cin >> num;
	int* arr = new int[num];
	for (int i = 0; i < num; i++) {
		cin >> arr[i];
	}

	permutation<int> p(arr, num);
	p.calpermutation();
	cout << p.getvalue();
}