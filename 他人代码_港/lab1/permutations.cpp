#include<iostream>
using namespace std;

/*iostream中有swap函数，在此使用自己编写的lgswap*/
template<typename T>
void lgswap(T& a,T& b){
	T temp;
	temp=a;
	a=b;
	b=temp;
}

/*
功能：全排列递归
输入：
	i：当前递归是第几层递归，也即排列到了第几个变量 
	n：总的递归层数，也即总共几个变量需要全排列 
	arr：T类型变量的指针数组
返回：无 
*/
template<typename T>
void permutation(int i,int n,T* arr ){
	
	/*如果是最后一层，则说明这是集合的一个全排列，输出数组内容并返回到上一层*/
	if(i==n){
		for(int i=0;i<n;i++){
			cout<<arr[i]<<" ";
		}
		cout<<endl;
		return;
	}
	
	/*非最后一层的递归，将当前层与剩余各层进行置换，并进入下一层递归*/
	for(int j=i;j<=n;j++){
		lgswap(arr[j-1],arr[i-1]);
		permutation(i+1,n,arr );
		lgswap(arr[j-1],arr[i-1]);
	}
}

int main(){
	int num;
	cin>>num;
	int* arr=new int[num];
	for(int i=0;i<num;i++){
		cin>>arr[i];
	}
	permutation(1,num,arr);
} 
