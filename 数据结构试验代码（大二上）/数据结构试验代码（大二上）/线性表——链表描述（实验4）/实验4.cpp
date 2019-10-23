#include<iostream>
#include<string>
using namespace std;

template<class T>
class linearlist //抽象类线性表 
{
	public:
		virtual ~linearlist() {	}
		virtual bool empty() const=0;
		virtual int size() const=0;
		virtual T& get(int theIndex) const=0;
		virtual int indexOf(T& theElement) const=0;
		virtual void erase(int theIndex)=0;
		virtual void insert(int theIndex,const T& theElement)=0;
		virtual void output() const = 0;
};

template<class T>
struct ChainNode
{
	T element;
	ChainNode *next=NULL;
	
	ChainNode(T ele,ChainNode *p)
	{
		element=ele;
		next=p;
	}
	ChainNode(T ele)
	{
		element=ele;
	}
	ChainNode() {	}
	ChainNode& operator=(ChainNode &A)
	{//结点赋值 
		element=A.element;
		next=A.next;
		return *this;
	}
};

template<class T>
class Chain :public linearlist<T>
{
	public:
		Chain() {	}
		Chain(int initialCapacity,T A[])
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
		Chain(int initialCapacity) //相当于默认构造函数 
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
		Chain(const Chain<T> &A)
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
		~Chain()
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
		void insert(int theIndex,const T& ele)
		{//将ele元素插入索引为theIndex位置的新节点 
			checkIndex(theIndex);
			if(theIndex==0)
			{//插入头节点 
				ChainNode<T> *p=new ChainNode<T> (ele,firstnode);
				firstnode=p;
			}
			else
			{
				ChainNode<T> *p=new ChainNode<T> (ele);//待插入节点
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
				cout<<p->element<<" ";
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
		void merge(Chain<T> A,Chain<T> B) 
		{//把A和B有序合并，放入*this中  （书本P125页T19的非成员方法） 
		    cout<<this->listSize<<endl;
		    this->clear();
		    listSize=A.listSize+B.listSize;
		    
		    firstnode=new ChainNode<T>;
			ChainNode<T> *p1=firstnode,*p2;
			   for(int i=1;i<listSize;i++)
			   {
			   	   p2=new ChainNode<T>;
			   	   p1->next=p2;
			   	   p1=p2;
				} 
		    
			iterator ai(A.firstnode);
			iterator bi(B.firstnode);
			iterator ti(firstnode);
			while(ai!=NULL&&bi!=NULL)
			{
				if(*ai<*bi)  {  *ti=*(ai++);  *(ti++);   }
				else    {  *ti=*(bi++);  *(ti++);  }
			}
			if(ai==NULL)
			{
				while(bi!=NULL){  *ti=*(bi++);  *(ti++);  }
			}
			else
			{  
			    while(ai!=NULL){  *ti=*(ai++);  *(ti++); }
			}
		}
		void best_Merge(Chain<T> &A,Chain<T> &B)
		{//标准答案，也是最好答案，仅修改指针指向，不另开辟空间 
			ChainNode<T> *pa=A.firstnode;  //指向A中节点的指针 
			ChainNode<T> *pb=B.firstnode;  //指向B中节点的指针
			ChainNode<T> *headnode=new ChainNode<T>;
			firstnode=NULL;
			headnode.next=firstnode;
			ChainNode<T> *pc=headnode;   //pc指向当前新链表的首节点(这里在firstnode前创建了一个前置节点） 
			
			while(pa!=NULL&&pb!=NULL)
			{
			  if(*pa<*pb)
			  {  
			 	 pc->next=pa;
				 pc=pa;
				 pa=pa->next;
				 pc->next=NULL;
			  }
			  else
			  {
				 pc->next=pb; 
				 pc=pb; 
				 pb=pb->next;
				 pc->next=NULL;
			  }
		    }
		    if(pa!=NULL) pc->next=pa;  //处理剩余元素
			       else  pc->next=pb;
			A.firstnode=NULL; 
		    B.firstnode=NULL; 	
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
		friend ostream& operator<<(ostream& out,const Chain<T> A)
		{//这里要调用复制构造函数 
		   if(A.listSize==0){  out<<"null"<<endl;  return out;  }
		   else{
			     ChainNode<T> *p=A.firstnode;
			     for(int i=0;i<A.listSize;i++)
			     {
				     out<<p->element<<" ";
				     p=p->next;
		         }
			     return out;
			   }
		}
		void binSort(int range)
		{//ChainNode中元素大小为[1,range] 
		 //复杂度Θ(n+range) 
		   //创建并初始化箱子
		   ChainNode<T> **bottom, **top;  //书本p133我画了示意图 
		   bottom = new ChainNode<T>* [range+1];
		   top = new ChainNode<T>* [range+1];
		   for(int b=0;b<=range;b++)
		      bottom[b]=NULL;
		   //把链表的节点分配到箱子 
		   ChainNode<T> *curNode=firstnode;
			for( ;curNode!=NULL;curNode=curNode->next)
			{
				int theBin=curNode->element;  //应该放入的箱子号
				if(bottom[theBin]==NULL)   //箱底为空，即箱子里没有放节点
				{
					bottom[theBin]=top[theBin]=curNode;
				}
				else  //箱子非空 
				{
					top[theBin]->next=curNode;  //让当前的箱顶节点next指针指向curNode 
					top[theBin]=curNode;       //更新箱顶指针 
				}  
			}
			 //把箱子中的节点收集到链表，这里是从前向后收
			curNode=NULL;  
			for(int theBin=0;theBin<=range;theBin++)
			{
				if(bottom[theBin]!=NULL)
				{//箱子不为空 
					if(curNode==NULL)  //第一个非空箱子，设置新的firstNode 
					   firstnode=bottom[theBin];
					else
					   curNode->next=bottom[theBin];  //将上一个箱子的箱顶节点和下一个箱子的箱底节点串起来 
					curNode=top[theBin];    //curNode指向本箱子的箱顶节点 
				}
			}
			if(curNode!=NULL) 
			  curNode->next=NULL; //把尾节点的next指针设为NULL 
			delete [] bottom;
			delete [] top; 
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
		
		protected:
			void checkIndex(int theIndex) const
			{//确定索引的有效性，防止越界
				if(theIndex<0||theIndex>listSize)
				{
					cerr<<"请检查索引的有效性！"<<endl;
				}
			}
			ChainNode<T> *firstnode;          //指向链表第一个元素的指针 
			int listSize;                     //链表的元素个数 	               
};

/*template<class T>
void reverse(Chain<T> &A,Chain<T> &B)
{//利用Chain的成员函数来完成逆序，A为输入链表，B是把A反序后所得到的链表
//直接移动节点指针，而不是改变节点中元素
    T x;
    B.first=0;
    while(A.empty()==false)
    {
    	A.erase()
    	B.insert(0,x);
	}	
}*/

void binSort(Chain<int> &A,int range)
{//ChainNode中元素大小为[0,range] 
	//对箱子初始化
	Chain<int> *bin=new Chain<int> [range+1];
	//把学生记录从链表中取出，然后分配到箱子里
	int num=A.size();
	for(int i=1;i<=num;i++)
	{
		ChainNode<int> x=A.get(0);   //永远从表头拿下 
		A.erase(0);
		bin[x.element].insert(0,x.element);  //在表头插入，我TM超索引范围！前面申请空间用的是默认构造函数，listSize设为0了 
	}
	//从箱子中搜集元素 
	for(int i=range;i>=1;i--)
	{//从后向前收 
		if(bin[i].empty()==false)
		{//当箱子不为空时 
			ChainNode<int> x=bin[i].get(0);
			cout<<x.element;
			bin[i].erase(0);
			A.insert(0,x.element);
		}
		//当箱子为空时什么也不做 
	}
	cout<<A<<endl;
	delete [] bin;
}

int main()
{
    cout<<"please the number of datas:";
	int n; cin>>n;
	int *a=new int[n];
	cout<<"please the value of datas:";
	for(int i=0;i<n;i++) { cin>>a[i]; }
	cout<<endl<<"The initialization operation is performed below："<<endl;
	Chain<int> A(n,a);  cout<<"Print A:"<<A<<endl;
	//以上是初始化部分

bool k=true;
while(k)
{
	int flag;
	cout<<"执行插入操作请输入1"<<endl<<"执行删除操作请输入2"<<endl;
	cout<<"执行查找操作请输入3"<<endl<<"输出线性表(迭代器)请输入4"<<endl;
	cout<<"执行合并操作请输入5"<<"执行排序操作请输入6"<<endl; 
	cin>>flag;
	switch(flag)
	{
			case 1: {
			cout<<"请输入要插入的数据"<<endl;
			int ele;  cin>>ele;
	        cout<<"请输入要插入的位置索引(从0开始)"<<endl;
	        int pos; cin>>pos;
			A.insert(pos,ele);
			cout<<"成功插入！"<<endl<<A<<endl;
			break;
		}
		case 2: {
			cout<<"请输入要删除元素的索引(从0开始)"<<endl;
			int pos; cin>>pos;
			A.erase(pos);
			cout<<"成功删除！"<<endl<<A<<endl;
			break;
		}
		case 3: {
			cout<<"请输入要查找的元素："<<endl;
			int ele;  cin>>ele;
			cout<<"所查找元素的索引是："<<A.indexOf(ele)<<endl;
			break;
		}
		case 4: {
			A.i_print(); cout<<endl;
			break;
		}
		case 5: {
			cout<<"请再输入一个有序数组B："<<endl;
			cout<<"please the number of datas:";
	        int n; cin>>n;
	        int *b=new int[n];
	        cout<<"please the value of datas:";
	        for(int i=0;i<n;i++) { cin>>b[i]; }
	        cout<<endl<<"The initialization operation is performed below："<<endl;
	        Chain<int> B(n,b);  cout<<"Print B:"<<B<<endl;
	        Chain<int> C(0);
	        C.merge(A,B);  cout<<"合并以后的内容："<<C<<endl;
			break;
	            }
	   case 6: {
	   	    binSort(A,20);
	   	    cout<<A<<endl;
		break;
	   }
}
	
cout<<"如要继续操作请输入continue,否则输入任意字符"<<endl;
string str;   cin>>str;
if(str=="continue")  k=true;
else k=false;
}
    delete []a;
	return 0;
}
