/*ʵ��ʮ��  ̰���㷨
һ��ʵ��Ŀ��
������С��������Prim�㷨��Kruskal�㷨�ļ���ʵ�֡�
����ʵ������
1��������Ȩ����ͼ�ࡣ��ͼû���رߺ��Ի����洢�ṹ�ֱ�ʹ���ڽӾ�����ڽ������ṩ��Ҫ�Ļ���������
2����������ͼ�ж���ĸ���n�ͱߵ���Ŀe������Ԫ�飨i,j,w����ʽ��������ͼ��ÿһ���߻�������ɺ�e���ߵ�ͼ�����У�i,j,w����ʾ����i�Ͷ���j֮��ӵ��ȨֵΪw�ıߣ�����ͼ��
3. �Խ����õ�ͼ���ֱ�ʹ��Prim�㷨��Kruskal�㷨����С�������������õ���С�����������ı���ʽ����������еĸ����߼���Ӧ��Ȩֵ����
*/
#include<iostream>
#include"adjacencyWGraph.h"
#define noEdge 1000000
#define until(re) while(!(re))

using namespace std;

int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	cout << "������ͼ�Ķ�����n�ͱ���e" << endl;
	int n, e;  cin >> n >> e;
	adjacencyWGraph<int> g (n, noEdge);
	cout << "���Զ����(����1,����2��Ȩֵ)����ʽ����ͼ��ÿһ����" << endl;

	for (int i = 0; i < e; i++) {
		int _from, _to, _w;  cin >> _from >> _to >> _w;
		edge<int>* Edge = new edge<int> (_from, _to, _w);
		g.insertEdge (Edge);
	}

	edge<int>* STE = new edge<int>[n - 1];
	cout << "kruskal��С��������ÿ����(v1,v2,w)����:" << endl;
	if (g.kruskal (STE) == true) {
		for (int i = 0; i <= n - 2; i++)
			cout << STE[i] << endl;
	}
	cout << "prim��С��������ÿ����(v1,v2,w)����:" << endl;
	if (g.prim (STE) == true) {
		for (int i = 0; i <= n - 2; i++) {
			cout << STE[i] << endl;
		}
	}
	return 0;
}
