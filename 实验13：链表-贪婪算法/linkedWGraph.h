#include<iostream>
#include"stack.h"
#include"queue.h"
#include"chain.h"
#include"minHeap.h"
#include"fastUnionFind.h"
#include"edge.h"

using namespace std;

//��Ȩ����ͼ,�ɳƳ�ΪͬȨ����ͼ 
template<class T>
class linkedWGraph {
protected:
	int _vertex_num;                 //������ 
	int _edge_num;                 //���� 
	chain<T>* _chain_heads;  //�ڽӱ� 
	int* _reach;  //����ָ�� 
	int _label = 1;

	void _dfs (int _head) {//�ݹ�ʵ�������������
		_reach[_head] = _label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myIterator* iv = iterator (_head);  //�����<T>�ͻᱨ��Ϊʲô���� 
		while ((u = iv->next ()) != 0) {//��v����һ���ڽӵ�uΪ�����ݹ����� 
		//cout<<v<<"����һ���ڽӵ��ǣ�"<<u<<" "<<endl;
			if (_reach[u] != _label)
				_dfs (u);  //u��һ��û�е�����Ķ��� 
		}
		delete iv;
		return;
	}

public:
	void output (ostream& out) {
		for (int i = 1; i <= _vertex_num; i++) {
			out << "_chain_heads[" << i << "]="; _chain_heads[i].output ();
			out << endl;
		}
	}
	linkedWGraph (int _head) {
		_vertex_num = _head;
		_edge_num = 0;
		_chain_heads = new chain<int>[_vertex_num + 1];
	}
	~linkedWGraph () {
		delete[] _chain_heads;  //�����ͻ��Լ�����chain������������ 
	}
	int numberOfVertices () const { return _vertex_num; }
	int numberOfEdges () const { return _edge_num; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void _checkVertex (int theVertex) const {//ȷ������Ч���� 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_chain_heads[v1].indexOf (v2) == -1) {//�±� 
			_chain_heads[v1].insert (0, v2, weight);
			_chain_heads[v2].insert (0, v1, weight);
			_edge_num++;
		}
	}
	void eraseEdge (int i, int j) {
		if (i > 1 && j > 1 && i <= _vertex_num && j <= _vertex_num) {
			int* _head = _chain_heads[i].eraseElement (j);
			int* j = _chain_heads[j].eraseElement (i);  //v,jһ��ͬʱΪ�ջ��߷ǿգ���Ȼ˵��һ���Գ������� 
			if (_head != nullptr && j != nullptr)   _edge_num--;   //�ñߴ���
		}
	}
	int degree (int Vertex) {
		_checkVertex (Vertex);
		return _chain_heads[Vertex].size ();
	}

