#include<iostream>
#include"indexedBinarySearchTree.h"
//#include"binarySearchTree.h"
using namespace std;

int main()
{
//	binarySearchTree<int,int> bsT; 
	indexedBinarySearchTree<int,int> ibsT; 
	cout<<"please input the number of pairs:";  int n;  cin>>n;
	int *first=new int [n];
	int *second=new int [n];
	Pair<int,int> *P=new Pair<int,int> [n];
	cout<<"please input the key and value of pairs:"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>first[i];
		cin>>second[i];
		P[i].first=first[i];
		P[i].second=second[i];
		
	}
	for(int i=0;i<n;i++)
    {
    	ibsT.insert(P[i]);
	}
	ibsT.ascend();
/*	cout<<"The height is:"<<ibsT.height()<<endl;
	cout<<"Please input the index you want to find:";  cin>>n;
	if(ibsT.find(n)!=NULL)  cout<<"find succeed!"<<endl;
	else  cout<<"find failed!"<<endl;
	
	cout<<"Please input the pair's key you want to find:";  cin>>n;
	if(ibsT.find(n,true)!=NULL)  cout<<"find succeed!"<<endl;
	else  cout<<"find failed!"<<endl;*/
	
	cout<<endl<<endl;
	cout<<"please input the pair's key you want to erase:";  cin>>n;
	bsT.erase(n);
	bsT.ascend();
	cout<<"The height is:"<<bsT.height()<<endl;
	
/*	cout<<"please input the data you want to insert:";
	int key,value;  cin>>key>>value;
	Pair<int,int> temp(key,value);
	ibsT.insert(temp);
	ibsT.ascend();  cout<<endl;
	
	cout<<"please input the pair's key you want to erase:";  cin>>n;
	ibsT.erase(n,true);
	ibsT.ascend();*/
	return 0;
}
