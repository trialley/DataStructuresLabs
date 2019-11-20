#include<iostream>
#include"graphChain.h"
#include"arrayQueue.h"
#include"edge.h"
#include<string.h>
#include"ջ.h"
using namespace std;


template<class T>
class linkedWGraph
{//��Ȩ����ͼ 
	protected:
		int n;                 //������ 
		int e;                 //���� 
		graphChain<T> *aList;  //�ڽӱ� 
		int *reach;  //����ָ�� 
		int label=1;
		
	void rDfs(int v)
	{//�ݹ�ʵ�������������
		reach[v]=label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myIterator *iv=iterator(v);  //�����<T>�ͻᱨ��Ϊʲô���� 
		while( ( u=iv->next() ) !=0 )
		{//��v����һ���ڽӵ�uΪ�����ݹ����� 
		//cout<<v<<"����һ���ڽӵ��ǣ�"<<u<<" "<<endl;
			if(reach[u]!=label)
				rDfs(u);  //u��һ��û�е�����Ķ��� 
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
	    	delete [] aList;  //�����ͻ��Լ�����graphChain������������ 
		}
		int numberOfVertices() const { return n; }
	    int numberOfEdges() const { return e; }
	    bool directed() const { return false; }
	    bool weight() const { return true; }
	    void checkVertex(int theVertex) const
		{//ȷ������Ч���� 
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
		    {//Խ�紦�� 
		   	   cerr<<"("<<v1<<","<<v2<<") is not a permissible edge"<<endl;
		   	   exit(1);
		    }
		    if(aList[v1].indexOf(v2)==-1)
		    {//�±� 
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
				int *j=aList[j].eraseElement(i);  //v,jһ��ͬʱΪ�ջ��߷ǿգ���Ȼ˵��һ���Գ������� 
				if(v!=NULL && j!=NULL )   e--;   //�ñߴ���
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
				{//����ָ���������һ���ڽӵ����ź����ĵ�Ȩֵ 
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
				{//����ָ���������һ���ڽӵ� 
					
					if(currentVertex!=NULL)
					{
						int vertex=currentVertex->element;
						currentVertex=currentVertex->next;
						return vertex;
					}
					return 0;
				}
			protected:
				graphChain<T> *v;    //�ڽӱ�ĵ� 
				ChainNode<T> *currentVertex;   //��ǰ�����Ķ��� 
		};	 
		myIterator* iterator(int theVertex)
        {
           checkVertex(theVertex);
           return new myIterator( &aList[theVertex] );
        }
	
	bool connected()
	{//�ж�����ͼ�Ƿ���ͨ 
		if( directed() )
		{
		   cerr<<"��ͼ������ͼ��"<<endl;  exit(2);
		}
		
		reach=new int [n+1];
		for(int i=1;i<=n;i++)
		  reach[i]=0;
		
		dfs(1,reach,1); //���ڽ��ڶ���1�Ŀɴﶥ�������
		
		for(int i=1;i<=n;i++)
		{//������ж����Ƿ��������
			if(reach[i]==0)
			  return false;
		}
		return true; 
	}	
    void bfs(int v,int reach[],int label)
	{//��������㷨��reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
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
	{//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i=0;
		for(i=0;i<=n;i++)
		   c[i]=0;
		   
		int label=0;  //���һ�������ı�� 
		for(i=1;i<=n;i++)
		{
			if( c[i]==0 )
			{//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs(i,c,label);  //���·�֧����� 
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
	{//ʹ��ջʵ�ֵ�DFS�����㷨 
        arrayStack<int> s(10);  int u;
        memset( reach,0,sizeof(int)*(n+1) );
		reach[v]=label;
		s.push(v);  cout<<v<<" ";
		
		while(!s.empty()) //��ջ����ʱ 
		{
			int w=s.top();
			s.pop();
			myIterator *iv=iterator(w);	  u=iv->next(); 	
			while( u !=0 )  //����һ������ĵ�w�������ڽӵ� 
			{
				if(  reach[u]!=label ) //�������һ��δ��ǵĵ�j 
				{  reach[u]=label;  
				   s.push(u); 
				   cout<<u<<" ";
				   iv=iterator(u);	//��ivָ����uΪ���ĵ����� 
				} 
				else{//�ö����ѱ����
				      u=iv->next();
				   	  if( u ==0 && s.empty()!=true )  s.pop(); //�ö���û�������ڽӵ���
			   		}
			}
		}		
	}
     int Dijkstra(int start,int dest,int predecessor[])
	{//�������·������¼�����·��·����predecessor�Ǵ�start��dest·����destǰ���Ǹ����� 
		int L[n+1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for(int i=1;i<=n;i++)
		{  L[i]=100000;  predecessor[i]=-1;  }   L[start]=0;
		for(ChainNode<int> *u=aList[start].firstnode; u!=NULL;u=u->next)
		{
			L[u->element]=u->weight;
			predecessor[u->element]=start;  //����start�ڽӵĵ� 
		}   
		predecessor[start]=0;    //Դ����û��ǰ��  
		bool S[n+1];
		for(int i=1;i<=n;i++)  S[i]=false;  //S[i]��ʾstart������i�����·����� 
		  
	    /*�������������ǳ�ʼ��������������*/	
		
		while( S[dest]!=true )
		{/*������һ�����ڶ��㼯S�е�u��L[u]�����С�����Խ���һ�����Ա���*/	 
			int u,tag;
			for(u=1;u<=n;u++)
			{
				if( S[u]==false && L[u]==Minium(L,S,n) )  //������һ�����ڶ��㼯S�ұ����С�ĵ㣬���Ӷȿ��Խ���O(1)�� 
				{                                        //���ҵ�д�����ӶȺ�����O(n^3)������ͨ��������ѭ���ж������ۺ������͸��Ӷ�� 
				    S[u]=true;  //��u���붥�㼯S��
				    tag=u;
				    break;
			    }
			}
			
			for(ChainNode<int> *u=aList[tag].firstnode; u!=NULL;u=u->next)
			{//�������ҵ��ĵ���ڽӵ�,�����û�б����ʹ����Ҿ���ɱ�����
			  //����д�����Ӷ���O(����)���Ϻ� 
				if(S[u->element]==false && L[tag]+ (u->weight) <L[u->element] ) 
				{
				    L[u->element]=L[tag]+ u->weight ;
				    predecessor[u->element]=tag;    //����v��ǰ����u 
				} 
		   }
		}
		return L[dest];
	}   
        
        
        
        
};
