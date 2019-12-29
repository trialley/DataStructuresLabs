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
		int currentNode = ++heapSize;//先放到末尾，然后保证是子树
		while (currentNode != 1 && theElement < heap[currentNode / 2])//只要没到顶而且没找到位置（元素小于子节点）
		{
			heap[currentNode] = heap[currentNode / 2];
			currentNode /= 2;
		}
		heap[currentNode] = theElement;
	}
	void pop () {
		if (heapSize == 0) return;

		T theLast = heap[heapSize--];//末尾元素拿出来
		heap[1].~T ();
		int currentNode = 1;//当前节点
		int child = 2;//子节点
		while (child <= heapSize)//自上而下找位置
		{
			if (child<heapSize && heap[child]>heap[child + 1]) {
				child++;
			}
			if (theLast <= heap[child]) { break; }//元素可以放在当前位置
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

struct Edge {//实现的边类
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
struct graphNode//实现的顶点类
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

template <class T>//无向图
class graph {
protected:
	graphNode<T>** aList;//
	Edge* edge_list;
	//T** weight;//用来存权重的二位数组
	int num_ver;//图顶点个数
	int num_edge;//图边个数
	int label;//到达标记
	int* reach;//标记是否到达的数组
	void rDfs (int v);
	void rBfs (int v);
	int* the_dfs;//该数组的首位用来充当计数器的功能
	int* the_bfs;
	int* sum_w;//用来存权重数组
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
		aList[i] = head;//不要忘记给这里赋值
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
	if (p->vertex == v2)//找到了边
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
	if (q->vertex == v1)//找到了边
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
		while (p->next != NULL && v2 > p->next->vertex)//??不能交换????
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
		for (graphNode<T>* u = aList[w]->next; u != NULL; u = u->next) {//访问顶点w的一个关联顶点
			if (reach[u->vertex] == 0)//说明u是一个未到达的顶点
			{
				q.push (u->vertex);
				reach[u->vertex] = label;//到达标记
			}
		}
	}
	return;
}

template<class T>
void graph<T>::get_sum_w (int s)//求解权重最重要的一个函数
{
	for (int i = 0; i <= num_ver; i++) { reach[i] = 0; the_dfs[i] = 0; }//reach数组用来记录点是否到达，the_bfs是保存经过的路径
	int sum_weight = 0;
	rDfs (s);
	int len = the_dfs[0];//dfs和bfs后，连通分量的点个数保存在了数组第一个元素
	fastUnionFind uf (num_ver + 1);//并查集元素个数设为顶点个数
	int num_e = 1;//已经加入图的边的条数
	minHeap<Edge> theHeap (10);//用堆排序来选最小的边,用的是小根堆，堆顶为最小元素
	for (int i = 1; i <= num_edge; i++) {
		int a = edge_list[i].v1;
		int b = edge_list[i].v2;
		if (reach[a] != 0 && reach[b] != 0)//必须是在同一个连通分量的边才可以加入
		{
			theHeap.push (edge_list[i]);
		}
	}
	while (num_e < len) {
		Edge temp = theHeap.top ();
		theHeap.pop ();
		int a = uf.find (temp.v1);//找到一条边的两个顶点的根节点
		int b = uf.find (temp.v2);
		if (a != b)//根节点不同，说明加入后不会形成环
		{
			uf.unite (a, b);//把二者合并
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

	int n, m, q;//n为顶点个数，m为边数，q为查询个数
	int* s;
	cin >> n >> m >> q;
	s = new int[q];//每次要查询的起始顶点
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