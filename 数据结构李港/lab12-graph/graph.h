/*��Ŀ����
����һ�������ͼ��n����m���ߣ���ı�Ŵ�1��n�����������������s��t��
Ҫ�����������ͼ����ͨ��ͼ���������������ÿ����ͨ��ͼ����С�ĵ��š�

���������s�㿪ʼ���ֵ�����С��DFS���У���t�㿪ʼ���ֵ�����С��BFS���С�
�����s��t�����·�����ȡ�
��������
��һ�����ĸ���������N��M��s��t
������m��
ÿ��������������a��b��c����ʾ��a����͵�b�������г���Ϊc�ıߣ���֤c����1����
�������
��һ�У�һ������k����ʾ��ͨ��ͼ����
�ڶ��У�k����������ʾ���������ÿ����ͨ��ͼ����С�ĵ���

�����У�һ������k����ʾ��s�㿪ʼ��DFS���г���
�����У�k����������s�㿪ʼ���ֵ�����С��DFS���У�����ÿ��Ԫ�ر�ʾ��ı��

�����У�һ������k����ʾ��t�㿪ʼ��BFS���г���
�����У�k����������t�㿪ʼ���ֵ�����С��BFS���У�����ÿ��Ԫ�ر�ʾ��ı��
�����У�s��t�����·�����ȣ��������ڣ����-1*/

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

	/*Number of Connected Component ���ص��������һ��Ԫ���Ƿ�������������Ԫ����ÿ����������Сֵ*/
	vector<int> GetNOCC() {
		bool* visited = new bool[nodeNum];//���ڼ�¼�Ƿ���ʹ�
		for (int i = 0; i < nodeNum; i++) {
			visited[i] = false;
		}
		vector<int> r;
		int nOCC = 0;//���ڼ�¼��ͨ������

		/*ÿ���µ�δ���ʵĽڵ㶼ʹ��BFS��DFS������������������е������ڵ�Ͳ�������µı���
		���ڸ�������BFS��DFS�Ĵ���������ͨ������*/
		for (int i = 0; i < nodeNum; i++) {
			if (visited[i] == true) {
				continue;
			}
			else {
				nOCC++;
				vector<int> subset;
				DFS(i, visited, subset);

				/*Ѱ����С�ڵ�*/

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

	/*iָʾDFS���ڵ㣬visitedָʾ�Ƿ������subset����÷����ڵ㣬Ѱ����С��*/
	void DFS(int i,bool* visited.vector<bool>& subset) {
		visited[i] = true;
		subset.push(i);
		/*������i�ڵ����ӵ���δ���ʹ������нڵ�
		��û��Ϊ���ʵĽڵ㣬������������������
		�����ͨ����������ɣ������нڵ㱻����*/
		for (int j = 0; j < nodeNum; j++) {
			if (!visited[j] && weights[i][j] != 0) {
				findAllConnceted(j, visited);
			}
		}
	}
	/*�ú������Ǳ���һ����ͨ����*/
	vector<int> GetDFS(int i) {
		bool* visited = new bool[nodeNum];//���ڼ�¼�Ƿ���ʹ�
		for (int i = 0; i < nodeNum; i++) {
			visited[i] = false;
		}

		//path��ʾ·��
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