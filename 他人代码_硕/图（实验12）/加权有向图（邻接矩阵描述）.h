#pragma once
#include<iostream>
#include"edge.h"
#include"arrayQueue.h"
#include"ջ.h"
using namespace std;

template<class T>
class adjacencyWDigraph
{//�ڽӾ����ʾ�ļ�Ȩ����ͼ 
	protected:
		int n;       //������� 
		int e;       //�ߵĸ��� 
		T **a;       //�ڽ����� 
		T noEdge;    //��ʾ�����ڵı�
		int *reach;  //����ָ�� 
		int label=20170013;
		
		
		void rDfs(int v)
		{//�ݹ�ʵ�������������
		    reach[v]=label;  int u;
		    myIterator *iv=iterator(v);  //�����<T>�ͻᱨ��Ϊʲô���� 
			while( ( u=iv->next() )!=0 )
			{//��v����һ���ڽӵ�uΪ�����ݹ����� 
				if(reach[u]!=label)
				  rDfs(u);  //u��һ��û�е�����Ķ��� 
			} 
			delete iv;
			return;
		} 
/*		void rDfs(int v) 
		{//ʹ��ջģ��ݹ� 
			arrayStack<int> s(10);  int u;
			reach[v]=label;
			s.push(v);
			
			while(!s.empty()) //��ջ����ʱ 
			{
				int w=s.top();
				s.pop();
				myIterator *iv=iterator(w);		
				while( ( u=iv->next() )!=0 )  //����һ������ĵ�w�������ڽӵ� 
				{
					if(  reach[u]!=label ) //�������һ��δ��ǵĵ�j 
					{  reach[u]=label;  s.push(u);	} 
					else{//j�ѱ������wû�������ڽӵ���
				   		if(iv->next()==0)  s.pop(); 
			   			}
				}
			}
		}*/
	public:
	    adjacencyWDigraph(int v=0,T theNoEdge=0)
	    {//���캯��
		    if(v<0) cerr<<"����鶥�����ĺϷ��ԣ�"<<endl;
		    n=v;
	    	noEdge=theNoEdge;
	    	e=0;
	    	
	    	 a=new T*[n+1];
	    	 for(int i=0;i<n+1;i++)
	    	 {//����ռ� 
	    		 a[i]=new T [n+1];
			 }
				for(int i=1;i<=n;i++)  //��ʼ���ڽӾ��� 
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
			a=NULL;  //����ΪNULL�Ļ����Ұָ�룬��������Ҳû�� 
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
		{//����ߣ�����ñ��Ѵ��ڣ�����theEdge->weight()�޸ıߵ�Ȩ
		   int v1=theEdge->vertex1();
		   int v2=theEdge->vertex2();
		   if( v1<1 || v2<1 || v1>n || v2>n || v1==v2 )
		   {//Խ�紦�� 
		   	   cerr<<"("<<v1<<","<<v2<<") is not a permissible edge"<<endl;
		   	   exit(1);
		   }
		   if(a[v1][v2]==noEdge)  //�±� 
		      e++;
		   a[v1][v2]=theEdge->weight();   
		}
	    void eraseEdge(int i,int j)
	    {//ɾ����(i,j),��������ڸñ߾�ʲôҲ���� 
		   if(i>=1 && j>=1 && i<=n && j<=n && a[i][j]!=noEdge )
		   {
		       a[i][j]=noEdge;
		   	   e--;
		   } 
		}
		void checkVertex(int theVertex) const
		{//ȷ������Ч���� 
			if(theVertex<1 || theVertex>n)
			{
				cerr<<"the vertex:"<<theVertex<<" is not permissible";
			    exit(1); 
			}  
			else return;
		}
		int outDegree(int Vertex)
		{//���㶥��Vertex�ĳ���
		    checkVertex(Vertex);
			int sum=0;
			for(int j=1;j<=n;j++)
			  if( a[Vertex][j]!=noEdge )  //������Vertex�� 
			    sum++;
			return sum; 
		}
		int inDegree(int Vertex)
		{//���㶥��Vertex�����
		    checkVertex(Vertex);
			int sum=0;
			for(int j=1;j<=n;j++)
			  if( a[j][Vertex]!=noEdge )  //������Vertex�� 
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
				{//����ָ���������һ���ڽӵ�����ĵ�Ȩֵ 
					for(int i=currentVertex;i<=n;i++)
					{
						if(Row[i]!=noEdge)
						{//����һ���ڽӵ� 
							currentVertex=i+1;
							theWeight=Row[i];
							return i;
						}
					}
					//��������һ���ڽӵ��� 
					currentVertex=n+1;
					return 0;
				}
				int next()
				{//����ָ���������һ���ڽӵ� 
					for(int i=currentVertex;i<=n;i++)
					{
						if(Row[i]!=noEdge)
						{//����һ���ڽӵ� 
							currentVertex=i+1;
							return i;
						}
					}
					//��������һ���ڽӵ��� 
					currentVertex=n+1;
					return 0;
				}
			protected:
				T *Row;              //�ڽӾ���ĵ��� 
				T noEdge;            //theRow[i]==noEdge�����ҽ���û�й����붥��i�ı� 
				int n;               //������ 
				int currentVertex;   //��ǰ�����Ķ��� 
		};
		myIterator* iterator(int theVertex)
		{//���ض���theVertex�ĵ����� 
			checkVertex(theVertex);
			return new myIterator( a[theVertex], noEdge, n);
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
