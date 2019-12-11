#include<iostream>
#include"graph.h"
using namespace std;

int main () {
#pragma warning(disable:4996)
    freopen ("input.txt", "r", stdin);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    linkedgraph g (n);
    until (m == 0) {
        int a, b, c;
        cin >> a >> b >> c;
        switch (a) {
        case 0:
            g.insertEdge (b, c);
            break;
        case 1:
            g.eraseEdge (b, c);
            break;
        }
        m--;
    }

    //��һ�����ͼ���ж��ٸ���ͨ����
    //�ڶ������������ͨ��ͼ����С��ı�ţ����򣩣���ż��ÿո�ָ�
    g.printCCs ();
    //�����������s�㿪ʼ��_dfs���г���

    //�����������s�㿪ʼ���ֵ�����С��_dfs����
    g.printDFS (s);

    //�����������t�㿪ʼ��_bfs���еĳ���
    //�����������t�㿪ʼ�ֵ�����С��_bfs����
    g.printBFS (t);

    //�����������s�㵽t������·�������ǲ�����·�������-1

    cout << g.getShortestDis (s, t);
    return 0;
}
