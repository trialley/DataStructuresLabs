#include "Graph.h"

template <class T, class E>
Graph<T, E>::Graph(int thistype, int sz) {
  type = thistype;
  maxVertices = sz;
  numberEdges = 0;
  numberVertices = 0;

  int i, j;
  VerticesList = new T[maxVertices];  //创建顶点表数组
  Edge = (E **)new E *[maxVertices];  //创建邻接矩阵数组  (E**)为显式转换，可不加
  for (i = 0; i < maxVertices; i++) {
    Edge[i] = new E[maxVertices];
  }
  for (i = 0; i < maxVertices; i++)
    for (j = 0; j < maxVertices; j++) {
      Edge[i][j] = (i == j) ? MAX_WEIGHT : 0;  //表中与自己的边的权值无限大
    }
}

template <class T, class E>
Graph<T, E>::~Graph() {
  delete[] VerticesList;
  delete[] Edge;
}

template <class T, class E>
bool Graph<T, E>::GraphEmpty() const {
  if (numberEdges == 0)
    return true;
  else
    return false;
}

template <class T, class E>
int Graph<T, E>::NumberOfVertices() {
  return numberVertices;
}

template <class T, class E>
int Graph<T, E>::NumberOfEdges() {
  return numberEdges;
}

template <class T, class E>
E Graph<T, E>::getWeight(int v1, int v2) {
  return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
}

template <class T, class E>
T Graph<T, E>::getValue(int i) {
  return i >= 0 && i <= numberVertices ? VerticesList[i] : NULL;
}

template <class T, class E>
int Graph<T, E>::getFirstNeighbor(T k) {
  int v = getVertexPos(k);
  if (v != -1) {
    for (int i = 0; i < numberVertices; i++)
      if (Edge[v][i] != 0 && Edge[v][i] != MAX_WEIGHT) return i;
  }
  return -1;
}

template <class T, class E>
int Graph<T, E>::getFirstNeighbor(int k, char type) {
  int v = k;
  if (v != -1) {
    for (int i = 0; i < numberVertices; i++)
      if (Edge[v][i] != 0 && Edge[v][i] != MAX_WEIGHT) return i;
  }
  return -1;
}

template <class T, class E>
int Graph<T, E>::getNextNeighbor(int k, int w) {
  if (k != -1 && w != -1) {
    for (int i = w + 1; i < numberVertices; i++)
      if (Edge[k][i] > 0 && Edge[k][i] < MAX_WEIGHT) return i;
  }
  return -1;
}

template <class T, class E>
int Graph<T, E>::getNextNeighbor(T k, int w, char t) {
  int v = getVertexPos(k);
  if (v != -1 && w != -1) {
    for (int i = w + 1; i < numberVertices; i++)
      if (Edge[v][i] > 0 && Edge[v][i] < MAX_WEIGHT) return i;
  }
  return -1;
}

template <class T, class E>
bool Graph<T, E>::insertVertex(const T &vertex) {
  if (numberVertices == maxVertices) return false;
  VerticesList[numberVertices++] = vertex;
  return true;
}

template <class T, class E>
bool Graph<T, E>::insertEdge(T n1, T n2, E cost) {
  if (type == 1) {
    if (cost > MAX_WEIGHT) return false;  //权值大于上限，插入失败
    int v1 = getVertexPos(n1);
    int v2 = getVertexPos(n2);
    if (v1 > -1 && v1 < numberVertices && v2 > -1 && v2 < numberVertices && Edge[v1][v2] == 0) {
      Edge[v1][v2] = cost;
      Edge[v2][v1] = cost;
      numberEdges++;
      return true;
    } else
      return false;
  } else {
    if (cost > MAX_WEIGHT) return false;  //权值大于上限，插入失败
    int v1 = getVertexPos(n1);
    int v2 = getVertexPos(n2);
    if (v1 > -1 && v1 < numberVertices && v2 > -1 && v2 < numberVertices && Edge[v1][v2] == 0) {
      Edge[v1][v2] = cost;
      numberEdges++;
      return true;
    } else
      return false;
  }
}

template <class T, class E>
bool Graph<T, E>::removeVertex(T v1) {
  if (type == 1) {
    int v = getVertexPos(v1);
    if (v < 0 || v >= numberVertices) return false;  //v1不在图中，不删除
    int i;
    VerticesList[v] = VerticesList[numberVertices - 1];  //用顶点表最后一个元素代替该删除元素
    for (i = 0; i < numberVertices; i++)                 //删除指向v1的边
    {
      if (Edge[i][v] > 0 && Edge[i][v] < MAX_WEIGHT) numberEdges--;
      Edge[i][v] = Edge[i][numberVertices - 1];
      Edge[i][numberVertices - 1] = 0;
    }
    for (i = 0; i < numberVertices - 1; i++)  //删除v1指出的边
    {
      Edge[v][i] = Edge[numberVertices - 1][i];
      Edge[numberVertices - 1][i] = 0;
    }
    numberVertices--;
    return true;
  } else {
    int v = getVertexPos(v1);
    if (v < 0 || v >= numberVertices) return false;  //v1不在图中，不删除
    int i;
    VerticesList[v] = VerticesList[numberVertices - 1];  //用顶点表最后一个元素代替该删除元素
    for (i = 0; i < numberVertices; i++)                 //删除指向v1的边
    {
      if (Edge[i][v] > 0 && Edge[i][v] < MAX_WEIGHT) numberEdges--;
      Edge[i][v] = Edge[i][numberVertices - 1];
      Edge[i][numberVertices - 1] = 0;
    }
    for (i = 0; i < numberVertices - 1; i++)  //删除v1指出的边
    {
      if (Edge[v][i] > 0 && Edge[v][i] < MAX_WEIGHT) numberEdges--;
      Edge[v][i] = Edge[numberVertices - 1][i];
      Edge[numberVertices - 1][i] = 0;
    }
    numberVertices--;
    return true;
  }
}

