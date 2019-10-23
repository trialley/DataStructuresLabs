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
		int row;    //�˴�������ֵΪ��ʵֵ�����д�1��ʼû�е�0�к͵�0��
		int col;
		T value;   //�����row�е�col�ж�Ӧ��ֵ
		struct OLNode* right;
		struct OLNode* down;
	}OLNode;

	typedef struct {
		OLNode* rhead;
		OLNode* chead;
		int row_num;      //�����������
		int col_num;	//�����������
		int non_zero;	//�����ܵķ���ֵ�ĸ���
	}CrossList;
private:
	CrossList* _matrix;
	bool _inited;
	//���������е�����˳���������
	void Increse_row ( OLNode* List_RHead ) {
		OLNode* current;
		OLNode* nex;
		OLNode* pre;
		int count = 0;
		int i, j;

		current = List_RHead->right;
		while ( current ) {		//ͳ�Ƶ�ǰ�б������
			count++;
			current = current->right;
		}
		for ( i = 1; i < count; i++ ) {  //ð�ݷ���������
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

	//�����������е�����˳���������
	void Increse_col ( OLNode* List_CHead ) {
		OLNode* current;
		OLNode* nex;
		OLNode* pre;
		int count = 0;
		int i, j;

		current = List_CHead->down;
		while ( current ) {  //ͳ�Ƶ�ǰ�б������
			count++;
			current = current->down;
		}
		for ( i = 1; i < count; i++ ) {//ð�ݷ���������
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
	//��current���뵽���Ӧ��������ĺ���λ�ã�ʹ�������Ԫ�ذ��кŵ���˳������				
	void Insert_R ( OLNode* rhead, OLNode* current ) {
		if ( ( rhead + current->row )->right == nullptr ) {
			( rhead + current->row )->right = current;
		} else {	    //����ǰ����뵽��Ӧ������ĵ�һ��������������
			current->right = ( rhead + current->row )->right;
			( rhead + current->row )->right = current;
			Increse_row ( rhead + current->row );
		}
	}

	//��current���뵽���Ӧ��������ĺ���λ�ã�ʹ�������Ԫ�ذ��кŵ���˳������
	void Insert_C ( OLNode* chead, OLNode* current ) {
		if ( ( chead + current->col )->down == nullptr ) {
			( chead + current->col )->down = current;
		} else {	    //����ǰ����뵽��Ӧ������ĵ�һ��������������
			current->down = ( chead + current->col )->down;
			( chead + current->col )->down = current;
			Increse_col ( chead + current->col );
		}
	}
	//Ϊʮ�������͵�ϡ�����������������ͷ�Ŀռ�
	int _malloc_head ( CrossList* temp) {
		int i;
		temp->rhead = (OLNode*)malloc ( sizeof ( OLNode ) * ( temp->row_num + 1 ) );   //Ϊ��������������ͷָ�����ռ�
		temp->chead = (OLNode*)malloc ( sizeof ( OLNode ) * ( temp->col_num + 1 ) );
		if ( !temp->rhead || !temp->chead ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
			return false;
		}
		for ( i = 0; i <= temp->row_num; i++ ) {//���������ͷ���г�ʼ��
			( temp->rhead + i )->right = nullptr;
			( temp->rhead + i )->down = nullptr;

		}
		for ( i = 0; i <= temp->col_num; i++ ) {//���������ͷ���г�ʼ��
			( temp->chead + i )->right = nullptr;
			( temp->chead + i )->down = nullptr;
		}
		return true;
	}
	int _malloc_head () {
		int i;
		_matrix->rhead = (OLNode*)malloc ( sizeof ( OLNode ) * ( _matrix->row_num + 1 ) );   //Ϊ��������������ͷָ�����ռ�
		_matrix->chead = (OLNode*)malloc ( sizeof ( OLNode ) * ( _matrix->col_num + 1 ) );
		if ( !_matrix->rhead || !_matrix->chead ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
			return false;
		}
		for ( i = 0; i <= _matrix->row_num; i++ ) {//���������ͷ���г�ʼ��
			( _matrix->rhead + i )->right = nullptr;
			( _matrix->rhead + i )->down = nullptr;

		}
		for ( i = 0; i <= _matrix->col_num; i++ ) {//���������ͷ���г�ʼ��
			( _matrix->chead + i )->right = nullptr;
			( _matrix->chead + i )->down = nullptr;
		}
		return true;
	}
	//��������ϡ�����
	void _destroy () {
		int i;
		OLNode* current;

		current = _matrix->rhead;
		for ( i = 1; i <= _matrix->row_num; i++ ) {  //��������ͷ�Ϊ���������Ŀռ�
			current = ( _matrix->rhead + i )->right;
			while ( current ) {
				( _matrix->rhead + i )->right = ( _matrix->rhead + i )->right->right;
				free ( current );
				current = ( _matrix->rhead + i )->right;
			}
		}
		free ( _matrix->rhead );//�ͷ�Ϊ������ͷ����Ŀռ�
		free ( _matrix->chead );//�ͷ�Ϊ������ͷ����Ŀռ�
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

		for ( i = 1; i <= source->row_num; i++ ) {   //����洢�ռ�ɹ�
			sur_cur = ( source->rhead + i )->right;
			while ( sur_cur ) {
				current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
				if ( !current ) {						 //����洢�ռ�ʧ�ܣ�������������ִ��
					printf ( "CopySMatrix_OL Error: OVERFLOW\n" );
					exit ( EXIT_FAILURE );
				}

				*current = *sur_cur;        //��source�еĵ�ǰ���ֵ����current
				current->right = nullptr;		//��ʼ����current��right��downָ��
				current->down = nullptr;

				Insert_R ( _matrix->rhead, current ); //��current����_matrix���ʵ�������λ��
				Insert_C ( _matrix->chead, current );
				sur_cur = sur_cur->right;			//����������һ��

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

		for ( i = 1; i <= source->row_num; i++ ) {   //����洢�ռ�ɹ�
			sur_cur = ( source->rhead + i )->right;
			while ( sur_cur ) {
				current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
				if ( !current ) {						 //����洢�ռ�ʧ�ܣ�������������ִ��
					printf ( "CopySMatrix_OL Error: OVERFLOW\n" );
					exit ( EXIT_FAILURE );
				}

				*current = *sur_cur;        //��source�еĵ�ǰ���ֵ����current
				current->right = nullptr;		//��ʼ����current��right��downָ��
				current->down = nullptr;

				Insert_R ( _matrix->rhead, current ); //��current����_matrix���ʵ�������λ��
				Insert_C ( _matrix->chead, current );
				sur_cur = sur_cur->right;			//����������һ��

			}
		}
	}


	//����ϡ����󣬾���Ԫ�شӵ�һ�е�һ�п�ʼû�е�0�к͵�0�У�����Ķ�Ӧֵ������ֵ��Ϊʵ�ʵ�����ֵ
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
				} else {				//����洢�ռ�ɹ����ԣ��У��У�ֵ������ʽ�����������ֵ
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
					current->down = nullptr;							//��current��down��right����ʼ��Ϊnullptr
					current->right = nullptr;

					current->row = i;
					current->col = j;
					current->value = tvalue;

					if ( current->row <= 0 || current->row > _matrix->row_num ||
						current->col > _matrix->col_num || current->col <= 0 ) {
						throw index_out_of_range;
					}
					//��current���뵽��Ӧ����������ĺ��ʵ�λ��
					Insert_R ( _matrix->rhead, current );
					Insert_C ( _matrix->chead, current );
					no_zero_num++;
				}
			}
		}
		_matrix->non_zero = no_zero_num;
	}

	//����Ԫ����У��У�ֵ������ʽ��ӡϡ�����
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

			for ( int i = 1; i <= _matrix->row_num; i++ ) {  //���н��д�ӡ
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
	//������վ���
	void clear () {
		int i;
		OLNode* current;

		current = _matrix->rhead;
		for ( i = 1; i <= _matrix->row_num; i++ ) {  //��������ͷ�Ϊ���������Ŀռ�
			current = ( _matrix->rhead + i )->right;
			while ( current ) {
				( _matrix->rhead + i )->right = ( _matrix->rhead + i )->right->right;
				free ( current );
				current = ( _matrix->rhead + i )->right;
			}
		}
		for ( i = 0; i <= _matrix->row_num; i++ ) {//����������ͷ
			( _matrix->rhead + i )->right = nullptr;
			( _matrix->rhead + i )->down = nullptr;

		}
		for ( i = 0; i <= _matrix->col_num; i++ ) {//����������ͷ
			( _matrix->chead + i )->right = nullptr;
			( _matrix->chead + i )->down = nullptr;
		}

	}



	//��������������ֵ��ͬʱ��������мӷ����㣬������ӵĽ���洢��result��
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
		if ( matrix1->row_num != matrix2->row_num || matrix1->col_num != matrix2->col_num ) {  //����������������������������ͬ
			printf ( "AddSMatrix Error: the row or the colum of the matrixs is different!\n" );
		} else {

			result->row_num = matrix1->row_num;//����������������������������һ���������������������
			result->col_num = matrix1->col_num;
			//�����������ڴ�ռ�
			if ( !_malloc_head ( result ) ) {
				printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
				exit ( EXIT_FAILURE );
			}
			i = 1;
			k = 0;//ÿ���뵽���������һ�������k������1������ͳ�ƽ������ķ���ֵ�ĸ���
			while ( i <= matrix1->row_num ) {     //���н�������
				current1 = ( matrix1->rhead + i )->right;
				current2 = ( matrix2->rhead + i )->right;
				while ( current1 && current2 ) {//�������������Ԫ�ض���û���������ʱ
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
					if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
						printf ( "AddSMatrix_OL Error: OVERFLOW\n" );
					} else {		//����ռ�ɹ�
						if ( current1->col < current2->col ) {//�Ƚ���������Ԫ�ص��кţ������һ�������current1���к�С�ڵڶ��������current2���к�
							*current = *current1;          //current��ֵΪcurrent1��ֵ
							current1 = current1->right;    //ȡ��һ���������һ���������
						} else if ( current1->col == current2->col ) { //���current1��valueֵ����current2��valueֵ
							*current = *current1;  //current�����к���current1��current2�����
							current->value = current1->value + current2->value;//current��valueֵ������֮��
							current1 = current1->right;//�ֱ�ȥ�����������һ���������
							current2 = current2->right;
							if ( current->value == 0 ) {  //���current��value��Ϊ0������Ҫ���д洢���ͷ�current����ʼ��һ��ѭ��
								free ( current );
								continue;
							}
						} else {   //����current1 ���кŴ���current2���к�
							*current = *current2;//current��ֵΪcurrent2��ֵ
							current2 = current2->right;//ȡ�ڶ����������һ���������
						}
						current->right = nullptr;//��current��down��rightָ����г�ʼ��
						current->down = nullptr;

						Insert_R ( result->rhead, current );  //��current���뵽dest����������ĺ���λ��
						Insert_C ( result->chead, current );
					}
					k++;
				}
				if ( current1 ) {  //��1������������������ֵ��û���Ѿ��������
					while ( current1 ) {  //����һ��������������ʣ����ֱ�Ӹ��Ƶ�dest��������ĺ���λ��
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
						if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
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
				if ( current2 ) {//�ڶ�������������������ֵ��û���Ѿ��������
					while ( current2 ) {//���ڶ���������������ʣ����ֱ�Ӹ��Ƶ�dest��������ĺ���λ��
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
						if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
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
			result->non_zero = k;  //k�����ս����Ϊ�������ķ���ֵ�ĸ���
		}

		return temp;
	}

	//��������������ֵ��ͬʱ���õ�һ�������ֵ��ȥ�ڶ��������ֵ�������������result������
	void SubSMatrix_OL ( const sparseMatrix& leftin, const sparseMatrix& rightin ) {
		CrossList* matrix1 = leftin._matrix;
		CrossList* matrix2 = rightin._matrix;
		CrossList* result = _matrix;
		int i;
		int k;
		OLNode* current;
		OLNode* current1;
		OLNode* current2;
		if ( matrix1->row_num != matrix2->row_num || matrix1->col_num != matrix2->col_num ) {  //����������������������������ͬ
			printf ( "SubSMatrix_OL Error: the row or the colum of the matrixs is different!\n" ); //����
		} else {

			result->row_num = matrix1->row_num;
			result->col_num = matrix1->col_num;
			//Ϊ�����������ڴ�ռ�
			if ( !_malloc_head ( result ) ) {      //����ʧ�ܣ��������ִ��
				printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
				exit ( EXIT_FAILURE );
			}
			i = 1;
			k = 0;  //ÿ���뵽���������һ�������k������1������ͳ�ƽ������ķ���ֵ�ĸ���
			while ( i <= matrix1->row_num ) { //�����������Ԫ�ض�û�д�����ʱ����������ӵ�һ��Ԫ�ؿ�ʼ���мӷ�����
				current1 = ( matrix1->rhead + i )->right;
				current2 = ( matrix2->rhead + i )->right;
				while ( current1 && current2 ) {
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
					if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
						printf ( "SubSMatrix_OL Error: OVERFLOW\n" );
						exit ( EXIT_FAILURE );
					} else {
						if ( current1->col < current2->col ) {//�����Ƚ���������Ԫ�ص��кţ������һ�������current1���к�С�ڵڶ��������current2���к�
							*current = *current1;//����һ������ĵ�i��Ԫ�ظ���current
							current1 = current1->right;
						} else if ( current1->col == current2->col ) {//�����һ�������current1���кŵ��ڵڶ��������current2���к�
							*current = *current2;      //current����ֵ��current1��current2�����
							current->value = current1->value - current2->value;  //current��value��Ϊcurrent1��value���ȥcurrent2��value��
							current1 = current1->right;
							current2 = current2->right;
							if ( current->value == 0 ) {   //���current��value��Ϊ0������Ҫ�Ը�����д洢���ͷ�current��������һ��ѭ��
								free ( current );
								continue;
							}
						} else {                   //�����һ�������current1���кŴ��ڵڶ��������current2���к�
							*current = *current2; //current����ֵ��current2���
							current->value = -current2->value; //current��value����current2��value����෴��
							current2 = current2->right;
						}
						current->right = nullptr;  //��current��right��downָ����г�ʼ��
						current->down = nullptr;

						Insert_R ( result->rhead, current );  //��current���뵽������������������ʵ�λ��
						Insert_C ( result->chead, current );
					}
					k++;
				}
				if ( current1 ) {   //�����һ�����������������ʣ��
					while ( current1 ) { //����һ��������������ʣ����ֱ�Ӹ��Ƶ�dest��������ĺ���λ��
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
						if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
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
				if ( current2 ) { //�����һ�����������������ʣ��
					while ( current2 ) {//����һ��������������ʣ������ʵ�������Ƶ�dest��������ĺ���λ��
						current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
						if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
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
			result->non_zero = k;  //k�����ս����Ϊ�������ķ���ֵ�ĸ���

		}
	}

	//����һ���������ֵ���ڵڶ����������ֵʱ�������������������˵����㲢���������result������
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

		if ( matrix1->col_num != matrix2->row_num ) {  //����������������������������ͬ
			printf ( "AddSMatrix Error: the colum of the first matrix and therow of the second matrix is different!\n" );
		} else {
			result->row_num = matrix1->row_num;
			result->col_num = matrix2->col_num;

			if ( !_malloc_head ( result ) ) {//Ϊ�����������ڴ�ռ�
				printf ( "CopySMatrix_OL Error:OVERFLOW!\n" );
				exit ( EXIT_FAILURE );
			}

			i = 1;
			count = 0;
			while ( i <= matrix1->row_num ) { //�Ե�һ���������н�������
				j = 1;
				while ( j <= matrix2->col_num ) {  //�õ�һ������ĵ�i��������ĸ���������ڶ�������ĸ���������ĸ�����к��ʵ�����
					current1 = ( matrix1->rhead + i )->right;
					current2 = ( matrix2->chead + j )->down;
					current = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
					if ( !current ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
						printf ( "SubSMatrix_OL Error: OVERFLOW\n" );
						exit ( EXIT_FAILURE );
					} else {             //����洢�ռ�ɹ��أ���ʼ��
						current->value = 0;
						current->right = nullptr;
						current->down = nullptr;
					}
					while ( current1 && current2 ) {  //����һ������ĵ�i��������͵ڶ�������ĵ�j���������û�е���ĩβʱ
						if ( current1->col == current2->row ) {   //���current1���к���current2���к����
							current->row = current1->row;  //current1���кź�current2���кŹ��ɽ��������current�����к�
							current->col = current2->col;
							current->value += current1->value * current2->value;//current1��current2��˵Ľ����Ϊcurrent��valueֵ
							current1 = current1->right;//������һ������
							current2 = current2->down;
						} else if ( current1->col < current2->row )  //���current1���к�С��current2���к�
							current1 = current1->right;     //ȡcurrent1����һ����бȽ�����
						else								//���current1���кŴ���current2���к�
							current2 = current2->down;		//ȡcurrent2����һ����бȽ�����
					}
					if ( current->value == 0 ) {  //���current��value�����ս��Ϊ0��˵����һ������ĵ�i���е�����Ԫ�ص��кŶ���
						free ( current );		//�ڶ�������ĵ�j���е�����Ԫ����кŶ�����ȣ���û�����������������ͷ�current
					} else {                 //���current��value�����ս����Ϊ0����current���뵽�������ĺ���λ��
						Insert_R ( result->rhead, current );
						Insert_C ( result->chead, current );
						count++;  ////ÿ���뵽���������һ�������count������1������ͳ�ƽ������ķ���ֵ�ĸ���
					}
					j++;
				}
				i++;
			}
			result->non_zero = count;
		}


		return temp;
	}

	//��ϡ������ת�þ���//�����1��ת�þ��󲢽�������ھ���2��
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
				current2 = (OLNode*)malloc ( sizeof ( OLNode ) ); //Ϊһ�����������ռ�
				if ( !current2 ) {  //����洢�ռ�ʧ�ܣ�������������ִ��
					printf ( "TransposeSMatrix_OL Error: OVERFLOW\n" );
				} else {
					current2->row = current1->col;  //����һ������ľ�������кŸ����ڶ�������ľ�������к�
					current2->col = current1->row; //����һ������ľ�������кŸ����ڶ�������ľ�������к�
					current2->value = current1->value; //����һ������ľ������valueֵ�����ڶ�������ľ������valueֵ
					current2->right = nullptr;  //��ʼ��current2��right��downָ��Ϊ��
					current2->down = nullptr;

					Insert_C ( matrix2->chead, current2 );//��current2���뵽matrix2����������ĺ���λ��
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

/*�������������أ�ֱ�ӵ���show����*/
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