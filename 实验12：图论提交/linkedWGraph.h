#include<cstring>//memcpy
#include<cstdlib>//min
#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class stack {
public:
	typedef enum { pointer_is_null, newLength_less_than_zero, stack_empty } stack_err;
protected:
	void _exLength () {
		T* temp = new T[bufferLength * 2];
		memcpy (temp, head, bufferLength * sizeof (T));
		delete[] head;
		head = temp;
		bufferLength = bufferLength * 2;
	}
	void _shLength () {
		T* temp = new T[bufferLength / 2];
		memcpy (temp, head, bufferLength / 2 * sizeof (T));
		delete[] head;
		head = temp;
		bufferLength = bufferLength / 2;
	}
	int stackTop;
	int bufferLength;
	T* head;
public:
	stack (int initialCapacity = 10) {
		bufferLength = initialCapacity;
		head = new T[bufferLength];
		stackTop = -1;
	}
	~stack () { delete[] head; }
	bool empty () const { return stackTop == -1; }
	int size () const { return stackTop + 1; }
	T top () {
		//判断是否为空
		//有的实现版本中top输入引用，栈空则返回原数值，这样很不符合职责单一原则
		if (stackTop == -1) {
			throw stack_empty;
		}
		return head[stackTop];
	}
	void pop () {
		if (stackTop == -1) {
			throw stack_empty;
		}
		head[stackTop--].~T ();

		/*用于缩小缓冲区的代码*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const T theElement) {
		//判断缓冲区长度并扩大缓冲区
		if (stackTop == bufferLength - 1) {
			_exLength ();
		}
		head[++stackTop] = theElement;
	}
};

template<class T>
class queue {
public:
	queue (int initialCapacity = 10) {//构造函数 
		if (initialCapacity < 0) {
			//std::cerr << "队列长度必须大于0！" << std::endl;
		}
		else {
			Queue = new T[initialCapacity];
			arrayLength = initialCapacity;
			qFront = qBack = 0;     //这里是从Queue[1]开始插入元素 
		}
	}
	~queue () { delete[] Queue; }
	bool empty () const {
		if (qFront == qBack) return true;
		else return false;
	}
	int size () const {
		return (arrayLength + qBack - qFront) % arrayLength;
	}
	T& front () {
		if (empty () != true)
			return Queue[(qFront + 1) % arrayLength];
		else {
			std::cerr << "队列为空" << std::endl;
		}
	}
	T& back () {
		if (empty () != true)
			return Queue[qBack];
		else {
			std::cerr << "队列为空" << std::endl; exit (1);
		}
	}
	T pop () {//从队首删除元素 
		T* p = &front (); //这里已经判断了队列是否为空 
		T temp = (*p);
		qFront = (qFront + 1) % arrayLength;
		(*p).~T ();  //析构首元素好像不能表示int的删除...，就是无法恢复到初始化以前的状态
		return temp;
	}
	void push (const T& ele) {//从队尾添加元素 
		if ((qBack + 1) % arrayLength == qFront) {//队列将满，加倍数组长度 
			T* newQueue = new T[2 * arrayLength];
			int start = (qFront + 1) % arrayLength;
			if (start == 0 || start == 1) {//未形成环 
				std::copy (Queue + start, Queue + qBack + 1, newQueue);
			} else {//形成了环 
				std::copy (Queue + start, Queue + arrayLength, newQueue);
				//复制第2段(start,队列末端，新队列起点） 
				std::copy (Queue, Queue + qBack + 1, newQueue + (arrayLength - start));
				//复制第1段（原队列首端，qback,新队列第arraylength-start个位置） 
			}
			qFront = (arrayLength) * 2 - 1;
			qBack = arrayLength - 1 - 1;   //重新设置首尾游标 
			arrayLength = arrayLength * 2;
			delete[] Queue;
			Queue = newQueue;
		}
		//把元素插入队列的尾部
		qBack = (qBack + 1) % arrayLength;
		Queue[qBack] = ele;

	}
	void output () {
		for (int i = qFront; i < qBack; i++)
			std::cout << Queue[i];
		std::cout << std::endl;
	}
private:
	int qFront;  //队列中第一个元素的前一个未知 
	int qBack;   //队列最后一个元素的位置 
	int arrayLength;  //队列的容量 
	T* Queue;	 //队列元素 
};

template<class T>
struct node {
	T data;
	T weight;
	node* next = NULL;

	node (T ele, T w, node* p) {
		data = ele;
		weight = w;
		next = p;
	}
	node (T ele, T w) {
		data = ele;
		weight = w;
	}
	node () {}
	node& operator=(node& A) {//结点赋值 
		data = A.data;
		weight = A.weight;
		next = A.next;
		return *this;
	}
};

template<class T>
class chain {
public:
	chain () {
		firstnode = NULL;
		listSize = 0;
	}
	chain (int initialCapacity, T A[]) {
		if (initialCapacity > 0) {
			firstnode = new node<T>;
			firstnode->data = A[0];
			node<T>* p1 = firstnode, * p2;
			for (int i = 1; i < initialCapacity; i++)  //等于1的话前面已经创建好了一个节点 
			{
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			listSize = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "初始长度过小！" << endl;
	}
	chain (int initialCapacity) //相当于默认构造函数 
	{//这里只开辟节点不给他们赋值 
		if (initialCapacity >= 0) {
			firstnode = new node<T>;
			node<T>* p1 = firstnode, * p2;
			for (int i = 1; i < initialCapacity; i++) {
				p2 = new node<T>;
				p1->next = p2;
				p1 = p2;
			}
			listSize = initialCapacity;
		}
		if (initialCapacity < 0) cerr << "初始长度过小！" << endl;
	}
	chain (const chain<T>& A) {
		listSize = A.listSize;
		if (listSize == 0) {//此表为空 
			firstnode = NULL;
		} else {//TargetNode指向A的节点，SourceNode指向此链表的节点
		//直接节点赋值会变成浅复制，ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			firstnode = SourceNode;
			TargetNode = A.firstnode;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < listSize; i++)  //等于1的话前面已经创建好了一个节点 
			{
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //这里给pre_node创建了一个新空间并初始化 
				SourceNode->next = pre_node;
				SourceNode = pre_node;
			}
		}


	}
	~chain () {
		while (firstnode != NULL) {
			node<T>* nextnode = firstnode->next;
			delete firstnode;
			firstnode = nextnode;
		}
	}
	bool empty () const {
		return listSize == 0;
	}
	int size () const {
		return listSize;
	}
	T& get (int theIndex) const {//返回索引是theIndex节点的data内容 
		checkIndex (theIndex);
		node<T>* cur_node = firstnode;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T get_Weight (int ele) const {//返回元素是ele节点的weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = firstnode; cur_node != NULL; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//返回节点元素内容是theElement的节点索引，若未找到则返回-1 
		node<T>* cur_node = firstnode;
		for (int i = 0; i < listSize; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseElement (int theVertex) {//搜索链表并查找顶点等于theVertex的元素，若找到则删除它并返回这个元素的指针 
		node<T>* p = firstnode, * tp = NULL;
		while (p != NULL) {
			if (p->data == theVertex) {
				if (p == firstnode) //删头结点 
					firstnode = firstnode->next;
				else {
					tp->next = p->next;
					delete p;
					return p;
				}
			} else {//元素不等于theVertex 
				tp = p;
				p = p->next;
			}
		}
		return NULL;  //找不到的话返回NULL 
	}

	void erase (int theIndex) {//从链表中删除索引为theIndex的节点 
		checkIndex (theIndex);
		node<T>* deletenode;
		if (theIndex == 0) {//删除头结点 
			deletenode = firstnode;
			firstnode = firstnode->next;
		} else {
			node<T>* p = firstnode;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//此时已经找到要删除的结点的前驱节点 
			deletenode = p->next;
			p->next = p->next->next;
		}
		listSize--;
		delete deletenode;
	}
	void insert (int theIndex, const T& ele, T weight) {//将ele元素插入索引为theIndex位置的新节点 
		checkIndex (theIndex);
		if (theIndex == 0) {//插入头节点 
			node<T>* p = new node<T> (ele, weight, firstnode);
			firstnode = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//待插入节点
			node<T>* cur_node = firstnode;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//此时已经找到要插入的结点的前驱节点 
			p->next = cur_node->next;
			cur_node->next = p;
		}
		listSize++;
	}
	void output () const {
		if (listSize == 0) { cout << "null" << endl;  return; } else {
			node<T>* p = firstnode;
			for (int i = 0; i < listSize; i++) {
				cout << "vertex=" << p->data << ",weight=" << p->weight << "   ";
				p = p->next;
			}
		}
	}
	void i_print () const {//使用迭代器输出 
		if (listSize == 0) { cout << "null" << endl;  return; } else {
			iterator I (firstnode);
			for (int i = 0; i < listSize; i++) {
				cout << (*I) << " ";
				I++;
			}
		}
	}

	void clear () {//清表操作 
		node<T>* deletenode, * p = firstnode;
		for (int i = 0; i < listSize; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		firstnode = NULL;
		listSize = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//这里要调用复制构造函数 
		if (A.listSize == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A.firstnode;
			for (int i = 0; i < A.listSize; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iterator {//构造函数、*&、前后自加、！=、== 
	protected:
		node<T>* _node = NULL;
	public:
		iterator (node<T>* theNode) {
			_node = theNode;
		}
		iterator () {}

		T& operator*() { return _node->data; }  //取内容运算符，作为引用返回 
		T* operator->() { return &(_node->data); }  //取地址运算符，作为指针返回 
		iterator& operator++() {//前加 
			_node = _node->next;
			return *this;
		}
		iterator operator++(int) {//后加 
			iterator temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iterator I)const {
			if (_node == I._node) return false;  //这里我没有定义_node的==，为什么没有报错？ 
			else return true;
		}
		bool operator==(const iterator I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void checkIndex (int theIndex) const {//确定索引的有效性，防止越界
		if (theIndex<0 || theIndex>listSize) {
			cerr << "index=" << theIndex << ",listSize=" << listSize << "请检查索引的有效性！" << endl;
		}
	}
	node<T>* firstnode;          //指向链表第一个元素的指针 
	int listSize;                     //链表的元素个数 	               
};

template<class T>
class linkedWGraph {
	//加权无向图 
protected:
	int n;                 //顶点数 
	int e;                 //边数 
	chain<T>* aList;  //邻接表 
	int* reach;  //数组指针 
	int label = 1;

	void rDfs (int v) {//递归实现深度优先搜索
		reach[v] = label;  int u;
		//cout<<"当前走到顶点："<<v<<endl;
		myIterator* iv = iterator (v);  //这里加<T>就会报错，为什么？？ 
		while ((u = iv->next ()) != 0) {//以v的下一个邻接点u为新起点递归搜索 
		//cout<<v<<"的下一个邻接点是："<<u<<" "<<endl;
			if (reach[u] != label)
				rDfs (u);  //u是一个没有到达过的顶点 
		}
		delete iv;
		return;
	}

public:
	void output () {
		for (int i = 1; i <= n; i++) {
			cout << "aList[" << i << "]="; aList[i].output ();
			cout << endl;
		}
	}
	linkedWGraph (int v) {
		if (v > 0)
			n = v;
		e = 0;
		aList = new chain<int>[n + 1];
	}
	~linkedWGraph () {
		delete[] aList;  //这样就会自己调用chain的析构函数吗？ 
	}
	int numberOfVertices () const { return n; }
	int numberOfEdges () const { return e; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void checkVertex (int theVertex) const {//确认是有效顶点 
		if (theVertex<1 || theVertex>n) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>n || v2>n || v1 == v2) {//越界处理 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (aList[v1].indexOf (v2) == -1) {//新边 
			aList[v1].insert (0, v2, weight);
			aList[v2].insert (0, v1, weight);
			e++;
		}
	}
	void eraseEdge (int i, int j) {
		if (i > 1 && j > 1 && i <= n && j <= n) {
			int* v = aList[i].eraseElement (j);
			int* j = aList[j].eraseElement (i);  //v,j一定同时为空或者非空，不然说明一致性出了问题 
			if (v != NULL && j != NULL)   e--;   //该边存在
		}
	}
	int Degree (int Vertex) {
		checkVertex (Vertex);
		return aList[Vertex].size ();
	}

	class myIterator {
	public:
		myIterator (chain<T>* theVertex) {
			v = theVertex;
			currentVertex = v->firstnode;
		}
		~myIterator () {}
		int next (T& theWeight) {//返回指定顶点的下一个邻接点的序号和它的的权值 
			if (currentVertex != NULL) {
				theWeight = currentVertex->weight;
				int vertex = currentVertex->data;
				currentVertex = currentVertex->next;
				return vertex;
			} else
				return 0;
		}
		int next () {//返回指定顶点的下一个邻接点 

			if (currentVertex != NULL) {
				int vertex = currentVertex->data;
				currentVertex = currentVertex->next;
				return vertex;
			}
			return 0;
		}
	protected:
		chain<T>* v;    //邻接表的点 
		node<T>* currentVertex;   //当前搜索的顶点 
	};
	myIterator* iterator (int theVertex) {
		checkVertex (theVertex);
		return new myIterator (&aList[theVertex]);
	}

	bool connected () {//判断无向图是否连通 
		if (directed ()) {
			cerr << "本图是无向图！" << endl;  exit (2);
		}

		reach = new int[n + 1];
		for (int i = 1; i <= n; i++)
			reach[i] = 0;

		dfs (1, reach, 1); //给邻接于顶点1的可达顶点做标记

		for (int i = 1; i <= n; i++) {//检查所有顶点是否已做标记
			if (reach[i] == 0)
				return false;
		}
		return true;
	}
	void bfs (int v, int reach[], int label) {//广度优先算法，reach[i]用来标记所有邻接于顶点v的可到达的顶点 
		queue<int> q (10);
		reach[v] = label;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (node<int>* u = aList[vertex].firstnode; u != NULL; u = u->next) {
				if (reach[u->data] == 0) {
					q.push (u->data);	reach[u->data] = label;
				}
			}
		}
	}
	void dfs (int v, int reach[], int label) {
		reach = reach;
		label = label;
		rDfs (v);
	}
	int labelComponents (int c[]) {//返回连通分支数，c[i]是顶点i所属的分支序号 
		int i = 0;
		for (i = 0; i <= n; i++)
			c[i] = 0;

		int label = 0;  //最后一个构建的编号 
		for (i = 1; i <= n; i++) {
			if (c[i] == 0) {//对所有未到达的顶点，都进行一次bfs标记 
				label++;
				bfs (i, c, label);  //给新分支做标记 
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

			for (node<int>* u = aList[vertex].firstnode; u != NULL; u = u->next) {
				if (reach[u->data] == 0) {
					q.push (u->data);	reach[u->data] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {//使用栈实现的DFS搜索算法 
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (n + 1));
		reach[v] = label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //当栈不空时 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //对上一个到达的点w的所有邻接点 
			{
				if (reach[u] != label) //如果存在一个未标记的点j 
				{
					reach[u] = label;
					s.push (u);
					cout << u << " ";
					iv = iterator (u);	//让iv指向以u为起点的迭代器 
				} else {//该顶点已被标记
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //该顶点没有其他邻接点了
				}
			}
		}
	}
	int Dijkstra (int start, int dest, int predecessor[]) {//返回最短路长，记录下最短路的路径，predecessor是从start到dest路径中dest前的那个顶点 
		int* L = new int[n + 1];  //L[i]就是从start点到顶点i的距离 
		for (int i = 1; i <= n; i++) {
			L[i] = 100000;  predecessor[i] = -1;
		}   L[start] = 0;
		for (node<int>* u = aList[start].firstnode; u != NULL; u = u->next) {
			L[u->data] = u->weight;
			predecessor[u->data] = start;  //对于start邻接的点 
		}
		predecessor[start] = 0;    //源顶点没有前驱  
		bool* S = new bool[n + 1];
		for (int i = 1; i <= n; i++)  S[i] = false;  //S[i]表示start到顶点i的最短路已求得 

		/*…………以上是初始化操作…………*/

		while (S[dest] != true) {/*下面找一个不在顶点集S中的u且L[u]标号最小，可以借助一下线性表吗？*/
			int u, tag;
			for (u = 1; u <= n; u++) {
				auto Minium = [](int L[], bool S[], int n) {//在L[1:n]数组中返回不在顶点集S中最小的元素 
					int min = 100000;
					for (int i = 1; i <= n; i++) {
						if (L[i] < min && S[i] == false)
							min = L[i];
					}
					return min;
				};
				if (S[u] == false && L[u] == Minium (L, S, n))  //这里找一个不在顶点集S且标号最小的点，复杂度可以降到O(1)吗？ 
				{                                        //按我的写法复杂度好像是O(n^3)，可以通过把两个循环判断条件糅合来降低复杂度嘛？ 
					S[u] = true;  //把u加入顶点集S中
					tag = u;
					break;
				}
			}

			for (node<int>* u = aList[tag].firstnode; u != NULL; u = u->next) {//遍历刚找到的点的邻接点,如果它没有被访问过，且距离可被更新
			  //这样写，复杂度是O(链表长)，较好 
				if (S[u->data] == false && L[tag] + (u->weight) < L[u->data]) {
					L[u->data] = L[tag] + u->weight;
					predecessor[u->data] = tag;    //顶点v的前驱是u 
				}
			}
		}
		return L[dest];
	}




};
