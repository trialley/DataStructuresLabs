#include<iostream>
#include"graphChain.h"
#include"arrayQueue.h"
#include"edge.h"
#include<string.h>
#include"栈.h"
using namespace std;


template<class T>
class linkedWGraph
{//加权无向图 
	protected:
		int n;                 //顶点数 
		int e;                 //边数 
		graphChain<T> *aList;  //邻接表 
		int *reach;  //数组指针 
		int label=1;
		
	void rDfs(int v)
	{//递归实现深度优先搜索
		reach[v]=label;  int u;
		//cout<<"当前走到顶点："<<v<<endl;
		myIterator *iv=iterator(v);  //这里加<T>就会报错，为什么？？ 
		while( ( u=iv->next() ) !=0 )
		{//以v的下一个邻接点u为新起点递归搜索 
		//cout<<v<<"的下一个邻接点是："<<u<<" "<<endl;
			if(reach[u]!=label)
				rDfs(u);  //u是一个没有到达过的顶点 
		} 
		delete iv;
		return;
	} 		
		
	public:
		void output()
		{
			for(int i=1;i<=n;i++)
			{
				cout<<"aList["<<i<<"]="; aList[i].output();
				cout<<endl;
			}
		}
		linkedWGraph(int v)
		{
			if(v>0) 
			n=v;
			e=0;
			aList=new graphChain<int> [n+1];
		}
	    ~linkedWGraph()
	    {
	    	delete [] aList;  //这样就会自己调用graphChain的析构函数吗？ 
		}
		int numberOfVertices() const { return n; }
	    int numberOfEdges() const { return e; }
	    bool directed() const { return false; }
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
		void insertEdge(edge<T> *theEdge)
		{
			int v1=theEdge->vertex1();
			int v2=theEdge->vertex2();
			int weight=theEdge->weight();
			if( v1<1 || v2<1 || v1>n || v2>n || v1==v2 )
		    {//越界处理 
		   	   cerr<<"("<<v1<<","<<v2<<") is not a permissible edge"<<endl;
		   	   exit(1);
		    }
		    if(aList[v1].indexOf(v2)==-1)
		    {//新边 
		    	aList[v1].insert(0,v2,weight);
		    	aList[v2].insert(0,v1,weight);
		    	e++;
			}
		}
		void eraseEdge(int i,int j)
		{
			if( i>1 && j>1 && i<=n && j<=n)
			{
				int *v=aList[i].eraseElement(j);
				int *j=aList[j].eraseElement(i);  //v,j一定同时为空或者非空，不然说明一致性出了问题 
				if(v!=NULL && j!=NULL )   e--;   //该边存在
			}
		}
		int Degree(int Vertex)
		{
			checkVertex(Vertex);
			return aList[Vertex].size();
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
				int next(T & theWeight)
				{//返回指定顶点的下一个邻接点的序号和它的的权值 
					if(currentVertex!=NULL)
					{
						theWeight=currentVertex->weight;
						int vertex=currentVertex->element;
						currentVertex=currentVertex->next;
						return vertex;
					}
					else
					    return 0;
				}
				int next()
				{//返回指定顶点的下一个邻接点 
					
					if(currentVertex!=NULL)
					{
						int vertex=currentVertex->element;
						currentVertex=currentVertex->next;
						return vertex;
					}
					return 0;
				}
			protected:
				graphChain<T> *v;    //邻接表的点 
				ChainNode<T> *currentVertex;   //当前搜索的顶点 
		};	 
		myIterator* iterator(int theVertex)
        {
           checkVertex(theVertex);
           return new myIterator( &aList[theVertex] );
        }
	
