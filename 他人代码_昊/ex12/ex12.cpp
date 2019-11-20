/* 
   ex-12 
   Wu Hao
   2019-1-3
*/

#include <queue>
#include <iostream>
#include <vector>
#include <stack>
#define INF 0x3f3f3f
#define MAX 1001
using namespace std;

/*ȫ�ֱ���*/ 
vector< vector<int> > Matrix(MAX, vector<int>(MAX));
//�ڽӾ���洢
vector<int> Reach(MAX), Res_BFS, Res_DFS;
//����� 
vector<bool> reachBFS(MAX, 0), reachDFS(MAX, 0), reach(MAX, 0);
//��¼�Ƿ񵽴�



void BFS(int i, int N) 
{/*
    BFS���������д洢Ҫ�����ĵ�ļ���
	������ÿ���ڶ����е��ڽӵ�
*/ 
	queue<int> que;
	reachBFS[i] = 1;
	que.push(i);
	Res_BFS.push_back(i);
	while (!que.empty()) 
	{
		int top = que.front();
		que.pop();
		for (int j = 1; j <= N; j++) 
		{
			if (reachBFS[j] == 0 && Matrix[top][j] == 1) 
			{
				reachBFS[j] = 1;
				Res_BFS.push_back(j);
				que.push(j);
			}
		}
	}
}



void DFS(int i, int N) 
{/*
   DFS������ÿ������ڽӵ��ڽ���DFS
   �ݹ���� 
*/
	if (reachDFS[i]) return;
	reachDFS[i] = 1;
	Res_DFS.push_back(i);
	for (int j = 1; j <= N; j++) 
	{
		if (reachDFS[j] == 0 && Matrix[i][j] == 1) 
		{
			DFS(j, N);
		}
	}
}


/*����ͼ����ͨ��֧�ĸ��� ����dfs*/
void sep_DFS(int i, int n) 
{
	if (reach[i]) return;
	reach[i] = 1;
	for (int index = 1; index <= n; index++) 
	{
		if (reach[index] == 0 && Matrix[i][index] == 1) 
		{
			sep_DFS(index, n);
		}
	}
}


//�Ͻ�˹�����㷨 ̰���㷨 
int shortPath(int s, int n, int t) 
{
	vector<int> dis(n + 1, INF);  //·��
	vector<int> reachdij(n + 1, 0);  //�Ƿ񵽴�
	dis[s] = 0;
	while (true) 
	{
		int temp = -1;
		for (int i = 1; i <= n; i++) 
		{
			if (!reachdij[i] && (temp == -1 || dis[temp] > dis[i])) temp = i;  //���ڽ� 
		}
		if (temp == -1) break;
		reachdij[temp] = 1;
		for (int i = 1; i <= n; i++) 
		{
			dis[i] = min(dis[i], dis[temp] + Matrix[temp][i]);  //̰�� 
		}
	}
	return dis[t];
}



int main() 
{
	int n,m,s,t;
	//n�ڵ��� m���� s��tĳ�ڵ� 
	queue<int> que;
	cin >> n; cin >> m; cin >> s ; cin >> t;
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= n; j++) 
		{
			if (i != j) 
			Matrix[i][j] = INF;
			else Matrix[i][j] = 0;
		}
	}
	int a,b,c;
	while (m--) 
	{
		cin >> a >> b >> c;
		Matrix[b][a] = Matrix[a][b] = c;
	}
	for (int i = 1; i <= n; i++) 
	{
		Reach[i] = i;
	}
	int count = 0;
	for (int i = 1; i <= n; i++) 
	{
		if (reach[i]) continue;
		count++;
		sep_DFS(i, n);
		que.push(i);
	}
	cout << count << endl;
	while (!que.empty()) 
	{
		cout << que.front() << " ";
		que.pop();
	}
	cout << endl;
	DFS(s, n);
	BFS(t, n);
	cout << Res_DFS.size() << endl;
	for (int index = 0; index < Res_DFS.size(); index++) 
	{
		cout << Res_DFS[index] << " ";
	}
	cout << endl;
	cout << Res_BFS.size() << endl;
	for (int index = 0; index < Res_BFS.size(); index++) 
	{
		cout << Res_BFS[index] << " ";
	}
	cout << endl;
	if (shortPath(s, n, t) == INF) cout << -1 << endl;
	else cout << shortPath(s, n, t);
}
