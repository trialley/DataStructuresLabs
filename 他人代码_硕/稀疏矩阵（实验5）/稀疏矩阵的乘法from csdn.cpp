#include"stdio.h"
#include"stdlib.h"
typedef int ElemType;
typedef struct{
	int row;    //�˴�������ֵΪ��ʵֵ�����д�1��ʼû�е�0�к͵�0��
	int col; 
	ElemType value;   //�����row�е�col�ж�Ӧ��ֵ
}Triple;
 
typedef struct{
	Triple *data; //������Ԫ���
	int row_num;      //�����������
	int col_num;	//�����������
	int non_zero;	//�����ܵķ���ֵ�ĸ���
}TSMatrix;

//����һ���������ֵ���ڵڶ����������ֵʱ�������������������˵����㲢���������result������
void MultSMatrix( TSMatrix *matrix1, TSMatrix *matrix2, TSMatrix *result )
{	
	int i = 0;
	int j = 0;
	int k = 0;
	int q;
 
	if( matrix1->col_num != matrix2->row_num ){  //����������������������������ͬ
		printf( "AddSMatrix Error: the colum of the first matrix and therow of the second matrix is different!\n" );
	}
	else{   //����Ϊ�����������ڴ�ռ�
		result->data = ( Triple *)malloc( sizeof( Triple ) * ( matrix1->row_num * matrix2->col_num ) ); 
		if( !result->data )   //����ʧ�ܣ��򱨴�
			printf( "AddSMatrix Error:OVERFLOW!\n" );
		else{         //����ռ�ɹ�
			result->row_num  = matrix1->row_num;//���ý���������ֵΪ��һ���������ֵ
			result->col_num  = matrix2->col_num;//���ý���������ֵΪ�ڶ����������ֵ
			for( k = 0; k < matrix1->row_num * matrix2->col_num; k++ )
				( result->data + k )->value = 0;
			k = 0;
			while( i < matrix1->non_zero ){ //�����������Ԫ�ض�û�д�����ʱ
				for( j = 0; j < matrix1->non_zero; j++ ){
				//���matrix1�ĵ�i��Ԫ�ص���ֵ��matrix2�ĵ�j��Ԫ�ص���ֵ��ͬ����������,�൱��a[row1][col2] = b[row1][rc]*c[rc][col2]
					if( ( matrix1->data + i )->col == ( matrix2->data + j )->row ){
						( result->data + k )->row = ( matrix1->data + i )->row;//result�ĵ�k��Ԫ�ص���ֵΪ��һ������ĵ�i��Ԫ�ض�Ӧ����ֵ
						( result->data + k )->col = ( matrix2->data + j )->col;//result�ĵ�k��Ԫ�ص���ֵΪ�ڶ�������ĵ�j��Ԫ�ض�Ӧ����ֵ
					//result�ĵ�k��Ԫ�ص�valueֵΪ��һ������ĵ�i��Ԫ�ض�Ӧ��valueֵ��ڶ�������ĵ�j��Ԫ�ض�Ӧ��valueֵ��˵Ľ��
						( result->data + k )->value = ( matrix1->data + i )->value * ( matrix2->data + j )->value;  
					//�õ�ǰresult�ĵ�k��Ԫ����ǰk-1��Ԫ�ص�����ֵ���бȽϣ�����ȣ�����k���Ӧ��valueֵ�ӵ���q��
					//�൱��a[row1][col2] = b[row1][rc]*c[rc][col2]�ж�rc��1��col1( = row2 )�����
						for( q = 0; q < k; q++ ){
							if( ( result->data + k )->row == ( result->data + q )->row && ( result->data + k )->col == ( result->data + q )->col ){
								( result->data + q )->value += ( result->data + k )->value;  
								k--; //��k-1��Ŀ�����������k+1��Ӧ��ʹkֵ���䣬��Ϊ���ʱ������Ľ����ӵ�֮ǰ�Ľ���ϣ��ʲ���Ҫ�����µ���
							}
						}
						k++;
					}
				}
				i++;
			}
			result->non_zero = k;
		//����Ϊresult->data�����ʺϴ�С�Ĵ洢�ռ�
			result->data = ( Triple *)realloc( result->data, sizeof( Triple ) * ( result->non_zero ) );
			ReorderSMatrix( result );
		}
	}
}

