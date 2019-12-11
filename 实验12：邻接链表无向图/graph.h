#include"chain.h"
#include"queue.h"
template<class T>
class edge {
public:
    ~edge () {}
    edge (int a, int b, T weight) {
        from = a;
        to = b;
    }
    int vertex1 () const { return from; }
    int vertex2 () const { return to; }
private:
    int from;
    int to;
    //T w;
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
    void insertEdge (int from, int to);
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
void linkedgraph::insertEdge (int from, int to) {
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

int linkedgraph::getShortestDis (int v, int t) {
    int* dis = new int[n];
    fill (dis, dis + n, 0);
    int* path = new int[n];
    fill (path, path + n, 0);

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