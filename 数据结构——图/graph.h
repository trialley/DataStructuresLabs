//#include<iostream>
//using namespace std;
//#define SIZE 10
/////////////////////////////////图邻接矩阵
//class Graph {
//public:
//	Graph () {
//		_V_MAX = SIZE;
//		_v_num = NumEdge = 0;//顶点数和边数初始化为0
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
//	void InsertVertex (char v)//插入一个顶点v
//	{
//		if (_v_num >= _V_MAX)
//			return;
//		Vertex[_v_num++] = v;
//	}
//	int GetVertexI (char v)//查找一个顶点v
//	{
//		int i;
//		for (i = 0; i < _v_num; i++) {
//			if (Vertex[i] == v)
//				return i;
//		}
//		return -1;
//	}
//	void InsertEdge (char v1, char v2)//插入一条由点v1和v2组成的边
//	{
//		int p1 = GetVertexI (v1);
//		int p2 = GetVertexI (v2);
//		if (p1 == -1 || p2 == -1)
//			return;
//		Edge[p1][p2] = Edge[p2][p1] = 1;
//		NumEdge++;
//	}
//	void ShowGraph ()//打印函数
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
//	int GetEdgeNum (char v)//获取图的边数
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
//	void DeleteVertex (char v)//删除一个顶点
//	{
//		int p = GetVertexI (v);
//		if (p == -1)
//			return;
//		int i, j;
//		int n = GetEdgeNum (v);
//		for (i = p; i < _v_num - 1; i++)  //顶点先删除
//			Vertex[i] = Vertex[i + 1];
//
//		for (i = p; i < _v_num - 1; i++)  //行上移
//		{
//			for (j = 0; j < _v_num; j++)
//				Edge[i][j] = Edge[i + 1][j];
//		}
//		for (i = 0; i < _v_num - 1; i++)  //列左移
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
//	void DeleteEdge (char v1, char v2)//删除顶点v1和v2之间的边
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
//		_v_num = 0;//析构函数释放空间可不写
//	}
//private:
//	int _V_MAX;
//	int _v_num;
//	int NumEdge;
//	char* Vertex;
//	int** Edge;
//};