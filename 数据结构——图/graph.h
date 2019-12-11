//#include<iostream>
//using namespace std;
//#define SIZE 10
/////////////////////////////////ͼ�ڽӾ���
//class Graph {
//public:
//	Graph () {
//		_V_MAX = SIZE;
//		_v_num = NumEdge = 0;//�������ͱ�����ʼ��Ϊ0
//		Vertex = new char[_V_MAX];
//		Edge = new int* [_V_MAX];//int *Edge[10];
//		int i, j;
//		for (i = 0; i < _V_MAX; i++)
//			Edge[i] = new int[_V_MAX]; //Edge[10][10]
//		for (i = 0; i < _V_MAX; i++) {
//			for (j = 0; j < _V_MAX; j++)
//				Edge[i][j] = 0;
//		}
//	}
//	void InsertVertex (char v)//����һ������v
//	{
//		if (_v_num >= _V_MAX)
//			return;
//		Vertex[_v_num++] = v;
//	}
//	int GetVertexI (char v)//����һ������v
//	{
//		int i;
//		for (i = 0; i < _v_num; i++) {
//			if (Vertex[i] == v)
//				return i;
//		}
//		return -1;
//	}
//	void InsertEdge (char v1, char v2)//����һ���ɵ�v1��v2��ɵı�
//	{
//		int p1 = GetVertexI (v1);
//		int p2 = GetVertexI (v2);
//		if (p1 == -1 || p2 == -1)
//			return;
//		Edge[p1][p2] = Edge[p2][p1] = 1;
//		NumEdge++;
//	}
//	void ShowGraph ()//��ӡ����
//	{
//		int i, j;
//		cout << "  ";
//		for (i = 0; i < _v_num; i++)
//			cout << Vertex[i] << " ";
//		cout << endl;
//		for (i = 0; i < _v_num; i++) {
//			cout << Vertex[i] << " ";
//			for (j = 0; j < _v_num; j++)
//				cout << Edge[i][j] << " ";
//			cout << endl;
//		}
//	}
//
//	int GetEdgeNum (char v)//��ȡͼ�ı���
//	{
//		int p = GetVertexI (v);
//		if (p == -1)
//			return 0;
//		int n = 0;
//		for (int i = 0; i < _v_num; i++) {
//			if (Edge[p][i] == 1)
//				n++;
//		}
//		return n;
//	}
//	void DeleteVertex (char v)//ɾ��һ������
//	{
//		int p = GetVertexI (v);
//		if (p == -1)
//			return;
//		int i, j;
//		int n = GetEdgeNum (v);
//		for (i = p; i < _v_num - 1; i++)  //������ɾ��
//			Vertex[i] = Vertex[i + 1];
//
//		for (i = p; i < _v_num - 1; i++)  //������
//		{
//			for (j = 0; j < _v_num; j++)
//				Edge[i][j] = Edge[i + 1][j];
//		}
//		for (i = 0; i < _v_num - 1; i++)  //������
//		{
//			for (j = p; j < _v_num - 1; j++) {
//				Edge[i][j] = Edge[i][j + 1];
//			}
//		}
//
//		_v_num--;
//		NumEdge -= n;
//
//	}
//	void DeleteEdge (char v1, char v2)//ɾ������v1��v2֮��ı�
//	{
//		int p1 = GetVertexI (v1);
//		int p2 = GetVertexI (v2);
//		if (p1 == -1 || p2 == -1)
//			return;
//		if (Edge[p1][p2] == 0)
//			return;
//		Edge[p1][p2] = Edge[p2][p1] = 0;
//		NumEdge--;
//	}
//	~Graph () {
//		delete[]Vertex;
//		Vertex = NULL;
//		for (int i = 0; i < _V_MAX; i++) {
//			delete[]Edge[i];
//			Edge[i] = NULL;
//		}
//		delete[]Edge;
//		Edge = NULL;
//		_v_num = 0;//���������ͷſռ�ɲ�д
//	}
//private:
//	int _V_MAX;
//	int _v_num;
//	int NumEdge;
//	char* Vertex;
//	int** Edge;
//};