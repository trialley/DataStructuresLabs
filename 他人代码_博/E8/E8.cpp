#include<iostream>
using namespace std;
#include"../zjslib/zjslib.h"
//若opt为0，则代表向散列表中插入x；
//    若x存在，输出Existed
//    否则输出插入桶号
//若opt为1，代表查询散列表中x是否存在；
//    若x存在，输出x桶号
//    否则输出Not Found
//若opt为2，(如果散列表中含有x)，删除x。
//    若x存在，输出x桶号
//    否则输出Delete Failed
int main(){
//	chaindic<int,char> zjs;
//	hashchaindic<int,char> zjs2;
	hashchaindic<int,int> test;
	int D = 0;
	int m = 0;
	cin >> D >> m;
	for(int i=0;i<m;i++)
	{
		int opt = 0;
		int x = 0;
		cin >> opt >> x;
		pair<int,int> tempx(x,0);
		switch(opt)
		{
			case 0:
			{
				int num_bucket = test.insert(tempx);
				if(num_bucket==-1) cout << "Existed" << endl;
				//else cout << num_bucket << endl;
				break;
			}
			case 1:
			{
				int num_bucket = test.locate(x);
				if(num_bucket==-1) cout << "Not Found" << endl;
				//else cout << num_bucket << endl;
				
				break;
			}
			case 2:
			{
				int num_bucket = test.erase(x);
				if(num_bucket==-1) cout << "Delete Failed" << endl;
				//else cout << num_bucket << endl;
				break;
			}
		}
	}
	return 0;
}


//int main(){
////	chaindic<int,char> zjs;
////	hashchaindic<int,char> zjs2;
//	hashchaindic<int,int> test;
//	int D = 0;
//	int m = 0;
//	cin >> D >> m;
//	for(int i=0;i<m;i++)
//	{
//		int opt = 0;
//		int x = 0;
//		cin >> opt >> x;
//		pair<int,int> tempx(x,0);
//		switch(opt)
//		{
//			case 0:
//			{
//				int num_bucket = test.insert(tempx);
//				if(num_bucket==-1) cout << "Existed" << endl;
//				//else cout << num_bucket << endl;
//				break;
//			}
//			case 1:
//			{
//				int num_bucket = test.locate(x);
//				if(num_bucket==-1) cout << "Not Found" << endl;
//				//else cout << num_bucket << endl;
//				break;
//			}
//			case 2:
//			{
//				int num_bucket = test.erase(x);
//				if(num_bucket==-1) cout << "Delete Failed" << endl;
//				//else cout << num_bucket << endl;
//				break;
//			}
//		}
//	}
//	return 0;
//}
