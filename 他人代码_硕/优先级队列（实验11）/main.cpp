#include<iostream>
#include"С����.h"
#include"������.h"
#include"huffmanNode.h"
#include <time.h>
#include<stdlib.h>
using namespace std;

int* generate_random(int size)
{
	srand((unsigned)time(0));   //������������1���ı�һ�Σ�������ϵͳʱ�� 
	int *p=new int[size+1];
	for(int i=1;i<=size;i++)
	{
		p[i]=(rand()%1001);
		cout<<"p["<<i<<"]="<<p[i]<<" ";
	}
	cout<<endl; 
	return p;
}

int main()
{
	minHeap<int> heap;
	int size,*a;
	cout<<"please input the size:";  cin>>size;
	a=new int [size+1];
	cout<<"please input the value of array��";
	for(int i=1;i<=size;i++)
	{
		cin>>a[i];
	} 
	heap.initialize(a,size);
	cout<<"the minHeap is:"<<heap<<endl;
	cout<<"erase:";   int n;   cin>>n;
	heap.erase(n);  cout<<"after erase:"<<heap<<endl;
    
	//�����Ƕ����򲿷�	
	cout<<"���������������������n"<<endl;   cin>>size;
	int *Array=generate_random(size);
	heapSort(Array,size);
	cout<<"After heap sort:";
	for(int i=1;i<size;i++)
      cout<<Array[i]<<" ";
    cout<<endl;
  
    //����������huffman���Ĳ��� 
    cout<<"please input the number of char:";   int num;  cin>>num;
    int *weight=new int[num+1];
    char *str=new char[num+1];
    cout<<"please input the data:"<<endl;
	for(int i=1;i<=num;i++)
	{
		cin>>str[i];
		cin>>weight[i];
	}
	linkedBinaryTree<int> *Htree=huffman(weight,num);
	cout<<"The huffman tree is as followed:"<<endl;
	cout<<"levelOrder:";  Htree->levelOrder(); cout<<endl;
	cout<<"preOrder:";   Htree->preOrder();  cout<<endl;
	Htree->huffmanCode(str);
  
}
// 5 5 3 2 4 1
