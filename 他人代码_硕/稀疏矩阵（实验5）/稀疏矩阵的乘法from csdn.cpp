#include"stdio.h"
#include"stdlib.h"
typedef int ElemType;
typedef struct{
	int row;    //此处的行列值为真实值，都有从1开始没有第0行和第0列
	int col; 
	ElemType value;   //矩阵第row行第col列对应的值
}Triple;
 
typedef struct{
	Triple *data; //非零三元组表
	int row_num;      //矩阵的总行数
	int col_num;	//矩阵的总列数
	int non_zero;	//矩阵总的非零值的个数
}TSMatrix;

//当第一个矩阵的列值等于第二个矩阵的行值时，对这两个矩阵进行相乘的运算并将结果存在result矩阵中
void MultSMatrix( TSMatrix *matrix1, TSMatrix *matrix2, TSMatrix *result )
{	
	int i = 0;
	int j = 0;
	int k = 0;
	int q;
 
	if( matrix1->col_num != matrix2->row_num ){  //如果两个矩阵的行数或者列数不相同
		printf( "AddSMatrix Error: the colum of the first matrix and therow of the second matrix is different!\n" );
	}
	else{   //否则为结果矩阵分配内存空间
		result->data = ( Triple *)malloc( sizeof( Triple ) * ( matrix1->row_num * matrix2->col_num ) ); 
		if( !result->data )   //分配失败，则报错
			printf( "AddSMatrix Error:OVERFLOW!\n" );
		else{         //分配空间成功
			result->row_num  = matrix1->row_num;//设置结果矩阵的行值为第一个矩阵的行值
			result->col_num  = matrix2->col_num;//设置结果矩阵的行值为第二个矩阵的列值
			for( k = 0; k < matrix1->row_num * matrix2->col_num; k++ )
				( result->data + k )->value = 0;
			k = 0;
			while( i < matrix1->non_zero ){ //当两个矩阵的元素都没有处理完时
				for( j = 0; j < matrix1->non_zero; j++ ){
				//如果matrix1的第i个元素的列值与matrix2的第j个元素的行值相同，则进行相乘,相当于a[row1][col2] = b[row1][rc]*c[rc][col2]
					if( ( matrix1->data + i )->col == ( matrix2->data + j )->row ){
						( result->data + k )->row = ( matrix1->data + i )->row;//result的第k个元素的行值为第一个矩阵的第i个元素对应的行值
						( result->data + k )->col = ( matrix2->data + j )->col;//result的第k个元素的列值为第二个矩阵的第j个元素对应的列值
					//result的第k个元素的value值为第一个矩阵的第i个元素对应的value值与第二个矩阵的第j个元素对应的value值相乘的结果
						( result->data + k )->value = ( matrix1->data + i )->value * ( matrix2->data + j )->value;  
					//用当前result的第k个元素与前k-1个元素的行列值进行比较：若相等，将第k项对应的value值加到第q项
					//相当于a[row1][col2] = b[row1][rc]*c[rc][col2]中对rc从1到col1( = row2 )的求和
						for( q = 0; q < k; q++ ){
							if( ( result->data + k )->row == ( result->data + q )->row && ( result->data + k )->col == ( result->data + q )->col ){
								( result->data + q )->value += ( result->data + k )->value;  
								k--; //将k-1的目的是与下面的k+1对应，使k值不变，因为相等时将该项的结果与加到之前的结果上，故不需要生成新的项
							}
						}
						k++;
					}
				}
				i++;
			}
			result->non_zero = k;
		//重新为result->data分配适合大小的存储空间
			result->data = ( Triple *)realloc( result->data, sizeof( Triple ) * ( result->non_zero ) );
			ReorderSMatrix( result );
		}
	}
}

