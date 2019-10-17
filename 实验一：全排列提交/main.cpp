/*****************************************************************************
*  permutations_test.cpp                                                     *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @file     permutations_test.cpp                                           *
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
#include<iostream>

/**
 * @brief ��ȫ������
 * private:
 *     T* arr;									//Ԫ������
 *     int n;									//Ԫ�ظ���
 *     void lgswap(T& a, T& b);					//���б�д�Ľ�������
 *     void show();								//�ݹ����ʱ��ʾȫ����
 *     void ipermutation(int i)					//��ȫ�������庯��
 *
 * public:
 *     permutation(T* iarr, int in);			//���캯��
 *     void calpermutation()					//��ȫ�������
 */
template<class T>
class permutation {
private:
	T* arr;
	int n;
	unsigned int value;
	/**
	* @brief iostream����swap�������ڴ�ʹ���Լ���д��lgswap
	*/
	void lgswap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	/**
	* @brief ȫ���м������ʾ����
	*/
	void cal() {
		unsigned int temp=0;
		for (unsigned int i = 0; i < n; i++){
			temp += (i+1)^(unsigned int)arr[i];
		}
		value=value | temp;
	}

	/**
	* @brief ȫ���м�������庯��
	*/
	void ipermutation(int i) {

		/*��������һ�㣬��˵�����Ǽ��ϵ�һ��ȫ���У�����������ݲ����ص���һ��*/
		if (i + 1 == n) {
			cal();
			return;
		}

		/*�����һ��ĵݹ飬����ǰ����ʣ���������û�����������һ��ݹ�*/
		for (int j = i; j < n; j++) {
			lgswap(arr[j], arr[i]);
			ipermutation(i + 1);
			lgswap(arr[j], arr[i]);
		}
	}
public:
	/**
	* @brief ���캯��
	*/
	permutation(T* iarr, int in) :arr(iarr), n(in) {
		value = 0;
	}
	//~permutation() {}

	/**
	* @brief ȫ���м�������
	*/
	void calpermutation() {
		/*�����һ��ĵݹ飬����ǰ����ʣ���������û�����������һ��ݹ�*/
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