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
		//�ж��Ƿ�Ϊ��
		//�е�ʵ�ְ汾��top�������ã�ջ���򷵻�ԭ��ֵ�������ܲ�����ְ��һԭ��
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

		/*������С�������Ĵ���*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const T theElement) {
		//�жϻ��������Ȳ����󻺳���
		if (stackTop == bufferLength - 1) {
			_exLength ();
		}
		head[++stackTop] = theElement;
	}
};

template<class T>
class queue {
public:
	queue (int initialCapacity = 10) {//���캯�� 
		if (initialCapacity < 0) {
			//std::cerr << "���г��ȱ������0��" << std::endl;
		}
		else {
			Queue = new T[initialCapacity];
			arrayLength = initialCapacity;
			qFront = qBack = 0;     //�����Ǵ�Queue[1]��ʼ����Ԫ�� 
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
			std::cerr << "����Ϊ��" << std::endl;
		}
	}
	T& back () {
		if (empty () != true)
			return Queue[qBack];
		else {
			std::cerr << "����Ϊ��" << std::endl; exit (1);
		}
	}
	T pop () {//�Ӷ���ɾ��Ԫ�� 
		T* p = &front (); //�����Ѿ��ж��˶����Ƿ�Ϊ�� 
		T temp = (*p);
		qFront = (qFront + 1) % arrayLength;
		(*p).~T ();  //������Ԫ�غ����ܱ�ʾint��ɾ��...�������޷��ָ�����ʼ����ǰ��״̬
		return temp;
	}
	void push (const T& ele) {//�Ӷ�β���Ԫ�� 
		if ((qBack + 1) % arrayLength == qFront) {//���н������ӱ����鳤�� 
			T* newQueue = new T[2 * arrayLength];
			int start = (qFront + 1) % arrayLength;
			if (start == 0 || start == 1) {//δ�γɻ� 
				std::copy (Queue + start, Queue + qBack + 1, newQueue);
			} else {//�γ��˻� 
				std::copy (Queue + start, Queue + arrayLength, newQueue);
				//���Ƶ�2��(start,����ĩ�ˣ��¶�����㣩 
				std::copy (Queue, Queue + qBack + 1, newQueue + (arrayLength - start));
				//���Ƶ�1�Σ�ԭ�����׶ˣ�qback,�¶��е�arraylength-start��λ�ã� 
			}
			qFront = (arrayLength) * 2 - 1;
			qBack = arrayLength - 1 - 1;   //����������β�α� 
			arrayLength = arrayLength * 2;
			delete[] Queue;
			Queue = newQueue;
		}
		//��Ԫ�ز�����е�β��
		qBack = (qBack + 1) % arrayLength;
		Queue[qBack] = ele;

	}
	void output () {
		for (int i = qFront; i < qBack; i++)
			std::cout << Queue[i];
		std::cout << std::endl;
	}
private:
	int qFront;  //�����е�һ��Ԫ�ص�ǰһ��δ֪ 
	int qBack;   //�������һ��Ԫ�ص�λ�� 
	int arrayLength;  //���е����� 
	T* Queue;	 //����Ԫ�� 
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
	node& operator=(node& A) {//��㸳ֵ 
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
			for (int i = 1; i < initialCapacity; i++)  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
			{
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			listSize = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "��ʼ���ȹ�С��" << endl;
	}
	chain (int initialCapacity) //�൱��Ĭ�Ϲ��캯�� 
	{//����ֻ���ٽڵ㲻�����Ǹ�ֵ 
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
		if (initialCapacity < 0) cerr << "��ʼ���ȹ�С��" << endl;
	}
	chain (const chain<T>& A) {
		listSize = A.listSize;
		if (listSize == 0) {//�˱�Ϊ�� 
			firstnode = NULL;
		} else {//TargetNodeָ��A�Ľڵ㣬SourceNodeָ�������Ľڵ�
		//ֱ�ӽڵ㸳ֵ����ǳ���ƣ�ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			firstnode = SourceNode;
			TargetNode = A.firstnode;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < listSize; i++)  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
			{
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //�����pre_node������һ���¿ռ䲢��ʼ�� 
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
	T& get (int theIndex) const {//����������theIndex�ڵ��data���� 
		checkIndex (theIndex);
		node<T>* cur_node = firstnode;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T get_Weight (int ele) const {//����Ԫ����ele�ڵ��weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = firstnode; cur_node != NULL; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//���ؽڵ�Ԫ��������theElement�Ľڵ���������δ�ҵ��򷵻�-1 
		node<T>* cur_node = firstnode;
		for (int i = 0; i < listSize; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseElement (int theVertex) {//�����������Ҷ������theVertex��Ԫ�أ����ҵ���ɾ�������������Ԫ�ص�ָ�� 
		node<T>* p = firstnode, * tp = NULL;
		while (p != NULL) {
			if (p->data == theVertex) {
				if (p == firstnode) //ɾͷ��� 
					firstnode = firstnode->next;
				else {
					tp->next = p->next;
					delete p;
					return p;
				}
			} else {//Ԫ�ز�����theVertex 
				tp = p;
				p = p->next;
			}
		}
		return NULL;  //�Ҳ����Ļ�����NULL 
	}

	void erase (int theIndex) {//��������ɾ������ΪtheIndex�Ľڵ� 
		checkIndex (theIndex);
		node<T>* deletenode;
		if (theIndex == 0) {//ɾ��ͷ��� 
			deletenode = firstnode;
			firstnode = firstnode->next;
		} else {
			node<T>* p = firstnode;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫɾ���Ľ���ǰ���ڵ� 
			deletenode = p->next;
			p->next = p->next->next;
		}
		listSize--;
		delete deletenode;
	}
	void insert (int theIndex, const T& ele, T weight) {//��eleԪ�ز�������ΪtheIndexλ�õ��½ڵ� 
		checkIndex (theIndex);
		if (theIndex == 0) {//����ͷ�ڵ� 
			node<T>* p = new node<T> (ele, weight, firstnode);
			firstnode = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//������ڵ�
			node<T>* cur_node = firstnode;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫ����Ľ���ǰ���ڵ� 
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
	void i_print () const {//ʹ�õ�������� 
		if (listSize == 0) { cout << "null" << endl;  return; } else {
			iterator I (firstnode);
			for (int i = 0; i < listSize; i++) {
				cout << (*I) << " ";
				I++;
			}
		}
	}

	void clear () {//������ 
		node<T>* deletenode, * p = firstnode;
		for (int i = 0; i < listSize; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		firstnode = NULL;
		listSize = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//����Ҫ���ø��ƹ��캯�� 
		if (A.listSize == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A.firstnode;
			for (int i = 0; i < A.listSize; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iterator {//���캯����*&��ǰ���Լӡ���=��== 
	protected:
		node<T>* _node = NULL;
	public:
		iterator (node<T>* theNode) {
			_node = theNode;
		}
		iterator () {}

		T& operator*() { return _node->data; }  //ȡ�������������Ϊ���÷��� 
		T* operator->() { return &(_node->data); }  //ȡ��ַ���������Ϊָ�뷵�� 
		iterator& operator++() {//ǰ�� 
			_node = _node->next;
			return *this;
		}
		iterator operator++(int) {//��� 
			iterator temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iterator I)const {
			if (_node == I._node) return false;  //������û�ж���_node��==��Ϊʲôû�б��� 
			else return true;
		}
		bool operator==(const iterator I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void checkIndex (int theIndex) const {//ȷ����������Ч�ԣ���ֹԽ��
		if (theIndex<0 || theIndex>listSize) {
			cerr << "index=" << theIndex << ",listSize=" << listSize << "������������Ч�ԣ�" << endl;
		}
	}
	node<T>* firstnode;          //ָ�������һ��Ԫ�ص�ָ�� 
	int listSize;                     //�����Ԫ�ظ��� 	               
};

template<class T>
class linkedWGraph {
	//��Ȩ����ͼ 
protected:
	int n;                 //������ 
	int e;                 //���� 
	chain<T>* aList;  //�ڽӱ� 
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
		delete[] aList;  //�����ͻ��Լ�����chain������������ 
	}
	int numberOfVertices () const { return n; }
	int numberOfEdges () const { return e; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void checkVertex (int theVertex) const {//ȷ������Ч���� 
		if (theVertex<1 || theVertex>n) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>n || v2>n || v1 == v2) {//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (aList[v1].indexOf (v2) == -1) {//�±� 
			aList[v1].insert (0, v2, weight);
			aList[v2].insert (0, v1, weight);
			e++;
		}
	}
	void eraseEdge (int i, int j) {
		if (i > 1 && j > 1 && i <= n && j <= n) {
			int* v = aList[i].eraseElement (j);
			int* j = aList[j].eraseElement (i);  //v,jһ��ͬʱΪ�ջ��߷ǿգ���Ȼ˵��һ���Գ������� 
			if (v != NULL && j != NULL)   e--;   //�ñߴ���
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
		int next (T& theWeight) {//����ָ���������һ���ڽӵ����ź����ĵ�Ȩֵ 
			if (currentVertex != NULL) {
				theWeight = currentVertex->weight;
				int vertex = currentVertex->data;
				currentVertex = currentVertex->next;
				return vertex;
			} else
				return 0;
		}
		int next () {//����ָ���������һ���ڽӵ� 

			if (currentVertex != NULL) {
				int vertex = currentVertex->data;
				currentVertex = currentVertex->next;
				return vertex;
			}
			return 0;
		}
	protected:
		chain<T>* v;    //�ڽӱ�ĵ� 
		node<T>* currentVertex;   //��ǰ�����Ķ��� 
	};
	myIterator* iterator (int theVertex) {
		checkVertex (theVertex);
		return new myIterator (&aList[theVertex]);
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

			for (node<int>* u = aList[vertex].firstnode; u != NULL; u = u->next) {
				if (reach[u->data] == 0) {
					q.push (u->data);	reach[u->data] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {//ʹ��ջʵ�ֵ�DFS�����㷨 
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (n + 1));
		reach[v] = label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //��ջ����ʱ 
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
	int Dijkstra (int start, int dest, int predecessor[]) {//�������·������¼�����·��·����predecessor�Ǵ�start��dest·����destǰ���Ǹ����� 
		int* L = new int[n + 1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for (int i = 1; i <= n; i++) {
			L[i] = 100000;  predecessor[i] = -1;
		}   L[start] = 0;
		for (node<int>* u = aList[start].firstnode; u != NULL; u = u->next) {
			L[u->data] = u->weight;
			predecessor[u->data] = start;  //����start�ڽӵĵ� 
		}
		predecessor[start] = 0;    //Դ����û��ǰ��  
		bool* S = new bool[n + 1];
		for (int i = 1; i <= n; i++)  S[i] = false;  //S[i]��ʾstart������i�����·����� 

		/*�������������ǳ�ʼ��������������*/

		while (S[dest] != true) {/*������һ�����ڶ��㼯S�е�u��L[u]�����С�����Խ���һ�����Ա���*/
			int u, tag;
			for (u = 1; u <= n; u++) {
				auto Minium = [](int L[], bool S[], int n) {//��L[1:n]�����з��ز��ڶ��㼯S����С��Ԫ�� 
					int min = 100000;
					for (int i = 1; i <= n; i++) {
						if (L[i] < min && S[i] == false)
							min = L[i];
					}
					return min;
				};
				if (S[u] == false && L[u] == Minium (L, S, n))  //������һ�����ڶ��㼯S�ұ����С�ĵ㣬���Ӷȿ��Խ���O(1)�� 
				{                                        //���ҵ�д�����ӶȺ�����O(n^3)������ͨ��������ѭ���ж������ۺ������͸��Ӷ�� 
					S[u] = true;  //��u���붥�㼯S��
					tag = u;
					break;
				}
			}

			for (node<int>* u = aList[tag].firstnode; u != NULL; u = u->next) {//�������ҵ��ĵ���ڽӵ�,�����û�б����ʹ����Ҿ���ɱ�����
			  //����д�����Ӷ���O(����)���Ϻ� 
				if (S[u->data] == false && L[tag] + (u->weight) < L[u->data]) {
					L[u->data] = L[tag] + u->weight;
					predecessor[u->data] = tag;    //����v��ǰ����u 
				}
			}
		}
		return L[dest];
	}




};
