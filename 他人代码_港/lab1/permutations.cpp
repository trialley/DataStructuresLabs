#include<iostream>
using namespace std;

/*iostream����swap�������ڴ�ʹ���Լ���д��lgswap*/
template<typename T>
void lgswap(T& a,T& b){
	T temp;
	temp=a;
	a=b;
	b=temp;
}

/*
���ܣ�ȫ���еݹ�
���룺
	i����ǰ�ݹ��ǵڼ���ݹ飬Ҳ�����е��˵ڼ������� 
	n���ܵĵݹ������Ҳ���ܹ�����������Ҫȫ���� 
	arr��T���ͱ�����ָ������
���أ��� 
*/
template<typename T>
void permutation(int i,int n,T* arr ){
	
	/*��������һ�㣬��˵�����Ǽ��ϵ�һ��ȫ���У�����������ݲ����ص���һ��*/
	if(i==n){
		for(int i=0;i<n;i++){
			cout<<arr[i]<<" ";
		}
		cout<<endl;
		return;
	}
	
	/*�����һ��ĵݹ飬����ǰ����ʣ���������û�����������һ��ݹ�*/
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
