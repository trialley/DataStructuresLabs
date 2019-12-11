#include <iostream>
using namespace std;
#define until(re) while(!(re))

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
    typedef enum err{ chain_index_out_of_range }err;
    chain ();
    chain (const chain<T>&);
    ~chain ();

    bool empty () const { return _list_size == 0; }
    int size () const { return _list_size; }
    T& getByIndex (int indexi) const;
    int getIndexByData (const T& datai) const;
    void eraseByIndex (int indexi);
    void insert (const T& weighti);
    void output (ostream& out) const;
    node<T>* getfirst () {
        return _head;
    }
    T* eraseByData(int theVertex);
protected:
    void _checkIndex (int indexi) const;
    node<T>* _head;
    int _list_size;
};

template<class T>
chain<T>::chain ():_head(nullptr), _list_size(0){}

template<class T>
chain<T>::chain (const chain<T>& theList) {
    _list_size = theList._list_size;

    if (_list_size == 0) {
        _head = nullptr;
        return;
    }

    node<T>* sorce_node = theList._head;

    _head = new node<T> (sorce_node->data);

    sorce_node = sorce_node->next;
    node<T>* target_node = _head;

    until (sorce_node == nullptr) {
        target_node->next = new node<T> (sorce_node->data);
        target_node = target_node->next;
        sorce_node = sorce_node->next;
    }
    target_node->next = nullptr;
}

template<class T>
chain<T>::~chain () {
    until (_head == nullptr) {
        node<T>* next_node = _head->next;
        delete _head;
        _head = next_node;
    }
}

template<class T>
void chain<T>::_checkIndex (int indexi) const {
    if (indexi < 0 || indexi >= _list_size)
        throw chain_index_out_of_range;
}

template<class T>
T& chain<T>::getByIndex (int indexi) const {
    _checkIndex (indexi);

    node<T>* current_node = _head;
    for (int i = 0; i < indexi; i++)
        current_node = current_node->next;

    return current_node->data;
}

