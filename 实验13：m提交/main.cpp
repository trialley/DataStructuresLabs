#include <iostream>
using namespace std;

template<class T>
class minHeap {
protected:
	T* heap;
	int heapSize;
	int arrayLength;
	void doubleLength () {
		T* newHeap = new T[2 * arrayLength];
		arrayLength *= 2;
		for (int i = 1; i <= heapSize; i++) {
			newHeap[i] = heap[i];
		}
		delete[]heap;
		heap = newHeap;
	}
public:
	minHeap (int initialCapacity = 10) {
		arrayLength = initialCapacity + 1;
		heap = new T[arrayLength];
		heapSize = 0;
	}
	~minHeap () { delete[] heap; }
	void push (T theElement) {
		if (heapSize == arrayLength - 1) {
			doubleLength ();
		}
		int currentNode = ++heapSize;//�ȷŵ�ĩβ��Ȼ��֤������
		while (currentNode != 1 && theElement < heap[currentNode / 2])//ֻҪû��������û�ҵ�λ�ã�Ԫ��С���ӽڵ㣩
		{
			heap[currentNode] = heap[currentNode / 2];
			currentNode /= 2;
		}
		heap[currentNode] = theElement;
	}
	void pop () {
		if (heapSize == 0) return;

		T theLast = heap[heapSize--];//ĩβԪ���ó���
		heap[1].~T ();
		int currentNode = 1;//��ǰ�ڵ�
		int child = 2;//�ӽڵ�
		while (child <= heapSize)//���϶�����λ��
		{
			if (child<heapSize && heap[child]>heap[child + 1]) {
				child++;
			}
			if (theLast <= heap[child]) { break; }//Ԫ�ؿ��Է��ڵ�ǰλ��
			heap[currentNode] = heap[child];
			currentNode = child;
			child *= 2;
		}
		heap[currentNode] = theLast;
	}
	bool empty () { return heapSize == 0; }
	T top () { if (heapSize != 0) { return heap[1]; } }
};

