/*
ʵ��ʮ��  ̰���㷨
һ��ʵ��Ŀ��
������С��������Prim�㷨��Kruskal�㷨�ļ���ʵ�֡�
����ʵ������
1��������Ȩ����ͼ�ࡣ��ͼû���رߺ��Ի����洢�ṹ�ֱ�ʹ���ڽӾ�����ڽ������ṩ��Ҫ�Ļ���������
2����������ͼ�ж���ĸ���n�ͱߵ���Ŀe������Ԫ�飨i,j,w����ʽ��������ͼ��ÿһ���߻�������ɺ�e���ߵ�ͼ�����У�i,j,w����ʾ����i�Ͷ���j֮��ӵ��ȨֵΪw�ıߣ�����ͼ��
3. �Խ����õ�ͼ���ֱ�ʹ��Prim�㷨��Kruskal�㷨����С�������������õ���С�����������ı���ʽ����������еĸ����߼���Ӧ��Ȩֵ����
*/

#include<iostream>
#include"linkedWGraph.h"
#include"edge.h"
#define noEdge 1000000
using namespace std;

int main(){
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	cout << "������ͼ�Ķ�����n�ͱ���e" << endl;
	int n, e;
	cin >> n >> e;

	//��ʼ���ڽ���������ͼ
	linkedWGraph<int> g (n);
	cout << "���Զ����(����1,����2��Ȩֵ)����ʽ����ͼ��ÿһ����" << endl;

	//��ʼ������
	for (int i = 0; i < e; i++) {
		int v1, v2, w;  cin >> v1 >> v2 >> w;
		edge<int>* Edge = new edge<int> (v1, v2, w);
		g.insertEdge (v1,v2,w);
	}

	//������С�����������
	edge<int>* STE = new edge<int>[n - 1];
	cout << "kruskal��С��������ÿ����(v1,v2,w)����:" << endl;
	if (g.kruskal (STE) == true) {
		for (int i = 0; i <= n - 2; i++)
			cout << STE[i] << endl;
	}
	cout << "prim��С��������ÿ����(v1,v2,w)����:" << endl;
	if (g.prim (STE) == true) {
		for (int i = 0; i <= n - 2; i++)
			cout << STE[i] << endl;
	}

	cout << "�ڽ�������ڵ�����Ϊ��" << endl;
	g.output (cout);
	if (g.connected () == true) cout << "��ͼ����ͨ�ġ�" << endl;
	else {
		int* lables = new int[n + 1];
		cout << "��ͨ��֧���ǣ�" << g.getCC (lables) << endl;
		for (int i = 1; i <= n; i++)
			cout << "����" << i << "���ڵ�" << lables[i] << "��ͨ��֧" << endl;

		delete[] lables;
	}
	int* reach = new int[n + 1];
	fill (reach, reach + n + 1, 0);

	cout << "BFS���У�";   g.printBfs (1);
	cout << "DFS���У�";   g.printDfs (1);
	cout << endl;
	delete[] reach;

	int* predecessor = new int[n + 1];
	cout << "��������ʼ��ͽ����㣺";  int start, dest;  cin >> start >> dest;
	cout << endl << "���·��" << g.dijkstra (start, dest, predecessor) << endl;
	cout << "���·��Ϊ��";
	n = dest;  cout << dest << " ";
	while (predecessor[n] != 0) {
		cout << predecessor[n] << " ";
		n = predecessor[n];
	}
	delete[] predecessor;

	return 0;
}