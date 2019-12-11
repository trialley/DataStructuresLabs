#pragma once
#include<iostream>
#include"edge.h"
#include"queue.h"
#include"stack.h"
#include<string.h>
using namespace std;


int Minium (int L[], bool S[], int n) {
	//��L[1:n]�����з��ز��ڶ��㼯S����С��Ԫ�� 
	int min = 100000;
	for (int i = 1; i <= n; i++) {
		if (L[i] < min && S[i] == false)
			min = L[i];
	}
	return min;
}

template<class T>
class adjacencyWGraph {//��Ȩ����ͼ 
protected:
	int n;       //������� 
	int e;       //�ߵĸ��� 
	T** a;       //�ڽ����� 
	T noEdge;    //��ʾ�����ڵı�
	int* reach;  //����ָ�� 
	int label = 1;

	void rDfs (int v) {//�ݹ�ʵ�������������
		reach[v] = label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myIterator* iv = iterator (v);  //�����<T>�ͻᱨ��Ϊʲô���� 
		while ((u = iv->next ()) != 0) {//��v����һ���ڽӵ�uΪ�����ݹ����� 
		//cout<<v<<"����һ���ڽӵ��ǣ�"<<u<<" "<<endl;
			if (reach[u] != label)
				rDfs (u);  //u��һ��û�е�����Ķ��� 
		}
		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, T theNoEdge = 0) {//���캯��
		if (v < 0) cerr << "����鶥�����ĺϷ��ԣ�" << endl;
		n = v;
		noEdge = theNoEdge;
		e = 0;

		a = new T * [n + 1];
		for (int i = 0; i < n + 1; i++) {//����ռ� 
			a[i] = new T[n + 1];
		}
		for (int i = 1; i <= n; i++)  //��ʼ���ڽӾ��� 
		{
			for (int j = 1; j <= n; j++) {
				a[i][j] = noEdge;
			}
		}
	}
	~adjacencyWGraph () {
		for (int i = 0; i < n + 1; i++) {
			delete[] a[i];
		}
		delete[] a;
		a = NULL;  //����ΪNULL�Ļ����Ұָ�룬��������Ҳû�� 
	}
	class myIterator {
	public:
		myIterator (T* theRow, T theEdge, int v) {
			Row = theRow;
			noEdge = theEdge;
			n = v;
			currentVertex = 1;
		}
		~myIterator () {}
		int next (T& theWeight) {//����ָ���������һ���ڽӵ�����ĵ�Ȩֵ 
			for (int i = currentVertex; i <= n; i++) {
				if (Row[i] != noEdge) {//����һ���ڽӵ� 
					currentVertex = i + 1;
					theWeight = Row[i];
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			currentVertex = n + 1;
			return 0;
		}
		int next () {//����ָ���������һ���ڽӵ� 
			for (int i = currentVertex; i <= n; i++) {
				if (Row[i] != noEdge) {//����һ���ڽӵ� 
					currentVertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			currentVertex = n + 1;
			return 0;
		}
	protected:
		T* Row;              //�ڽӾ���ĵ��� 
		T noEdge;            //theRow[i]==noEdge�����ҽ���û�й����붥��i�ı� 
		int n;               //������ 
		int currentVertex;   //��ǰ�����Ķ��� 
	};
	myIterator* iterator (int theVertex) {//���ض���theVertex�ĵ����� 
		checkVertex (theVertex); //cout<<"a[theVertex]="<<a[theVertex];
		return new myIterator (a[theVertex], noEdge, n);
	}
	void checkVertex (int theVertex) const {//ȷ������Ч���� 
		if (theVertex<1 || theVertex>n) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<T>* theEdge) {
		//����ߣ�����ñ��Ѵ��ڣ�����theEdge->weight()�޸ıߵ�Ȩ
		int v1 = theEdge->vertex1 ();
		int v2 = theEdge->vertex2 ();
		if (v1<1 || v2<1 || v1>n || v2>n || v1 == v2) {//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (a[v1][v2] == noEdge)  //�±� 
			e++;
		a[v2][v1] = a[v1][v2] = theEdge->weight ();
	}
	void eraseEdge (int i, int j) {//ɾ����(i,j),��������ڸñ߾�ʲôҲ���� 
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge) {
			a[i][j] = a[j][i] = noEdge;
			e--;
		}
	}
	int Degree (int Vertex) {//���㶥��Vertex�Ķ�
		checkVertex (Vertex);
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[Vertex][j] != noEdge)  //������Vertex�� 
				sum++;
		return sum;
	}
	bool connected () {//�ж�����ͼ�Ƿ���ͨ 
		if (directed ()) {
			cerr << "��ͼ������ͼ��" << endl;  exit (2);
		}

		reach = new int[n + 1];
		for (int i = 1; i <= n; i++)
			reach[i] = 0;

		dfs (1, reach, 1); //���ڽ��ڶ���1�Ŀɴﶥ�������

		for (int i = 1; i <= n; i++) {//������ж����Ƿ��������
			if (reach[i] == 0)
				return false;
		}
		return true;
	}
	void bfs (int v, int reach[], int label) {//��������㷨��reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
		queue<int> q (10);
		reach[v] = label;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (int j = 1; j <= n; j++) {
				if (a[vertex][j] != noEdge && reach[j] == 0) {
					q.push (j);	reach[j] = label;
				}
			}
		}
	}
	void dfs (int v, int reach[], int label) {
		reach = reach;
		label = label;
		rDfs (v);
	}
	int labelComponents (int c[]) {//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i = 0;
		for (i = 0; i <= n; i++)
			c[i] = 0;

		int label = 0;  //���һ�������ı�� 
		for (i = 1; i <= n; i++) {
			if (c[i] == 0) {//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs (i, c, label);  //���·�֧����� 
			}
		}
		return label;
	}
	void print_bfs (int v, int reach[]) {
		memset (reach, 0, sizeof (int) * (n + 1));
		int label = 1; reach[v] = label;
		queue<int> q (10);
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (int j = 1; j <= n; j++) {
				if (a[vertex][j] != noEdge && reach[j] == 0) {
					q.push (j);	reach[j] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (n + 1));
		reach[v] = label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //��stack����ʱ 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //����һ������ĵ�w�������ڽӵ� 
			{
				if (reach[u] != label) //�������һ��δ��ǵĵ�j 
				{
					reach[u] = label;
					s.push (u);
					cout << u << " ";
					iv = iterator (u);	//��ivָ����uΪ���ĵ����� 
				} else {//�ö����ѱ����
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //�ö���û�������ڽӵ���
				}
			}
		}
	}
	/*	void bfSpanningTree(int v)
		{//������v�����BFS������
			queue<int> q(10);
			reach[v]=label;
			q.push(v);
			TreeNode Node(v);  TreeNode *root=&Node;

			while(q.empty()!=true)
			{
				int vertex=q.front();  TreeNode *pp=Tree_search(vetrex,root);  //����Ӧ��дһ�������������ؼ��ֵĺ���������ָ��ڵ��ָ��
				q.pop();

				for(int j=1;j<=n;j++)
				{
					if( a[vertex][j]!=noEdge && reach[j]==0 )
					{  q.push(j);
					   reach[j]=label;
					   TreeNode *p=new TreeNode(j);  //���ｨһ���½ڵ�
					   linkNode(pp,p);    //��pp��p��������
					}
				}
			}
		}*/
	int Dijkstra (int start, int dest, int predecessor[]) {//�������·������¼�����·��·����predecessor�Ǵ�start��dest·����destǰ���Ǹ����� 
		int* L = new int[n + 1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for (int i = 1; i <= n; i++)  L[i] = a[start][i];  L[start] = 0;
		bool* S = new bool[n + 1];
		for (int i = 1; i <= n; i++)  S[i] = false;  //S[i]��ʾstart������i�����·����� 
		for (int i = 1; i <= n; i++) {
			if (L[i] == noEdge)    //�Բ��ڽӵĵ� 
				predecessor[i] = -1;
			else
				predecessor[i] = start;  //�ڽӵ��ǰ������start 
		}
		predecessor[start] = 0;    //Դ����û��ǰ�� 
	  /*�������������ǳ�ʼ��������������*/

		while (S[dest] != true) {/*������һ�����ڶ��㼯S�е�u��L[u]�����С�����Խ���һ�����Ա���*/
			int u;
			for (u = 1; u <= n; u++) {
				if (S[u] == false && L[u] == Minium (L, S, n))  //������һ�����ڶ��㼯S�ұ����С�ĵ㣬���Ӷȿ��Խ���O(1)�� 
				{//����Ƚϴֱ���ֱ��ɨ�������ж��㣬��ʵ������һ��collected�����Ż���ɨ����������¼����
				 //���ҵ�д�����ӶȺ�����O(n^3)������ͨ��������ѭ���ж������ۺ������͸��Ӷ��������ĸ��Ӷ���O(N^2) 
					S[u] = true;  //��u���붥�㼯S��
					for (int v = 1; v <= n; v++) {//��ÿһ��������S�Ķ���v 
						if (S[v] == false && L[u] + a[u][v] < L[v]) {
							L[v] = L[u] + a[u][v];
							predecessor[v] = u;   //����v��ǰ����u 
						}
					}
					break;  //����������whileѭ�� 
				}
			}
		}
		return L[dest];
	}

};


