#include<iostream>
using namespace std;
#include<stdlib.h>
#pragma warning(disable:4996)
using namespace std;

template<class T>
class sparseMatrix {
public:
	typedef enum { index_out_of_range }err;
	typedef struct OLNode {
		int row;    //此处的行列值为真实值，都有从1开始没有第0行和第0列
		int col;
		T value;   //矩阵第row行第col列对应的值
		struct OLNode* right;
		struct OLNode* down;
	}OLNode;

	typedef struct {
		OLNode* rhead;
		OLNode* chead;
		int row_num;      //矩阵的总行数
		int col_num;	//矩阵的总列数
		int non_zero;	//矩阵总的非零值的个数
	}CrossList;
private:
	CrossList* _matrix;
	bool _inited;
	//对行链表按列递增的顺序进行排序
	void Increse_row ( OLNode* List_RHead ) {
		OLNode* current;
		OLNode* nex;
		OLNode* pre;
		int count = 0;
		int i, j;

		current = List_RHead->right;
		while ( current ) {		//统计当前列表的项数
			count++;
			current = current->right;
		}
		for ( i = 1; i < count; i++ ) {  //冒泡法进行排序
			current = List_RHead->right;
			pre = List_RHead->right;
			for ( j = 0; j < count - i; j++ ) {
				nex = current->right;
				if ( current->col > nex->col ) {
					current->right = nex->right;
					nex->right = current;
					if ( current == List_RHead->right ) {
						List_RHead->right = nex;
						pre = List_RHead->right;
					} else {
						pre->right = nex;
						pre = pre->right;
					}

				} else {
					pre = current;
					current = nex;
				}
			}
		}
	}

	//将列链表按照行递增的顺序进行排序
	void Increse_col ( OLNode* List_CHead ) {
		OLNode* current;
		OLNode* nex;
		OLNode* pre;
		int count = 0;
		int i, j;

		current = List_CHead->down;
		while ( current ) {  //统计当前列表的项数
			count++;
			current = current->down;
		}
		for ( i = 1; i < count; i++ ) {//冒泡法进行排序
			current = List_CHead->down;
			pre = List_CHead->down;
			for ( j = 0; j < count - i; j++ ) {
				nex = current->down;
				if ( current->row > nex->row ) {
					current->down = nex->down;
					nex->down = current;
					if ( current == List_CHead->down ) {
						List_CHead->down = nex;
						pre = List_CHead->down;
					} else {
						pre->down = nex;
						pre = pre->down;
					}

				} else {
					pre = current;
					current = nex;
				}
			}
		}
	}
	//将current插入到其对应的行链表的合适位置，使行链表的元素按行号递增顺序排列				
	void Insert_R ( OLNode* rhead, OLNode* current ) {
		if ( ( rhead + current->row )->right == nullptr ) {
			( rhead + current->row )->right = current;
		} else {	    //将当前项插入到对应行链表的第一项，并对其进行排序
			current->right = ( rhead + current->row )->right;
			( rhead + current->row )->right = current;
			Increse_row ( rhead + current->row );
		}
	}

