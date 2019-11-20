#include<stdio.h>
#include<time.h>
template <typename T>
void diy_swap(T &a,T &b){	//Ϊ�˷���,�Ƚ���һ���Զ����swap����
	if(&a==&b)return;
    T temp=a;
    a=b;
    b=temp;
}
template<typename T>
class Smatrix{
	public:
	typedef struct triple_group{
		int x;
		int y;
		T value;
	}_unit;
	private:
		int x;
		int y;
		int size;
		_unit* unit;
	public:
		Smatrix(){
			x = 0;
			y = 0;
			unit = NULL;
			size = 0;
		}
		Smatrix(T**in,int _x,int _y){
			x = _x;
			y = _y;
			size = 0;
			int i = 0;
			for(;i<x;i++)
				for(int j=0;j<y;j++)
					if(in[i][j]!=0)size++;
			unit = new _unit[size];
			int k = 0;
			i = 0;
			for(;i<x;i++)
				for(int j=0;j<y;j++)
					if(in[i][j]!=0){
						unit[k].x=i+1;
						unit[k].y=j+1;
						unit[k].value = in[i][j];
						k++;
					}
		}
		Smatrix(T**in,int _x,int _y,int num_unzero){
			x = _x;
			y = _y;
			size = num_unzero;
			unit = new _unit[size];
			int k = 0;
			int i = 0;
			for(;i<x;i++)
				for(int j=0;j<y;j++)
					if(in[i][j]!=0){
						unit[k].x=i+1;
						unit[k].y=j+1;
						unit[k].value = in[i][j];
						k++;
					}
		}
		Smatrix(FILE*fp){
			size = 0;
			fscanf(fp,"%d",&x);
			fscanf(fp,"%d",&y);
//			printf("x=%d\ty=%d\n",x,y);
			int num_element = x*y;
			int temp;
			for(int i=0;i<num_element;i++){
				fscanf(fp,"%d",&temp);
				if(temp!=0) size++;
			}
			rewind(fp);
			fscanf(fp,"%d",&temp);
			fscanf(fp,"%d",&temp);
			unit = new _unit[size];
			int k = 0;
			for(int i=0;i<num_element;i++){
				fscanf(fp,"%d",&temp);
				if(temp!=0){
					unit[k].value = temp;
					unit[k].x = i/x+1;
					unit[k].y = i%y+1;
					k++;
				}
			}
			fclose(fp);
		}
		Smatrix(const Smatrix& copy){
			x = copy.x;
			y = copy.y;
			size = copy.size;
			unit = new _unit[size];
			int i = 0;
			for(;i<size;i++){
				unit[i].x = copy.unit[i].x;
				unit[i].y = copy.unit[i].y;
				unit[i].value = copy.unit[i].value;
			}
		}
		Smatrix operator=(const Smatrix& right){
			x = right.x;
			y = right.y;
			size = right.size;
			unit = new _unit[size];
			int i = 0;
			for(;i<size;i++){
				unit[i].x = right.unit[i].x;
				unit[i].y = right.unit[i].y;
				unit[i].value = right.unit[i].value;
			}
			return *this;
		}
		friend Smatrix operator+(const Smatrix& left,const Smatrix& right){
			Smatrix<int> t;
			int num_duplicated_unit = 0;
			t.x = left.x;
			t.y = left.y;
			for(int i=0;i<left.size;i++)
				for(int j=0;j<right.size;j++)
					if(left.unit[i].x==right.unit[j].x&&left.unit[i].y==right.unit[j].y) num_duplicated_unit++;
			t.size = left.size + right.size - num_duplicated_unit;
			t.unit = new _unit[t.size];
			int k = 0;
			for(int i=0;i<left.size;i++){
				t.unit[k].x = left.unit[i].x;
				t.unit[k].y = left.unit[i].y;
				t.unit[k].value = left.unit[i].value;
				for(int j=0;j<right.size;j++)
					if(left.unit[i].x==right.unit[j].x&&left.unit[i].y==right.unit[j].y) t.unit[k].value = t.unit[k].value + right.unit[i].value;
				k++;
			}
			bool judge = false;
			for(int j=0;j<right.size;j++){
				for(int i=0;i<left.size;i++)
					if(left.unit[i].x==right.unit[j].x&&left.unit[i].y==right.unit[j].y) judge = true;
				if(judge==false){
					t.unit[k].x = right.unit[j].x;
					t.unit[k].y = right.unit[j].y;
					t.unit[k].value = right.unit[j].value;
					k++;
				}
			}
			return t;
		}
// 		friend Smatrix operator*(const Smatrix& left,const Smatrix& right){
// 			if(left.y!=right.x) printf("error\n");
// 			Smatrix<int> t;
// 			t.size = 0;
// 			t.x = left.x;
// 			t.y = right.y;
// 			for(int i=0;i<left.size;i++)
// 				for(int j=0;j<right.size;j++)
// 					if(left.unit[i].x==right.unit[j].y){
// 						t.size++;
// 						break;
// 	 				}
// 			t.unit = new _unit[t.size];
// //			printf("1\n");
// 			for(int i=0;i<t.size;i++)
// 				t.unit[i].value = 0;
// //			printf("2\n");
// 			int k=0;
// 			for(int i=0;i<left.size;i++)
// 				for(int j=0;j<right.size;j++)
// 					if(left.unit[i].y==right.unit[j].x){
// 						t.unit[k].x = left.unit[i].x;
// 						t.unit[k].y = right.unit[j].y;
// 						t.unit[k].value = t.unit[k].value + (left.unit[i].value*right.unit[j].value);
// 						k++;
// 	 				}
// //			printf("%d %d %d\n",t.x,t.y,t.size);
// 			return t;
// 		}
		friend Smatrix operator*(const Smatrix& left,const Smatrix& right){
			int i = 0;
			int j = 0;
			int k = 0;
			int q;
			Smatrix result;
			if( left.y != right.x ){  //����������������������������ͬ
				printf( "Error: the y of the first matrix and the x of the second matrix is different!\n" );
				return result;
			}
			else{   //����Ϊ�����������ڴ�ռ�
				result.unit = new _unit[left.x*right.y];
				if( !result.unit ){
					printf( "Error: MemoryError!\n" );
					return result;
				}
				else{         //����ռ�ɹ�
					result.x  = left.x;//���ý���������ֵΪ��һ���������ֵ
					result.y  = right.y;//���ý���������ֵΪ�ڶ����������ֵ
					for( k = 0; k < left.x * right.y; k++ )
						result.unit[k].value = 0;
					k = 0;
					while( i < left.size ){ //�����������Ԫ�ض�û�д�����ʱ
						for( j = 0; j < left.size; j++ ){
						//���left�ĵ�i��Ԫ�ص���ֵ��right�ĵ�j��Ԫ�ص���ֵ��ͬ����������,�൱��a[x1][y2] = b[x1][rc]*c[rc][y2]
							if( left.unit[i].y == right.unit[j].x ){
								result.unit[k].x = left.unit[i].x;//result�ĵ�k��Ԫ�ص���ֵΪ��һ������ĵ�i��Ԫ�ض�Ӧ����ֵ
								result.unit[k].y = right.unit[j].y;//result�ĵ�k��Ԫ�ص���ֵΪ�ڶ�������ĵ�j��Ԫ�ض�Ӧ����ֵ
							//result�ĵ�k��Ԫ�ص�valueֵΪ��һ������ĵ�i��Ԫ�ض�Ӧ��valueֵ��ڶ�������ĵ�j��Ԫ�ض�Ӧ��valueֵ��˵Ľ��
								result.unit[k].value = left.unit[i].value * right.unit[j].value;  
							//�õ�ǰresult�ĵ�k��Ԫ����ǰk-1��Ԫ�ص�����ֵ���бȽϣ�����ȣ�����k���Ӧ��valueֵ�ӵ���q��
							//�൱��a[x1][y2] = b[x1][rc]*c[rc][y2]�ж�rc��1��y1( = x2 )�����
								for( q = 0; q < k; q++ ){
									if( result.unit[k].x == result.unit[q].x && result.unit[k].y == result.unit[q].y ){
										result.unit[q].value += result.unit[k].value;
										k--; //��k-1��Ŀ�����������k+1��Ӧ��ʹkֵ���䣬��Ϊ���ʱ������Ľ����ӵ�֮ǰ�Ľ���ϣ��ʲ���Ҫ�����µ���
									}
								}
								k++;
							}
						}
						i++;
					}
					result.size = k;
				//����Ϊresult.unit�����ʺϴ�С�Ĵ洢�ռ�
					//result.unit = ( _unit *)realloc( result.unit, sizeof( _unit ) * ( result.size ) );
					//ReorderSMatrix( result );
				}
				return result;
			}
		}
		int output(){
//			T out[x][y];    //1000*1000ʱ�ռ�����ʧ�ܣ�output˼·Ҫ�ģ�
//			printf("insert\n"); //��仰�ʹ�ӡ��������
//			for(int i=0;i<x;i++)
//				for(int j=0;j<y;j++)
//					out[i][j] = 0;
//			printf("5\n");
//			for(int k=0;k<size;k++){
//				int i = unit[k].x;
//				int j = unit[k].y;
//				out[i][j] = unit[k].value;
//	 		}
//	 		printf("6\n");
	/////////ԭ�������
//			bool waitforprint = true;
//			for(int i=1;i<=x;i++){
//				for(int j=1;j<=y;j++){
//					waitforprint = true;
//					for(int k=0;k<size;k++){
//						if(waitforprint){
//							if(i==unit[k].x&&j==unit[k].y){
//								printf("%d ",unit[k].value);   //¼�����ֳ�����λ�ͻ᲻����
//								waitforprint = false;
//							}
//						}
//						else break;
//					}
//					if(waitforprint)printf("%d ",0);
//				}
//				printf("\n");
//			}
	//////////�Ż�����������
			for(int i=0;i<size;i++)
				for(int j=0;j<size-1-i;j++)	//�˴��� j<length-1-iȷ����ʱֹͣ
					if(unit[j].y>unit[j+1].y){
						diy_swap(unit[j].x,unit[j+1].x);
						diy_swap(unit[j].y,unit[j+1].y);
						diy_swap(unit[j].value,unit[j+1].value);
					}
			for(int i=0;i<size;i++)
				for(int j=0;j<size-1-i;j++)	//�˴��� j<length-1-iȷ����ʱֹͣ
					if(unit[j].x>unit[j+1].x){
						diy_swap(unit[j].x,unit[j+1].x);
						diy_swap(unit[j].y,unit[j+1].y);
						diy_swap(unit[j].value,unit[j+1].value);
					}
			printf("%d\t%d\n",x,y);
    		int  k = 0 ;
   			for (int i = 1 ; i <= x;++i){
        		for (int j = 1 ; j <= y;++j){
            		if ( (i == unit[k].x) && (j == unit[k].y) ){
                		printf("%4d\t",unit[k].value);
                		k++;
					}
            		else printf("%4d\t",0);
        		}
       			printf("\n");
    		}
		}
		int foutput(FILE*fp){
//			bool waitforprint = true;
//			for(int i=1;i<=x;i++){
//				for(int j=1;j<=y;j++){
//					waitforprint = true;
//					for(int k=0;k<size;k++){
//						if(waitforprint){
//							if(i==unit[k].x&&j==unit[k].y){
//								fprintf(fp,"%d ",unit[k].value);
//								waitforprint = false;
//							}
//						}
//						else break;
//					}
//					if(waitforprint)fprintf(fp,"%d ",0);
//				}
//				fprintf(fp,"\n");
//				printf("Completed:%.2f\n",(float)i/10.0);   //�ȴ�ʱ��̫�������������������ı���������
//			}
			//������,���ж�������
			for(int i=0;i<size;i++)
				for(int j=0;j<size-1-i;j++)	//�˴��� j<length-1-iȷ����ʱֹͣ
					if(unit[j].y>unit[j+1].y){
						diy_swap(unit[j].x,unit[j+1].x);
						diy_swap(unit[j].y,unit[j+1].y);
						diy_swap(unit[j].value,unit[j+1].value);
					}
			for(int i=0;i<size;i++)
				for(int j=0;j<size-1-i;j++)	//�˴��� j<length-1-iȷ����ʱֹͣ
					if(unit[j].x>unit[j+1].x){
						diy_swap(unit[j].x,unit[j+1].x);
						diy_swap(unit[j].y,unit[j+1].y);
						diy_swap(unit[j].value,unit[j+1].value);
					}
			//�����
    		int  k = 0 ;
   			for (int i = 1 ; i <= x;++i)
			{
        		for (int j = 1 ; j <= y;++j)
				{
            		if ( (i == unit[k].x) && (j == unit[k].y) )
					{
                		fprintf(fp,"%d ",unit[k].value);
                		k++;
					}
            		else fprintf(fp,"0 ");
        		}
       			fprintf(fp,"\n");
    		}
			fclose(fp);
		}
		int output_base(){
			printf("x=%d y=%d size=%d\n",x,y,size);
		}
		int output_unit(){
			printf("x=%d y=%d size=%d\n",x,y,size);
			for(int i=0;i<size;i++)
				printf("%d:\t%8d\t%8d\t%8d\n",i+1,unit[i].x,unit[i].y,unit[i].value);
			printf("E--------N--------D\n");
		}
};

