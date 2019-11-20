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
		{//��*thisת�ú����A
   A.row=row;
   A.col=col;
   A.terms.reSet(terms.size());
   
   int *colSize=new int[col+1]; //ԭ����ÿһ�з���Ԫ������ 
   int *rowNext=new int[col+1]; //ԭ����ÿһ�е�һ����0Ԫ����һά�����е����� 
   
   for(int i=1;i<col;i++)
     colSize[i]=0;
   for(typename Arraylist < matrixTerm<T> >::iterator i=terms.begin();i!=terms.end();i++)
   {   colSize[(*i).col]++;  }
   
   rowNext[1]=0;
   for(int i=2;i<=col;i++)
   {//��¼��A�е�ÿ����ʼ�� 
   	  rowNext[i]=rowNext[i-1]+colSize[i-1];
   } 
   
   matrixTerm<T> temp; 
   for(typename Arraylist < matrixTerm<T> >::iterator i=terms.begin();i!=terms.end();i++)
   {
   	  int j=rowNext[(*i).col]++;  //j��Ԫ����A���е�λ��
	  temp.row=(*i).row; 
	  temp.col=(*i).col;
	  temp.value=(*i).value;
	  A.terms.set(j,temp); 
   }  
}
		void add(sparseMatrix<T> &B,sparseMatrix<T> &C)
		{//����C=(*this)+B
    if(row!=B.row||col!=B.col)
	  std::cerr<<"�������ݣ�\n"; 
   //���ý����������� 
  	C.row=row;
  	C.col=col;
    //C.terms.clear();  ������ͻᱨ��,������ֵ����� 
  	int Csize=0;
   //����*this��B�ĵ�����
   typename Arraylist < matrixTerm<T> >::iterator it=terms.begin();
   typename Arraylist < matrixTerm<T> >::iterator itend=terms.end();
   typename Arraylist < matrixTerm<T> >::iterator ib=B.terms.begin();
   typename Arraylist < matrixTerm<T> >::iterator ibend=B.terms.end();
   //����*this��B������������
   while(it!=itend&&ib!=ibend)
   {
   	  int tIndex=( (*it).row-1 ) * col+(*it).col;
   	  int bIndex=( (*ib).row-1 ) * col+(*ib).col;
   	  //ȷ��������Ȼ��Ƚϴ�С
	  if(tIndex<bIndex)
	  {//���ǰ��С 
	  	 C.terms.insert(Csize++,(*it));
	  	 it++;
	   } 
	
	   if(tIndex>bIndex)
	   {//���ǰ�ߴ� 
	   	  C.terms.insert(Csize++,(*ib));
	   	  ib++;
	   }
	   
	   if(tIndex==bIndex)
	   {//�ȿ����������ӦԪ�صĺ��Ƿ����0 
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
   //����ʣ���Ԫ��
   for( ;it!=itend;it++)
    C.terms.insert(Csize++,(*it));
   for( ;ib!=ibend;ib++)
    C.terms.insert(Csize++,(*ib));
   	
}
		friend ostream& operator<<(ostream &out,sparseMatrix<T> &A)
		{//������������
		 //��������������� 
		 int size=A.terms.size();
		 out<<"������"<<A.row<<"\t������"<<A.col<<"\t��0Ԫ�ظ���:"<<size<<endl;
			for(typename Arraylist< matrixTerm<T> >::iterator i=A.terms.begin();i!=A.terms.end();i++ )
			{
				out<<"a("<<(*i).row<<","<<(*i).col<<")="<<(*i).value<<"\t";
			}
			return out;
		}
		friend istream& operator>>(istream &in,sparseMatrix<T> &A)
		{//�����������������������������
	     //���������������
		    int num;
			cout<<"�������ϡ�����������������ͷ�0Ԫ������"<<endl;
			in>>A.row>>A.col>>num;
			  if(A.row<=0||A.col<=0||num<0||num>A.row*A.col)
			  {//���Ϸ��� 
			  	cerr<<"�������ݷǷ���"<<endl;
			  }
		 //����arraylist term�Ĵ�С 
		    A.terms.reSet(num);
		//����ÿһ��
		    matrixTerm<T> temp_term;
			for(int i=1;i<=num;i++)
			{
				cout<<"�������"<<i<<"��Ԫ���кš��кź�Ԫ��ֵ"<<endl;
				in>>temp_term.row>>temp_term.col>>temp_term.value;
				if(temp_term.row<0||temp_term.row>A.row||temp_term.col<0||temp_term.col>A.col)
				   {//���Ϸ��� 
				   	 cerr<<"�������ݷǷ���"<<endl;
				   }
				A.terms.set(i-1,temp_term);
			}
			return in;
		}
		sparseMatrix& operator*(sparseMatrix<T> &B)
		{//ϡ�����˷�����*this��B��˷���һ���¾��� 
            if(col!=B.row)
            {
    	       cerr<<"��ѧ����"<<endl;
    	       exit(1);
            }
	        //�����Ǵ�����ʱ�Ľ������ ,����ʼ�� 
	        int i=0,j=0,k=0,rc=0;
	        sparseMatrix<T> *Res=new sparseMatrix<T>;  //���е�arraylistĬ�Ϻ���ֻ��10�����ȣ���Ҳ 
         	Res->row=row;
	        Res->col=B.col;
           
    //��*this��A������Ԫ�ض�û�д����� 
         for(i=0;i<terms.size();i++)
         {//��*this�е�һ��Ԫ��������A�ж�ӦԪ����Ƚ�
            for(j=0;j<B.terms.size();j++)
            {
            	if(terms.element[i].col==B.terms.element[j].row)
            	{//���ֿ�����˵��� 
            	    matrixTerm<T> TEMP;
            	    TEMP.row=terms.element[i].row;  TEMP.col=B.terms.element[j].col;
            	    TEMP.value=terms.element[i].value*B.terms.element[j].value;
            	    cout<<TEMP<<endl;
            		if( Res->terms.Term_search(TEMP)==-1 )
            		{//�����ѱ����������û���±���ͬ������
            			//Res->terms.element[rc++]=TEMP;
            			Res->terms.insert(rc++,TEMP);
            			//Res->terms.listSize++;
         			}
            		 else if(Res->terms.Term_search(TEMP)>=0)
         		    { //���Ѿ������±���ͬ������,��ǰ��Ľ����� 
	         		   int index=Res->terms.Term_search(TEMP);
			           Res->terms.element[index].value+=TEMP.value;
		         	}
	           }
	       }	  
        } 
           return  *Res;
       }
		void matrix_print()
		{//����һ�����������ö�ά���飡�� 
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
		int row,col;//�������� 
		Arraylist < matrixTerm<T> > terms;  //��0��� 
};
