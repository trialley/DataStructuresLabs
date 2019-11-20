#include<iostream>
#include<string>
using namespace std;

template<class T>
struct ChainNode
{
	T element;
	T weight;
	ChainNode *next=NULL;
	
	ChainNode(T ele,T w,ChainNode *p)
	{
		element=ele;
		weight=w;
		next=p;
	}
	ChainNode(T ele,T w)
	{
		element=ele;
		weight=w;
	}
	ChainNode() {	}
	ChainNode& operator=(ChainNode &A)
	{//��㸳ֵ 
		element=A.element;
		weight=A.weight;
		next=A.next;
		return *this;
	}
};

template<class T>
class graphChain 
{
	public:
		graphChain() 
		{
		    firstnode=NULL;
		    listSize=0;
		}
		graphChain(int initialCapacity,T A[])
		{
			if(initialCapacity>0) 
			{ 
			   firstnode=new ChainNode<T>;
			   firstnode->element=A[0];
			   ChainNode<T> *p1=firstnode,*p2;
			   for(int i=1;i<initialCapacity;i++)  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
			   {
			   	   p2=new ChainNode<T>;
			   	   p2->element=A[i];
			   	   p1->next=p2;
			   	   p1=p2;
				} 
			  listSize=initialCapacity;
			}
			if(initialCapacity<=0) cerr<<"��ʼ���ȹ�С��"<<endl;
		}
		graphChain(int initialCapacity) //�൱��Ĭ�Ϲ��캯�� 
		{//����ֻ���ٽڵ㲻�����Ǹ�ֵ 
	        if(initialCapacity>=0) 
			{ 
			   firstnode=new ChainNode<T>;
			   ChainNode<T> *p1=firstnode,*p2;
			   for(int i=1;i<initialCapacity;i++)
			   {
			   	   p2=new ChainNode<T>;
			   	   p1->next=p2;
			   	   p1=p2;
				} 
			  listSize=initialCapacity;
			}
			if(initialCapacity<0) cerr<<"��ʼ���ȹ�С��"<<endl;
		}
		graphChain(const graphChain<T> &A)
		{
			listSize=A.listSize;
			if(listSize==0)
			{//�˱�Ϊ�� 
				firstnode=NULL;
			}
			else
			{//TargetNodeָ��A�Ľڵ㣬SourceNodeָ�������Ľڵ�
			//ֱ�ӽڵ㸳ֵ����ǳ���ƣ�ciao! 
			   ChainNode<T> *SourceNode=new ChainNode<T>;
			   ChainNode<T> *pre_node,*TargetNode;
			   firstnode=SourceNode;
			   TargetNode=A.firstnode;
			   SourceNode->element=TargetNode->element;
			   
			   for(int i=1;i<listSize;i++)  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
			   {
			   	   TargetNode=TargetNode->next;
			   	   pre_node=new ChainNode<T> (TargetNode->element);  //�����pre_node������һ���¿ռ䲢��ʼ�� 
			   	   SourceNode->next=pre_node;
			   	   SourceNode=pre_node;  
				} 
			}
			
			
		}
		~graphChain()
		{
			while(firstnode!=NULL)
			{
				ChainNode<T> *nextnode=firstnode->next;
			    delete firstnode;
			    firstnode=nextnode;
			}
		}
	    bool empty() const
		{    return listSize==0;   }
		int size() const 
		{    return listSize;	   }
		T& get(int theIndex) const
		{//����������theIndex�ڵ��element���� 
			checkIndex(theIndex);
			ChainNode<T> *cur_node=firstnode;
			for(int i=0;i<theIndex;i++)
			{
				cur_node=cur_node->next;
			}
			return cur_node->element;
		}
		T get_Weight(int ele) const
		{//����Ԫ����ele�ڵ��weight
			ChainNode<T> *cur_node;
			cout<<"vetrex="<<ele;
			for(cur_node=firstnode; cur_node!=NULL ; cur_node=cur_node->next )
			{
				if(cur_node->element==ele)
				   return cur_node->weight;
			}
			return -1;
		}
		int indexOf(T& theElement) const
		{//���ؽڵ�Ԫ��������theElement�Ľڵ���������δ�ҵ��򷵻�-1 
			ChainNode<T> *cur_node=firstnode;
			for(int i=0;i<listSize;i++)
			{
				if(cur_node->element==theElement)
				   return i;
				else
				   cur_node=cur_node->next;
			}
			return -1;
		}
		ChainNode<T>* eraseElement(int theVertex)
		{//�����������Ҷ������theVertex��Ԫ�أ����ҵ���ɾ�������������Ԫ�ص�ָ�� 
			ChainNode<T> *p=firstnode,*tp=NULL;
			while(p!=NULL)
			{
				if(p->element==theVertex)
				{
					if(p==firstnode) //ɾͷ��� 
					  firstnode=firstnode->next;
					else
					{
					  tp->next=p->next;
					  delete p;
					  return p;
					}
				}
				else{//Ԫ�ز�����theVertex 
					  tp=p; 
					  p=p->next;
				    }
			}
			return NULL;  //�Ҳ����Ļ�����NULL 
		}
		
