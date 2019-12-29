#include <iostream>
#include<climits>
using namespace std;

template<class T>
class arrayQueue
{
public:
	arrayQueue(int initialCapacity = 10)
	{
		if (initialCapacity < 1)
			return;
		arrayLength = initialCapacity;
		queue = new T[arrayLength];
		theFront = 0;
		theBack = 0;
	}
	~arrayQueue() { delete[] queue; }
	bool empty() const { return theFront == theBack; }
	int size() const
	{
		return (theBack - theFront + arrayLength) % arrayLength;
	}
	T& front()
	{
		if (theFront == theBack)
			throw empty();
		return queue[(theFront + 1) % arrayLength];
	}
	T& back()
	{
		if (theFront == theBack)
			throw empty();
		return queue[theBack];
	}
	void pop()
	{
		if (theFront == theBack)
			return;
		theFront = (theFront + 1) % arrayLength;
		queue[theFront].~T();
	}
	void push(const T& theElement)
	{
		if ((theBack + 1) % arrayLength == theFront)
		{
			T* newQueue = new T[2 * arrayLength];

			int start = (theFront + 1) % arrayLength;
			if (start < 2)
				copy(queue + start, queue + start + arrayLength - 1, newQueue);
			else
			{
				copy(queue + start, queue + arrayLength, newQueue);
				copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
			}
			theFront = 2 * arrayLength - 1;
			theBack = arrayLength - 2;   // queue size arrayLength - 1
			arrayLength *= 2;
			queue = newQueue;
		}
		theBack = (theBack + 1) % arrayLength;
		queue[theBack] = theElement;
	}
private:
	int theFront;
	int theBack;
	int arrayLength;
	T* queue;
};

struct Edge {//ʵ�ֵı���
	int v1;
	int v2;
	int w;
	~Edge() {}
	Edge() {}
	Edge(int a, int b, int weight) {
		v1 = a;
		v2 = b;
		w = weight;
	}

	bool operator > (const Edge& x) { return (this->w > x.w); }
	bool operator < (const Edge& x) { return (this->w < x.w); }
	bool operator >= (const Edge& x) { return (this->w >= x.w); }
	bool operator <= (const Edge& x) { return (this->w <= x.w); }
	void operator = (const Edge& x)
	{
		this->v1 = x.v1;
		this->v2 = x.v2;
		this->w = x.w;
	}
};

template<class T>
struct graphNode//ʵ�ֵĶ�����
{
	T vertex;
	int weight;
	graphNode<T>* next;

	graphNode() { next = NULL; }
	graphNode(T v, int w) { vertex = v; weight = w; next = NULL; }
	graphNode(T v, int w, graphNode<T>* theNext) { vertex = v;  weight = w; next = theNext; }
	void push(T v) { vertex = v; }
	void push(graphNode<T>* theNode) { vertex = theNode->vertex; next = theNode->next; }

	bool operator<= (graphNode<T>& GNode) { return (this->weight <= GNode.weight); }
	bool operator>= (graphNode<T>& GNode) { return (this->weight >= GNode.weight); }
	bool operator> (graphNode<T>& GNode) { return (this->weight > GNode.weight); }
	bool operator< (graphNode<T>& GNode) { return (this->weight < GNode.weight); }
	void set(T element) {
		weight = element;
	}
	T& get() {
		return weight;
	}
};
struct unionFindNode
{
	int parent;  // if true then tree weight
	// otherwise pointer to parent in tree
	bool root;   // true iff root

	unionFindNode()
	{
		parent = 1;
		root = true;
	}
};
class fastUnionFind
{
public:
	fastUnionFind(int numberOfElements)
	{
		// Initialize numberOfElements trees, 1 element per set/class/tree.
		node = new unionFindNode[numberOfElements + 1];
	}
	~fastUnionFind()
	{
		delete[] node;
	}
	void unite(int rootA, int rootB)
	{
		// Combine trees with different roots rootA and rootB.
		// Use the weighting rule.
		if (node[rootA].parent < node[rootB].parent)
		{
			// rootA becomes subtree of rootB
			node[rootB].parent += node[rootA].parent;
			node[rootA].root = false;
			node[rootA].parent = rootB;
		}
		else
		{
			// rootB becomes subtree of rootA
			node[rootA].parent += node[rootB].parent;
			node[rootB].root = false;
			node[rootB].parent = rootA;
		}
	}

