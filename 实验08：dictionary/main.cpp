/* ʵ���  ɢ�б�
һ��ʵ��Ŀ��
1������ɢ�б�ṹ�Ķ����ʵ�֡�
2������ɢ�б�ṹ��Ӧ�á�
����ʵ������
1���ֱ�ʹ�� ���Կ���Ѱַ �� ����ɢ�� ������������ɢ�б��ࣻ
2��ʹ��ɢ�б����ʵ��һ���ֵ䣬����ؼ���Ϊ������DΪ961�����ֵ��в������������500����ͬ��������ʵ���ֵ�Ľ���������������*ʵ���ֵ��ɾ����*/



#include"hashtable.h"
#include<iostream>
using namespace std;

int main () {

	hashtable<int, int> h;
	h.insert ( hashtable<int, int>::makepair ( 1, 10 ) );
	int i = 1;
	cout << h.find ( i );

}