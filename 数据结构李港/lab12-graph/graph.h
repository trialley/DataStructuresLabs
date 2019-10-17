/*题目描述
给定一个无向简单图，n个点m条边，点的编号从1到n。另外给定两个点编号s，t。
要求输出该无向图的联通子图个数，并按序输出每个联通子图中最小的点编号。

另外输出从s点开始的字典序最小的DFS序列，从t点开始的字典序最小的BFS序列。
再输出s到t的最短路径长度。
输入描述
第一行有四个正整数，N，M，s，t
接下来m行
每行有三个整数：a，b，c，表示第a个点和第b个点连有长度为c的边（保证c等于1）。
输出描述
第一行，一个数字k，表示联通子图个数
第二行，k个整数，表示按序输出的每个联通子图中最小的点编号

第三行，一个数字k，表示从s点开始的DFS序列长度
第四行，k个整数，从s点开始的字典序最小的DFS序列，序列每个元素表示点的编号

第五行，一个数字k，表示从t点开始的BFS序列长度
第六行，k个整数，从t点开始的字典序最小的BFS序列，序列每个元素表示点的编号
第七行，s到t的最短路径长度，若不存在，输出-1*/

#pragma once
#include"vector.h"


enum arrGraphErr {no_parameter_size};
template<typename T>
class arrGraph {
	T* nodes;
	int** weights;
	int nodeNum;
public:
	arrGraph() {
		throw no_parameter_size;
	}
	arrGraph(int isize) {
		size = isize;
		
		nodes = new T[size];
		weights = new int*[size];
		for (int i = 0; i < size; i++) {
			weights[i]=new int[size];
		}
	}
	~arrGraph() {
		delete[] nodes;
		for (int i = 0; i < size; i++) {
			delete[] weights[i];
		}
		delete[] weights;
	}


	T** ShortestPath() {

	}

	/*Number of Connected Component 返回的向量最后一个元素是分量个数，其他元素是每个分量的最小值*/
	vector<int> GetNOCC() {
		bool* visited = new bool[nodeNum];//用于记录是否访问过
		for (int i = 0; i < nodeNum; i++) {
			visited[i] = false;
		}
		vector<int> r;
		int nOCC = 0;//用于记录联通分量数

		/*每个新的未访问的节点都使用BFS或DFS遍历，这样这个分量中的其他节点就不会出发新的遍历
		则在根部调用BFS或DFS的次数就是联通分量数*/
		for (int i = 0; i < nodeNum; i++) {
			if (visited[i] == true) {
				continue;
			}
			else {
				nOCC++;
				vector<int> subset;
				DFS(i, visited, subset);

				/*寻找最小节点*/

				int min = 0;
				for (int i = 0; i < subset.getlength(); i++) {
					min = min < subset[i] ? min : subset[i];
				}
				r.push(min);
			}
		}

		r.push(nOCC);
		return r;
	}

	/*i指示DFS根节点，visited指示是否遍历，subset储存该分量节点，寻找最小点*/
	void DFS(int i,bool* visited.vector<bool>& subset) {
		visited[i] = true;
		subset.push(i);
		/*遍历与i节点连接的且未访问过的所有节点
		当没有为访问的节点，则这课搜索树建立完毕
		则该连通分量遍历完成，其所有节点被访问*/
		for (int j = 0; j < nodeNum; j++) {
			if (!visited[j] && weights[i][j] != 0) {
				findAllConnceted(j, visited);
			}
		}
	}
	/*该函数就是遍历一个连通分量*/
	vector<int> GetDFS(int i) {
		bool* visited = new bool[nodeNum];//用于记录是否访问过
		for (int i = 0; i < nodeNum; i++) {
			visited[i] = false;
		}

		//path表示路径
		vector<int> path;
		DFS(i, visited, path);

		return path;
	}
};

template<typename T>
class linkGraph {
private:
	struct link;
	typedef struct node {
		T data;
		link* link;
	}node;
	typedef struct link {
		int weight;
		node* node;
	}link;

public:


};