template<class T>
int chain<T>::getIndexByData (const T& datai) const {
    node<T>* current_node = _head;
    int index = 0;
    until (current_node == nullptr || current_node->data == datai) {
        current_node = current_node->next;
        index++;
    }

    if (current_node == nullptr) {
        return -1;
    }else {
        return index;
    }
}
template<class T>
T* chain<T>::eraseByData (int theVertex) {
    node<T>* current = _head, * trail = nullptr;

    until (current == nullptr || current->data == theVertex) {
        trail = current;
        current = current->next;
    }
    if (current == nullptr) {
        return nullptr;
    }

    T* datai = &current->data;

    if (trail != nullptr) {
        trail->next = current->next;
    } else {
        _head = current->next;
    }

    delete current;
    _list_size--;
    return datai;
}
template<class T>
void chain<T>::eraseByIndex (int indexi) {
    _checkIndex (indexi);

    node<T>* deleteNode;
    if (indexi == 0) {
        deleteNode = _head;
        _head = _head->next;
    } else {
        node<T>* p = _head;
        for (int i = 0; i < indexi - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next;
    }
    _list_size--;
    delete deleteNode;
}
template<class T>
void chain<T>::insert (const T& weighti) {
    int a = this->getIndexByData (weighti);
    if (a == -1) {
        node<int>* p = _head, * q = _head;
        if (_head == nullptr || weighti <= _head->data)
            _head = new node<T> (weighti, _head);
        else {
            while (weighti > p->data) {
                q = p;
                p = p->next;
                if (p == nullptr)
                    break;
            }
            p = new node<T> (weighti, q->next);
            q->next = p;
        }
    }
}


template<class T>
void chain<T>::output (ostream& out) const {
    for (node<T>* current_node = _head; current_node != nullptr; current_node = current_node->next)
        out << current_node->data << "  ";
    out << endl;
}

template<class T>
class edge {
public:
    ~edge () {}
    edge (int a, int b, T weight) {
        from = a;
        to = b;
    }
    int vertex1 () const {return from;}
    int vertex2 () const {return to;}
private:
    int from;
    int to;
    //T w;
};

/*****************************************************************************
*  queue.h                                                                   *
*  Copyright (C) 2019.10.30 TriAlley  lg139@139.com                          *
*  @brief    链表队列的实现                                                   *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
/*queue
public:
    enum queue_err { queue_empty };  //常见的错误
private:
    struct node;					//结点类型
    node* _head;					//头结点指针
    node* _end;						//尾结点指针，指向nullptr
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
        until (_head->next == nullptr) {
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
        n_end->next = nullptr;

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
        _chain_heads = new chain<int>[n + 1];
    }
    ~linkedgraph () { delete[] _chain_heads; }
    int numberOfVertices () const { return n; }
    int numberOfEdges () const { return e; }
    bool directed () const { return true; }
    bool weighted () const { return false; }
    bool existsEdge (int i, int j) const {
        if (i < 1 || j < 1 || i > n || j > n || _chain_heads[i].getIndexByData (j) == -1)
            return false;
        else
            return true;
    }
    void insertEdge (int from,int to);
    void eraseEdge (int i, int j);
    void checkVertex (int theVertex) const {
        if (theVertex < 1 || theVertex > n)
            return;
    }
    int Degree (int theVertex) const {
        checkVertex (theVertex);
        return _chain_heads[theVertex].size ();
    }
    void _bfs (int v, int* reach, int* path, int label, int& length);
    void _dfs (int v, int* reach, int* path, int label, int& length);
    void printBFS (int s);
    void printDFS (int s);
    void printCCs ();
    int getShortestDis (int v, int t);
protected:
    int n;
    int e;
    chain<int>* _chain_heads;
};
void linkedgraph::_dfs (int v, int* reach, int* path, int label, int& length) {
    reach[v] = label;
    path[++length] = v;
    for (node<int>* u = _chain_heads[v].getfirst (); u != nullptr; u = u->next) {
        if (reach[u->data] == 0)
            _dfs (u->data, reach, path, label, length);
    }
}
void linkedgraph::_bfs (int v, int* reach, int* path, int label, int& length) {
    queue<int> q;
    reach[v] = label;
    q.push (v);
    length = 0;
    until (q.isempty ()) {
        int w = q.front ();
        q.pop ();
        path[++length] = w;
        for (node<int>* u = _chain_heads[w].getfirst (); u != nullptr; u = u->next)
            if (reach[u->data] == 0) {
                q.push (u->data);
                reach[u->data] = label;
            }
    }
}
void linkedgraph::eraseEdge (int i, int j) {
    if (i >= 1 && j >= 1 && i <= n && j <= n) {
        int* v = _chain_heads[i].eraseByData (j);
        int* t = _chain_heads[j].eraseByData (i);
        if (v != nullptr)
            e--;
    }
}
void linkedgraph::insertEdge (int from,int to) {
    if (from < 1 || to < 1 || from > n || to > n || from == to)
        return;
    if (_chain_heads[from].getIndexByData (to) == -1) {
        _chain_heads[from].insert (to);
        _chain_heads[to].insert (from);
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
    _dfs (s, reach, path, label, length);
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
    _bfs (s, reach, path, label, length);
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
            _dfs (i, reach, path, label, length);
            weight[label] = path[1];
        }
    }
    cout << label << endl;
    for (int i = 1; i <= label; i++) {
        cout << weight[i] << " ";
    }
        
    cout << endl;
}

int linkedgraph::getShortestDis (int v,int t) {
    int* dis = new int[n];
    fill (dis, dis + n, 0);
int* path = new int[n];
fill (path, path+ n, 0);

    queue<int> q;
    q.push (v);
   int  length = 0;
    until (q.isempty ()) {
        int w = q.front ();
        q.pop ();
        path[++length] = w;
        for (node<int>* u = _chain_heads[w].getfirst (); u != nullptr; u = u->next)
            if (dis[u->data] == 0 && (u->data != v)) {
                q.push (u->data);
                dis[u->data] = dis[w] + 1;
                if (u->data == t) {
                    return dis[u->data];
                }
            }
    }
    return -1;
}

int main () {
#pragma warning(disable:4996)
    freopen ("input.txt", "r", stdin);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    linkedgraph g (n);
    until (m == 0) {
        int a, b, c;
        cin >> a >> b >> c;
        switch (a) {
        case 0:
            g.insertEdge (b,c);
            break;
        case 1:
            g.eraseEdge (b, c);
            break;
        }
        m--;
    }

    //第一行输出图中有多少个连通分量
    //第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔
    g.printCCs ();
    //第三行输出从s点开始的_dfs序列长度

    //第四行输出从s点开始的字典序最小的_dfs序列
    g.printDFS (s);

    //第五行输出从t点开始的_bfs序列的长度
    //第六行输出从t点开始字典序最小的_bfs序列
    g.printBFS (t);

    //第七行输出从s点到t点的最短路径，若是不存在路径则输出-1
 
    cout <<g.getShortestDis (s, t);
    return 0;
}
