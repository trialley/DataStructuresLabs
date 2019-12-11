#include <iostream>
using namespace std;
#define INFINITY  65535 /* ��ʾȨֵ������*/
typedef int EdgeType;//���ϵ�Ȩֵ����
typedef int VertexType;//��������
const int MaxSize = 100;
int visited[MaxSize];//ȫ�ֱ�ʶ����
//����ͼ�ڽӱ��߱���ṹ
struct EdgeNode {
    int adjvex;//�ڽӵ���
    EdgeNode* next;//ָ����һ���߽���ָ��
};
//����ͼ�ڽӱ���ͷ���ṹ
struct VexNode {
    VertexType vertex;//����
    EdgeNode* firstedge;//�߱��ͷָ��
};
//�ڽӱ���
class ALGraph {
public:
    ALGraph ()//�޲ι��캯��
    {
        vertexNum = 0;
        edgeNum = 0;
        for (int i = 0; i < MaxSize; i++)
            adjlist[i].firstedge = NULL;
    }
    ALGraph (VertexType a[], int n);//�вι��캯��
    void createGraph (int start, int end);//����ͼ,��ȡǰ�巨
    void DFSL (int v);//��v����������ȱ����ɴﶥ��ݹ麯��
    void DFSL1 (int v);//��v����������ȱ����ɴﶥ��ķǵݹ麯��
    void displayGraph (int nodeNum);//��ӡ
    void CountComp (ALGraph g);//����ͨ���������ж�ͼ����ͨ��
private:
    VexNode adjlist[MaxSize];//��Ŷ���������
    int vertexNum, edgeNum;//ͼ�Ķ������ͱ���
};
//�вι��캯�������춥���
ALGraph::ALGraph (VertexType a[], int n) {
    vertexNum = n;
    edgeNum = 0;
    for (int i = 0; i < vertexNum; i++) {
        adjlist[i].vertex = a[i];
        adjlist[i].firstedge = NULL;
    }
}
//����ͼ,��ȡǰ�巨
void ALGraph::createGraph (int start, int end) {//��(start,end)
    //adjlist[start].vertex=start;//��ͷ����еĶ���
    EdgeNode* p = new EdgeNode;//�߽��
    p->adjvex = end;//�ڽӵ�
    //p->weight=weight;
    p->next = adjlist[start].firstedge;//ǰ�巨����߽��p
    adjlist[start].firstedge = p;
}
//��ӡ�洢��ͼ
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
//��v����������ȱ����ɴﶥ��ݹ麯��
void ALGraph::DFSL (int v) {
    int n = vertexNum;
    int j;
    EdgeNode* p;
    if (v >= n || v < 0) throw "λ�ó���";
    cout << adjlist[v].vertex << " ";
    visited[v] = 1;
    p = adjlist[v].firstedge;
    while (p) {
        j = p->adjvex;//����
        if (visited[j] == 0) DFSL (j);
        p = p->next;
    }
}
//��v����������ȱ����ɴﶥ��ķǵݹ麯��
void ALGraph::DFSL1 (int v) {
    int S[MaxSize], top = -1, j, n = vertexNum;
    EdgeNode* p;
    if (v >= n || v < 0) throw "λ�ó���";
    cout << adjlist[v].vertex << " ";
    visited[v] = 1;
    S[++top] = v;//v��ջ
    while (top != -1) {
        v = S[top--];//ջ��Ԫ�س�ջ
        p = adjlist[v].firstedge;
        while (p) {
            j = p->adjvex;//����
            if (visited[j] == 1) p = p->next;
            else {
                cout << adjlist[j].vertex << " ";
                visited[j] = 1;
                S[++top] = j;//v��ջ
                p = adjlist[j].firstedge;
            }
        }
    }
}
//����ͨ���������ж�ͼ����ͨ��
void ALGraph::CountComp (ALGraph g) {
    int count = 0;
    int n = g.vertexNum;
    for (int v = 0; v < n; v++) {
        if (visited[v] == 0) {
            count++;
            g.DFSL (v);
        }
    }
    if (count == 1) cout << endl << "��ͼ����ͨ�ģ�" << endl;
    else cout << endl << "��ͼ����ͨ����ͨ������Ϊ��" << count << endl;
}
int main () {
    int a[8] = { 0,1,2,3,4,5,6,7 };
    ALGraph gr = ALGraph (a, 8);//��ʼ����ͷ
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