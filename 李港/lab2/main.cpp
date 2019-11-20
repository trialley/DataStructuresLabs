#include<iostream>
using namespace std; 

#include<cstdlib>
#include<ctime>
#define lgrand(min,max) ((rand()%(max-min+1))+min )

template<typename T>
lgswap(T A,T B){
	T TEMP=A;
	A=B;
	B=TEMP;
}

template<typename T>
class lgsorts{
	private:
		int* arr;
		int len;
	public:
		lgsorts(int n=10){
			len=n;
			arr=new int[n];
			
			for(int i=0;i<n;i++){
				arr[i]=lgrand(1,1000);
			}
			
			cout<<"排序源数组初始化完成，";
			show(0);
			cout<<endl;
		}
		void rearrange(){
			for(int i=0;i<len;i++){
				lgswap(arr[i],arr[lgrand(0,len-1)]);
				//arr[i]=len-i;
			}
			return;
			arr[0]=9;
			arr[1]=9;
			arr[2]=8;
			arr[3]=9;
			arr[4]=6;
			arr[5]=10;
			arr[6]=4;
			arr[7]=3;
			arr[8]=2;
			arr[9]=1;
			
			
		}
		show(int i){
			cout<<"第 "<<i<<" 轮循环：";
			for(int i=0;i<len;i++){
				cout<<arr[i]<<" ";
			}
			cout<<endl;
		}
		BubbleSort(){
			int cmptimes=0;		//记录比较次数 
			int movetimes=0;	//记录交换次数 
			int loop=0;			//纪录扫描次数 
			for(int j=0;j<len-1;j++){
				loop++;
				bool noswap=1;	//记录该次扫描是否有交换行为 
				
				/*单次扫描*/
				for(int i=0; i<len-j-1;i++){
					cmptimes++;
					if(arr[i]>arr[i+1]){
						movetimes++;
						
						lgswap(arr[i],arr[i+1]);
						noswap=0;
					}else{
						continue;
					}	
				}
				
				show();		//输出扫描结果 
				
				/*判断该次扫描是否有过交换行为*/
				if(noswap){
					cout<<"无可交换数据，提前停止。"<<endl;
					break;
				}
			}
			
			/*输出统计数据*/
			cout<<"扫描次数："<<loop<<" 比较次数："<<cmptimes<<" 移动次数："<<movetimes<<endl;
		}
		SelectSort(){//在未排序去选择最值，与两区交界的未排序值进行互换 
			int cmptimes=0;
			int movetimes=0;
			int loop=0;
			//i~len-1   0~i-1    
			for(int i=0;i<len;i++){
				int maxindex=len-1;//该下标从目标最低处开始，如果他一直变化，说明未排序区也排好序了 
				loop++;
				bool sorted=true;
				
				for(int j=len-1;j>i-1;j--){
					cmptimes++;
					if(arr[j]>=arr[maxindex]){
						maxindex=j;
					}else{
						sorted=false;//maxindex初值选择有讲究。需要选最小的，这样才会一直被增大，等号也算增大，因为要的就是index一直改变 
					}
				}
				
				if(sorted){
					cout<<"排序完成，提前终止！"<<endl;
					break;
				}
				
				lgswap(arr[maxindex],arr[i]);
				movetimes++;
				show(i+1);
			} 
			
			
			
			cout<<"扫描次数："<<loop<<" 比较次数："<<cmptimes<<" 移动次数："<<movetimes<<endl;
		}
		InsertSort(){
			int cmptimes=0;
			int movetimes=0;
			int loop=0;
			
			for(int i= 1;i<len;i++){ // i到len-1是未排序区域，0到i-1是已排序区域 
				int temp = arr[i];
				for(int j=i;0<j;j-- ){
					cmptimes++;
					
					if(arr[j-1]<=temp){
						break;
					}else{
						movetimes++;
						arr[j]=arr[j-1];
						arr[j-1]=temp;
					}
							
				}
					show();	
				loop++;
				
			}
			
			cout<<"扫描次数："<<loop<<" 比较次数："<<cmptimes<<" 移动次数："<<movetimes<<endl;
		}
		Rank(){
			int r[len]={0};			
			for (int i = 1; i < len; i++){
				for (int j = 0; j < i; j++){
					if (arr[j] <= arr[i]){//名次等于比他小的元素的数量加上左侧同大小元素的数量 
						r[i]++;
					}else{
						r[j]++;
					}
				}		
			}
			cout<<"排名结果："; 
			for(int i=0;i<len;i++){
				cout<<r[i]<<" ";
			}
			cout<<endl;
		}
		testall(){
			cout<<"名次排序测试----------------"<<endl;
			rearrange(); 
			Rank();
			cout<<"名次排序结束----------------"<<endl<<endl;
			
			cout<<"插入排序测试----------------"<<endl;
				rearrange(); 
			//InsertSort();
			cout<<"插入排序结束----------------"<<endl<<endl;
			
			cout<<"选择排序测试----------------"<<endl;
				rearrange(); 
			//SelectSort();
			cout<<"选择排序结束----------------"<<endl<<endl;
			
			cout<<"冒泡排序测试----------------"<<endl;
				rearrange(); 
			//BubbleSort();
			cout<<"冒泡排序结束----------------"<<endl<<endl;
		}
		
};




int main(){
	srand((int)time(0));
	lgsorts<int> s;
	s.testall(); 
	 
	return 0;
}
