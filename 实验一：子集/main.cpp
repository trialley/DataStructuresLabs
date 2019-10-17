/*****************************************************************************
*  subset.cpp                                                                *
*  Copyright (C) 2019 TriAlley  lg139@139.com.                               *
*                                                                            *
*  @file     subset.cpp                                                      *
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
 *     void show();	//�ݹ����ʱ��ʾ����
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

	/**
	 * @brief �ݹ鷵��ǰ��ʾ��ǰ״̬
	 */
	void show() {
		cout << "{";
		bool showcam = false;
		for (int i = 0; i < n; i++) {

			if (isshowarr[i]) {
				if (showcam) {
					cout << ",";
				}
				cout << arr[i];
				showcam = true;
			} else {

			}

		}
		cout << "}" << endl;
	}

	/**
	 * @brief ���Ӽ����庯��
	 * int i  ��ǰ���Ƶ�Ԫ��֮�±꣬�ǵݹ�Ľ�������֮һ
	 * bool isshow  ָ��i��ָ��Ԫ�ص�����
	 */
	void isubset(int i, bool isshow) {
		isshowarr[i] = isshow;
		if (i + 1 == n) {
			show();
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
};


int main() {
	/*��ȡ�����С������*/
	int num;
	cout << "�����������С��";
	cin >> num;
	int* arr = new int[num];

	cout << "�������������ݣ��ո�ֿ���";
	for (int i = 0; i < num; i++) {
		int temp;
		cin >> temp;
		arr[i] = temp;
	}

	/*��ʼ�����Ӽ��ಢ���ú���*/
	subset<int> s(arr, num);
	s.calsubset();

	/*˭����˭�ͷ�*/
	delete[] arr;
	return 0;
}
