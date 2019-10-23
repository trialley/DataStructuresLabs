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
	Sort(int *temp,int n) //���캯�� 
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
	Sort() {  }          //Ĭ�Ϲ��캯�� 
	Sort(const Sort &X)
	{
		size=X.size;
		array=new int [size];
		for(int i=0;i<size;i++)
		{
			array[i]=X.array[i];
		}
	}
	~Sort()   //���������ͷ��ڴ� 
	{
		delete [] array;
	}
	
	Sort& operator =(const Sort S)  //����=��Sort��ֵ 
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
	{//������a[0:n-1]��n��Ԫ�ذ���������
	//�����Ǽ������β���
	 *mov_step=0;
	 *comp_step=0;
	memset(r,0,size*sizeof(r[0]));
	for(int i=1;i<size;i++)  //����Ƚ�����Ԫ�ض� 
	{
		for(int j=0;j<i;j++)  //����д�����i��j��ȵ�������Ӷ���r[i]��Сֵ��0��1 
		{
			(*comp_step)++;
			if(array[i]>array[j])  r[i]++;
			else r[j]++;
		}
	}  cout<<"����array��Ԫ�ذ�˳������Σ�";
	for(int i=0;i<size;i++)  cout<<r[i]<<" "; cout<<endl;
	 int *temp=new int [size];
	   for(int i=0;i<size;i++)  //������������ʱ���������� 
	   {   temp[r[i]]=array[i];	(*mov_step)++;   }
	   for(int i=0;i<size;i++)
	   {   array[i]=temp[i]; (*mov_step)++;	  }
		
		delete [] temp;
	}
	
	void select_sort(int *mov_step,int *comp_step)
	{
		*mov_step=0;
	    *comp_step=0;
		bool sorted=false;   //���ڲ鿴�����Ƿ��Ѿ����򣨴�С���� 
		int i,j;
		//����������ȥ����ѭ�����ǲ������������鱾�ϵ�˫��ѭ���������ж�������� 
		   for(i=0;i<size&&sorted==false;i++)  //ֻ�е���������ʱ�ż���ִ�� 
		   {     int max=0; *comp_step+=2;
		         sorted=true;
			   for(j=0;j<size-i;j++)
			   {  (*comp_step)++;
			      if(array[max]<=array[j]) max=j;  //�ӵ�һ��Ԫ�ؿ�ʼ�������������������Ԫ�ض��ǵ����ģ���ô���� 
			      else sorted=false;   //�����������һ��Ԫ�ر�a[max]С��˵��������Ȼ����ע��������max��Ԫ����Ҫ�����������ģ� 
			   }
			   swap(array[max],array[size-1-i],mov_step);
	       /****************/ cout<<"��"<<i<<"�������Ľ���ǣ�" ; output(); cout<<" "<<sorted<<endl; /********************/
		   }
	       
		
	 }
	
	void bubble_sort(int *mov_step,int *comp_step)
	{//��С���� 
	    *mov_step=0;
	    *comp_step=0;
		int i,j;
		bool sorted=false;
		int count=0;   //������ 
		    for(j=0;j<size&&sorted==false;j++)
		    {   
			    sorted=true;
		        for(i=0;i<size-1;i++)
		        {
		        	(*comp_step)++;
			       if(array[i]>array[i+1]) { swap(array[i],array[i+1]); (*mov_step)++; sorted=false;  }
				}
				cout<<"��"<<++count<<"�������Ľ���ǣ�"; output(); cout<<" "<<sorted<<endl;
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
				if(array[j]>temp) { array[j+1]=array[j]; (*mov_step)++; count++; }   //��tempǰ�������������ô�����Ǻ��� 
				if(array[j]<=temp)   break;    //�����temp���룬����ѭ�� 
			}
			array[j+1]=temp;  (*mov_step)++;
			cout<<"��"<<i<<"�������Ľ���ǣ�"; output(); cout<<" "<<endl;
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
	cout<<"������Ԫ�ص�����n"<<endl;   cin>>n;
	srand((unsigned)time(0));   //������������1���ı�һ�Σ�������ϵͳʱ�� 
	p=new int[n];
	for(int i=0;i<n;i++)
	{
		p[i]=(rand()%1001);
	}
	Sort A(p,n),B(p,n),C(p,n),D(p,n);  //��������ʼ�� 
	cout<<"The elements are:";  A.output();
	
	cout<<"��ʱ��ֹ��ѡ������"<<endl;
	A.select_sort(&mov_step,&comp_step); A.output();
    cout<<"�Ƚϴ���Ϊ��"<<comp_step<<"\t"<<"�ƶ�����Ϊ��"<<mov_step<<endl;
    
	cout<<"���������� ��"<<endl;
	int *ref=new int[n];  B.rank_sort(ref,&mov_step,&comp_step);  B.output();
	cout<<"�Ƚϴ���Ϊ��"<<comp_step<<"\t"<<"�ƶ�����Ϊ��"<<mov_step<<endl;
	
	cout<<"��ʱ��ֹ��ð���������� ��"<<endl;
	C.bubble_sort(&mov_step,&comp_step);  C.output();
	cout<<"�Ƚϴ���Ϊ��"<<comp_step<<"\t"<<"�ƶ�����Ϊ��"<<mov_step<<endl;
	
	cout<<"�������� ��"<<endl;
	D.insert_sort(&mov_step,&comp_step);  D.output();
	cout<<"�Ƚϴ���Ϊ��"<<comp_step<<"\t"<<"�ƶ�����Ϊ��"<<mov_step<<endl;
	
	delete [] p;
	return 0;
}
