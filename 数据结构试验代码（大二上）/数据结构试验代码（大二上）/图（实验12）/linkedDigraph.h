#include<iostream>
#include"graphChain.h"
#include"edge.h"
using namespace std;

template<class T>
class linkedDigraph
{//无权有向图 
	protected:
		int n;                 //顶点数 
		int e;                 //边数 
		graphChain<T> *aList;  //邻接表 
	public:
		linkedDigraph(int v=0)
		{
			if(v<0) 
			n=v;
			e=0;
			aList=new graphChain<int> [n+1];
		}
	    ~linkedDigraph()
	    {
	    	delete [] aList;  //这样就会自己调用graphChain的析构函数吗？ 
		}
		int numberOfVertices() const { return n; }
	    int numberOfEdges() const { return e; }
	    bool directed() const { return true; }
	    bool weight() const { return true; }
	    void checkVertex(int theVertex) const
		{//确认是有效顶点 
			if(theVertex<1 || theVertex>n)
			{
				cerr<<"the vertex:"<<theVertex<<" is not permissible";
			    exit(1); 
			}  
			else return;
		}
		void insertEdge(edge<bool> *theEdge)
		{
			int v1=theEdge->vertex1();
			int v2=theEdge->vertex2();
			if( v1<1 || v2<1 || v1>n || v2>n || v1==v2 )
		    {//越界处理 
		   	   cerr<<"("<<v1<<","<<v2<<") is not a permissible edge"<<endl;
		   	   exit(1);
		    }
		    if(aList[v1].indexOf(v2)==-1)
		    {//新边 
		    	aList[v1].insert(0,v2);
		    	e++;
			}
		}
		void eraseEdge(int i,int j)
		{
			if( i>1 && j>1 && i<=n && j<=n)
			{
				int *v=aList[i].eraseElement(j);
				if(v!=NULL)
				  e--;   //该边存在 
			}
		}
		int outDegree(int Vertex)
		{
			checkVertex(Vertex);
			return aList[Vertex].size();
		}
		int inDegree(int Vertex)
		{
			checkVertex(Vertex);
			int sum=0;
			for(int i=0;i<=n;i++)
			{//在每个点的链表中搜索Vertex 
				if( aList[i].indexOf(Vertex)!=-1 ) 
				  sum++;
			}
			return sum;
		}
		
		class myIterator
		{
			public:
				myIterator(graphChain<T> *theVertex)
				{
				     v=theVertex;
				     currentVertex=v->firstnode;
				}
				~myIterator(){  }
				ChainNode<T>* next(bool & theWeight)
				{//返回指定顶点的下一个邻接点和它的的权值 
				    currentVertex=currentVertex->next;
					if(currentVertex!=NULL)
					{
						theWeight=true;
						return currentVertex;
					}
					return NULL;
				}
				ChainNode<T>* next()
				{//返回指定顶点的下一个邻接点 
					currentVertex=currentVertex->next;
					if(currentVertex!=NULL)
					{
						return currentVertex;
					}
					return NULL;
				}
			protected:
				graphChain<T> *v;    //邻接表的点 
				ChainNode<T> *currentVertex;   //当前搜索的顶点 
		};	 
		myIterator* iterator(int theVertex)
        {
           checkVertex(theVertex);
           return new myIterator( aList[theVertex] );
        }
		   
};
