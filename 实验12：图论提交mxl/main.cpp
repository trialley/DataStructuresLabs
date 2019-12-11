#include <iostream>
using namespace std;

template <class T>
struct node {
    T data;
    node<T>* next;

    node () {}
    node (const T& datai) :data (datai), next (nullptr) {}
    node (const T& datai, node<T>* nexti) :data (datai), next (nexti) {}
};
template<class T>
class chain {
public:
    chain (int initialCapacity = 10);
    chain (const chain<T>&);
    ~chain ();

    bool empty () const { return listSize == 0; }
    int size () const { return listSize; }
    T& get (int indexi) const;
    int indexOf (const T& datai) const;
    void erase (int indexi);
    void insert (const T& datai);
    void insert (int indexi, const T& datai);
    void output (ostream& out) const;
    node<T>* getfirst () {
        return firstNode;
    }
    T* eraseElement (int theVertex);
protected:
    void checkIndex (int indexi) const;
    node<T>* firstNode;
    int listSize;
};

template<class T>
chain<T>::chain (int initialCapacity) {// Constructor.
    if (initialCapacity < 1)
        return;
    firstNode = NULL;
    listSize = 0;
}

template<class T>
chain<T>::chain (const chain<T>& theList) {// Copy constructor.
    listSize = theList.listSize;

    if (listSize == 0) {// theList is empty
        firstNode = NULL;
        return;
    }

    // non-empty list
    node<T>* sourceNode = theList.firstNode;
    // node in theList to copy from
    firstNode = new node<T> (sourceNode->data);
    // copy first data of theList
    sourceNode = sourceNode->next;
    node<T>* targetNode = firstNode;
    // current last node in *this
    while (sourceNode != NULL) {// copy remaining datas
        targetNode->next = new node<T> (sourceNode->data);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain () {// Chain destructor. Delete all nodes in chain.
    while (firstNode != NULL) {// delete firstNode
        node<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void chain<T>::checkIndex (int indexi) const {// Verify that indexi is between 0 and listSize - 1.
    if (indexi < 0 || indexi >= listSize)
        return;
}

template<class T>
T& chain<T>::get (int indexi) const {// Return data whose index is indexi.
 // Throw illegalIndex exception if no such data.
    checkIndex (indexi);

    // move to desired node
    node<T>* currentNode = firstNode;
    for (int i = 0; i < indexi; i++)
        currentNode = currentNode->next;

    return currentNode->data;
}

template<class T>
int chain<T>::indexOf (const T& datai) const {// Return index of first occurrence of datai.
 // Return -1 if datai not in list.

   // search the chain for datai
    node<T>* currentNode = firstNode;
    int index = 0;  // index of currentNode
    while (currentNode != NULL && currentNode->data != datai) {
        // move to next node
        currentNode = currentNode->next;
        index++;
    }

    // make sure we found matching data
    if (currentNode == NULL)
        return -1;
    else
        return index;
}
template<class T>
T* chain<T>::eraseElement (int theVertex) {
    node<T>* current = firstNode, * trail = NULL;

    while (current != NULL && current->data != theVertex) {
        trail = current;
        current = current->next;
    }
    if (current == NULL)
        return NULL;


    T* datai = &current->data;

    if (trail != NULL)
        trail->next = current->next;
    else
        firstNode = current->next;

    delete current;
    listSize--;
    return datai;
}
template<class T>
void chain<T>::erase (int indexi) {
    checkIndex (indexi);

    node<T>* deleteNode;
    if (indexi == 0) {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        node<T>* p = firstNode;
        for (int i = 0; i < indexi - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next;
    }
    listSize--;
    delete deleteNode;
}
template<class T>
void chain<T>::insert (const T& datai) {
    int a = this->indexOf (datai);
    if (a == -1) {
        node<int>* p = firstNode, * q = firstNode;
        if (firstNode == NULL || datai <= firstNode->data)
            firstNode = new node<T> (datai, firstNode);
        else {
            while (datai > p->data) {
                q = p;
                p = p->next;
                if (p == NULL)
                    break;
            }
            p = new node<T> (datai, q->next);
            q->next = p;
        }
    }
}
template<class T>
void chain<T>::insert (int indexi, const T& datai) {
    if (indexi < 0 || indexi > listSize) {
        return;
    }

    if (indexi == 0)
        firstNode = new node<T> (datai, firstNode);
    else {  // find predecessor of new data
        node<T>* p = firstNode;
        for (int i = 0; i < indexi - 1; i++)
            p = p->next;

        // insert after p
        p->next = new node<T> (datai, p->next);
    }
    listSize++;
}

template<class T>
void chain<T>::output (ostream& out) const {// Put the list into the stream out.
    for (node<T>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
        out << currentNode->data << "  ";
    out << endl;
}

template<class T>
class edge {
public:
    ~edge () {}
    edge (int a, int b, T weight) {
        v1 = a;
        v2 = b;
        w = weight;
    }
    int vertex1 () const {
        return v1;
    }
    int vertex2 () const {
        return v2;
    }
    T weight () const {
        return w;
    }
private:
    int v1;
    int v2;
    T w;
};

/*****************************************************************************
*  queue.h                                                                   *
*  Copyright (C) 2019.10.30 TriAlley  lg139@139.com                          *
*  @brief    链表队列的实现                                                   *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once


/*queue
public:
    enum queue_err { queue_empty };  //常见的错误
private:
    struct node;					//结点类型
    node* _head;					//头结点指针
    node* _end;						//尾结点指针，指向NULL
    int _length;					//元素个数
public:
    queue ();						//构造函数
    ~queue ();						//析构函数
    void push ( const T& in );		//入队列
    T front ();						//获得首元素
    void pop ();					//弹出首元素
    bool isempty ()const;			//是否为空
    int size ()const;				//获取元素个数
*/
template<typename T>
class queue {
public:
    enum queue_err { queue_empty };
private:
    typedef struct node {
        T data;
        node* next;
        node () { next = nullptr; }
    }node;
    node* _head;
    node* _end;
    int _length;
public:
    queue () {
        _head = new node;
        _end = _head;
        _length = 0;
    }
    ~queue () {
        while (_head->next != NULL) {
            node* temp = _head;
            _head = _head->next;
            delete temp;
        }
        delete _head;
    }

    void push (const T& in) {
        _length++;
        node* n_end = new node;
        n_end->data = in;
        n_end->next = NULL;

        _end->next = n_end;
        _end = n_end;
    }
    T front () {
        if (isempty ()) {
            throw queue_empty;
        }
        return _head->next->data;
    }
    void pop () {
        if (isempty ()) {
            throw queue_empty;
        }
        node* n_head = _head->next;
        delete _head;

        _head = n_head;

        _length--;
        return;
    }
    bool isempty ()const { return _head == _end; }
    int size ()const { return _length; }
};
class linkedgraph {
public:
    linkedgraph (int numberOfVertices = 0) {
        if (numberOfVertices < 0)
            return;
        n = numberOfVertices;
        e = 0;
        aList = new chain<int>[n + 1];
    }
    ~linkedgraph () { delete[] aList; }
    int numberOfVertices () const { return n; }
    int numberOfEdges () const { return e; }
    bool directed () const { return true; }
    bool weighted () const { return false; }
    bool existsEdge (int i, int j) const {
        if (i < 1 || j < 1 || i > n || j > n || aList[i].indexOf (j) == -1)
            return false;
        else
            return true;
    }
    void insertEdge (edge<bool>* theEdge);
    void eraseEdge (int i, int j);
    void checkVertex (int theVertex) const {
        if (theVertex < 1 || theVertex > n)
            return;
    }
    int Degree (int theVertex) const {
        checkVertex (theVertex);
        return aList[theVertex].size ();
    }
    void bfs (int v, int* reach, int* path, int label, int& length);
    void dfs (int v, int* reach, int* path, int label, int& length);
    void printBFS (int s);
    void printDFS (int s);
    void printCCs ();
    void printPath (int s, int t);
    void shortestPaths (int v, int* reach, int* path, int label, int& length);
protected:
    int n;
    int e;
    chain<int>* aList;
};
void linkedgraph::dfs (int v, int* reach, int* path, int label, int& length) {
    reach[v] = label;
    path[++length] = v;
    for (node<int>* u = aList[v].getfirst (); u != NULL; u = u->next) {
        if (reach[u->data] == 0)
            dfs (u->data, reach, path, label, length);
    }
}
void linkedgraph::bfs (int v, int* reach, int* path, int label, int& length) {
    queue<int> q;
    reach[v] = label;
    q.push (v);
    length = 0;
    while (!q.isempty ()) {
        int w = q.front ();
        q.pop ();
        path[++length] = w;
        for (node<int>* u = aList[w].getfirst (); u != NULL; u = u->next)
            if (reach[u->data] == 0) {
                q.push (u->data);
                reach[u->data] = label;
            }
    }
}
void linkedgraph::eraseEdge (int i, int j) {
    if (i >= 1 && j >= 1 && i <= n && j <= n) {
        int* v = aList[i].eraseElement (j);
        int* t = aList[j].eraseElement (i);
        if (v != NULL)
            e--;
    }
}
void linkedgraph::insertEdge (edge<bool>* theEdge) {
    int v1 = theEdge->vertex1 ();
    int v2 = theEdge->vertex2 ();
    if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
        return;
    if (aList[v1].indexOf (v2) == -1) {
        aList[v1].insert (v2);
        aList[v2].insert (v1);
        e++;
    }
}
void linkedgraph::printDFS (int s) {
    int* reach = new int[n + 1];
    int* path = new int[n + 1];
    int label = 1;
    int length = 0;
    for (int i = 1; i <= n; i++)
        reach[i] = 0;
    dfs (s, reach, path, label, length);
    cout << length << endl;
    for (int i = 1; i <= length; i++)
        cout << path[i] << " ";
    cout << endl;
}
void linkedgraph::printBFS (int s) {
    int* reach = new int[n + 1];
    int* path = new int[n + 1];
    int label = 1;
    int length = 0;
    for (int i = 1; i <= n; i++)
        reach[i] = 0;
    bfs (s, reach, path, label, length);
    cout << length << endl;
    for (int i = 1; i <= length; i++)
        cout << path[i] << " ";
    cout << endl;
}
void linkedgraph::printCCs () {
    int label = 0;
    int length = 0;
    int* reach = new int[n + 1];
    int* path = new int[n + 1];
    int* weight = new int[n + 1];
    for (int i = 1; i <= n; i++)
        reach[i] = 0;
    for (int i = 1; i <= n; i++) {
        if (reach[i] == 0) {
            length = 0;
            label++;
            dfs (i, reach, path, label, length);
            weight[label] = path[1];
        }
    }
    cout << label << endl;
    for (int i = 1; i <= label; i++) {
        cout << weight[i] << " ";
    }
        
    cout << endl;
}

void linkedgraph::shortestPaths (int v, int* reach, int* path, int label, int& length) {
    queue<int> q;
    q.push (v);
    length = 0;
    while (!q.isempty ()) {
        int w = q.front ();
        q.pop ();
        path[++length] = w;
        for (node<int>* u = aList[w].getfirst (); u != NULL; u = u->next)
            if (reach[u->data] == 0 && (u->data != v)) {
                q.push (u->data);
                reach[u->data] = reach[w] + 1;
            }
    }
}
void linkedgraph::printPath (int s, int t) {
    int* reach = new int[n + 1];
    int* path = new int[n + 1];
    int label = 1;
    int length = 0;
    for (int i = 1; i <= n; i++)
        reach[i] = 0;
    shortestPaths (s, reach, path, label, length);
    if (reach[t] != 0)
        cout << reach[t] << endl;
    else
        cout << "-1" << endl;
}
int main () {
#pragma warning(disable:4996)
    freopen ("input.txt", "r", stdin);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    linkedgraph map (n);
    while (m != 0) {
        int a, b, c;
        cin >> a >> b >> c;
        edge<bool>* theEdge = new edge<bool> (b, c, true);
        switch (a) {
        case 0:
            map.insertEdge (theEdge);
            break;
        case 1:
            map.eraseEdge (b, c);
            break;
        }
        m--;
    }

    //第一行输出图中有多少个连通分量
    //第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔
    map.printCCs ();
    //第三行输出从s点开始的dfs序列长度

    //第四行输出从s点开始的字典序最小的dfs序列
    map.printDFS (s);

    //第五行输出从t点开始的bfs序列的长度
    //第六行输出从t点开始字典序最小的bfs序列
    map.printBFS (t);

    //第七行输出从s点到t点的最短路径，若是不存在路径则输出-1
    map.printPath (s, t);
    return 0;
}
