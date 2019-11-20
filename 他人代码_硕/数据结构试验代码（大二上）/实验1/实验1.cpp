#include<iostream>
using namespace std;
#define N 5

template <class T>
void permutations(T list[],int m,int n)  //生成list[m:n]的全排列 
{
	if(m>n) cerr<<"math error!"<<endl;
	if(m==n) {  //LIST[M:N]仅有一个排列，输出它 
		/*copy(list,list+n+1,ostream_iterator<T>(cout,""));*/
		for(int i=0;i<=n;i++) { cout<<list[i];	}
		cout<<" ";
	}
	
	else 
	   for(int i=m;i<=n;i++)
	   {
	   	swap(list[i],list[m]);  //为什么出错？ call of overloaded 'swap(int&,int&) is ambiguous? std文件里已经定义了swap函数，你不要再写了 
	   	permutations(list,m+1,n); 
		swap(list[m],list[i]);
		} 
}

template <class T>
void Sub_Generation(T list[],int temp[],int n,int pos=0)   //there is n elements in the list. And temp用于储存0、1序列
{//生成n位的0、1序列表示list的元素是否在子集中 ,pos是代表初始位置  
   
/************************************************ 
if(list[0]==0)  cout<<"error!"<<endl;
    for(int i=0;i<n;i++)
		{  cout<<list[i]<<" ";} 	
/************************************************/		
		
	if(pos==n)  //前面跳出循环条件时pos已经等于n 
	{   cout<<"{";
		for(int i=0;i<n;i++)
		{
		   if(temp[i]==1) 
		   {  /*if(list[i]==0) list[i]=1;*/ cout<<list[i];  //神bug..... 
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
	int i,list[N],temp[N];   //害人不浅 
	cout<<"请输入"<<N<<"个数字"<<endl; 
	for(i=0;i<N;i++)  {  cin>>list[i];  }
	cout<<"下面是它的全排列:"<<endl;
	permutations(list,0,N-1);
    //for(i=0;i<N;i++)  {  cout<<endl<<list[i];  }  //这里检查发现list在传入第二个函数之前是正常的 
    cout<<endl;
    cout<<"下面是它的子集:"<<endl;
    Sub_Generation(list,temp,N,0);
	return 0;
}
