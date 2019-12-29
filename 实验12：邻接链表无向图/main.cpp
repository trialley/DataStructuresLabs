/*
1.��������ͼ�ࡣ�洢�ṹ�ֱ�ʹ���ڽӾ�����ڽ������ṩ������
1.����һ����
2.ɾ��һ����
3.������BFS��DFS��

2.��������ͼ�ж���ĸ���n�ͱߵ���Ŀe���Զ���ԣ�i��j����ʽ
��������ͼ��ÿһ���߻�������ɺ�e���ߵ�ͼ�����У�i,j����ʾ
����i�Ͷ���j֮���б�����������ͼ��-

3.�ж�ͼ�Ƿ���ͨ��������ͨ�������ͼ����ͨ�����ĸ�����ÿ��
��ͨ�����еĶ��㣻-

4.�Խ����õ���ͨͼ����������һ���㣬����Ӹö��㿪ʼ��һ��
DFS���к�BFS���У�һ��DFS��������BFS���������������ı���ʽ
�����

5.�������������㣬���������֮������·����-
*/

#include<iostream>
#include"linkedWGraph.h"
#define noEdge 1000000
using namespace std;

int main(){
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);

	cout<<"������ͼ�Ķ�����n�ͱ���e"<<endl;
	int n,e;  
	cin>>n>>e;
	linkedWGraph<int> g(n);
	cout<<"���Զ���� ����1 ����2 Ȩֵ ����ʽ����ͼ��ÿһ����"<<endl;

	for(int i=0;i<e;i++){
		int v1,v2,w; 
		cin>>v1>>v2>>w;
		g.insertEdge(v1,v2,w);
	}
	//cout<<"�ڽ�������ڵ�����Ϊ��"<<endl;
	//g.output(cout);
	if (g.connected () == true) {
		cout << "��ͼ����ͨ�ġ�" << endl;
	} else {
		int* c = new int[n + 1];
		int ltfzs = g.getCC (c);
		cout << "��ͨ��֧���ǣ�" << ltfzs << endl;
		for (int i = 1; i <= ltfzs; i++) {
			for (int j = 1; j <= n; j++)
				if (c[j] == i)cout << j << " ";
			cout << "\n";
		}


		delete[] c;
	}
	cout<<"������һ��������ţ�"; int num; cin>>num;
	cout<<"BFS���У�";   g.printBfs (num);
	cout<<"DFS���У�";   g.printDfs (num);  cout<<endl;
	
	int* path=new int[n+1]; 
	cout<<"��������ʼ��ͽ����㣺";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"���·��"<<g.dijkstra(start,dest,path)<<endl;
	cout<<"���·��Ϊ��"; 
	n=dest;  cout<<dest<<" ";
	while(path[n]!=0){
		cout<<path[n]<<" ";
		n=path[n];
	}
	delete[] path;

	return 0;
}