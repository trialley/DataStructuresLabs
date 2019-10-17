#include <iostream> 
#include "矩阵类.cpp" 
#include "数组类.cpp" 
#include <stdio.h> 
using namespace std; 
template <class T> 
class sparseMatrix 
{ 
    private: 
        long long int rows;    //稀疏矩阵的行列总数
        long long int cols; 
        arrayList<MatrixTerm<T> > terms;    //存放稀疏矩阵的数组
    public: 
        void Add(sparseMatrix<T>&, sparseMatrix<T>&);  //加法a+b=c 
        void Multiply(sparseMatrix<T>&, sparseMatrix<T>&);  //乘法a*b=c 
        void Input();    //输入
        void Output();   //输出稀疏矩阵
        void Output_as_arratList();   //按线性表格式输出
        void Transpose(sparseMatrix<T> &b); //矩阵转置
}; 
/*
输入
*/ 
template <class T> 
void sparseMatrix<T>::Input() 
{ 
    cout << "Input the number of rows and columns" << endl; 
    cin >> rows >> cols; 
    T notZero; 
    cout << "Input the element:" << endl; 
    long long int num = 0; 
    for (long long i=0; i<rows; i++) 
        for (long long int j=0; j<cols; j++) 
            { 
                cin >> notZero; 
                if(notZero!=0)  //非零时存储
                { 
                    MatrixTerm<T> term(i,j,notZero); 
                    terms.Insert(num++,term); 
                } 
            } 
} 
/*
输出稀疏矩阵
*/ 
template <class T> 
void sparseMatrix<T>::Output() 
{ 
    long long int num = 0; 
    cout << "Output the sparseMatrix:" << endl; 
    for (long long int i=0; i<rows; i++) 
    { 
        for (long long int j=0; j<cols; j++) 
        { 
if  (num  <  terms.Size()  &&  terms.Get(num).row==i  &&  terms.Get(num).col==j ) 
                cout << terms.Get(num++).value << " " ; 
            else 
                cout << "0" << " " ; 
        } 
        cout << endl; 
    } 
} 
/*
按线性表格式输出
*/ 
template <class T> 
void sparseMatrix<T>::Output_as_arratList() 
{ 
    cout << "Output the sparseMatrix as arrayList:" << endl; 
    cout << "List size: " << terms.Size() << endl; 
    terms.OutputA(); 
} 
/*
矩阵转置
*/ 
template <class T> 
void sparseMatrix<T>::Transpose(sparseMatrix<T> &b) 
{ 
    cols = b.rows; 
    rows = b.cols;  //设置行列特征
    terms = b.terms; 
    for (long long int i=0; i<terms.Size(); i++) 
    { 
        long long int temp = terms.Get(i).row; 
        terms.Get(i).row = terms.Get(i).col; 
        terms.Get(i).col = temp; 
    } 
    bool swapped = true;   //及时终止的冒泡排序
    for (long long int i=terms.Size(); i>1&&swapped; i--) 
    { 
        swapped = false; 
        for (long long int j=0; j<i-1; j++) 
        { 
            if       ((terms.Get(j).row==
terms.Get(j+1).row       &&       
terms.Get(j).col>terms.Get(j+1).col)                             ||                             
terms.Get(j).row>terms.Get(j+1).row) 
            {//j的位置应该在j+1的位置之后，进行交换
                MatrixTerm<T> temp = terms.Get(j); 
                terms.Set(j,terms.Get(j+1)); 
                terms.Set(j+1,temp); 
                //swap(terms[j],terms[j+1]); 
                swapped  =  true;      //当无序时进行了交换，swapped为真，继续循环
            } 
        } 
    } 
} 
/*
矩阵加法
*/ 
template <class T> 
void sparseMatrix<T>::Add(sparseMatrix<T> &b,sparseMatrix<T> &c) 
{ 
    if (b.rows!=c.rows || b.cols!=c.cols) 
    { 
        cout << "Not match" << endl; 
        return ; 
    } 
    rows = b.rows; 
    cols = b.cols; 
    long long int num_a = 0; 
    long long int num_b = 0; 
    long long int num_c = 0;//分别标记a，b，c的数组元素下标
    while (b.terms.Size()>num_b || c.terms.Size()>num_c) 
    { 
if    ((b.terms.Get(num_b).row==c.terms.Get(num_c).row    &&    
b.terms.Get(num_b).col<c.terms.Get(num_c).col)                   ||                   
b.terms.Get(num_b).row<c.terms.Get(num_c).row) 
            terms.Insert(num_a++,b.terms.Get(num_b++));   //b的元素在前，插入b的元素
else if ((b.terms.Get(num_b).row==c.terms.Get(num_c).row && 
b.terms.Get(num_b).col>c.terms.Get(num_c).col)                   ||                   
b.terms.Get(num_b).row>c.terms.Get(num_c).row) 
            terms.Insert(num_a++,c.terms.Get(num_c++));   //c的元素在前，插入c的元素
        else   //b和 c的元素位置匹配，插入两者之和
        { 
T      sum      =      b.terms.Get(num_b++).value      +      
c.terms.Get(num_c++).value; 
            MatrixTerm<T> temp; 
            temp.row = b.terms.Get(num_b-1).row; 
            temp.col = b.terms.Get(num_b-1).col; 
            temp.value = sum; 
            terms.Insert(num_a++,temp); 
        } 
        while (c.terms.Size()==num_c && b.terms.Size()!=num_b) 
            terms.Insert(num_a++,b.terms.Get(num_b++));   //c中没有元素
        while (b.terms.Size()==num_b && c.terms.Size()!=num_c) 
            terms.Insert(num_a++,c.terms.Get(num_c++));   //b中没有元素
    } 
} 
/*
矩阵乘法
*/ 
template <class T> 
void  sparseMatrix<T>::Multiply(sparseMatrix<T>  &b,  sparseMatrix<T>  
&c) 
{ 
    if (b.rows!=c.cols) 
    { 
        cout << "Not match" << endl; 
        return ; 
    } 
    rows = b.rows; 
    cols = c.cols; 
    sparseMatrix<T> d; 
    d.Transpose(c);   //将c转置，这样就可以与b行行相乘
    //统计出b,d两个矩阵每行有多少非零元素
    long long int b_rows[b.rows] = {0}; 
    long long int d_rows[d.rows] = {0}; 
    for (long long int i=0; i<b.terms.Size(); i++) 
        b_rows[b.terms.Get(i).row]++; 
    for (long long int i=0; i<d.terms.Size(); i++) 
        d_rows[d.terms.Get(i).row]++; 
    //逐个计算元素值
    long long int no_a = 0;  //数组的下标
    for (long long int i=0; i<rows; i++) 
        for (long long int j=0; j<cols; j++) 
        { 
            long long int no_b = 0;  //数组的下标
            long long int no_d = 0;  //数组的下标
            if (b_rows[i]==0 || d_rows[j]==0) 
                continue; 
            MatrixTerm<T> temp(i,j,0);  //temp存储计算值
            for (long long int k=0; k<i; k++)  //使稀疏矩阵跳转到做乘法的那一行
                no_b += b_rows[k]; 
            for (long long int k=0; k<j; k++) 
                no_d += d_rows[k]; 
            long long int num_b = b_rows[i]; 
            long long int num_d = d_rows[j];//b,d两个矩阵在i行剩余的元素数量
            while (num_b>0 && num_d>0)  //当b,d矩阵在这行还有元素
            { 
                if (b.terms.Get(no_b).col == d.terms.Get(no_d).col) 
                { 
                    temp.value    +=    b.
terms.Get(no_b).value    *    
d.terms.Get(no_d).value; 
                    num_b--; 
                    num_d--; 
                    no_b++; 
                    no_d++; 
                } 
                else if (b.terms.Get(no_b).col < 
d.terms.Get(no_d).col) 
                {//b的位置靠前，移动到下一个b 
                    no_b++; 
                    num_b--; 
                } 
                else 
                {//d的位置靠前，移动到下一个d 
                    no_d++; 
                    num_d--; 
                } 
            } 
            if (temp.value != 0)  //非零值插入
                terms.Insert(no_a++,temp); 
        } 
} 
int main() 
{ 
    int uuuu; 
    freopen("data_structure_ex5.in","r",stdin); 
    sparseMatrix<long long int> a,b,c,d; 
    a.Input(); 
    //a.Output(); 
    //a.Output_as_arratList(); 
    b.Input(); 
    //b.Output(); 
    //b.Output_as_arratList(); 
    c.Add(a,b); 
    //cout << endl << "Add: " << endl; 
    //c.Output(); 
    //c.Output_as_arratList(); 
    d.Multiply(a,b); 
    //cout << endl << "Multiply: " << endl; 
    //d.Output(); 
    //d.Output_as_arratList(); 
} 
