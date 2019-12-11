#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
using namespace std;

const int MAX_VERTEX_NUM = 20;  //一般情况图的最大顶点数(vertex:顶点)
const int MAX_WEIGHT = 10000;   //最大极值

template <class T, class E>  //T为顶点值的类型，E为权值的类型
class Graph {
 public:
  Graph(int thistype = 1, int sz = MAX_VERTEX_NUM);  //邻接矩阵0表无边，MAX_WEIGHT表与自己的关系；type为1表无向图，type为2表有向图（默认有向图）；
  ~Graph();

  friend istream &operator>>(istream &in, Graph<T, E> &G);

  friend ostream &operator<<(ostream &out, Graph<T, E> &G);

  bool GraphEmpty() const;                     //判断图空否
  int NumberOfVertices();                      //返回顶点数
  int NumberOfEdges();                         //返回边数
  E getWeight(int v1, int v2);                 //取边v1,v2的权值
  T getValue(int i);                           //取位置i的值，不合理返回0
  int getFirstNeighbor(T k);                   //取顶点为k的第一个邻接节点
  int getFirstNeighbor(int k, char type);      //取顶点位置为k的第一个邻接节点
  int getNextNeighbor(int k, int w);           //取顶点为k的邻接顶点位置w的下一个邻接顶点位置（下标定位顶点）
  int getNextNeighbor(T k, int w, char type);  //取顶点位置为k的邻接顶点位置w的下一个邻接顶点位置(顶点数据定位顶点）
  bool insertVertex(const T &vertex);          //插入一个顶点
  bool insertEdge(T n1, T n2, E cost = 1);     //插入边(n1,n2)，权值为cost。边只有一条，不可覆盖，重复插入相同边。不允许插入自己与自己的边
  bool removeVertex(T v1);                     //删除顶点v1和与之相关的边。可删除最后一个顶点。
  bool removeEdge(T n1, T n2);                 //删除边（n1,n2）
  int outdegree(T v);                          //出度(无向图出度等于入度）
  int indegree(T v);                           //入度
  void DFS(Graph &G, const T &v);              //深度遍历，从v开始
  void BFS(Graph<T, E> &G, const T &v);        //广度遍历，从v开始

 private:
  int type;  //type为1表无向图，type为2表有向图

  int maxVertices;     //图中最大顶点数
  int numberEdges;     //当前边数
  int numberVertices;  //当前顶点数

  T *VerticesList;  //顶点表。无初始化，用maxVertices控制使用
  E **Edge;         //邻接矩阵。初始化：0位无边，MAX_WEIGHT表与自己的关系

  int getVertexPos(T vertex);  //给出顶点vertex在图中的位置
  void DFS(Graph &G, int v, bool visited[]);
};

#endif  // GRAPH_H
