#include<iostream>
#include"adjacencyWGraph.h"
#define noEdge 1000000
using namespace std;

int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	cout << "������ͼ�Ķ�����n�ͱ���e" << endl;
	int n, e;  cin >> n >> e;
	adjacencyWGraph<int> AWGraph (n, noEdge);
	cout << "���Զ����(����1,����2��Ȩֵ)����ʽ����ͼ��ÿһ����" << endl;

	for (int i = 0; i < e; i++) {
		int v1, v2, w;  cin >> v1 >> v2 >> w;
		edge<int>* Edge = new edge<int> (v1, v2, w);
		AWGraph.insertEdge (Edge);
	}
	if (AWGraph.connected () == true) cout << "��ͼ����ͨ�ġ�" << endl;
	else {
		int* c = new int[n + 1];
		cout << "��ͨ��֧���ǣ�" << AWGraph.labelComponents (c) << endl;
		for (int i = 1; i <= n; i++)
			cout << "����" << i << "���ڵ�" << c[i] << "��ͨ��֧" << endl;
		delete[] c;
	}
	cout << "������һ��������ţ�"; int num; cin >> num;
	int* reach = new int[n + 1];
	cout << "BFS���У�";   AWGraph.print_bfs (num, reach);
	cout << "DFS���У�";   AWGraph.print_dfs (num, reach);  cout << endl;
	delete[] reach;


	int* predecessor = new int[n + 1]; cout << "��������ʼ��ͽ����㣺";  int start, dest;  cin >> start >> dest;
	cout << endl << "���·��" << AWGraph.Dijkstra (start, dest, predecessor) << endl;
	cout << "���·��Ϊ��";
	n = dest;  cout << dest << " ";
	while (predecessor[n] != 0) {
		cout << predecessor[n] << " ";
		n = predecessor[n];
	}
	delete[] predecessor;
	return 0;
}