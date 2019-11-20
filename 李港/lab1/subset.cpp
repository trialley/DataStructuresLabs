#include<iostream>
using namespace std;

template<typename T>
void show(T* arr,bool* isshow,int n){
	cout<<"{";
	bool showcam=false;
	for(int i=0;i<n;i++){
		
		if(isshow[i]){
			if(showcam){
				cout<<",";
			}
			cout<<arr[i];
			showcam=true;
		}else{
			
		}

	}
	cout<<"}"<<endl;
}

template<typename T>
void subset(int i,int n,T* arr,bool* isshow){
	if(i==n+1){
		show(arr,isshow,n);
		return;
	}
	
	isshow[i-1]=false;
	subset(i+1,n,arr,isshow);
	isshow[i-1]=true;
	subset(i+1,n,arr,isshow);
	
}

 

int main(){
	int num;
	
	cout<<"请输入数字总数：" ;
	cin>>num;
	int* arr=new int[num];
	
	cout<<"请输入数字，使用空格分隔"<<endl; 
	for(int i=0;i<num;i++){
		int temp;
		cin>>temp;
		for(int j =0;j<i;j++){
			if(arr[j]==temp){
				cout<<"错误：输入了重复的数字!\n";
				return 0;
			}
		}
		arr[i]=temp;
	}
	
	cout<<"您输入了："<<endl;
	for(int i=0;i<num;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	
	
	cout<<"子集有："<<endl;
	bool* isshow=new bool[num];
	for(int i=0;i<num;i++){
		isshow[i]=true;
	}
	subset(1,num,arr,isshow);
	
	return 0;
} 
