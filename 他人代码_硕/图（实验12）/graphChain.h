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
	{//结点赋值 
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
			   for(int i=1;i<initialCapacity;i++)  //等于1的话前面已经创建好了一个节点 
			   {
			   	   p2=new ChainNode<T>;
			   	   p2->element=A[i];
			   	   p1->next=p2;
			   	   p1=p2;
				} 
			  listSize=initialCapacity;
			}
			if(initialCapacity<=0) cerr<<"初始长度过小！"<<endl;
		}
		graphChain(int initialCapacity) //相当于默认构造函数 
		{//这里只开辟节点不给他们赋值 
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
			if(initialCapacity<0) cerr<<"初始长度过小！"<<endl;
		}
		graphChain(const graphChain<T> &A)
		{
			listSize=A.listSize;
			if(listSize==0)
			{//此表为空 
				firstnode=NULL;
			}
			else
			{//TargetNode指向A的节点，SourceNode指向此链表的节点
			//直接节点赋值会变成浅复制，ciao! 
			   ChainNode<T> *SourceNode=new ChainNode<T>;
			   ChainNode<T> *pre_node,*TargetNode;
			   firstnode=SourceNode;
			   TargetNode=A.firstnode;
			   SourceNode->element=TargetNode->element;
			   
			   for(int i=1;i<listSize;i++)  //等于1的话前面已经创建好了一个节点 
			   {
			   	   TargetNode=TargetNode->next;
			   	   pre_node=new ChainNode<T> (TargetNode->element);  //这里给pre_node创建了一个新空间并初始化 
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
		{//返回索引是theIndex节点的element内容 
			checkIndex(theIndex);
			ChainNode<T> *cur_node=firstnode;
			for(int i=0;i<theIndex;i++)
			{
				cur_node=cur_node->next;
			}
			return cur_node->element;
		}
		T get_Weight(int ele) const
		{//返回元素是ele节点的weight
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
		{//返回节点元素内容是theElement的节点索引，若未找到则返回-1 
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
		{//搜索链表并查找顶点等于theVertex的元素，若找到则删除它并返回这个元素的指针 
			ChainNode<T> *p=firstnode,*tp=NULL;
			while(p!=NULL)
			{
				if(p->element==theVertex)
				{
					if(p==firstnode) //删头结点 
					  firstnode=firstnode->next;
					else
					{
					  tp->next=p->next;
					  delete p;
					  return p;
					}
				}
				else{//元素不等于theVertex 
					  tp=p; 
					  p=p->next;
				    }
			}
			return NULL;  //找不到的话返回NULL 
		}
		
		void erase(int theIndex)
		{//从链表中删除索引为theIndex的节点 
			checkIndex(theIndex);
			ChainNode<T> *deletenode;
			if(theIndex==0)
			{//删除头结点 
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
			    //此时已经找到要删除的结点的前驱节点 
			    deletenode=p->next;
				p->next=p->next->next;
			}
			listSize--;
			delete deletenode;
		}
		void insert(int theIndex,const T& ele,T weight)
		{//将ele元素插入索引为theIndex位置的新节点 
			checkIndex(theIndex);
			if(theIndex==0)
			{//插入头节点 
				ChainNode<T> *p=new ChainNode<T> (ele,weight,firstnode);
				firstnode=p;
			}
			else
			{
				ChainNode<T> *p=new ChainNode<T> (ele,weight);//待插入节点
				ChainNode<T> *cur_node=firstnode;
			    for(int i=0;i<theIndex-1;i++)
			    {
				    cur_node=cur_node->next;
			    }
			    //此时已经找到要插入的结点的前驱节点 
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
		{//使用迭代器输出 
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
		{//清表操作 
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
		{//这里要调用复制构造函数 
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
   {//构造函数、*&、前后自加、！=、== 
    protected:
	    ChainNode<T> *node=NULL;
	public:
		iterator(ChainNode<T> *theNode)
		{  node=theNode;  }
		iterator() {	}
		
		T& operator*() {  return node->element; }  //取内容运算符，作为引用返回 
		T* operator->() { return &(node->element);	}  //取地址运算符，作为指针返回 
	    iterator& operator++()
	    {//前加 
	    	node =node->next;
	    	return *this;
		}
		iterator operator++(int)
		{//后加 
			iterator temp=*this;
			node =node->next;
			return temp;
		}
		bool operator!=(const iterator I)const
		{
			if(node==I.node) return false;  //这里我没有定义ChainNode的==，为什么没有报错？ 
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
			{//确定索引的有效性，防止越界
				if(theIndex<0||theIndex>listSize)
				{
					cerr<<"index="<<theIndex<<",listSize="<<listSize<<"请检查索引的有效性！"<<endl;
				}
			}
			ChainNode<T> *firstnode;          //指向链表第一个元素的指针 
			int listSize;                     //链表的元素个数 	               
};