template<class T>
class arrayQueue {
public:
	arrayQueue (int initialCapacity = 10) {
		if (initialCapacity < 1)
			return;
		arrayLength = initialCapacity;
		queue = new T[arrayLength];
		theFront = 0;
		theBack = 0;
	}
	~arrayQueue () { delete[] queue; }
	bool empty () const { return theFront == theBack; }
	int size () const {
		return (theBack - theFront + arrayLength) % arrayLength;
	}
	T& front () {
		if (theFront == theBack)
			throw empty ();
		return queue[(theFront + 1) % arrayLength];
	}
	T& back () {
		if (theFront == theBack)
			throw empty ();
		return queue[theBack];
	}
	void pop () {
		if (theFront == theBack)
			return;
		theFront = (theFront + 1) % arrayLength;
		queue[theFront].~T ();
	}
	void push (const T& theElement) {
		if ((theBack + 1) % arrayLength == theFront) {
			T* newQueue = new T[2 * arrayLength];

			int start = (theFront + 1) % arrayLength;
			if (start < 2)
				copy (queue + start, queue + start + arrayLength - 1, newQueue);
			else {
				copy (queue + start, queue + arrayLength, newQueue);
				copy (queue, queue + theBack + 1, newQueue + arrayLength - start);
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
	~Edge () {}
	Edge () {}
	Edge (int a, int b, int weight) {
		v1 = a;
		v2 = b;
		w = weight;
	}

	bool operator > (const Edge& x) { return (this->w > x.w); }
	bool operator < (const Edge& x) { return (this->w < x.w); }
	bool operator >= (const Edge& x) { return (this->w >= x.w); }
	bool operator <= (const Edge& x) { return (this->w <= x.w); }
	void operator = (const Edge& x) {
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

	graphNode () { next = NULL; }
	graphNode (T v, int w) { vertex = v; weight = w; next = NULL; }
	graphNode (T v, int w, graphNode<T>* theNext) { vertex = v;  weight = w; next = theNext; }
	void push (T v) { vertex = v; }
	void push (graphNode<T>* theNode) { vertex = theNode->vertex; next = theNode->next; }

	bool operator<= (graphNode<T>& GNode) { return (this->weight <= GNode.weight); }
	bool operator>= (graphNode<T>& GNode) { return (this->weight >= GNode.weight); }
	bool operator> (graphNode<T>& GNode) { return (this->weight > GNode.weight); }
	bool operator< (graphNode<T>& GNode) { return (this->weight < GNode.weight); }
	void set (T element) {
		weight = element;
	}
	T& get () {
		return weight;
	}
};
struct unionFindNode {
	int parent;  // if true then tree weight
	// otherwise pointer to parent in tree
	bool root;   // true iff root

	unionFindNode () {
		parent = 1;
		root = true;
	}
};
class fastUnionFind {
public:
	fastUnionFind (int numberOfElements) {
		// Initialize numberOfElements trees, 1 element per set/class/tree.
		node = new unionFindNode[numberOfElements + 1];
	}
	~fastUnionFind () {
		delete[] node;
	}
	void unite (int rootA, int rootB) {
		// Combine trees with different roots rootA and rootB.
		// Use the weighting rule.
		if (node[rootA].parent < node[rootB].parent) {
			// rootA becomes subtree of rootB
			node[rootB].parent += node[rootA].parent;
			node[rootA].root = false;
			node[rootA].parent = rootB;
		} else {
			// rootB becomes subtree of rootA
			node[rootA].parent += node[rootB].parent;
			node[rootB].root = false;
			node[rootB].parent = rootA;
		}
	}
	int find (int theElement) {
		// Return root of tree containing theElement.
		// Compact path from theElement to root.

		// theRoot will eventually be the root of the tree
		int theRoot = theElement;
		while (!node[theRoot].root)
			theRoot = node[theRoot].parent;

		// compact pathe from theElement to theRoot
		int currentNode = theElement;  // start at theElement
		while (currentNode != theRoot) {
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
class graph {
protected:
	graphNode<T>** aList;//
	Edge* edge_list;
	//T** weight;//������Ȩ�صĶ�λ����
	int num_ver;//ͼ�������
	int num_edge;//ͼ�߸���
	int label;//������
	int* reach;//����Ƿ񵽴������
	void rDfs (int v);
	void rBfs (int v);
	int* the_dfs;//���������λ�����䵱�������Ĺ���
	int* the_bfs;
	int* sum_w;//������Ȩ������
	void get_sum_w (int s);
public:
	graph (int initialize_v, int initialize_e);
	~graph () {
		for (int i = 0; i <= num_ver; i++) {
			delete[]aList[i];
		}
		delete[]aList;
		delete[]reach;
		delete[]the_dfs;
		delete[]the_bfs;
		delete[]edge_list;
	}
	void add (T v1, T v2, int TheWeight);
	void erase (T v1, T v2);
	void get_sum (int s) {
		if (sum_w[s] == 0) {
			get_sum_w (s);
			cout << sum_w[s] << endl;
		} else {
			cout << sum_w[s] << endl;
		}
	}
	void get_edge_list (Edge* a) {
		edge_list = a;
		for (int i = 1; i <= num_edge; i++) {
			add (edge_list[i].v1, edge_list[i].v2, edge_list[i].w);
		}
	}
};

template<class T>
graph<T>::graph (int initialize_v, int initialize_e) {
	num_ver = initialize_v;
	num_edge = initialize_e;
	aList = new graphNode<T> * [initialize_v + 1];
	reach = new int[initialize_v + 1];
	sum_w = new int[initialize_v + 1];
	for (int i = 0; i <= initialize_v; i++) {
		reach[i] = 0;
		sum_w[i] = 0;
	}
	for (int i = 1; i <= initialize_v; i++) {
		graphNode<T>* head = new graphNode<T>;
		aList[i] = head;//��Ҫ���Ǹ����︳ֵ
	}
	label = 1;
	the_dfs = new int[num_ver + 1];
	the_bfs = new int[num_ver + 1];
}
template<class T>
void graph<T>::erase (T v1, T v2) {
	graphNode<T>* p = aList[v1];
	graphNode<T>* pp = NULL;
	while (p->next != NULL && p->vertex != v2) {
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
	while (q->next != NULL && q->vertex != v1) {
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
void graph<T>::add (T v1, T v2, int TheWeight) {
	graphNode<T>* p = aList[v1];
	graphNode<T>* newNode1 = new graphNode<T> (v2, TheWeight);
	graphNode<T>* temp;
	if (p->next == NULL) {
		p->next = newNode1;
	} else {
		while (p->next != NULL && v2 > p->next->vertex)//??���ܽ���????
		{
			p = p->next;
		}
		temp = p->next;
		p->next = newNode1;
		newNode1->next = temp;
	}
	graphNode<T>* q = aList[v2];
	graphNode<T>* newNode2 = new graphNode<T> (v1, TheWeight);
	if (q->next == NULL) {
		q->next = newNode2;
	} else {
		while (q->next != NULL && v1 > q->next->vertex) {
			q = q->next;
		}
		temp = q->next;
		q->next = newNode2;
		newNode2->next = temp;
	}
}

template<class T>
void graph<T>::rDfs (int v) {
	//if (v <= min_ver) { min_ver = v; }
	int x = ++the_dfs[0];
	the_dfs[x] = v;
	reach[v] = label;
	graphNode<T>* p = aList[v];
	while ((p = p->next) != NULL) {
		int u = p->vertex;
		if (reach[u] == 0) {
			rDfs (u);
		}
	}
	return;
}
template<class T>
void graph<T>::rBfs (int v) {
	arrayQueue<int> q (10);
	reach[v] = label;
	q.push (v);
	while (!q.empty ()) {
		int x = ++the_bfs[0];
		int w = q.front ();
		the_bfs[x] = w;
		q.pop ();
		for (graphNode<T>* u = aList[w]->next; u != NULL; u = u->next) {//���ʶ���w��һ����������
			if (reach[u->vertex] == 0)//˵��u��һ��δ����Ķ���
			{
				q.push (u->vertex);
				reach[u->vertex] = label;//������
			}
		}
	}
	return;
}

template<class T>
void graph<T>::get_sum_w (int s)//���Ȩ������Ҫ��һ������
{
	for (int i = 0; i <= num_ver; i++) { reach[i] = 0; the_dfs[i] = 0; }//reach����������¼���Ƿ񵽴the_bfs�Ǳ��澭����·��
	int sum_weight = 0;
	rDfs (s);
	int len = the_dfs[0];//dfs��bfs����ͨ�����ĵ�����������������һ��Ԫ��
	fastUnionFind uf (num_ver + 1);//���鼯Ԫ�ظ�����Ϊ�������
	int num_e = 1;//�Ѿ�����ͼ�ıߵ�����
	minHeap<Edge> theHeap (10);//�ö�������ѡ��С�ı�,�õ���С���ѣ��Ѷ�Ϊ��СԪ��
	for (int i = 1; i <= num_edge; i++) {
		int a = edge_list[i].v1;
		int b = edge_list[i].v2;
		if (reach[a] != 0 && reach[b] != 0)//��������ͬһ����ͨ�����ı߲ſ��Լ���
		{
			theHeap.push (edge_list[i]);
		}
	}
	while (num_e < len) {
		Edge temp = theHeap.top ();
		theHeap.pop ();
		int a = uf.find (temp.v1);//�ҵ�һ���ߵ���������ĸ��ڵ�
		int b = uf.find (temp.v2);
		if (a != b)//���ڵ㲻ͬ��˵������󲻻��γɻ�
		{
			uf.unite (a, b);//�Ѷ��ߺϲ�
			sum_weight = sum_weight + temp.w;
			num_e++;
		}
	}
	for (int i = 1; i <= num_ver; i++) {
		if (reach[i] != 0) {
			sum_w[i] = sum_weight;
		}
	}
}

int main () {

	int n, m, q;//nΪ���������mΪ������qΪ��ѯ����
	int* s;
	cin >> n >> m >> q;
	s = new int[q];//ÿ��Ҫ��ѯ����ʼ����
	graph<int> theGraph (n, m);
	Edge* theEdge = new Edge[m + 1];
	for (int i = 1; i <= m; i++) {
		cin >> theEdge[i].v1 >> theEdge[i].v2 >> theEdge[i].w;
	}
	for (int i = 0; i < q; i++) { cin >> s[i]; }
	theGraph.get_edge_list (theEdge);

	for (int i = 0; i < q; i++) {
		theGraph.get_sum (s[i]);
	}


}