template <class T, class E>
bool Graph<T, E>::removeEdge(T n1, T n2) {
  if (type == 1) {
    int v1 = getVertexPos(n1);
    int v2 = getVertexPos(n2);
    if (v1 > -1 && v1 < numberVertices && v2 > -1 && v2 < numberVertices && Edge[v1][v2] != 0 && Edge[v1][v2] != MAX_WEIGHT) {
      Edge[v1][v2] = 0;
      Edge[v2][v1] = 0;
      numberEdges--;
      return true;
    } else
      return false;
  } else {
    int v1 = getVertexPos(n1);
    int v2 = getVertexPos(n2);
    if (v1 > -1 && v1 < numberVertices && v2 > -1 && v2 < numberVertices && Edge[v1][v2] != 0 && Edge[v1][v2] != MAX_WEIGHT) {
      Edge[v1][v2] = 0;
      numberEdges--;
      return true;
    } else
      return false;
  }
}

template <class T, class E>
int Graph<T, E>::outdegree(T v) {
  int k = 0;
  int n = getVertexPos(v);
  for (int i = 0; i < maxVertices; i++) {
    if (Edge[n][i] != 0 && Edge[n][i] != MAX_WEIGHT) k++;
  }
  return k;
}

template <class T, class E>
int Graph<T, E>::indegree(T v) {
  int k = 0;
  int n = getVertexPos(v);
  for (int i = 0; i < maxVertices; i++) {
    if (Edge[i][n] != 0 && Edge[i][n] != MAX_WEIGHT) k++;
  }
  return k;
}

template <class T, class E>
int Graph<T, E>::getVertexPos(T vertex) {
  for (int i = 0; i < numberVertices; i++) {
    if (VerticesList[i] == vertex) return i;
  }
  return -1;
}

template <class T, class E>
void Graph<T, E>::DFS(Graph<T, E> &G, const T &v) {
  int i, loc, n = G.NumberOfVertices();
  bool *visited = new bool[n];
  for (i = 0; i < n; i++) visited[i] = false;
  loc = G.getVertexPos(v);
  DFS(G, loc, visited);
  delete[] visited;
}

template <class T, class E>
void Graph<T, E>::DFS(Graph<T, E> &G, int v, bool visited[]) {
  cout << G.getValue(v) << ',';
  visited[v] = true;
  int w = G.getFirstNeighbor(G.getValue(v));
  while (w != -1) {
    if (visited[w] == false) {
      DFS(G, w, visited);
    }
    w = G.getNextNeighbor(v, w);
  }
}

template <class T, class E>
void Graph<T, E>::BFS(Graph<T, E> &G, const T &v) {
  int i, m, n = G.NumberOfVertices();
  bool *visite = new bool[n];
  for (i = 0; i < n; i++) visite[i] = false;
  int loc = G.getVertexPos(v);
  cout << G.getValue(loc) << ' ';
  visite[loc] = true;
  queue<int> Q;  //存某层下标
  Q.push(loc);   //顶点进队列，实现分层访问
  while (!Q.empty()) {
    m = G.getFirstNeighbor(Q.front(), '1');
    for (; m != -1;)  //将顶层结点的所有邻接节点进队列
    {
      if (!visite[m]) {
        Q.push(m);
        visite[m] = true;
      }
      m = G.getNextNeighbor(Q.front(), m);
    }
    Q.pop();
    if (!Q.empty()) {
      cout << G.getValue(Q.front()) << ' ';
    }
  }
}

template <class T, class E>
istream &operator>>(istream &in, Graph<T, E> &G) {
  int i, n, m;
  T e1, e2;
  cout << "请输入顶点数和边数：";
  in >> n >> m;  //输入顶点数和边数
  cout << endl
       << "请输入" << n << "个顶点：";
  for (i = 0; i < n; i++) {
    in >> e1;
    G.insertVertex(e1);
  }
  cout << endl
       << "请输入" << m << "条边：";
  i = 0;
  while (i < m) {
    in >> e1 >> e2;
    if (G.insertEdge(e1, e2)) {
      i++;
    } else
      cout << "边两端点信息有误，重新输入！" << endl;
  }
  return in;
}
template <class T, class E>
ostream &operator<<(ostream &out, Graph<T, E> &G) {
  //TODO:运算符重载好像优先于构造函数，type无法使用，使得有向图和无向图无法直接控制
  int i, j, n, m;  //无向图
  T e1, e2;
  E w;
  n = G.NumberOfVertices();
  m = G.NumberOfEdges();
  out << n << ',' << m << endl;
  for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++) {
      w = G.getWeight(i, j);
      if (w > 0 && w < MAX_WEIGHT) {
        e1 = G.getValue(i);
        e2 = G.getValue(j);
        out << "(" << e1 << "," << e2 /*<< "," << w */ << ")" << endl;
      }
    }
  return out;
}