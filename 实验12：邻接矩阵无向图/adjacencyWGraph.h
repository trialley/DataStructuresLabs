#pragma once
#include<iostream>
#include"edge.h"
#include"queue.h"
#include"stack.h"
#include<string.h>
using namespace std;



template<class N,class W>
class adjacencyWGraph {//��Ȩ����ͼ 
protected:
	N* _vertexes;
	int _vertex_num;       //������� 
	int _edge_num;       //�ߵĸ��� 
	W** _edges;       //�ڽ����� 
	W _no_edge;    //��ʾ�����ڵı�
	int* _reach;  //����ָ�� 
	int _label = 1;

	void rDfs (int v) {//�ݹ�ʵ�������������
		_reach[v] = _label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myItertor* iv = itertor (v);  //�����<W>�ͻᱨ��Ϊʲô���� 
		while ((u = iv->next ()) != 0) {//��v����һ���ڽӵ�uΪ�����ݹ����� 
			if (_reach[u] != _label)
				rDfs (u);  //u��һ��û�е�����Ķ��� 
		}
		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, W theNoWdge = 0) {//���캯��
		if (v < 0) cerr << "����鶥�����ĺϷ��ԣ�" << endl;
		_vertex_num = v;
		_no_edge = theNoWdge;
		_edge_num = 0;

		_edges = new W * [_vertex_num + 1];
		for (int i = 0; i < _vertex_num + 1; i++) {//����ռ� 
			_edges[i] = new W[_vertex_num + 1];
		}
		for (int i = 1; i <= _vertex_num; i++){  //��ʼ���ڽӾ��� 
			for (int j = 1; j <= _vertex_num; j++) {
				_edges[i][j] = _no_edge;
			}
		}
	}
	~adjacencyWGraph () {
		for (int i = 0; i < _vertex_num + 1; i++) {
			delete[] _edges[i];
		}
		delete[] _edges;
		_edges = nullptr;  //����Ϊnullptr�Ļ����Ұָ�룬��������Ҳû�� 
	}
	class myItertor {
	public:
		myItertor (W* theRow, W theWdge, int v) {
			Row = theRow;
			_no_edge = theWdge;
			_vertex_num = v;
			currentVertex = 1;
		}
		~myItertor () {}
		int next (W& theWeight) {//����ָ���������һ���ڽӵ�����ĵ�Ȩֵ 
			for (int i = currentVertex; i <= _vertex_num; i++) {
				if (Row[i] != _no_edge) {//����һ���ڽӵ� 
					currentVertex = i + 1;
					theWeight = Row[i];
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			currentVertex = _vertex_num + 1;
			return 0;
		}
		int next () {//����ָ���������һ���ڽӵ� 
			for (int i = currentVertex; i <= _vertex_num; i++) {
				if (Row[i] != _no_edge) {//����һ���ڽӵ� 
					currentVertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			currentVertex = _vertex_num + 1;
			return 0;
		}
	protected:
		W* Row;              //�ڽӾ���ĵ��� 
		W _no_edge;            //theRow[i]==_no_edge�����ҽ���û�й����붥��i�ı� 
		int _vertex_num;               //������ 
		int currentVertex;   //��ǰ�����Ķ��� 
	};
	myItertor* itertor (int theVertex) {//���ض���theVertex�ĵ����� 
		checkVertex (theVertex); //cout<<"_edges[theVertex]="<<_edges[theVertex];
		return new myItertor (_edges[theVertex], _no_edge, _vertex_num);
	}
	void checkVertex (int theVertex) const {//ȷ������Ч���� 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<W>* theWdge) {
		//����ߣ�����ñ��Ѵ��ڣ�����theWdge->weight()�޸ıߵ�Ȩ
		int v1 = theWdge->vertex1 ();
		int v2 = theWdge->vertex2 ();
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not _edges permissible edge" << endl;
			exit (1);
		}
		if (_edges[v1][v2] == _no_edge)  //�±� 
			_edge_num++;
		_edges[v2][v1] = _edges[v1][v2] = theWdge->weight ();
	}
	void er_edgesseWdge (int i, int j) {//ɾ����(i,j),��������ڸñ߾�ʲôҲ���� 
		if (i >= 1 && j >= 1 && i <= _vertex_num && j <= _vertex_num && _edges[i][j] != _no_edge) {
			_edges[i][j] = _edges[j][i] = _no_edge;
			_edge_num--;
		}
	}
	int Degree (int Vertex) {//���㶥��Vertex�Ķ�
		checkVertex (Vertex);
		int sum = 0;
		for (int j = 1; j <= _vertex_num; j++)
			if (_edges[Vertex][j] != _no_edge)  //������Vertex�� 
				sum++;
		return sum;
	}
	bool connected () {//�ж�����ͼ�Ƿ���ͨ 
		if (directed ()) {
			cerr << "��ͼ������ͼ��" << endl;  exit (2);
		}

		_reach = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)
			_reach[i] = 0;

		dfs (1, _reach, 1); //���ڽ��ڶ���1�Ŀɴﶥ�������

		for (int i = 1; i <= _vertex_num; i++) {//������ж����Ƿ��������
			if (_reach[i] == 0)
				return false;
		}
		return true;
	}
	void bfs (int v, int _reach[], int _label) {//��������㷨��_reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
		queue<int> q (10);
		_reach[v] = _label;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_edges[vertex][j] != _no_edge && _reach[j] == 0) {
					q.push (j);	_reach[j] = _label;
				}
			}
		}
	}
	void dfs (int v, int _reach[], int _label) {
		_reach = _reach;
		_label = _label;
		rDfs (v);
	}
	int labelComponents (int c[]) {//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++)
			c[i] = 0;

		int _label = 0;  //���һ�������ı�� 
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {//������δ����Ķ��㣬������һ��bfs��� 
				_label++;
				bfs (i, c, _label);  //���·�֧����� 
			}
		}
		return _label;
	}
	void print_bfs (int v, int _reach[]) {
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		int _label = 1; _reach[v] = _label;
		queue<int> q (10);
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_edges[vertex][j] != _no_edge && _reach[j] == 0) {
					q.push (j);	_reach[j] = _label;
				}
			}
		}
	}
	void print_dfs (int v, int _reach[]) {
		stack<int> s (10);  int u;
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		_reach[v] = _label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //��stack����ʱ 
		{
			int w = s.top ();
			s.pop ();
			myItertor* iv = itertor (w);	  u = iv->next ();
			while (u != 0)  //����һ������ĵ�w�������ڽӵ� 
			{
				if (_reach[u] != _label) //�������һ��δ��ǵĵ�j 
				{
					_reach[u] = _label;
					s.push (u);
					cout << u << " ";
					iv = itertor (u);	//��ivָ����uΪ���ĵ����� 
				} else {//�ö����ѱ����
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //�ö���û�������ڽӵ���
				}
			}
		}
	}

	int Dijkstra (int starti, int desti, int pre[]) {
		//�������·������¼�����·��·����pre�Ǵ�start��desti·����destiǰ���Ǹ����� 


		bool* S = new bool[_vertex_num + 1];  //S[i]��ʾstarti������i�����·����� 
		fill (S, S + _vertex_num + 1, false);

		int* dis = new int[_vertex_num + 1];  //dis[i]�Ǵ�starti�㵽����i�ľ��� 

		/*��ʼ������*/
		for (int i = 1; i <= _vertex_num; i++) {
			dis[i] = _edges[starti][i];
		}
		dis[starti] = 0;

		/*��ʼ��ǰ���ڵ�*/
		for (int i = 1; i <= _vertex_num; i++) {
			if (dis[i] == _no_edge)
				pre[i] = -1;    //�Բ��ڽӵĵ� 
			else
				pre[i] = starti;//�ڽӵ��ǰ������starti 
		}
		pre[starti] = 0;    //Դ����û��ǰ�� 

		while (S[desti] != true) {
			int u;
			for (u = 1; u <= _vertex_num; u++) {

				auto minVertex = [](int dis[], bool S[], int n) {//�ڷ�SԪ�����ҵ�����S����������Ǹ� 
					int min = 100000;
					for (int i = 1; i <= n; i++) {
						if (dis[i] < min && S[i] == false) {
							min = dis[i];
						}
					}
					return min;
				};

				if (!S[u] && dis[u] == minVertex (dis, S, _vertex_num)) {
					S[u] = true;  //��u���붥�㼯S��
					
					//��ÿһ��������S�Ķ���v ,�������ǵ����ľ���
					for (int v = 1; v <= _vertex_num; v++) {
						if (!S[v] && dis[u] + _edges[u][v] < dis[v]) {
							dis[v] = dis[u] + _edges[u][v];
							pre[v] = u;   //����v��ǰ����u 
						}
					}
				}
			}
		}
		return dis[desti];
	}

};


