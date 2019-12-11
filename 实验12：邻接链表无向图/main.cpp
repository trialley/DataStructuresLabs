#include <iostream>
using namespace std;
#define INFINITY  65535 /* 表示权值的无穷*/
typedef int EdgeType;//边上的权值类型
typedef int VertexType;//顶点类型
const int MaxSize = 100;
int visited[MaxSize];//全局标识数组
//无向图邻接表。边表结点结构
struct EdgeNode {
    int adjvex;//邻接点域
    EdgeNode* next;//指向下一个边结点的指针
};
//无向图邻接表。表头结点结构
struct VexNode {
    VertexType vertex;//顶点
    EdgeNode* firstedge;//边表的头指针
};
//邻接表类
class ALGraph {
public:
    ALGraph ()//无参构造函数
    {
        vertexNum = 0;
        edgeNum = 0;
        for (int i = 0; i < MaxSize; i++)
            adjlist[i].firstedge = NULL;
    }
    ALGraph (VertexType a[], int n);//有参构造函数
    void createGraph (int start, int end);//创建图,采取前插法
    void DFSL (int v);//从v出发深度优先遍历可达顶点递归函数
    void DFSL1 (int v);//从v出发深度优先遍历可达顶点的非递归函数
    void displayGraph (int nodeNum);//打印
    void CountComp (ALGraph g);//求连通分量数，判断图的连通性
private:
    VexNode adjlist[MaxSize];//存放顶点表的数组
    int vertexNum, edgeNum;//图的顶点数和边数
};
//有参构造函数。构造顶点表
ALGraph::ALGraph (VertexType a[], int n) {
    vertexNum = n;
    edgeNum = 0;
    for (int i = 0; i < vertexNum; i++) {
        adjlist[i].vertex = a[i];
        adjlist[i].firstedge = NULL;
    }
}
//创建图,采取前插法
void ALGraph::createGraph (int start, int end) {//边(start,end)
    //adjlist[start].vertex=start;//表头结点中的顶点
    EdgeNode* p = new EdgeNode;//边结点
    p->adjvex = end;//邻接点
    //p->weight=weight;
    p->next = adjlist[start].firstedge;//前插法插入边结点p
    adjlist[start].firstedge = p;
}
//打印存储的图
void ALGraph::displayGraph (int nodeNum) {
    int i, j;
    EdgeNode* p;
    for (i = 0; i < nodeNum; i++) {
        p = adjlist[i].firstedge;
        while (p) {
            cout << '(' << adjlist[i].vertex << ',' << p->adjvex << ')' << endl;
            p = p->next;
        }
    }
}
//从v出发深度优先遍历可达顶点递归函数
void ALGraph::DFSL (int v) {
    int n = vertexNum;
    int j;
    EdgeNode* p;
    if (v >= n || v < 0) throw "位置出错";
    cout << adjlist[v].vertex << " ";
    visited[v] = 1;
    p = adjlist[v].firstedge;
    while (p) {
        j = p->adjvex;//顶点
        if (visited[j] == 0) DFSL (j);
        p = p->next;
    }
}
//从v出发深度优先遍历可达顶点的非递归函数
void ALGraph::DFSL1 (int v) {
    int S[MaxSize], top = -1, j, n = vertexNum;
    EdgeNode* p;
    if (v >= n || v < 0) throw "位置出错";
    cout << adjlist[v].vertex << " ";
    visited[v] = 1;
    S[++top] = v;//v进栈
    while (top != -1) {
        v = S[top--];//栈顶元素出栈
        p = adjlist[v].firstedge;
        while (p) {
            j = p->adjvex;//顶点
            if (visited[j] == 1) p = p->next;
            else {
                cout << adjlist[j].vertex << " ";
                visited[j] = 1;
                S[++top] = j;//v进栈
                p = adjlist[j].firstedge;
            }
        }
    }
}
//求连通分量数，判断图的连通性
void ALGraph::CountComp (ALGraph g) {
    int count = 0;
    int n = g.vertexNum;
    for (int v = 0; v < n; v++) {
        if (visited[v] == 0) {
            count++;
            g.DFSL (v);
        }
    }
    if (count == 1) cout << endl << "改图是连通的！" << endl;
    else cout << endl << "改图不连通，连通分量数为：" << count << endl;
}
int main () {
    int a[8] = { 0,1,2,3,4,5,6,7 };
    ALGraph gr = ALGraph (a, 8);//初始化表头
    gr.createGraph (0, 2);
    gr.createGraph (0, 1);
    gr.createGraph (1, 3);
    gr.createGraph (1, 0);
    gr.createGraph (2, 3);
    gr.createGraph (2, 0);
    gr.createGraph (3, 2);
    gr.createGraph (3, 1);
    gr.createGraph (4, 5);
    gr.createGraph (5, 6);
    gr.createGraph (5, 4);
    gr.createGraph (6, 7);
    gr.createGraph (6, 5);
    gr.createGraph (7, 6);
    gr.displayGraph (8);
    for (int i = 0; i < MaxSize; i++)
        visited[i] = 0;
    gr.CountComp (gr);
    return 0;
}