	//将current插入到其对应的列链表的合适位置，使列链表的元素按列号递增顺序排列
	void Insert_C ( OLNode* chead, OLNode* current ) {
		if ( ( chead + current->col )->down == nullptr ) {
			( chead + current->col )->down = current;
		} else {	    //将当前项插入到对应行链表的第一项，并对其进行排序
			current->down = ( chead + current->col )->down;
			( chead + current->col )->down = current;
			Increse_col ( chead + current->col );
		}
	}
	//为十字链表型的稀疏矩阵分配行列链表的头的空间
	int _malloc_head ( CrossList* temp) {
		int i;
		temp->rhead = (OLNode*)malloc ( sizeof ( OLNode ) * ( temp->row_num + 1 ) );   //为矩阵的行列链表的头指针分配空间
		temp->chead = (OLNode*)malloc ( sizeof ( OLNode ) * ( temp->col_num + 1 ) );
		if ( !temp->rhead || !temp->chead ) {  //分配存储空间失败，报错并结束程序执行
			return false;
		}
		for ( i = 0; i <= temp->row_num; i++ ) {//对行链表的头进行初始化
			( temp->rhead + i )->right = nullptr;
			( temp->rhead + i )->down = nullptr;

		}
		for ( i = 0; i <= temp->col_num; i++ ) {//对列链表的头进行初始化
			( temp->chead + i )->right = nullptr;
			( temp->chead + i )->down = nullptr;
		}
		return true;
	}
	int _malloc_head () {
		int i;
		_matrix->rhead = (OLNode*)malloc ( sizeof ( OLNode ) * ( _matrix->row_num + 1 ) );   //为矩阵的行列链表的头指针分配空间
		_matrix->chead = (OLNode*)malloc ( sizeof ( OLNode ) * ( _matrix->col_num + 1 ) );
		if ( !_matrix->rhead || !_matrix->chead ) {  //分配存储空间失败，报错并结束程序执行
			return false;
		}
		for ( i = 0; i <= _matrix->row_num; i++ ) {//对行链表的头进行初始化
			( _matrix->rhead + i )->right = nullptr;
			( _matrix->rhead + i )->down = nullptr;

		}
		for ( i = 0; i <= _matrix->col_num; i++ ) {//对列链表的头进行初始化
			( _matrix->chead + i )->right = nullptr;
			( _matrix->chead + i )->down = nullptr;
		}
		return true;
	}
	//按行销毁稀疏矩阵
	void _destroy () {
		int i;
		OLNode* current;

		current = _matrix->rhead;
		for ( i = 1; i <= _matrix->row_num; i++ ) {  //按行逐个释放为矩阵项分配的空间
			current = ( _matrix->rhead + i )->right;
			while ( current ) {
				( _matrix->rhead + i )->right = ( _matrix->rhead + i )->right->right;
				free ( current );
				current = ( _matrix->rhead + i )->right;
			}
		}
		free ( _matrix->rhead );//释放为行链表头分配的空间
		free ( _matrix->chead );//释放为列链表头分配的空间
	}
public:
	sparseMatrix () {
		_matrix = new CrossList;
		_inited = false;
		return;
	}
	const sparseMatrix& operator = ( const sparseMatrix& in ) {

		_inited = true;
		_matrix = new CrossList;

		CrossList* source = in._matrix;
		int i;
		OLNode* current;
		OLNode* sur_cur;

		_matrix->row_num = source->row_num;
		_matrix->col_num = source->col_num;
		_matrix->non_zero = source->non_zero;
		_malloc_head ();

		for ( i = 1; i <= source->row_num; i++ ) {   //分配存储空间成功
			sur_cur = ( source->rhead + i )->right;
			while ( sur_cur ) {
				current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
				if ( !current ) {						 //分配存储空间失败，报错并结束程序执行
					printf ( "CopySMatrix_OL Error: OVERFLOW\n" );
					exit ( EXIT_FAILURE );
				}

				*current = *sur_cur;        //将source中的当前项的值赋给current
				current->right = nullptr;		//初始化将current的right和down指针
				current->down = nullptr;

				Insert_R ( _matrix->rhead, current ); //将current插入_matrix的适当的行列位置
				Insert_C ( _matrix->chead, current );
				sur_cur = sur_cur->right;			//继续复制下一项

			}
		}
		return *this;
	}
	sparseMatrix ( const sparseMatrix& in ) {
		//if ( _inited ) {
		//	clear ();
		//	_destroy ();
		//}
		_inited = true;
		_matrix = new CrossList;

		CrossList* source = in._matrix;
		int i;
		OLNode* current;
		OLNode* sur_cur;

		_matrix->row_num = source->row_num;
		_matrix->col_num = source->col_num;
		_matrix->non_zero = source->non_zero;
		_malloc_head ();

		for ( i = 1; i <= source->row_num; i++ ) {   //分配存储空间成功
			sur_cur = ( source->rhead + i )->right;
			while ( sur_cur ) {
				current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
				if ( !current ) {						 //分配存储空间失败，报错并结束程序执行
					printf ( "CopySMatrix_OL Error: OVERFLOW\n" );
					exit ( EXIT_FAILURE );
				}

				*current = *sur_cur;        //将source中的当前项的值赋给current
				current->right = nullptr;		//初始化将current的right和down指针
				current->down = nullptr;

				Insert_R ( _matrix->rhead, current ); //将current插入_matrix的适当的行列位置
				Insert_C ( _matrix->chead, current );
				sur_cur = sur_cur->right;			//继续复制下一项

			}
		}
	}


