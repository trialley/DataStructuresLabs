#include<iostream>
using namespace std;
#include"linktable.h"
#include<cstdlib>
#include<ctime>
#define lgrand(min,max) (rand()%(max-min+1))+min 
/*ʵ��ʮ�� �ֶ���֮
һ��ʵ��Ŀ��
���շֶ���֮�㷨�������ѡ�������ϵ�Ӧ�á�
����ʵ������
1����дһ���鲢�������Ҫ�����������洢Ԫ�ء�������Ϊ��������
���Ѻ�����Ϊ������ chain ���һ����Ա����;
2���������� n, ������� n �� 0~1000 ֮���������������������� 1 ��
�鲢����Ĺ��̡�

*3�� �޸�ѡ������ĳ��� 18 �C 9�� ��ѭ�����������еĵݹ���ã� ��������
n, ������� n �� 0~1000 ֮��������������������飬���� k, �����������
���е� K С��Ԫ�أ���������ıȽϴ�����*/
int main() {
	srand((int)time(0));//ʹ��ϵͳʱ����Ϊ�������
	int num;
	cin >> num;

	
	chain<int> c;

	for (int i = 0; i < num;i++)c.push(lgrand(1,1000));

	c.ShowChain();
	c.callMergeSort();
	return 0;
}