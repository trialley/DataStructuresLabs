/*****************************************************************************
*  permutations.cpp                                                          *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @brief    �ݹ���ȫ���еĲ��Գ���                                            *
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
 * @brief ��ȫ������
 * private:
 *     T* arr;									//Ԫ������
 *     int num;									//Ԫ�ظ���
 *     void lgswap(T& a, T& b);					//���б�д�Ľ�������
 *     void show();								//�ݹ����ʱ��ʾȫ����
 *
 * public:
 *     void calpermutation(int i=0);					//��ȫ�������
 */
template<class T>
class permutation {
private:
	T* arr;
	int num;

	/*
	* ���ܣ���ʾ�����������ڵݹ龡ͷʱ��ӡһ�ν��
	* ���룺������Ҫ�û���Ԫ��
	* ���أ���
	* ����˵����iostream����swap�������ڴ�ʹ���Լ���д��lgswap
	*/
	void lgswap(T& a, T& b) {
		T temp;
		temp = a;
		a = b;
		b = temp;
	}


	/*
	* ���ܣ���ʾ�����������ڵݹ龡ͷʱ��ӡһ�ν��
	* ���룺��
	* ���أ���
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
	* ���ܣ�ȫ���еݹ�������
	* ���룺
	* 	i����ǰ�ݹ��ǵڼ���ݹ飬Ҳ�����е��˵ڼ���������Ĭ��Ϊ0
	* ���أ���
	*/
	void calpermutation(int i=0) {
		/*��������һ�㣬��˵�����Ǽ��ϵ�һ��ȫ���У�����������ݲ����ص���һ��*/
		if (i+1 == num) {
			show();
		}

		/*�����һ��ĵݹ飬����ǰ����ʣ���������û�����������һ��ݹ�*/
		for (int j = i; j < num; j++) {
			lgswap(arr[j], arr[i]);
			calpermutation(i + 1);
			lgswap(arr[j], arr[i]);
		}
	}

};



int main() {
	/*��ȡ���룬��ʼ������*/
	cout << "�����������С��";
	int num;
	cin >> num;
	cout << "������Ԫ�����ݣ��ո�ֿ���";

	int* arr = new int[num];
	for (int i = 0; i < num; i++) {
		cin >> arr[i];
	}

	/*�����࣬���������С������ָ�룬����ȫ���к���*/
	permutation<int> p(num,arr);
	p.calpermutation();

	/*˭����˭�ͷţ��������ͷ�����*/
	delete[] arr;
	return 0;
}
