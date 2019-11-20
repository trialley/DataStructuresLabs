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

/*全局变量*/ 
vector< vector<int> > Matrix(MAX, vector<int>(MAX));
//邻接矩阵存储
vector<int> Reach(MAX), Res_BFS, Res_DFS;
//到达点 
vector<bool> reachBFS(MAX, 0), reachDFS(MAX, 0), reach(MAX, 0);
//记录是否到达



void BFS(int i, int N) 
{/*
    BFS遍历，队列存储要遍历的点的集合
	，遍历每个在队列中的邻接点
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
   DFS遍历对每个点的邻接点在进行DFS
   递归进行 
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


/*无向图的连通分支的个数 就是dfs*/
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


//迪杰斯特拉算法 贪心算法 
int shortPath(int s, int n, int t) 
{
	vector<int> dis(n + 1, INF);  //路径
	vector<int> reachdij(n + 1, 0);  //是否到达
	dis[s] = 0;
	while (true) 
	{
		int temp = -1;
		for (int i = 1; i <= n; i++) 
		{
			if (!reachdij[i] && (temp == -1 || dis[temp] > dis[i])) temp = i;  //最邻近 
		}
		if (temp == -1) break;
		reachdij[temp] = 1;
		for (int i = 1; i <= n; i++) 
		{
			dis[i] = min(dis[i], dis[temp] + Matrix[temp][i]);  //贪心 
		}
	}
	return dis[t];
}



int main() 
{
	int n,m,s,t;
	//n节点数 m边数 s，t某节点 
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