//int main(){   //�ļ�¼���д����
////	int a[3][4];
////	for(int i=0;i<3;i++)
////				for(int j=0;j<4;j++)
////					a[i][j] = i+j;
////	Smatrix<int> t(a,3,4);
////	t.output(); //˵�����캯����output��ȷ
//	
////���Դ��ļ�����Բ��ԡ�
//	FILE *fpin = fopen("data_structure_ex5_1000_1000.in","r+"); //�Զ���ʽ���ļ�
//	Smatrix<int> t2(fpin);
//	FILE *fpout = fopen("data_structure_ex5_1000_1000.out","w+");
//	t2.foutput(fpout);     //�ҵ������ļ��������������һ��fclose��
//	return 0;
//}

//int main(){   //����¼�����
//int x,y;
//scanf("%d%d",&x,&y);
//int**arr = new int*[x];
//for(int i=0;i<x;i++)
//	arr[i] = new int[y];
//for(int i=0;i<x;i++)
//	for(int j=0;j<y;j++)
//		scanf("%d",&arr[i][j]);
//Smatrix<int> t(arr,x,y);
//t.output();
//}

int main(){   //����˷�����
//������ȷ����˷��Ķ��塣
//��������ij = ������ik*�Ҿ����kj��k��0��P��PΪ��������ȵ�����
//L[M][P]*R[P][N]
int x1,y1;
scanf("%d%d",&x1,&y1);
int**left = new int*[x1];
for(int i=0;i<x1;i++)
	left[i] = new int[y1];
for(int i=0;i<x1;i++)
	for(int j=0;j<y1;j++)
		scanf("%d",&left[i][j]);
int x2,y2;
scanf("%d%d",&x2,&y2);
int**right = new int*[x2];
for(int i=0;i<x2;i++)
	right[i] = new int[y2];
for(int i=0;i<x2;i++)
	for(int j=0;j<y2;j++)
		scanf("%d",&right[i][j]);

Smatrix<int> t1(left,x1,y1);
Smatrix<int> t2(right,x2,y2);
(t1 + t2).output();
}

//int main(){     //�������ԣ������
//	FILE *fpin1 = fopen("data_structure_ex5_1000_1000_left.in","r+"); //�Զ���ʽ���ļ�
//	Smatrix<int> t1(fpin1);
//	FILE *fpin2 = fopen("data_structure_ex5_1000_1000_right.in","r+"); //�Զ���ʽ���ļ�
//	Smatrix<int> t2(fpin2);     //0.49
//	Smatrix<int> t3(t1*t2);
////	(t1*t2).output();                     //0.48 0.47 0.48 0.50 0.48	//36s
//	FILE *fpfout1 = fopen("zjs.out","w+");
//	t3.foutput(fpfout1);
////	t1.output_base();
////	t2.output_base();
////	t3.output_base();
////	t1.output_unit();
////	t2.output_unit();
////	t3.output_unit();
//	return 0;
//}
