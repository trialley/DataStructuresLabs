/*****************************************************************************
*  subset_test.cpp                                                           *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @file     subset_test.cpp                                                 *
*  @brief    �ݹ����Ӽ��������                                                *
*  @author   TriAlley                                                        *
*  @email    lg139@139.com                                                   *
*  @version  1.0                                                             *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*  2019/09/11 | 1.0       | TriAlley       | Create file                     *
*****************************************************************************/
#include<iostream>   //ʹ���������
#include<cstring>    //ʹ��memset
using namespace std;
/**
 * @brief ���Ӽ���
 * private:
 *     T* arr;									//Ԫ������
 *     int n;									//Ԫ�ظ���
 *     bool* isshowarr;							//������������
 *     void show(T* arr, bool* isshow, int n);	//�ݹ����ʱ��ʾ����
 *     void isubset(int i, bool isshow);		//���Ӽ����庯��
 *
 * public:
 *     subset(T* ia,int in);					//���캯��
 *     void calsubset();						//���Ӽ����
 */
template<class T>
class subset {
private:
	T* arr;
	int n;
	bool* isshowarr;
	unsigned int value;
	/**
	 * @brief �ݹ鷵��ǰ��ʾ��ǰ״̬
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
	 * @brief ���Ӽ����庯��
	 * int i  ��ǰ���Ƶ�Ԫ��֮�±꣬�ǵݹ�Ľ�������֮һ
	 * bool isshow  ָ��i��ָ��Ԫ�ص�����
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
	 * @brief ���캯�� ������Դ
	 * int in Ԫ��������
	 * T* ia Ԫ������ָ��
	 */
	subset(T* ia, int in) :n(in), arr(ia) {
		/*��Ԫ����������������г�ʼ��*/
		isshowarr = new bool[in];
		value = 0;
		memset(isshowarr, 0, sizeof(bool) * n);
	}

	/**
	 * @brief �������� �ͷ���Դ
	 */
	~subset() {
		//delete[] arr;		//˭����˭�ͷţ��಻����Ԫ��������ڴ棬�����ڴ��ͷ�
		delete[] isshowarr;
	}

	/**
	 * @brief �Ӽ���������
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