	int find(int theElement)
	{
		// Return root of tree containing theElement.
		// Compact path from theElement to root.

		// theRoot will eventually be the root of the tree
		int theRoot = theElement;
		while (!node[theRoot].root)
			theRoot = node[theRoot].parent;

		// compact pathe from theElement to theRoot
		int currentNode = theElement;  // start at theElement
		while (currentNode != theRoot)
		{
			int parentNode = node[currentNode].parent;
			node[currentNode].parent = theRoot;  // move to level 2
			currentNode = parentNode;            // moves to old parent
		}

		return theRoot;
	}

protected:
	unionFindNode* node;
};

template <class T>//����ͼ
class graph
{
protected:
	graphNode<T>** aList;//
	Edge* edge_list;
	//T** weight;//������Ȩ�صĶ�λ����
	int num_ver;//ͼ�������
	int num_edge;//ͼ�߸���
	int label;//������
	int* reach;//����Ƿ񵽴������
	void rDfs(int v);
	void rBfs(int v);
	int begin;//��ʼ����
	int end;//��������
	int* the_dfs;//���������λ�����䵱�������Ĺ���
	int* the_bfs;
	int* sum_w;//������Ȩ������
	//int cnctd_num;//��ͨ��������
	//int* min_ver_cnctd;//��ͨ��֧��С����
	//int min_ver;
	//int min_length;
	int length_of_edges;//���ں�����ͨ�������󳤶�
	int* TheSum, * father;
	void get_sum_w(int s);
	int** a;
public:
	graph(int** x,int initialize_v, int initialize_e);
	~graph()
	{
		for (int i = 0; i <= num_ver; i++)
		{
			delete[]aList[i];
		}
		delete[]aList;
		delete[]reach;
		delete[]the_dfs;
		delete[]the_bfs;
	}
	void add(T v1, T v2, int TheWeight);
	void erase(T v1, T v2);
	void test();
	void output(int v);	//���һ������������ڽӶ���
	bool connected()//�����ж�ͼ�Ƿ���ͨ
	{
		for (int i = 0; i <= num_ver; i++) //��Prim�㷨�У������жϺ������Ǿ���Ϊ�Ѿ��ӽ���ͨ��,����ʹ��������ȱ���
		{
			reach[i] = 0; the_dfs[i] = 0;
		}
		rDfs(1);
		for (int i = 1; i <= num_ver; i++)
		{
			if (reach[i] == 0)
			{
				return false;
			}
		}
		return true;
	}
	//void test();
	void get_sum(int s)
	{
		if (TheSum[s] == 0)
		{
			prim(s);
			cout << TheSum[s] ;
		}
		else
		{
			cout << TheSum[s] ;
		}
	}
	void clear();
	void get_edge_list(Edge* a)
	{
		edge_list = a;
		for (int i = 1; i <= num_edge; i++)
		{
			add(edge_list[i].v1, edge_list[i].v2, edge_list[i].w);
		}
	}
	void prim(int s);
	void deal();
};

template<class T>
graph<T>::graph(int **x,int initialize_v, int initialize_e)
{
	aList = new graphNode<T> * [initialize_v + 1];

	reach = new int[initialize_v + 1];
	sum_w = new int[initialize_v + 1];
	for (int i = 0; i <= initialize_v; i++)
	{
		reach[i] = 0;
		sum_w[i] = 0;
	}
	for (int i = 1; i <= initialize_v; i++)
	{
		graphNode<T>* head = new graphNode<T>;
		aList[i] = head;//��Ҫ���Ǹ����︳ֵ
	}
	num_ver = initialize_v;
	num_edge = initialize_e;

	label = 1;
	//cnctd_num = 0;
	//min_ver = 1;
	the_dfs = new int[num_ver + 1];
	the_bfs = new int[num_ver + 1];

	a = x;
	


	TheSum = new int[num_ver + 1];
	for (int i = 1; i <= num_ver; i++)
		TheSum[i] = 0;
	father = new int[num_ver + 1];
	for (int i = 1; i <= num_ver; i++)
		father[i] = -1;
	//min_length = 0;
}
template<class T>
void graph<T>::erase(T v1, T v2)
{
	graphNode<T>* p = aList[v1];
	graphNode<T>* pp = NULL;
	while (p->next != NULL && p->vertex != v2)
	{
		pp = p;
		p = p->next;
	}
	if (p->vertex == v2)//�ҵ��˱�
	{
		pp->next = p->next;
		delete p;
	}
	graphNode<T>* q = aList[v2];
	graphNode<T>* pq = NULL;
	while (q->next != NULL && q->vertex != v1)
	{
		pq = q;
		q = q->next;
	}
	if (q->vertex == v1)//�ҵ��˱�
	{
		pq->next = q->next;
		delete q;
	}
}
template<class T>
void graph<T>::add(T v1, T v2, int TheWeight)
{
	graphNode<T>* p = aList[v1];
	graphNode<T>* newNode1 = new graphNode<T>(v2, TheWeight);
	graphNode<T>* temp;
	if (p->next == NULL)
	{
		p->next = newNode1;
	}
	else
	{
		while (p->next != NULL && v2 > p->next->vertex)//??���ܽ���????
		{
			p = p->next;
		}
		temp = p->next;
		p->next = newNode1;
		newNode1->next = temp;
	}
	graphNode<T>* q = aList[v2];
	graphNode<T>* newNode2 = new graphNode<T>(v1, TheWeight);
	if (q->next == NULL)
	{
		q->next = newNode2;
	}
	else
	{
		while (q->next != NULL && v1 > q->next->vertex)
		{
			q = q->next;
		}
		temp = q->next;
		q->next = newNode2;
		newNode2->next = temp;
	}
}

