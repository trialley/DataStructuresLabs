#pragma once
#include"Arraylist.cpp"
using namespace std;
template<class T>
class matrixTerm
{
	public:
	int row,col;
	T value;
	friend ostream& operator<<(ostream &out,matrixTerm<T> &A)
	{
		out<<"row="<<A.row<<",col="<<A.col<<",value="<<A.value<<endl;
	}
	bool operator<(matrixTerm<T> &A)
	{
		if(row<A.row) return true;
		if(row==A.row)
		{
			if(col<A.col) return true;
			else return false;
		}
		if(row>A.row) return false;
	}
	bool operator>(matrixTerm<T> &A)
	{
		if(row<A.row) return false;
		if(row==A.row)
		{
			if(col<A.col) return false;
			else return true;
		}
		if(row>A.row) return true;
	}
};

template<class T>
class sparseMatrix
{
	public:
		void transpose(sparseMatrix<T> &A)
		{//把*this转置后放入A
   A.row=row;
   A.col=col;
   A.terms.reSet(terms.size());
   
   int *colSize=new int[col+1]; //原矩阵每一列非零元素数量 
   int *rowNext=new int[col+1]; //原矩阵每一列第一个非0元素在一维数组中的索引 
   
   for(int i=1;i<col;i++)
     colSize[i]=0;
   for(typename Arraylist < matrixTerm<T> >::iterator i=terms.begin();i!=terms.end();i++)
   {   colSize[(*i).col]++;  }
   
   rowNext[1]=0;
   for(int i=2;i<=col;i++)
   {//记录下A中的每行起始点 
   	  rowNext[i]=rowNext[i-1]+colSize[i-1];
   } 
   
   matrixTerm<T> temp; 
   for(typename Arraylist < matrixTerm<T> >::iterator i=terms.begin();i!=terms.end();i++)
   {
   	  int j=rowNext[(*i).col]++;  //j是元素在A表中的位置
	  temp.row=(*i).row; 
	  temp.col=(*i).col;
	  temp.value=(*i).value;
	  A.terms.set(j,temp); 
   }  
}
		void add(sparseMatrix<T> &B,sparseMatrix<T> &C)
		{//计算C=(*this)+B
    if(row!=B.row||col!=B.col)
	  std::cerr<<"矩阵不相容！\n"; 
   //设置结果矩阵的特征 
  	C.row=row;
  	C.col=col;
    //C.terms.clear();  加这个就会报错,出现奇怪的数字 
  	int Csize=0;
   //定义*this和B的迭代器
   typename Arraylist < matrixTerm<T> >::iterator it=terms.begin();
   typename Arraylist < matrixTerm<T> >::iterator itend=terms.end();
   typename Arraylist < matrixTerm<T> >::iterator ib=B.terms.begin();
   typename Arraylist < matrixTerm<T> >::iterator ibend=B.terms.end();
   //遍历*this和B，把相关项相加
   while(it!=itend&&ib!=ibend)
   {
   	  int tIndex=( (*it).row-1 ) * col+(*it).col;
   	  int bIndex=( (*ib).row-1 ) * col+(*ib).col;
   	  //确定索引，然后比较大小
	  if(tIndex<bIndex)
	  {//如果前者小 
	  	 C.terms.insert(Csize++,(*it));
	  	 it++;
	   } 
	
	   if(tIndex>bIndex)
	   {//如果前者大 
	   	  C.terms.insert(Csize++,(*ib));
	   	  ib++;
	   }
	   
	   if(tIndex==bIndex)
	   {//先看两个矩阵对应元素的和是否等于0 
	   	   if((*it).value+(*ib).value==0)
	   	   {  it++;  ib++;  }
	   	   else
		  {
			matrixTerm<T> temp;
			temp.col=(*it).col;
			temp.row=(*it).row;
			temp.value=(*it).value+(*ib).value;
	   	 	C.terms.insert(Csize++,temp);
	   	 	it++;   ib++;
		  }
	   }	  
   }
   //处理剩余的元素
   for( ;it!=itend;it++)
    C.terms.insert(Csize++,(*it));
   for( ;ib!=ibend;ib++)
    C.terms.insert(Csize++,(*ib));
   	
}
		friend ostream& operator<<(ostream &out,sparseMatrix<T> &A)
		{//重载输出运算符
		 //首先输出矩阵特征 
		 int size=A.terms.size();
		 out<<"行数："<<A.row<<"\t列数："<<A.col<<"\t非0元素个数:"<<size<<endl;
			for(typename Arraylist< matrixTerm<T> >::iterator i=A.terms.begin();i!=A.terms.end();i++ )
			{
				out<<"a("<<(*i).row<<","<<(*i).col<<")="<<(*i).value<<"\t";
			}
			return out;
		}
		friend istream& operator>>(istream &in,sparseMatrix<T> &A)
		{//重载输入运算符，以行主次序输入
	     //首先输入矩阵特征
		    int num;
			cout<<"请输入该稀疏矩阵的行数、列数和非0元素数量"<<endl;
			in>>A.row>>A.col>>num;
			  if(A.row<=0||A.col<=0||num<0||num>A.row*A.col)
			  {//检查合法性 
			  	cerr<<"输入数据非法！"<<endl;
			  }
		 //设置arraylist term的大小 
		    A.terms.reSet(num);
		//输入每一项
		    matrixTerm<T> temp_term;
			for(int i=1;i<=num;i++)
			{
				cout<<"请输入第"<<i<<"个元素行号、列号和元素值"<<endl;
				in>>temp_term.row>>temp_term.col>>temp_term.value;
				if(temp_term.row<0||temp_term.row>A.row||temp_term.col<0||temp_term.col>A.col)
				   {//检查合法性 
				   	 cerr<<"输入数据非法！"<<endl;
				   }
				A.terms.set(i-1,temp_term);
			}
			return in;
		}
		sparseMatrix& operator*(sparseMatrix<T> &B)
		{//稀疏矩阵乘法，将*this和B相乘返回一个新矩阵 
            if(col!=B.row)
            {
    	       cerr<<"数学错误！"<<endl;
    	       exit(1);
            }
	        //下面是创建临时的结果矩阵 ,并初始化 
	        int i=0,j=0,k=0,rc=0;
	        sparseMatrix<T> *Res=new sparseMatrix<T>;  //其中的arraylist默认好像只有10个长度，非也 
         	Res->row=row;
	        Res->col=B.col;
           
    //当*this和A矩阵中元素都没有处理完 
         for(i=0;i<terms.size();i++)
         {//把*this中的一个元素拿来和A中对应元素相比较
            for(j=0;j<B.terms.size();j++)
            {
            	if(terms.element[i].col==B.terms.element[j].row)
            	{//发现可以相乘的项 
            	    matrixTerm<T> TEMP;
            	    TEMP.row=terms.element[i].row;  TEMP.col=B.terms.element[j].col;
            	    TEMP.value=terms.element[i].value*B.terms.element[j].value;
            	    cout<<TEMP<<endl;
            		if( Res->terms.Term_search(TEMP)==-1 )
            		{//若在已保存的数对中没有下标相同的数对
            			//Res->terms.element[rc++]=TEMP;
            			Res->terms.insert(rc++,TEMP);
            			//Res->terms.listSize++;
         			}
            		 else if(Res->terms.Term_search(TEMP)>=0)
         		    { //若已经存在下标相同的数对,把前后的结果相加 
	         		   int index=Res->terms.Term_search(TEMP);
			           Res->terms.element[index].value+=TEMP.value;
		         	}
	           }
	       }	  
        } 
           return  *Res;
       }
		void matrix_print()
		{//看我一波操作，不用二维数组！！ 
			 terms.matrixTerm_sort();
			 int k=0;
			 for(int i=1;i<=row;i++)
			 {
			 	for(int j=1;j<=col;j++)
			 	{
			 		if( terms.element[k].row==i && terms.element[k].col==j )
					     cout<<terms.element[k++].value<<" ";
					else cout<<"0 ";
				 }
				 cout<<endl;
			 }
		/*	for(int i=1;i<=row;i++)
			{
			    for(int j=1;j<=col;j++)
			 	 cout<<A[i][j]<<" ";
			 	cout<<endl; 
			}*/
		}
	private:
		int row,col;//矩阵特征 
		Arraylist < matrixTerm<T> > terms;  //非0项表 
};
