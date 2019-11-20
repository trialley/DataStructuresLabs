#include <iostream>
#include <string.h>
#include <time.h>
#include<stdlib.h>
using namespace std;
void swap(int &a,int &b,int *mov_step)
{
	int t=a;
	a=b;
	b=t;
	(*mov_step)++;
}

class Sort
{
	int size,*array;
	public:
	Sort(int *temp,int n) //构造函数 
	{
		if(n<=0)  cout<<"logic error!"<<endl;
		else 
		{
			size=n;
			array=new int [n];
			for(int i=0;i<n;i++)
			{
				array[i]=temp[i];
			}
		}
	}
	Sort() {  }          //默认构造函数 
	Sort(const Sort &X)
	{
		size=X.size;
		array=new int [size];
		for(int i=0;i<size;i++)
		{
			array[i]=X.array[i];
		}
	}
	~Sort()   //析构函数释放内存 
	{
		delete [] array;
	}
	
	Sort& operator =(const Sort S)  //重载=给Sort赋值 
	{
		delete [] array;
		array=new int [S.size];
		size=S.size;
		for(int i=0;i<S.size;i++)
		{
			array[i]=S.array[i];
		}
		return *this;
	}
	
	void rank_sort(int r[],int *mov_step,int *comp_step)
	{//给数组a[0:n-1]的n个元素按名次排序
	//下面是计算名次部分
	 *mov_step=0;
	 *comp_step=0;
	memset(r,0,size*sizeof(r[0]));
	for(int i=1;i<size;i++)  //这里比较所有元素对 
	{
		for(int j=0;j<i;j++)  //这样写会避免i和j相等的情况，从而让r[i]最小值是0非1 
		{
			(*comp_step)++;
			if(array[i]>array[j])  r[i]++;
			else r[j]++;
		}
	}  cout<<"这是array中元素按顺序的名次：";
	for(int i=0;i<size;i++)  cout<<r[i]<<" "; cout<<endl;
	 int *temp=new int [size];
	   for(int i=0;i<size;i++)  //根据名次在临时数组中排序 
	   {   temp[r[i]]=array[i];	(*mov_step)++;   }
	   for(int i=0;i<size;i++)
	   {   array[i]=temp[i]; (*mov_step)++;	  }
		
		delete [] temp;
	}
	
	void select_sort(int *mov_step,int *comp_step)
	{
		*mov_step=0;
	    *comp_step=0;
		bool sorted=false;   //用于查看数组是否已经有序（从小到大） 
		int i,j;
		//这里试来试去三重循环还是不合理，还是用书本上的双重循环加两个判断条件最好 
		   for(i=0;i<size&&sorted==false;i++)  //只有当数组无序时才继续执行 
		   {     int max=0; *comp_step+=2;
		         sorted=true;
			   for(j=0;j<size-i;j++)
			   {  (*comp_step)++;
			      if(array[max]<=array[j]) max=j;  //从第一个元素开始向后搜索，若发现其后的元素都是递增的，那么有序 
			      else sorted=false;   //如果发现其后的一个元素比a[max]小，说明数组仍然无序（注意我这里max的元素是要放在数组最后的） 
			   }
			   swap(array[max],array[size-1-i],mov_step);
	       /****************/ cout<<"第"<<i<<"次排序后的结果是：" ; output(); cout<<" "<<sorted<<endl; /********************/
		   }
	       
		
	 }
	
	void bubble_sort(int *mov_step,int *comp_step)
	{//从小到大 
	    *mov_step=0;
	    *comp_step=0;
		int i,j;
		bool sorted=false;
		int count=0;   //计数器 
		    for(j=0;j<size&&sorted==false;j++)
		    {   
			    sorted=true;
		        for(i=0;i<size-1;i++)
		        {
		        	(*comp_step)++;
			       if(array[i]>array[i+1]) { swap(array[i],array[i+1]); (*mov_step)++; sorted=false;  }
				}
				cout<<"第"<<++count<<"次排序后的结果是："; output(); cout<<" "<<sorted<<endl;
		    }
	}
	
	void insert_sort(int *mov_step,int *comp_step)
	{
		*mov_step=0;
	    *comp_step=0;
		int i,j,temp,count=0;
		for(i=1;i<size;i++)
		{
		     temp=array[i];
			for(j=i-1;j>=0;j--)
			{
				(*comp_step)++;
				if(array[j]>temp) { array[j+1]=array[j]; (*mov_step)++; count++; }   //当temp前面的数比它大，那么把它们后移 
				if(array[j]<=temp)   break;    //否则把temp插入，跳出循环 
			}
			array[j+1]=temp;  (*mov_step)++;
			cout<<"第"<<i<<"次排序后的结果是："; output(); cout<<" "<<endl;
		}
		output();
	}
	
	void output() const
	{
		for(int i=0;i<size;i++)
		  cout<<array[i]<<" ";
		cout<<endl;
	}
};

int main()
{
	int n,*p,mov_step=0,comp_step=0;
	cout<<"请输入元素的数量n"<<endl;   cin>>n;
	srand((unsigned)time(0));   //这个随机数种子1秒会改变一次，利用了系统时钟 
	p=new int[n];
	for(int i=0;i<n;i++)
	{
		p[i]=(rand()%1001);
	}
	Sort A(p,n),B(p,n),C(p,n),D(p,n);  //对类对象初始化 
	cout<<"The elements are:";  A.output();
	
	cout<<"即时终止的选择排序："<<endl;
	A.select_sort(&mov_step,&comp_step); A.output();
    cout<<"比较次数为："<<comp_step<<"\t"<<"移动次数为："<<mov_step<<endl;
    
	cout<<"按名次排序 ："<<endl;
	int *ref=new int[n];  B.rank_sort(ref,&mov_step,&comp_step);  B.output();
	cout<<"比较次数为："<<comp_step<<"\t"<<"移动次数为："<<mov_step<<endl;
	
	cout<<"及时终止的冒泡排序排序 ："<<endl;
	C.bubble_sort(&mov_step,&comp_step);  C.output();
	cout<<"比较次数为："<<comp_step<<"\t"<<"移动次数为："<<mov_step<<endl;
	
	cout<<"插入排序 ："<<endl;
	D.insert_sort(&mov_step,&comp_step);  D.output();
	cout<<"比较次数为："<<comp_step<<"\t"<<"移动次数为："<<mov_step<<endl;
	
	delete [] p;
	return 0;
}
