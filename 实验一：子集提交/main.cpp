/*****************************************************************************
*  subset_test.cpp                                                           *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @file     subset_test.cpp                                                 *
*  @brief    递归求子集程序测试                                                *
*  @author   TriAlley                                                        *
*  @email    lg139@139.com                                                   *
*  @version  1.0                                                             *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*  2019/09/11 | 1.0       | TriAlley       | Create file                     *
*****************************************************************************/
#include<iostream>   //使用输入输出
#include<cstring>    //使用memset
using namespace std;
/**
 * @brief 求子集类
 * private:
 *     T* arr;									//元素数组
 *     int n;									//元素个数
 *     bool* isshowarr;							//显隐控制数组
 *     void show(T* arr, bool* isshow, int n);	//递归结束时显示集合
 *     void isubset(int i, bool isshow);		//求子集主体函数
 *
 * public:
 *     subset(T* ia,int in);					//构造函数
 *     void calsubset();						//求子集入口
 */
template<class T>
class subset {
private:
	T* arr;
	int n;
	bool* isshowarr;
	unsigned int value;
	/**
	 * @brief 递归返回前显示当前状态
	 */
	void cal() {
		unsigned int temp = 0;
		unsigned int num=0;
		for (int i = 0; i < n; i++) {
			if (isshowarr[i]) {
				temp += (++num) * arr[i];
			}
		}
		value = value^temp;
	}
	/**
	 * @brief 求子集主体函数
	 * int i  当前控制的元素之下标，是递归的结束条件之一
	 * bool isshow  指定i所指向元素的显隐
	 */
	void isubset(int i, bool isshow) {
		isshowarr[i] = isshow;
		if (i + 1 == n) {
			cal();
			return;
		}
		isubset(i + 1, false);
		isubset(i + 1, true);
	}
public:
	/**
	 * @brief 构造函数 申请资源
	 * int in 元素总数量
	 * T* ia 元素数组指针
	 */
	subset(T* ia, int in) :n(in), arr(ia) {
		/*对元素显隐控制数组进行初始化*/
		isshowarr = new bool[in];
		value = 0;
		memset(isshowarr, 0, sizeof(bool) * n);
	}

	/**
	 * @brief 析构函数 释放资源
	 */
	~subset() {
		//delete[] arr;		//谁申请谁释放，类不申请元素数组的内存，无需在此释放
		delete[] isshowarr;
	}

	/**
	 * @brief 子集计算的入口
	 */
	void calsubset() {
		isubset(0, false);
		isubset(0, true);
	}

	int getvalue() {
		return value;
	}

};


int main() {
	int num;

	cin >> num;
	int* arr = new int[num];

	for (int i = 0; i < num; i++) {
		int temp;
		cin >> temp;
		arr[i] = temp;
	}

	subset<int> s(arr, num);
	s.calsubset();
	cout << s.getvalue();
	delete[] arr;
	return 0;
}