	//创建稀疏矩阵，矩阵元素从第一行第一列开始没有第0行和第0列，矩阵的对应值的行列值即为实际的行列值
	void init ( istream& rcin ) {
		if ( _inited ) {
			_destroy ();
		}
		_inited = true;

		rcin >> _matrix->row_num >> _matrix->col_num;
		_malloc_head ();

		int no_zero_num = 0;
		OLNode* current;
		for ( size_t i = 1; i <= _matrix->row_num; i++ ) {
			for ( size_t j = 1; j <= _matrix->col_num; j++ ) {
				T tvalue;
				rcin >> tvalue;
				if ( tvalue == 0 ) {
					continue;
				} else {				//分配存储空间成功，以（行，列，值）的形式逐个输入矩阵的值
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
					current->down = nullptr;							//将current的down和right都初始化为nullptr
					current->right = nullptr;

					current->row = i;
					current->col = j;
					current->value = tvalue;

					if ( current->row <= 0 || current->row > _matrix->row_num ||
						current->col > _matrix->col_num || current->col <= 0 ) {
						throw index_out_of_range;
					}
					//将current插入到对应的行列链表的合适的位置
					Insert_R ( _matrix->rhead, current );
					Insert_C ( _matrix->chead, current );
					no_zero_num++;
				}
			}
		}
		_matrix->non_zero = no_zero_num;
	}

	//以三元组表（行，列，值）的形式打印稀疏矩阵
	void show ( ostream& oout )const {
		OLNode* current;

		if ( _matrix->non_zero == 0 ) {
			for ( int i = 1; i <= _matrix->row_num; i++ ) {
				for ( int j = 1; j <= _matrix->col_num; j++ ) {
					cout << "0 ";
				}
				oout << endl;
			}
		} else {

			for ( int i = 1; i <= _matrix->row_num; i++ ) {  //按行进行打印
				current = ( _matrix->rhead + i )->right;
				int j0 = 1;
				while ( current ) {
					while(j0 < current->col) {
						cout << "0 ";
						j0++;
					}
					oout << current->value << " ";
					j0 = current->col+1;
					current = current->right;
				}
				for ( ; j0 < _matrix->col_num; j0++ ) {
					cout << "0 ";
				}
				oout << endl;
			}
		}
	}
	//按行清空矩阵
	void clear () {
		int i;
		OLNode* current;

		current = _matrix->rhead;
		for ( i = 1; i <= _matrix->row_num; i++ ) {  //按行逐个释放为矩阵项分配的空间
			current = ( _matrix->rhead + i )->right;
			while ( current ) {
				( _matrix->rhead + i )->right = ( _matrix->rhead + i )->right->right;
				free ( current );
				current = ( _matrix->rhead + i )->right;
			}
		}
		for ( i = 0; i <= _matrix->row_num; i++ ) {//清空行链表的头
			( _matrix->rhead + i )->right = nullptr;
			( _matrix->rhead + i )->down = nullptr;

		}
		for ( i = 0; i <= _matrix->col_num; i++ ) {//清空列链表的头
			( _matrix->chead + i )->right = nullptr;
			( _matrix->chead + i )->down = nullptr;
		}

	}