	bool connected()
	{//判断无向图是否连通 
		if( directed() )
		{
		   cerr<<"本图是无向图！"<<endl;  exit(2);
		}
		
		reach=new int [n+1];
		for(int i=1;i<=n;i++)
		  reach[i]=0;
		
		dfs(1,reach,1); //给邻接于顶点1的可达顶点做标记
		
		for(int i=1;i<=n;i++)
		{//检查所有顶点是否已做标记
			if(reach[i]==0)
			  return false;
		}
		return true; 
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
				
			for(ChainNode<int> *u=aList[vertex].firstnode; u!=NULL;u=u->next)	
			{
				if( reach[u->element]==0 )
				{  q.push(u->element);	reach[u->element]=label;	}
			}		
		}
	}
	void dfs(int v,int reach[],int label)
	{
		reach=reach;
		label=label;
		rDfs(v);
	}		
	int labelComponents(int c[])
	{//返回连通分支数，c[i]是顶点i所属的分支序号 
		int i=0;
		for(i=0;i<=n;i++)
		   c[i]=0;
		   
		int label=0;  //最后一个构建的编号 
		for(i=1;i<=n;i++)
		{
			if( c[i]==0 )
			{//对所有未到达的顶点，都进行一次bfs标记 
				label++;
				bfs(i,c,label);  //给新分支做标记 
			}	
		}
		return label;
	}
	void print_bfs(int v,int reach[])
	{
		memset( reach,0,sizeof(int)*(n+1) ); 
		int label=1; reach[v]=label;
        arrayQueue<int> q(10);
		q.push(v);
		
		while(q.empty()!=true)
		{
			int vertex=q.front();
			cout<<vertex<<" ";
			q.pop();
				
			for(ChainNode<int> *u=aList[vertex].firstnode; u!=NULL;u=u->next)	
			{
				if( reach[u->element]==0 )
				{  q.push(u->element);	reach[u->element]=label;	}
			}
		}		
	}
	void print_dfs(int v,int reach[])
	{//使用栈实现的DFS搜索算法 
        arrayStack<int> s(10);  int u;
        memset( reach,0,sizeof(int)*(n+1) );
		reach[v]=label;
		s.push(v);  cout<<v<<" ";
		
		while(!s.empty()) //当栈不空时 
		{
			int w=s.top();
			s.pop();
			myIterator *iv=iterator(w);	  u=iv->next(); 	
			while( u !=0 )  //对上一个到达的点w的所有邻接点 
			{
				if(  reach[u]!=label ) //如果存在一个未标记的点j 
				{  reach[u]=label;  
				   s.push(u); 
				   cout<<u<<" ";
				   iv=iterator(u);	//让iv指向以u为起点的迭代器 
				} 
				else{//该顶点已被标记
				      u=iv->next();
				   	  if( u ==0 && s.empty()!=true )  s.pop(); //该顶点没有其他邻接点了
			   		}
			}
		}		
	}
     int Dijkstra(int start,int dest,int predecessor[])
	{//返回最短路长，记录下最短路的路径，predecessor是从start到dest路径中dest前的那个顶点 
		int L[n+1];  //L[i]就是从start点到顶点i的距离 
		for(int i=1;i<=n;i++)
		{  L[i]=100000;  predecessor[i]=-1;  }   L[start]=0;
		for(ChainNode<int> *u=aList[start].firstnode; u!=NULL;u=u->next)
		{
			L[u->element]=u->weight;
			predecessor[u->element]=start;  //对于start邻接的点 
		}   
		predecessor[start]=0;    //源顶点没有前驱  
		bool S[n+1];
		for(int i=1;i<=n;i++)  S[i]=false;  //S[i]表示start到顶点i的最短路已求得 
		  
	    /*…………以上是初始化操作…………*/	
		
		while( S[dest]!=true )
		{/*下面找一个不在顶点集S中的u且L[u]标号最小，可以借助一下线性表吗？*/	 
			int u,tag;
			for(u=1;u<=n;u++)
			{
				if( S[u]==false && L[u]==Minium(L,S,n) )  //这里找一个不在顶点集S且标号最小的点，复杂度可以降到O(1)吗？ 
				{                                        //按我的写法复杂度好像是O(n^3)，可以通过把两个循环判断条件糅合来降低复杂度嘛？ 
				    S[u]=true;  //把u加入顶点集S中
				    tag=u;
				    break;
			    }
			}
			
			for(ChainNode<int> *u=aList[tag].firstnode; u!=NULL;u=u->next)
			{//遍历刚找到的点的邻接点,如果它没有被访问过，且距离可被更新
			  //这样写，复杂度是O(链表长)，较好 
				if(S[u->element]==false && L[tag]+ (u->weight) <L[u->element] ) 
				{
				    L[u->element]=L[tag]+ u->weight ;
				    predecessor[u->element]=tag;    //顶点v的前驱是u 
				} 
		   }
		}
		return L[dest];
	}   
        
        
        
        
};
