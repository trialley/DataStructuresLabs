#include<iostream>
using namespace std;
#include"../zjslib/zjslib.h"
//��optΪ0���������ɢ�б��в���x��
//    ��x���ڣ����Existed
//    �����������Ͱ��
//��optΪ1�������ѯɢ�б���x�Ƿ���ڣ�
//    ��x���ڣ����xͰ��
//    �������Not Found
//��optΪ2��(���ɢ�б��к���x)��ɾ��x��
//    ��x���ڣ����xͰ��
//    �������Delete Failed
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
