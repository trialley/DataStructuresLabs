// adjacency matrix representation of a weighted undirected graph
#ifndef adjacencyWGraph_
#define adjacencyWGraph_

#include "adjacencyWDigraph.h"

using namespace std;

template <class T>
class adjacencyWGraph : public adjacencyWDigraph<T>
{
public:
    adjacencyWGraph(int numberOfVertices = 0, T theNoEdge = 0)
        : adjacencyWDigraph<T>(numberOfVertices, theNoEdge) {}
    void insertEdge(edge<T> *theEdge)
    {
        // Insert edge theEdge into the graph; if the edge is already
        // there, update its weight to theEdge.weight().
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > adjacencyWDigraph<T>::n || v2 > adjacencyWDigraph<T>::n || v1 == v2)
        {
            ostringstream s;
            s << "(" << v1 << "," << v2
              << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
        }

        if (adjacencyWDigraph<T>::a[v1][v2] == adjacencyWDigraph<T>::noEdge)  // new edge
            adjacencyWDigraph<T>::e++;
        adjacencyWDigraph<T>::a[v1][v2] = theEdge->weight();
        adjacencyWDigraph<T>::a[v2][v1] = theEdge->weight();
    }

    bool directed() const
    {
        return false;
    }

    void eraseEdge(int i, int j)
    {
        // Delete the edge (i,j).
        if (i >= 1 && j >= 1 && i <= adjacencyWDigraph<T>::n && j <= adjacencyWDigraph<T>::n && adjacencyWDigraph<T>::a[i][j] != adjacencyWDigraph<T>::noEdge)
        {
            adjacencyWDigraph<T>::a[i][j] = adjacencyWDigraph<T>::noEdge;
            adjacencyWDigraph<T>::a[j][i] = adjacencyWDigraph<T>::noEdge;
            adjacencyWDigraph<T>::e--;
        }
    }

    int degree(int theVertex) const
    {
        // Return degree of vertex theVertex.
        adjacencyWDigraph<T>::checkVertex(theVertex);	
        //此处需要在 checkVertex函数前加上定义域限定.
		//类似错误还有超过60处，我猜测是编者使用了MinGW系列编译器，包含了智能限域的功能
		//而我们使用的多为TDM，因此出现此类错误.
		//但是从知识上来说，加定义域才是正确之举. 

        // count out edges from vertex theVertex
        int sum = 0;
        for (int j = 1; j <= adjacencyWDigraph<T>::n; j++)
            if (adjacencyWDigraph<T>::a[theVertex][j] != adjacencyWDigraph<T>::noEdge)
                sum++;

        return sum;
    }

    int outDegree(int theVertex) const
    {
        // Return out-degree of vertex theVertex.
        return degree(theVertex);
    }

    int inDegree(int theVertex) const
    {
        // Return in-degree of vertex theVertex.
        return degree(theVertex);
    }
};
#endif