template<class T>
void graph<T>::rDfs(int v)
{
	//if (v <= min_ver) { min_ver = v; }
	int x = ++the_dfs[0];
	the_dfs[x] = v;
	reach[v] = label;
	graphNode<T>* p = aList[v];
	while ((p = p->next) != NULL)
	{
		int u = p->vertex;
		if (reach[u] == 0)
		{
			rDfs(u);
		}
	}
	return;
}
template<class T>
void graph<T>::rBfs(int v)
{
	arrayQueue<int> q(10);
	reach[v] = label;
	q.push(v);
	while (!q.empty())
	{
		int x = ++the_bfs[0];
		int w = q.front();
		the_bfs[x] = w;
		q.pop();
		for (graphNode<T>* u = aList[w]->next; u != NULL; u = u->next)
		{//���ʶ���w��һ����������
			if (reach[u->vertex] == 0)//˵��u��һ��δ����Ķ���
			{
				q.push(u->vertex);
				reach[u->vertex] = label;//������
			}
		}
	}
	return;
}

template<class T>
void graph<T>::clear()
{
	for (int i = 0; i <= num_ver; i++)
	{
		delete[]aList[i];
	}
	delete[]aList;
	aList = new graphNode<T> * [num_ver + 1];
	for (int i = 1; i <= num_ver; i++)
	{
		graphNode<T>* head = new graphNode<T>;
		aList[i] = head;//��Ҫ���Ǹ����︳ֵ
	}

}

template<class T>
void graph<T>::prim(int s)
{
	int* TheWeight = new int[num_ver + 1];
	for (int i = 1; i <= num_ver; i++)//��ʼ������
		TheWeight[i] = a[s][i];
	fastUnionFind uf(num_ver);
	//father[s] = s;//���ó�u��ʾ�Ѿ�����uΪ������ 
	for (int i = 1; i < num_ver; i++)//�˴�ֻ��Ҫ����n-1�μ���
	{
		int min_edge = INT_MAX;
		int v = -1;
		//��TheWeight������Ѱ��δ����u������Сֵ
		for (int j = 1; j <= num_ver; j++)
			if (uf.find(j)!=uf.find(s) && TheWeight[j] < min_edge)
			{
				v = j;
				min_edge = TheWeight[j];
			}
		if (v != -1)//v=-1��ʾδ�ҵ���С�ı�,
		{
			uf.unite(v, s);
			//father[v] = s;
			//cout << "break" << "i=" << i  << endl;
			TheSum[s] += TheWeight[v];
			for (int j = 1; j <= num_ver; j++)//������̱�
				if (father[j] != s && TheWeight[j] > a[v][j])
					TheWeight[j] = a[v][j];
		}
		else return;
	}
	for (int i = 1; i <= num_ver; i++)
	{
		if (uf.find(i) == uf.find(s))
		{
			TheSum[i] = TheSum[s];
		}
	}

}


int main()
{

	int n, m, q;//nΪ���������mΪ������qΪ��ѯ����
	int* s;
	cin >> n >> m >> q;
	s = new int[q];//ÿ��Ҫ��ѯ����ʼ����
	
	int** x;
	x = new int* [n + 1];
	for (int i = 1; i <= n; i++)
	{
		x[i] = new int[n + 1];
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i == j)
				x[i][j] = 0;
			else x[i][j] = INT_MAX;
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		if (x[u][v] > w)
		{
			x[u][v] = w;
			x[v][u] = w;
		}
	}
	graph<int> theGraph(x, n, m);
	//theGraph.deal();
	for (int i = 0; i < q; i++)
	{
		cin >> s[i];
	}

	for (int i = 0; i < q; i++)
	{
		//cout<<"break"<<endl;
		theGraph.get_sum(s[i]);
		cout << endl;
	}
	cout << endl;
	//cout << endl;
}

