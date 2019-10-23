#pragma once
#include<iostream>
#include"edge.h"
#include"arrayQueue.h"
#include"栈.h"
using namespace std;

template<class T>
class adjacencyWDigraph
{//邻接矩阵表示的加权有向图 
	protected:
		int n;       //顶点个数 
		int e;       //边的个数 
		T **a;       //邻接数组 
		T noEdge;    //表示不存在的边
		int *reach;  //数组指针 
		int label=20170013;
		
		
		void rDfs(int v)
		{//递归实现深度优先搜索
		    reach[v]=label;  int u;
		    myIterator *iv=iterator(v);  //这里加<T>就会报错，为什么？？ 
			while( ( u=iv->next() )!=0 )
			{//以v的下一个邻接点u为新起点递归搜索 
				if(reach[u]!=label)
				  rDfs(u);  //u是一个没有到达过的顶点 
			} 
			delete iv;
			return;
		} 
/*		void rDfs(int v) 
		{//使用栈模拟递归 
			arrayStack<int> s(10);  int u;
			reach[v]=label;
			s.push(v);
			
			while(!s.empty()) //当栈不空时 
			{
				int w=s.top();
				s.pop();
				myIterator *iv=iterator(w);		
				while( ( u=iv->next() )!=0 )  //对上一个到达的点w的所有邻接点 
				{
					if(  reach[u]!=label ) //如果存在一个未标记的点j 
					{  reach[u]=label;  s.push(u);	} 
					else{//j已被标记且w没有其他邻接点了
				   		if(iv->next()==0)  s.pop(); 
			   			}
				}
			}
		}*/
	public:
	    adjacencyWDigraph(int v=0,T theNoEdge=0)
	    {//构造函数
		    if(v<0) cerr<<"请检验顶点数的合法性！"<<endl;
		    n=v;
	    	noEdge=theNoEdge;
	    	e=0;
	    	
	    	 a=new T*[n+1];
	    	 for(int i=0;i<n+1;i++)
	    	 {//分配空间 
	    		 a[i]=new T [n+1];
			 }
				for(int i=1;i<=n;i++)  //初始化邻接矩阵 
				{
					for(int j=1;j<=n;j++)
					{
						a[i][j]=noEdge;
					}
				}
		}
	    ~adjacencyWDigraph()
	    {
	    	for(int i=0;i<n+1;i++)
	    	{
	    		delete [] a[i];
			}
			delete [] a;
			a=NULL;  //不置为NULL的话会变野指针，但是这里也没事 
		}
	    int numberOfVertices() const { return n; }
	    int numberOfEdges() const { return e; }
	    
	    bool weight() const { return true; }
	    bool existsEdge(int i,int j) const
	    {
	    	if( i<1 || j<1 || i>n || j>n || a[i][j]=noEdge )
	    	   return false;
	    	else 
	    	   return true;
		}
		void insertEdge(edge<T> *theEdge)
		{//插入边，如果该边已存在，则用theEdge->weight()修改边的权
		   int v1=theEdge->vertex1();
		   int v2=theEdge->vertex2();
		   if( v1<1 || v2<1 || v1>n || v2>n || v1==v2 )
		   {//越界处理 
		   	   cerr<<"("<<v1<<","<<v2<<") is not a permissible edge"<<endl;
		   	   exit(1);
		   }
		   if(a[v1][v2]==noEdge)  //新边 
		      e++;
		   a[v1][v2]=theEdge->weight();   
		}
	    void eraseEdge(int i,int j)
	    {//删除边(i,j),如果不存在该边就什么也不做 
		   if(i>=1 && j>=1 && i<=n && j<=n && a[i][j]!=noEdge )
		   {
		       a[i][j]=noEdge;
		   	   e--;
		   } 
		}
		void checkVertex(int theVertex) const
		{//确认是有效顶点 
			if(theVertex<1 || theVertex>n)
			{
				cerr<<"the vertex:"<<theVertex<<" is not permissible";
			    exit(1); 
			}  
			else return;
		}
		int outDegree(int Vertex)
		{//计算顶点Vertex的出度
		    checkVertex(Vertex);
			int sum=0;
			for(int j=1;j<=n;j++)
			  if( a[Vertex][j]!=noEdge )  //遍历第Vertex行 
			    sum++;
			return sum; 
		}
		int inDegree(int Vertex)
		{//计算顶点Vertex的入度
		    checkVertex(Vertex);
			int sum=0;
			for(int j=1;j<=n;j++)
			  if( a[j][Vertex]!=noEdge )  //遍历第Vertex列 
			    sum++;
			return sum; 
		}
		
		class myIterator
		{
			public:
				myIterator(T* theRow,T theEdge,int v)
				{
					Row=theRow;
					noEdge=theEdge;
					n=v;
					currentVertex=1;
				}
				~myIterator(){  }
				int next(T & theWeight)
				{//返回指定顶点的下一个邻接点和它的的权值 
					for(int i=currentVertex;i<=n;i++)
					{
						if(Row[i]!=noEdge)
						{//发现一个邻接点 
							currentVertex=i+1;
							theWeight=Row[i];
							return i;
						}
					}
					//不存在下一个邻接点了 
					currentVertex=n+1;
					return 0;
				}
				int next()
				{//返回指定顶点的下一个邻接点 
					for(int i=currentVertex;i<=n;i++)
					{
						if(Row[i]!=noEdge)
						{//发现一个邻接点 
							currentVertex=i+1;
							return i;
						}
					}
					//不存在下一个邻接点了 
					currentVertex=n+1;
					return 0;
				}
			protected:
				T *Row;              //邻接矩阵的的行 
				T noEdge;            //theRow[i]==noEdge，当且仅当没有关联与顶点i的边 
				int n;               //顶点数 
				int currentVertex;   //当前搜索的顶点 
		};
		myIterator* iterator(int theVertex)
		{//返回顶点theVertex的迭代器 
			checkVertex(theVertex);
			return new myIterator( a[theVertex], noEdge, n);
		}
		void bfs(int v,int reach[],int label)
		{//广度优先算法，reach[i]用来标记所有邻接于顶点v的可到达的顶点 
			arrayQueue<int> q(10);
			reach[v]=label;
			q.push(v);
			
			while(q.empty()!=true)
			{
				int vertex=q.front();
				q.pop();
				
				for(int j=1;j<=n;j++)
				{
					if( a[vertex][j]!=noEdge && reach[j]==0 )
					{  q.push(j);	reach[j]=label;	 }
				}
			}
		}
		void dfs(int v,int reach[],int label)
		{
			reach=reach;
			label=label;
			rDfs(v);
		}
	 
};