	class myIterator {
	public:
		myIterator (chain<T>* theVertex) {
			_head = theVertex;
			_current_vertex = _head->_head;
		}
		~myIterator () {}
		int next (T& theWeight) {//����ָ���������һ���ڽӵ����ź����ĵ�Ȩֵ 
			if (_current_vertex != nullptr) {
				theWeight = _current_vertex->weight;
				int vertex = _current_vertex->data;
				_current_vertex = _current_vertex->next;
				return vertex;
			} else
				return 0;
		}
		int next () {//����ָ���������һ���ڽӵ� 

			if (_current_vertex != nullptr) {
				int vertex = _current_vertex->data;
				_current_vertex = _current_vertex->next;
				return vertex;
			}
			return 0;
		}
	protected:
		chain<T>* _head;    //�ڽӱ�ĵ� 
		node<T>* _current_vertex;   //��ǰ�����Ķ��� 
	};
	myIterator* iterator (int theVertex) {
		_checkVertex (theVertex);
		return new myIterator (&_chain_heads[theVertex]);
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
			if (_reach[i] == 0) {
				return false;
			}
		}
		return true;
	}

	void bfs (int _head, int _reach[], int label) {//��������㷨��_reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
		queue<int> q (10);
		_reach[_head] = label;
		q.push (_head);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (node<int>* u = _chain_heads[vertex]._head; u != nullptr; u = u->next) {
				if (_reach[u->data] == 0) {
					q.push (u->data);	_reach[u->data] = label;
				}
			}
		}
	}

	void dfs (int _head, int _reach[], int label) {
		_reach = _reach;
		label = label;
		_dfs (_head);
	}
	int labelComponents (int c[]) {//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++)
			c[i] = 0;

		int label = 0;
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs (i, c, label);  //���·�֧����� 
			}
		}
		return label;
	}
	void print_bfs (int _head, int _reach[]) {
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		int label = 1; _reach[_head] = label;
		queue<int> q (10);
		q.push (_head);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (node<int>* u = _chain_heads[vertex]._head; u != nullptr; u = u->next) {
				if (_reach[u->data] == 0) {
					q.push (u->data);	_reach[u->data] = label;
				}
			}
		}
	}
	void print_dfs (int _head, int _reach[]) {//ʹ��ջʵ�ֵ�DFS�����㷨 
		stack<int> s (10);  int u;
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		_reach[_head] = _label;
		s.push (_head);  cout << _head << " ";

		while (!s.empty ()) //��ջ����ʱ 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //����һ������ĵ�w�������ڽӵ� 
			{
				if (_reach[u] != _label) //�������һ��δ��ǵĵ�j 
				{
					_reach[u] = _label;
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
	int Dijkstra (int start, int dest, int predecessor[]) {//�������·������¼�����·��·����predecessor�Ǵ�start��dest·����destǰ���Ǹ����� 
		int* L = new int[_vertex_num + 1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for (int i = 1; i <= _vertex_num; i++) {
			L[i] = 100000;  predecessor[i] = -1;
		}   L[start] = 0;
		for (node<int>* u = _chain_heads[start]._head; u != nullptr; u = u->next) {
			L[u->data] = u->weight;
			predecessor[u->data] = start;  //����start�ڽӵĵ� 
		}
		predecessor[start] = 0;    //Դ����û��ǰ��  
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]��ʾstart������i�����·����� 

		/*�������������ǳ�ʼ��������������*/

		while (S[dest] != true) {/*������һ�����ڶ��㼯S�е�u��L[u]�����С�����Խ���һ�����Ա���*/
			int u, tag;
			for (u = 1; u <= _vertex_num; u++) {
				auto Minium = [](int L[], bool S[], int _vertex_num) {//��L[1:n]�����з��ز��ڶ��㼯S����С��Ԫ�� 
					int min = 100000;
					for (int i = 1; i <= _vertex_num; i++) {
						if (L[i] < min && S[i] == false)
							min = L[i];
					}
					return min;
				};
				if (S[u] == false && L[u] == Minium (L, S, _vertex_num))  //������һ�����ڶ��㼯S�ұ����С�ĵ㣬���Ӷȿ��Խ���O(1)�� 
				{                                        //���ҵ�д�����ӶȺ�����O(n^3)������ͨ��������ѭ���ж������ۺ������͸��Ӷ�� 
					S[u] = true;  //��u���붥�㼯S��
					tag = u;
					break;
				}
			}

			for (node<int>* u = _chain_heads[tag]._head; u != nullptr; u = u->next) {//�������ҵ��ĵ���ڽӵ�,�����û�б����ʹ����Ҿ���ɱ�����
			  //����д�����Ӷ���O(����)���Ϻ� 
				if (S[u->data] == false && L[tag] + (u->weight) < L[u->data]) {
					L[u->data] = L[tag] + u->weight;
					predecessor[u->data] = tag;    //����v��ǰ����u 
				}
			}
		}
		return L[dest];
	}

	bool kruskal (edge<T>* spanningTreeEdges) {
		//����С������������ͼ��ͨ�򷵻�true����sTE[0:n-2]�д�����С�������ı� 
		edge<T>* Edge = new edge<T>[_edge_num + 1];
		int k = 1;  //����Edge������ 

		//�����edge�����ʼ���������б߼���edge����
		for (int i = 1; i <= _vertex_num; i++) {//ȡ���й�������i�ı� 
			myIterator* ii = iterator (i);
			int j; T w;
			while ((j = ii->next (w)) != 0) {
				if (i < j)    //�����ظ��ӱ� 
				{
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//��С���ѱ�ʾ�߼���Ч�ʽϺ�
		minHeap<edge<T> > heap (1);
		heap.initialize (Edge, _edge_num);  //cout<<heap<<endl;
		fastUnionFind uf (_vertex_num);
		k = 0;  //����
		while (_edge_num > 0 && k < _vertex_num - 1) {//������û����ɲ��һ��бߴ��� 
			edge<T> x = heap.getTop ();
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
	bool Prim (edge<T>* spanningTreeEdges) {//spanningTreeEdges���Ѿ���ѡ�ı߼� 
		int e = this->_edge_num;
		minHeap< edge<T> > heap;

		bool* TV = new bool[_vertex_num + 1];      //TV���������еĶ��㼯
		for (int i = 1; i <= _vertex_num; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->next (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //��ʾ�߼������� 
		while (!heap.empty () && k < _vertex_num - 1) {
			edge<T> x = heap.getTop ();  //�����ı�����С�� 
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (TV[b] == false)  //����TV[a]==true 
				spanningTreeEdges[k++] = edge<T> (a, b, x.getWeight ());
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b)  //��֤���ظ������ 
				{
					edge<T> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV���������еĶ��㼯

		return (k == _vertex_num - 1);

	}

};
