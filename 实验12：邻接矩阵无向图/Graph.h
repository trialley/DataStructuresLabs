#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
using namespace std;

const int MAX_VERTEX_NUM = 20;  //һ�����ͼ����󶥵���(vertex:����)
const int MAX_WEIGHT = 10000;   //���ֵ

template <class T, class E>  //TΪ����ֵ�����ͣ�EΪȨֵ������
class Graph {
 public:
  Graph(int thistype = 1, int sz = MAX_VERTEX_NUM);  //�ڽӾ���0���ޱߣ�MAX_WEIGHT�����Լ��Ĺ�ϵ��typeΪ1������ͼ��typeΪ2������ͼ��Ĭ������ͼ����
  ~Graph();

  friend istream &operator>>(istream &in, Graph<T, E> &G);

  friend ostream &operator<<(ostream &out, Graph<T, E> &G);

  bool GraphEmpty() const;                     //�ж�ͼ�շ�
  int NumberOfVertices();                      //���ض�����
  int NumberOfEdges();                         //���ر���
  E getWeight(int v1, int v2);                 //ȡ��v1,v2��Ȩֵ
  T getValue(int i);                           //ȡλ��i��ֵ����������0
  int getFirstNeighbor(T k);                   //ȡ����Ϊk�ĵ�һ���ڽӽڵ�
  int getFirstNeighbor(int k, char type);      //ȡ����λ��Ϊk�ĵ�һ���ڽӽڵ�
  int getNextNeighbor(int k, int w);           //ȡ����Ϊk���ڽӶ���λ��w����һ���ڽӶ���λ�ã��±궨λ���㣩
  int getNextNeighbor(T k, int w, char type);  //ȡ����λ��Ϊk���ڽӶ���λ��w����һ���ڽӶ���λ��(�������ݶ�λ���㣩
  bool insertVertex(const T &vertex);          //����һ������
  bool insertEdge(T n1, T n2, E cost = 1);     //�����(n1,n2)��ȨֵΪcost����ֻ��һ�������ɸ��ǣ��ظ�������ͬ�ߡ�����������Լ����Լ��ı�
  bool removeVertex(T v1);                     //ɾ������v1����֮��صıߡ���ɾ�����һ�����㡣
  bool removeEdge(T n1, T n2);                 //ɾ���ߣ�n1,n2��
  int outdegree(T v);                          //����(����ͼ���ȵ�����ȣ�
  int indegree(T v);                           //���
  void DFS(Graph &G, const T &v);              //��ȱ�������v��ʼ
  void BFS(Graph<T, E> &G, const T &v);        //��ȱ�������v��ʼ

 private:
  int type;  //typeΪ1������ͼ��typeΪ2������ͼ

  int maxVertices;     //ͼ����󶥵���
  int numberEdges;     //��ǰ����
  int numberVertices;  //��ǰ������

  T *VerticesList;  //������޳�ʼ������maxVertices����ʹ��
  E **Edge;         //�ڽӾ��󡣳�ʼ����0λ�ޱߣ�MAX_WEIGHT�����Լ��Ĺ�ϵ

  int getVertexPos(T vertex);  //��������vertex��ͼ�е�λ��
  void DFS(Graph &G, int v, bool visited[]);
};

#endif  // GRAPH_H