	//当两个矩阵行列值相同时，对其进行加法运算，并将相加的结果存储到result中
	const sparseMatrix operator + (const sparseMatrix& rightin ) {
		sparseMatrix temp;
		CrossList* matrix1 = _matrix;
		CrossList* matrix2 = rightin._matrix;
		CrossList* result = temp._matrix;
		int i;
		int k;
		OLNode* current;
		OLNode* current1;
		OLNode* current2;
		if ( matrix1->row_num != matrix2->row_num || matrix1->col_num != matrix2->col_num ) {  //如果两个矩阵的行数或者列数不相同
			printf ( "AddSMatrix Error: the row or the colum of the matrixs is different!\n" );
		} else {

			result->row_num = matrix1->row_num;//结果矩阵的总行数和总列数等于任一个矩阵的总行数和总列数
			result->col_num = matrix1->col_num;
			//结果矩阵分配内存空间
			if ( !_malloc_head ( result ) ) {
				printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
				exit ( EXIT_FAILURE );
			}
			i = 1;
			k = 0;//每插入到结果矩阵中一个矩阵项，k就增加1，用于统计结果矩阵的非零值的个数
			while ( i <= matrix1->row_num ) {     //按行进行运算
				current1 = ( matrix1->rhead + i )->right;
				current2 = ( matrix2->rhead + i )->right;
				while ( current1 && current2 ) {//当两个行链表的元素都还没有运算完毕时
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
					if ( !current ) {  //分配存储空间失败，报错并结束程序执行
						printf ( "AddSMatrix_OL Error: OVERFLOW\n" );
					} else {		//分配空间成功
						if ( current1->col < current2->col ) {//比较两个矩阵元素的列号，如果第一个矩阵的current1的列号小于第二个矩阵的current2的列号
							*current = *current1;          //current的值为current1的值
							current1 = current1->right;    //取第一个矩阵的下一项继续运算
						} else if ( current1->col == current2->col ) { //如果current1的value值等于current2的value值
							*current = *current1;  //current的行列号与current1和current2都相等
							current->value = current1->value + current2->value;//current的value值是两项之和
							current1 = current1->right;//分别去两个矩阵的下一项进行运算
							current2 = current2->right;
							if ( current->value == 0 ) {  //如果current的value项为0，则不需要进行存储，释放current，开始下一次循环
								free ( current );
								continue;
							}
						} else {   //付过current1 的列号大于current2的列号
							*current = *current2;//current的值为current2的值
							current2 = current2->right;//取第二个矩阵的下一项继续运算
						}
						current->right = nullptr;//将current的down和right指针进行初始化
						current->down = nullptr;

						Insert_R ( result->rhead, current );  //将current插入到dest的行列链表的合适位置
						Insert_C ( result->chead, current );
					}
					k++;
				}
				if ( current1 ) {  //第1个矩阵的行链表的所有值还没有已经运算完毕
					while ( current1 ) {  //将第一个矩阵的行链表的剩余项直接复制到dest的行链表的合适位置
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
						if ( !current ) {  //分配存储空间失败，报错并结束程序执行
							printf ( "AddSMatrix_OL Error: OVERFLOW\n" );
						} else {
							*current = *current1;
							current->right = nullptr;
							current->down = nullptr;
							current1 = current1->right;

							Insert_R ( result->rhead, current );
							Insert_C ( result->chead, current );
						}
						k++;
					}
				}
				if ( current2 ) {//第二个矩阵的行链表的所有值还没有已经运算完毕
					while ( current2 ) {//将第二个矩阵的行链表的剩余项直接复制到dest的行链表的合适位置
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
						if ( !current ) {  //分配存储空间失败，报错并结束程序执行
							printf ( "AddSMatrix_OL Error: OVERFLOW\n" );
						} else {
							*current = *current2;
							current->right = nullptr;
							current->down = nullptr;
							current2 = current2->right;
						}

						Insert_R ( result->rhead, current );
						Insert_C ( result->chead, current );
						k++;
					}
				}
				i++;
			}
			result->non_zero = k;  //k的最终结果即为结果矩阵的非零值的个数
		}

		return temp;
	}

