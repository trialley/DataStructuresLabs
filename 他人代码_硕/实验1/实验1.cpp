#include<iostream>
using namespace std;
#define N 5

template <class T>
void permutations(T list[],int m,int n)  //����list[m:n]��ȫ���� 
{
	if(m>n) cerr<<"math error!"<<endl;
	if(m==n) {  //LIST[M:N]����һ�����У������ 
		/*copy(list,list+n+1,ostream_iterator<T>(cout,""));*/
		for(int i=0;i<=n;i++) { cout<<list[i];	}
		cout<<" ";
	}
	
	else 
	   for(int i=m;i<=n;i++)
	   {
	   	swap(list[i],list[m]);  //Ϊʲô���� call of overloaded 'swap(int&,int&) is ambiguous? std�ļ����Ѿ�������swap�������㲻Ҫ��д�� 
	   	permutations(list,m+1,n); 
		swap(list[m],list[i]);
		} 
}

template <class T>
void Sub_Generation(T list[],int temp[],int n,int pos=0)   //there is n elements in the list. And temp���ڴ���0��1����
{//����nλ��0��1���б�ʾlist��Ԫ���Ƿ����Ӽ��� ,pos�Ǵ����ʼλ��  
   
/************************************************ 
if(list[0]==0)  cout<<"error!"<<endl;
    for(int i=0;i<n;i++)
		{  cout<<list[i]<<" ";} 	
/************************************************/		
		
	if(pos==n)  //ǰ������ѭ������ʱpos�Ѿ�����n 
	{   cout<<"{";
		for(int i=0;i<n;i++)
		{
		   if(temp[i]==1) 
		   {  /*if(list[i]==0) list[i]=1;*/ cout<<list[i];  //��bug..... 
		   }
		  
	    }  cout<<"} ";  //return;
	} 
	else 
	{
		   temp[pos]=0;
		   Sub_Generation(list,temp,n,pos+1);
		   temp[pos]=1;
		   Sub_Generation(list,temp,n,pos+1);
	}
}

 
int main()
{
	int i,list[N],temp[N];   //���˲�ǳ 
	cout<<"������"<<N<<"������"<<endl; 
	for(i=0;i<N;i++)  {  cin>>list[i];  }
	cout<<"����������ȫ����:"<<endl;
	permutations(list,0,N-1);
    //for(i=0;i<N;i++)  {  cout<<endl<<list[i];  }  //�����鷢��list�ڴ���ڶ�������֮ǰ�������� 
    cout<<endl;
    cout<<"�����������Ӽ�:"<<endl;
    Sub_Generation(list,temp,N,0);
	return 0;
}