		void erase(int theIndex)
		{//��������ɾ������ΪtheIndex�Ľڵ� 
			checkIndex(theIndex);
			ChainNode<T> *deletenode;
			if(theIndex==0)
			{//ɾ��ͷ��� 
			    deletenode=firstnode;
			   firstnode=firstnode->next;
			}
			else
			{
				ChainNode<T> *p=firstnode;
			    for(int i=0;i<theIndex-1;i++)
			    {
				    p=p->next;
			    }
			    //��ʱ�Ѿ��ҵ�Ҫɾ���Ľ���ǰ���ڵ� 
			    deletenode=p->next;
				p->next=p->next->next;
			}
			listSize--;
			delete deletenode;
		}
		void insert(int theIndex,const T& ele,T weight)
		{//��eleԪ�ز�������ΪtheIndexλ�õ��½ڵ� 
			checkIndex(theIndex);
			if(theIndex==0)
			{//����ͷ�ڵ� 
				ChainNode<T> *p=new ChainNode<T> (ele,weight,firstnode);
				firstnode=p;
			}
			else
			{
				ChainNode<T> *p=new ChainNode<T> (ele,weight);//������ڵ�
				ChainNode<T> *cur_node=firstnode;
			    for(int i=0;i<theIndex-1;i++)
			    {
				    cur_node=cur_node->next;
			    }
			    //��ʱ�Ѿ��ҵ�Ҫ����Ľ���ǰ���ڵ� 
			    p->next=cur_node->next;
			    cur_node->next=p;
			}
			listSize++;
		}
		void output() const
		{
			if(listSize==0){  cout<<"null"<<endl;  return; }
			else{
			ChainNode<T> *p=firstnode;
			for(int i=0;i<listSize;i++)
			{
				cout<<"vertex="<<p->element<<",weight="<<p->weight<<"   ";
				p=p->next;
			}    
			    }
		}
		void i_print() const
		{//ʹ�õ�������� 
		    if(listSize==0){  cout<<"null"<<endl;  return; }
		    else{
			iterator I(firstnode);
			for(int i=0;i<listSize;i++)
			{
				cout<<(*I)<<" ";
				I++;
			}
		        }
		}
	
		void clear()
		{//������ 
		    ChainNode<T> *deletenode,*p=firstnode;
			for(int i=0;i<listSize;i++)
			{
				deletenode=p;
				p=p->next;
				delete deletenode;
			}
			firstnode=NULL;
			listSize=0;
		}
		friend ostream& operator<<(ostream& out,const graphChain<T> A)
		{//����Ҫ���ø��ƹ��캯�� 
		   if(A.listSize==0){  out<<"null"<<endl;  return out;  }
		   else{
			     ChainNode<T> *p=A.firstnode;
			     for(int i=0;i<A.listSize;i++)
			     {
				     out<<p->element<<" "<<p->weight<<" ";
				     p=p->next;
		         }
			     return out;
			   }
		}
		class iterator
   {//���캯����*&��ǰ���Լӡ���=��== 
    protected:
	    ChainNode<T> *node=NULL;
	public:
		iterator(ChainNode<T> *theNode)
		{  node=theNode;  }
		iterator() {	}
		
		T& operator*() {  return node->element; }  //ȡ�������������Ϊ���÷��� 
		T* operator->() { return &(node->element);	}  //ȡ��ַ���������Ϊָ�뷵�� 
	    iterator& operator++()
	    {//ǰ�� 
	    	node =node->next;
	    	return *this;
		}
		iterator operator++(int)
		{//��� 
			iterator temp=*this;
			node =node->next;
			return temp;
		}
		bool operator!=(const iterator I)const
		{
			if(node==I.node) return false;  //������û�ж���ChainNode��==��Ϊʲôû�б��� 
			else return true;
		}
		bool operator==(const iterator I)const
		{
			if(node==I.node) return true;
			else return false;
		}
		
   };
		
		//protected:
			void checkIndex(int theIndex) const
			{//ȷ����������Ч�ԣ���ֹԽ��
				if(theIndex<0||theIndex>listSize)
				{
					cerr<<"index="<<theIndex<<",listSize="<<listSize<<"������������Ч�ԣ�"<<endl;
				}
			}
			ChainNode<T> *firstnode;          //ָ�������һ��Ԫ�ص�ָ�� 
			int listSize;                     //�����Ԫ�ظ��� 	               
};
