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

    //第一行输出图中有多少个连通分量
    //第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔
    g.printCCs ();
    //第三行输出从s点开始的_dfs序列长度

    //第四行输出从s点开始的字典序最小的_dfs序列
    g.printDFS (s);

    //第五行输出从t点开始的_bfs序列的长度
    //第六行输出从t点开始字典序最小的_bfs序列
    g.printBFS (t);

    //第七行输出从s点到t点的最短路径，若是不存在路径则输出-1

    cout << g.getShortestDis (s, t);
    return 0;
}
