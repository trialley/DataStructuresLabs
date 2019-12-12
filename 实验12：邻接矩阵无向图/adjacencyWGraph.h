#pragma once
#include<iostream>
#include"edge.h"
#include"queue.h"
#include"stack.h"
#include"minHeap.h"
#include"fastUnionFind.h"
using namespace std;
#define until(re) while(!(re))

template<class W>
class adjacencyWGraph {
	//��Ȩ����ͼ 
protected:
	int _vertex_num;       //������� 
	int _edge_num;       //�ߵĸ��� 
	W** _weights;       //�ڽ����� 
	W _no_edge;    //��ʾ�����ڵı�
	int* _reach;  //����ָ�� 
	int _label = 1;

	void _dfs (int v) {
		//�ݹ�ʵ�������������
		_reach[v] = _label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myIterator* iv = iterator (v);  //�����<T>�ͻᱨ��Ϊʲô���� 
		while ((u = iv->next ()) != 0) {
			//��v����һ���ڽӵ�uΪ�����ݹ����� 
			if (_reach[u] != _label) {
				_dfs (u);  //u��һ��û�е�����Ķ��� 
			}
		}

		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, W no_edgei = 0) {
		//���캯��
		if (v < 0) cerr << "����鶥�����ĺϷ��ԣ�" << endl;
		_vertex_num = v;
		_no_edge = no_edgei;
		_edge_num = 0;

		_weights = new W * [_vertex_num + 1];
		for (int i = 0; i < _vertex_num + 1; i++) {
			//����ռ� 
			_weights[i] = new W[_vertex_num + 1];
		}
		for (int i = 1; i <= _vertex_num; i++) {
			//��ʼ���ڽӾ��� 
			for (int j = 1; j <= _vertex_num; j++) {
				_weights[i][j] = _no_edge;
			}
		}
	}
	~adjacencyWGraph () {
		for (int i = 0; i < _vertex_num + 1; i++) {
			delete[] _weights[i];
		}
		delete[] _weights;
		_weights = NULL;  //����ΪNULL�Ļ����Ұָ�룬��������Ҳû�� 
	}
	class myIterator {
	public:
		myIterator (W* theRow, W theEdge, int v) {
			_row = theRow;
			_no_edge = theEdge;
			_vertex_num = v;
			_current_vertex = 1;
		}
		~myIterator () {}
		int next (W& theWeight) {
			//����ָ���������һ���ڽӵ�����ĵ�Ȩֵ 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {
					//����һ���ڽӵ� 
					_current_vertex = i + 1;
					theWeight = _row[i];
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
		int next () {
			//����ָ���������һ���ڽӵ� 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {//����һ���ڽӵ� 
					_current_vertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
	protected:
		W* _row;              //�ڽӾ���ĵ��� 
		W _no_edge;            //theRow[i]==noEdge�����ҽ���û�й����붥��i�ı� 
		int _vertex_num;               //������ 
		int _current_vertex;   //��ǰ�����Ķ��� 
	};
	myIterator* iterator (int indexi) {
		//���ض���indexi�ĵ����� 
		_checkVertex (indexi);
		return new myIterator (_weights[indexi], _no_edge, _vertex_num);
	}
	void _checkVertex (int theVertex) const {
		//ȷ������Ч���� 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<W>* theEdge) {
		//����ߣ�����ñ��Ѵ��ڣ�����theEdge->weight()�޸ıߵ�Ȩ
		int v1 = theEdge->getFrom ();
		int v2 = theEdge->getTo ();
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {
			//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_weights[v1][v2] == _no_edge) {
			_edge_num++;
		}
		_weights[v2][v1] = _weights[v1][v2] = theEdge->weight ();
	}
	void eraseEdge (int i, int j) {
		//ɾ����(i,j),��������ڸñ߾�ʲôҲ���� 
		if (i >= 1 && j >= 1 && i <= _vertex_num && j <= _vertex_num && _weights[i][j] != _no_edge) {
			_weights[i][j] = _weights[j][i] = _no_edge;
			_edge_num--;
		}
	}
	int Degree (int Vertex) {
		//���㶥��Vertex�Ķ�
		_checkVertex (Vertex);
		int sum = 0;
		for (int j = 1; j <= _vertex_num; j++) {
			if (_weights[Vertex][j] != _no_edge) {
				sum++;
			}
		}
		return sum;
	}
	bool connected () {
		//�ж�����ͼ�Ƿ���ͨ 
		if (directed ()) {
			cerr << "��ͼ������ͼ��" << endl;
			exit (2);
		}

		_reach = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			_reach[i] = 0;
		}

		dfs (1, _reach, 1); //���ڽ��ڶ���1�Ŀɴﶥ�������

		for (int i = 1; i <= _vertex_num; i++) {
			//������ж����Ƿ��������
			if (_reach[i] == 0) {
				return false;
			}
		}

		return true;
	}
	void bfs (int v, int reach[], int label) {
		//��������㷨��reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
		queue<int> q;
		reach[v] = label;
		q.push (v);

		until (q.empty ()) {
			int vertex = q.front ();
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_weights[vertex][j] != _no_edge && reach[j] == 0) {
					q.push (j);
					reach[j] = label;
				}
			}
		}
	}
	void dfs (int v, int _reach[], int _label) {
		_reach = _reach;
		_label = _label;
		_dfs (v);
	}
	int labelComponents (int c[]) {
		//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++) {
			c[i] = 0;
		}

		int label = 0;  //���һ�������ı�� 
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {
				//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs (i, c, label);  //���·�֧����� 
			}
		}
		return label;
	}
	void print_bfs (int v, int reach[]) {
		fill (reach, reach + _vertex_num + 1, 0);
		int label = 1;
		reach[v] = label;
		queue<int> q;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_weights[vertex][j] != _no_edge && reach[j] == 0) {
					q.push (j);	reach[j] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (_vertex_num + 1));
		reach[v] = _label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //��stack����ʱ 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //����һ������ĵ�w�������ڽӵ� 
			{
				if (reach[u] != _label) //�������һ��δ��ǵĵ�j 
				{
					reach[u] = _label;
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
	int Dijkstra (int start, int dest, int path[]) {
		//�������·������¼�����·��·����predecessor�Ǵ�start��dest·����destǰ���Ǹ����� 
		
		int* L = new int[_vertex_num + 1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for (int i = 1; i <= _vertex_num; i++)  L[i] = _weights[start][i];  L[start] = 0;
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]��ʾstart������i�����·����� 
		for (int i = 1; i <= _vertex_num; i++) {
			path[i] = (L[i] == _no_edge) ?-1 : start;
		}
		path[start] = 0;    //Դ����û��ǰ�� 
		for (int i = 1; i <= _vertex_num; i++) {

			auto Minium = [](int L[], bool S[], int n) {
				//��L[1:n]�����з��ز��ڶ��㼯S����С��Ԫ�� 
				int min = 100000;
				for (int i = 1; i <= n; i++) {
					if (L[i] < min && S[i] == false) {
						min = L[i];
					}
				}
				return min;
			};

			if (S[i] == false && L[i] == Minium (L, S, _vertex_num)) {
				S[i] = true;  //��u���붥�㼯S��

				//���¼���·������
				for (int j = 1; j <= _vertex_num; j++) {//��ÿһ��������S�Ķ���v 
					if (S[j] == false && L[i] + _weights[i][j] < L[j]) {
						L[j] = L[i] + _weights[i][j];
						path[j] = i;   //����v��ǰ����u 
					}
				}
			}
		}
		return L[dest];
	}
	bool kruskal (edge<W>* spanningTreeEdges) {
		//����С������������ͼ��ͨ�򷵻�true����sTE[0:n-2]�д�����С�������ı� 
		//ע�⣬��Ҫ�ò��鼯��ֹ��·��ÿ��Ѱ����С�䣬�γɻ��Ͳ�ȥ����
		//�ö�ȡ��ÿ����С��

		edge<W>* Edge = new edge<W>[_edge_num + 1];
		int k = 1;  //����Edge������ 

		//�����edge�����ʼ���������б߼���edge����
		for (int i = 1; i <= _vertex_num; i++) {//ȡ���й�������i�ı� 
			myIterator* ii = iterator (i);
			int j; W w;
			while ((j = ii->next (w)) != 0) {
				if (i < j) { //�����ظ��ӱ� 
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//��С���ѱ�ʾ�߼���Ч�ʽϺ�
		minHeap<edge<W>> heap;

		heap.initialize (Edge, _edge_num);  //cout<<heap<<endl;
		fastUnionFind uf (_vertex_num);
		k = 0;  //����
		while (_edge_num > 0 && k < _vertex_num - 1) {

			//������û����ɲ��һ��бߴ��� 
			edge<W> x = heap.top ();
			heap.pop ();
			_edge_num--;
			int a = uf.find (x.getFrom ());
			int b = uf.find (x.getTo ());
			if (a != b) {//��֤��û�л�·�������ѡȡ��x 
				spanningTreeEdges[k++] = x;
				uf.unite (a, b);
			}
		}
		return (k == _vertex_num - 1);
	}
	bool prim (edge<W>* spanningTreeEdges) {
		//spanningTreeEdges���Ѿ���ѡ�ı߼� 
		minHeap<edge<W>> heap;

		bool* TV = new bool[_vertex_num + 1];      //TV���������еĶ��㼯
		for (int i = 1; i <= _vertex_num; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;
		W w;

		//�Զ������������򣬹���С����
		while ((j = i->next (w)) != 0) {
			edge<W> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //��ʾ�߼������� 
		while (!heap.empty () && k < _vertex_num - 1) {
			edge<W> x = heap.top ();  //�����ı�����С�� 
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (TV[b] == false) { //����TV[a]==true 
				spanningTreeEdges[k++] = edge<W> (a, b, x.weight ());
			}
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b) {
					//��֤���ظ������ 
					edge<W> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV���������еĶ��㼯

		return (k == _vertex_num - 1);
	}

};


