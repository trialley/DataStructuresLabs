#include <iostream> 
using namespace std; 
template <class T> 
struct MatrixTerm     //三元法存储稀疏矩阵中非零元素的行列值以及元素信息
{ 
    public: 
        long long int row;  //行
        long long int col;  //列
        T value;  //元素值
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
       void OutputM()   //输出
       { 
           cout << row << " " << col << " " << value; 
           cout << endl; 
       } 
}; 