	//当两个矩阵行列值相同时，用第一个矩阵的值减去第二个矩阵的值，并将结果存在result矩阵中
	void SubSMatrix_OL ( const sparseMatrix& leftin, const sparseMatrix& rightin ) {
		CrossList* matrix1 = leftin._matrix;
		CrossList* matrix2 = rightin._matrix;
		CrossList* result = _matrix;
		int i;
		int k;
		OLNode* current;
		OLNode* current1;
		OLNode* current2;
		if ( matrix1->row_num != matrix2->row_num || matrix1->col_num != matrix2->col_num ) {  //如果两个矩阵的行数或者列数不相同
			printf ( "SubSMatrix_OL Error: the row or the colum of the matrixs is different!\n" ); //报错
		} else {

			result->row_num = matrix1->row_num;
			result->col_num = matrix1->col_num;
			//为结果矩阵分配内存空间
			if ( !_malloc_head ( result ) ) {      //分配失败，程序结束执行
				printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
				exit ( EXIT_FAILURE );
			}
			i = 1;
			k = 0;  //每插入到结果矩阵中一个矩阵项，k就增加1，用于统计结果矩阵的非零值的个数
			while ( i <= matrix1->row_num ) { //当两个矩阵的元素都没有处理完时对两个矩阵从第一个元素开始进行加法运算
				current1 = ( matrix1->rhead + i )->right;
				current2 = ( matrix2->rhead + i )->right;
				while ( current1 && current2 ) {
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
					if ( !current ) {  //分配存储空间失败，报错并结束程序执行
						printf ( "SubSMatrix_OL Error: OVERFLOW\n" );
						exit ( EXIT_FAILURE );
					} else {
						if ( current1->col < current2->col ) {//继续比较两个矩阵元素的列号，如果第一个矩阵的current1的列号小于第二个矩阵的current2的列号
							*current = *current1;//将第一个矩阵的第i个元素赋给current
							current1 = current1->right;
						} else if ( current1->col == current2->col ) {//如果第一个矩阵的current1的列号等于第二个矩阵的current2的列号
							*current = *current2;      //current行列值与current1和current2都相等
							current->value = current1->value - current2->value;  //current的value项为current1的value项减去current2的value项
							current1 = current1->right;
							current2 = current2->right;
							if ( current->value == 0 ) {   //如果current的value项为0，不需要对该项进行存储，释放current，继续下一次循环
								free ( current );
								continue;
							}
						} else {                   //如果第一个矩阵的current1的列号大于第二个矩阵的current2的列号
							*current = *current2; //current行列值与current2相等
							current->value = -current2->value; //current的value项是current2的value项的相反数
							current2 = current2->right;
						}
						current->right = nullptr;  //将current的right和down指针进行初始化
						current->down = nullptr;

						Insert_R ( result->rhead, current );  //将current插入到结果矩阵的行列链表的适当位置
						Insert_C ( result->chead, current );
					}
					k++;
				}
				if ( current1 ) {   //如果第一个矩阵的行链表的项还有剩余
					while ( current1 ) { //将第一个矩阵的行链表的剩余项直接复制到dest的行链表的合适位置
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
						if ( !current ) {  //分配存储空间失败，报错并结束程序执行
							printf ( "SubSMatrix_OL Error: OVERFLOW\n" );
						} else {
							*current = *current1;
							current->right = nullptr;
							current->down = nullptr;
							current1 = current1->right;

							Insert_R ( result->rhead, current );
							Insert_C ( result->chead, current );
						}
						k++;
					}
				}
				if ( current2 ) { //如果第一个矩阵的行链表的项还有剩余
					while ( current2 ) {//将第一个矩阵的行链表的剩余项经过适当运算后复制到dest的行链表的合适位置
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
						if ( !current ) {  //分配存储空间失败，报错并结束程序执行
							printf ( "SubSMatrix_OL Error: OVERFLOW\n" );
						} else {
							*current = *current2;
							current->value = -current2->value;
							current->right = nullptr;
							current->down = nullptr;
							current2 = current2->right;
						}

						Insert_R ( result->rhead, current );
						Insert_C ( result->chead, current );
						k++;
					}
				}
				i++;
			}
			result->non_zero = k;  //k的最终结果即为结果矩阵的非零值的个数

		}
	}

