#include <iostream> 
using namespace std; 
template <class T> 
struct MatrixTerm     //��Ԫ���洢ϡ������з���Ԫ�ص�����ֵ�Լ�Ԫ����Ϣ
{ 
    public: 
        long long int row;  //��
        long long int col;  //��
        T value;  //Ԫ��ֵ
        MatrixTerm() 
        { 
            row = 0; 
            col = 0; 
            value = 0; 
        } 
        MatrixTerm(long long int ro, long long int co, T va) 
        { 
            row = ro; 
            col = co; 
            value = va; 
        } 
       void OutputM()   //���
       { 
           cout << row << " " << col << " " << value; 
           cout << endl; 
       } 
}; 
