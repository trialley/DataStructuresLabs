#include<iostream>
#include <time.h>
#include<stdlib.h>
#include"sortedChain.h"
#include"pair.h"
#include"hashTable.h"
#include"hashChain.h"
using namespace std;

int main()
{
	//������500�������Ȼ���ʼ����ϣ�� 
	srand((unsigned)time(0)); 
	Pair<int,int> *P_array=new Pair<int,int> [500];
	for(int i=0;i<500;i++)
	{
		P_array[i].first=(rand()%1001);
		P_array[i].second=i;
		//cout<<P_array[i]<<endl;
	}
	
	hashChain<int,int> C(961);   //499�ǲ����ڹ�ϣ������500�����������������鱾P254 
	for(int i=0;i<500;i++)
	{
		C.insert( P_array[i] );
	}
	cout<<C;
	int n; cout<<"search:";   cin>>n;
	Pair<int,int> *p=C.find(n);
	if(p!=NULL)
	   cout<<"The element is:"<<(*p)<<endl;
	else cout<<"NULL!"<<endl;
	
	cout<<"erase:";  cin>>n;
	C.erase(n);   
	p=C.find(n);
	if(p!=NULL)
	   {
	      cout<<"erase failed. "<<(*p)<<endl;  
	   }
	else cout<<"erase succeed."<<endl;
	
/*             �����Ƕ�hashChain�ĵ���               */	


/*    hashTable<int,int> B(961);
    for(int i=0;i<500;i++)
    {
    	B.insert( P_array[i] );
	}
    cout<<B<<endl;
    int n; cout<<"search:";   cin>>n;
    Pair<int,int> *p=B.find(n);
    cout<<"The element is:"<<(*p)<<endl;
    cout<<"delete:";  cin>>n;
    B.erase(n);
    
	cin>>n;
    p=B.find(n);
    cout<<p<<endl;*/
	return 0;
}
