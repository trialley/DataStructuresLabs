/*
1.��������ͼ�ࡣ�洢�ṹ�ֱ�ʹ���ڽӾ�����ڽ������ṩ������
1.����һ����
2.ɾ��һ����
3.������BFS��DFS��
2.��������ͼ�ж���ĸ���n�ͱߵ���Ŀe���Զ���ԣ�i��j����ʽ��������ͼ��ÿһ���߻�������ɺ�e���ߵ�ͼ�����У�i,j����ʾ����i�Ͷ���j֮���б�����������ͼ��
3.�ж�ͼ�Ƿ���ͨ��������ͨ�������ͼ����ͨ�����ĸ�����ÿ����ͨ�����еĶ��㣻
4.�Խ����õ���ͨͼ����������һ���㣬����Ӹö��㿪ʼ��һ��DFS���к�BFS���У�һ��DFS��������BFS���������������ı���ʽ�����
5.�������������㣬���������֮������·����
*/


#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
	#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	Graph<int,int> a;
	cin >> a;
	cout << a;
	return 0;
	/*Ŀ¼��
	<<                                              //��ʽ���������������ʱ�Ķ������򶥵�������Ҫ����Ϊ��дһ��cout������
	>>                                              //��ʽ������
	bool GraphEmpty()const;							//�ж�ͼ�շ�
	int NumberOfVertices();							//���ض�����
	int NumberOfEdges();							//���ر���
	E getWeight(int v1, int v2);					//ȡ��v1,v2��Ȩֵ
	T getValue(int i);								//ȡλ��i��ֵ����������0
	int getFirstNeighbor(T k);                      //ȡ����Ϊk�ĵ�һ���ڽӽڵ�
	int getFirstNeighbor(int k,char type);          //ȡ����λ��Ϊk�ĵ�һ���ڽӽڵ�
	int getNextNeighbor(int k, int w);				//ȡ����Ϊk���ڽӶ���λ��w����һ���ڽӶ���λ�ã��±궨λ���㣩
	int getNextNeighbor(T k, int w, char type);		//ȡ����λ��Ϊk���ڽӶ���λ��w����һ���ڽӶ���λ��(�������ݶ�λ���㣩
	bool insertVertex(const T& vertex);				//����һ������
	bool insertEdge(T n1, T n2, E cost = 1);		//�����(n1,n2)��ȨֵΪcost����ֻ��һ�������ɸ��ǣ��ظ�������ͬ�ߡ�����������Լ����Լ��ı�
	bool removeVertex(T v1);						//ɾ������v1����֮��صıߡ���ɾ�����һ�����㡣
	bool removeEdge(T n1, T n2);					//ɾ���ߣ�n1,n2��
	int outdegree(T v);								//����(����ͼ���ȵ�����ȣ�
	int indegree(T v);								//���
	void DFS(Graph&G, const T&v);					//��ȱ�������v��ʼ
	void BFS(Graph<T,E>&G, const T &v);             //��ȱ�������v��ʼ
	*/
}