	//当第一个矩阵的列值等于第二个矩阵的行值时，对这两个矩阵进行相乘的运算并将结果存在result矩阵中
	const sparseMatrix operator * (const sparseMatrix& rightin ) {

		sparseMatrix temp;
		CrossList* matrix1 = _matrix;
		CrossList* matrix2 = rightin._matrix;
		CrossList* result = temp._matrix;

		int i;
		int j;
		int count;
		OLNode* current1;
		OLNode* current2;
		OLNode* current;

		if ( matrix1->col_num != matrix2->row_num ) {  //如果两个矩阵的行数或者列数不相同
			printf ( "AddSMatrix Error: the colum of the first matrix and therow of the second matrix is different!\n" );
		} else {
			result->row_num = matrix1->row_num;
			result->col_num = matrix2->col_num;

			if ( !_malloc_head ( result ) ) {//为结果矩阵分配内存空间
				printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
				exit ( EXIT_FAILURE );
			}

			i = 1;
			count = 0;
			while ( i <= matrix1->row_num ) { //对第一个矩阵逐行进行运算
				j = 1;
				while ( j <= matrix2->col_num ) {  //用第一个矩阵的第i个行链表的各项依次与第二个矩阵的各个列链表的各项进行合适的运算
					current1 = ( matrix1->rhead + i )->right;
					current2 = ( matrix2->chead + j )->down;
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
					if ( !current ) {  //分配存储空间失败，报错并结束程序执行
						printf ( "SubSMatrix_OL Error: OVERFLOW\n" );
						exit ( EXIT_FAILURE );
					} else {             //分配存储空间成功呢，初始化
						current->value = 0;
						current->right = nullptr;
						current->down = nullptr;
					}
					while ( current1 && current2 ) {  //当第一个矩阵的第i个行链表和第二个矩阵的第j个列链表均没有到达末尾时
						if ( current1->col == current2->row ) {   //如果current1的列号与current2的行号相等
							current->row = current1->row;  //current1的行号和current2的列号构成结果矩阵项current的行列号
							current->col = current2->col;
							current->value += current1->value * current2->value;//current1和current2相乘的结果作为current的value值
							current1 = current1->right;//继续下一项运算
							current2 = current2->down;
						} else if ( current1->col < current2->row )  //如果current1的列号小于current2的行号
							current1 = current1->right;     //取current1的下一项进行比较运算
						else								//如果current1的列号大于current2的行号
							current2 = current2->down;		//取current2的下一项进行比较运算
					}
					if ( current->value == 0 ) {  //如果current的value的最终结果为0，说明第一个矩阵的第i行中的所有元素的列号都与
						free ( current );		//第二个矩阵的第j列中的所有元算的行号都不想等，即没有满足相乘条件的项，释放current
					} else {                 //如果current的value的最终结果不为0，则将current插入到结果矩阵的合适位置
						Insert_R ( result->rhead, current );
						Insert_C ( result->chead, current );
						count++;  ////每插入到结果矩阵中一个矩阵项，count就增加1，用于统计结果矩阵的非零值的个数
					}
					j++;
				}
				i++;
			}
			result->non_zero = count;
		}


		return temp;
	}

	//求稀疏矩阵的转置矩阵，//求矩阵1的转置矩阵并将结果存在矩阵2中
	void TransposeSMatrix_OL ( const sparseMatrix& in ) {
		CrossList* matrix1 = in._matrix;
		CrossList* matrix2 = _matrix;
		int i = 0;
		OLNode* current1;
		OLNode* current2;

		matrix2->col_num = matrix1->row_num;
		matrix2->row_num = matrix1->col_num;
		matrix2->non_zero = matrix1->non_zero;

		if ( !_malloc_head ( matrix2 ) ) {
			printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
			exit ( EXIT_FAILURE );
		}
		for ( i = 1; i <= matrix1->row_num; i++ ) {
			current1 = ( matrix1->rhead + i )->right;
			while ( current1 ) {
				current2 = (OLNode*)malloc ( sizeof ( OLNode ) ); //为一个矩阵项分配空间
				if ( !current2 ) {  //分配存储空间失败，报错并结束程序执行
					printf ( "TransposeSMatrix_OL Error: OVERFLOW\n" );
				} else {
					current2->row = current1->col;  //将第一个矩阵的矩阵项的行号赋给第二个矩阵的矩阵项的列号
					current2->col = current1->row; //将第一个矩阵的矩阵项的列号赋给第二个矩阵的矩阵项的行号
					current2->value = current1->value; //将第一个矩阵的矩阵项的value值赋给第二个矩阵的矩阵项的value值
					current2->right = nullptr;  //初始化current2的right和down指针为空
					current2->down = nullptr;

					Insert_C ( matrix2->chead, current2 );//将current2插入到matrix2的行列链表的合适位置
					Insert_R ( matrix2->rhead, current2 );
				}
				current1 = current1->right;
			}
		}
	}




	int getCols ()const { return _matrix->col_num; }
	int getRows ()const{ return _matrix->row_num;}

	template <class U>
	friend istream& operator>> ( istream& in, sparseMatrix<U>& temp );

	template <class U>
	friend ostream& operator<< ( ostream& out, const sparseMatrix<U>& temp );

};

/*输出运算符的重载，直接调用show函数*/
template<class  T>
ostream& operator << ( ostream& out, const sparseMatrix<T>& temp ) {
	temp.show ( out );
	return out;
}
template<class T>
istream& operator>>( istream& in, sparseMatrix<T>& temp ) {
	temp.init ( in );
	return in;
}