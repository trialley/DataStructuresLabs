#include<iostream>
#include"graphChain.h"
#include"edge.h"
using namespace std;

template<class T>
class linkedDigraph
{//��Ȩ����ͼ 
	protected:
		int n;                 //������ 
		int e;                 //���� 
		graphChain<T> *aList;  //�ڽӱ� 
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
	    	delete [] aList;  //�����ͻ��Լ�����graphChain������������ 
		}
		int numberOfVertices() const { return n; }
	    int numberOfEdges() const { return e; }
	    bool directed() const { return true; }
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
		void insertEdge(edge<bool> *theEdge)
		{
			int v1=theEdge->vertex1();
			int v2=theEdge->vertex2();
			if( v1<1 || v2<1 || v1>n || v2>n || v1==v2 )
		    {//Խ�紦�� 
		   	   cerr<<"("<<v1<<","<<v2<<") is not a permissible edge"<<endl;
		   	   exit(1);
		    }
		    if(aList[v1].indexOf(v2)==-1)
		    {//�±� 
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
				  e--;   //�ñߴ��� 
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
			{//��ÿ���������������Vertex 
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
				{//����ָ���������һ���ڽӵ�����ĵ�Ȩֵ 
				    currentVertex=currentVertex->next;
					if(currentVertex!=NULL)
					{
						theWeight=true;
						return currentVertex;
					}
					return NULL;
				}
				ChainNode<T>* next()
				{//����ָ���������һ���ڽӵ� 
					currentVertex=currentVertex->next;
					if(currentVertex!=NULL)
					{
						return currentVertex;
					}
					return NULL;
				}
			protected:
				graphChain<T> *v;    //�ڽӱ�ĵ� 
				ChainNode<T> *currentVertex;   //��ǰ�����Ķ��� 
		};	 
		myIterator* iterator(int theVertex)
        {
           checkVertex(theVertex);
           return new myIterator( aList[theVertex] );
        }
		   
};
