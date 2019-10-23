#include<iostream>
#include<string>
using namespace std;

template<class T>
class linearlist //���������Ա� 
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
	{//��㸳ֵ 
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
		Chain(int initialCapacity) //�൱��Ĭ�Ϲ��캯�� 
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
		Chain(const Chain<T> &A)
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
		{//����������theIndex�ڵ��element���� 
			checkIndex(theIndex);
			ChainNode<T> *cur_node=firstnode;
			for(int i=0;i<theIndex;i++)
			{
				cur_node=cur_node->next;
			}
			return cur_node->element;
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
		void insert(int theIndex,const T& ele)
		{//��eleԪ�ز�������ΪtheIndexλ�õ��½ڵ� 
			checkIndex(theIndex);
			if(theIndex==0)
			{//����ͷ�ڵ� 
				ChainNode<T> *p=new ChainNode<T> (ele,firstnode);
				firstnode=p;
			}
			else
			{
				ChainNode<T> *p=new ChainNode<T> (ele);//������ڵ�
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
				cout<<p->element<<" ";
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
		void merge(Chain<T> A,Chain<T> B) 
		{//��A��B����ϲ�������*this��  ���鱾P125ҳT19�ķǳ�Ա������ 
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
		{//��׼�𰸣�Ҳ����ô𰸣����޸�ָ��ָ�򣬲����ٿռ� 
			ChainNode<T> *pa=A.firstnode;  //ָ��A�нڵ��ָ�� 
			ChainNode<T> *pb=B.firstnode;  //ָ��B�нڵ��ָ��
			ChainNode<T> *headnode=new ChainNode<T>;
			firstnode=NULL;
			headnode.next=firstnode;
			ChainNode<T> *pc=headnode;   //pcָ��ǰ��������׽ڵ�(������firstnodeǰ������һ��ǰ�ýڵ㣩 
			
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
		    if(pa!=NULL) pc->next=pa;  //����ʣ��Ԫ��
			       else  pc->next=pb;
			A.firstnode=NULL; 
		    B.firstnode=NULL; 	
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
		friend ostream& operator<<(ostream& out,const Chain<T> A)
		{//����Ҫ���ø��ƹ��캯�� 
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
		{//ChainNode��Ԫ�ش�СΪ[1,range] 
		 //���ӶȦ�(n+range) 
		   //��������ʼ������
		   ChainNode<T> **bottom, **top;  //�鱾p133�һ���ʾ��ͼ 
		   bottom = new ChainNode<T>* [range+1];
		   top = new ChainNode<T>* [range+1];
		   for(int b=0;b<=range;b++)
		      bottom[b]=NULL;
		   //������Ľڵ���䵽���� 
		   ChainNode<T> *curNode=firstnode;
			for( ;curNode!=NULL;curNode=curNode->next)
			{
				int theBin=curNode->element;  //Ӧ�÷�������Ӻ�
				if(bottom[theBin]==NULL)   //���Ϊ�գ���������û�зŽڵ�
				{
					bottom[theBin]=top[theBin]=curNode;
				}
				else  //���ӷǿ� 
				{
					top[theBin]->next=curNode;  //�õ�ǰ���䶥�ڵ�nextָ��ָ��curNode 
					top[theBin]=curNode;       //�����䶥ָ�� 
				}  
			}
			 //�������еĽڵ��ռ������������Ǵ�ǰ�����
			curNode=NULL;  
			for(int theBin=0;theBin<=range;theBin++)
			{
				if(bottom[theBin]!=NULL)
				{//���Ӳ�Ϊ�� 
					if(curNode==NULL)  //��һ���ǿ����ӣ������µ�firstNode 
					   firstnode=bottom[theBin];
					else
					   curNode->next=bottom[theBin];  //����һ�����ӵ��䶥�ڵ����һ�����ӵ���׽ڵ㴮���� 
					curNode=top[theBin];    //curNodeָ�����ӵ��䶥�ڵ� 
				}
			}
			if(curNode!=NULL) 
			  curNode->next=NULL; //��β�ڵ��nextָ����ΪNULL 
			delete [] bottom;
			delete [] top; 
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
		
		protected:
			void checkIndex(int theIndex) const
			{//ȷ����������Ч�ԣ���ֹԽ��
				if(theIndex<0||theIndex>listSize)
				{
					cerr<<"������������Ч�ԣ�"<<endl;
				}
			}
			ChainNode<T> *firstnode;          //ָ�������һ��Ԫ�ص�ָ�� 
			int listSize;                     //�����Ԫ�ظ��� 	               
};

/*template<class T>
void reverse(Chain<T> &A,Chain<T> &B)
{//����Chain�ĳ�Ա�������������AΪ��������B�ǰ�A��������õ�������
//ֱ���ƶ��ڵ�ָ�룬�����Ǹı�ڵ���Ԫ��
    T x;
    B.first=0;
    while(A.empty()==false)
    {
    	A.erase()
    	B.insert(0,x);
	}	
}*/

void binSort(Chain<int> &A,int range)
{//ChainNode��Ԫ�ش�СΪ[0,range] 
	//�����ӳ�ʼ��
	Chain<int> *bin=new Chain<int> [range+1];
	//��ѧ����¼��������ȡ����Ȼ����䵽������
	int num=A.size();
	for(int i=1;i<=num;i++)
	{
		ChainNode<int> x=A.get(0);   //��Զ�ӱ�ͷ���� 
		A.erase(0);
		bin[x.element].insert(0,x.element);  //�ڱ�ͷ���룬��TM��������Χ��ǰ������ռ��õ���Ĭ�Ϲ��캯����listSize��Ϊ0�� 
	}
	//���������Ѽ�Ԫ�� 
	for(int i=range;i>=1;i--)
	{//�Ӻ���ǰ�� 
		if(bin[i].empty()==false)
		{//�����Ӳ�Ϊ��ʱ 
			ChainNode<int> x=bin[i].get(0);
			cout<<x.element;
			bin[i].erase(0);
			A.insert(0,x.element);
		}
		//������Ϊ��ʱʲôҲ���� 
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
	cout<<endl<<"The initialization operation is performed below��"<<endl;
	Chain<int> A(n,a);  cout<<"Print A:"<<A<<endl;
	//�����ǳ�ʼ������

bool k=true;
while(k)
{
	int flag;
	cout<<"ִ�в������������1"<<endl<<"ִ��ɾ������������2"<<endl;
	cout<<"ִ�в��Ҳ���������3"<<endl<<"������Ա�(������)������4"<<endl;
	cout<<"ִ�кϲ�����������5"<<"ִ���������������6"<<endl; 
	cin>>flag;
	switch(flag)
	{
			case 1: {
			cout<<"������Ҫ���������"<<endl;
			int ele;  cin>>ele;
	        cout<<"������Ҫ�����λ������(��0��ʼ)"<<endl;
	        int pos; cin>>pos;
			A.insert(pos,ele);
			cout<<"�ɹ����룡"<<endl<<A<<endl;
			break;
		}
		case 2: {
			cout<<"������Ҫɾ��Ԫ�ص�����(��0��ʼ)"<<endl;
			int pos; cin>>pos;
			A.erase(pos);
			cout<<"�ɹ�ɾ����"<<endl<<A<<endl;
			break;
		}
		case 3: {
			cout<<"������Ҫ���ҵ�Ԫ�أ�"<<endl;
			int ele;  cin>>ele;
			cout<<"������Ԫ�ص������ǣ�"<<A.indexOf(ele)<<endl;
			break;
		}
		case 4: {
			A.i_print(); cout<<endl;
			break;
		}
		case 5: {
			cout<<"��������һ����������B��"<<endl;
			cout<<"please the number of datas:";
	        int n; cin>>n;
	        int *b=new int[n];
	        cout<<"please the value of datas:";
	        for(int i=0;i<n;i++) { cin>>b[i]; }
	        cout<<endl<<"The initialization operation is performed below��"<<endl;
	        Chain<int> B(n,b);  cout<<"Print B:"<<B<<endl;
	        Chain<int> C(0);
	        C.merge(A,B);  cout<<"�ϲ��Ժ�����ݣ�"<<C<<endl;
			break;
	            }
	   case 6: {
	   	    binSort(A,20);
	   	    cout<<A<<endl;
		break;
	   }
}
	
cout<<"��Ҫ��������������continue,�������������ַ�"<<endl;
string str;   cin>>str;
if(str=="continue")  k=true;
else k=false;
}
    delete []a;
	return 0;
}
