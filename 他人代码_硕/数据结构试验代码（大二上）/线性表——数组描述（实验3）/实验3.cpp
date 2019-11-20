//使用模板类怎么<<运算符重载？ 
#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;

template<class T>
class linearlist //抽象类线性表 
{
	public:
		virtual ~linearlist() {	}
		virtual bool empty() const=0;
		virtual int size() const=0;
		virtual T& get(int theIndex) const=0;
		virtual int indexOf(T& theElement) const=0;
		virtual void erase(int theIndex)=0;
		virtual void insert(int theIndex,const T& theElement)=0;
		virtual void output() const = 0;
};

template<class T>
class Arraylist :public linearlist<T>
{
	public:
		Arraylist(int initialCapacity=10)
		{//不考虑智障用户输负数 
			element=new T [initialCapacity];  //这里已经初始化了一遍。 
			arrayLength=initialCapacity;
			listSize=0;
			string name,tel_num,Class,dor_room;
	/*			cin>>name>>tel_num>>Class>>dor_room;
				element[1] (name,tel_num,Class,dor_room);*/
			cout<<"请输入"<<initialCapacity<<"条数据"<<"（姓名、电话号码、班级、宿舍）"<<endl;
			for(int i=0;i<initialCapacity;i++)
			{
				cin>>name>>tel_num>>Class>>dor_room;
				T temp(name,tel_num,Class,dor_room);
				element[i]=temp;  //这里应该调用复制构造函数 ,瓜皮没法调用？！？！		
			}
			listSize=initialCapacity;
		}
	    Arraylist(string STR,int initialCapacity)
		{
			element=new T [initialCapacity];  //这里已经初始化了一遍。 
			arrayLength=initialCapacity;
			listSize=0;
			int i=0;
		    char ch[50];
			strcpy( ch,STR.c_str() );  //string转char 
			fstream fin;
			fin.open(ch);
			
			if(!fin) 
			{
			   cerr<<"open error!"<<endl;  return;
		    }
			while(!fin.eof())  //跳出循环条件是infile为空
			{
				/*infile.getline(element[i++],sizeof(element[0]),'\n');
				getline仅支持字符串的复制,考虑下copy*/
			    fin>>element[i].name;
				fin>>element[i].tel_num;
				fin>>element[i].Class;
				fin>>element[i].dor_room;
				cout<<element[i]<<endl;
				i++;  listSize++;
			}
			fin.close();
		}
		Arraylist(const Arraylist<T>& A)
		{
			listSize=A.listSize;
			arrayLength=A.arrayLength;
			element=new T [arrayLength];
			for(int i=0;i<listSize;i++)
			{
				element[i]=A.element[i];
			}
		}
		~Arraylist() { delete [] element;	}
		
		//ADT方法
		bool empty() const
		{    return listSize==0;   }
		int size() const 
		{    return listSize;	   }
		T& get(int theIndex) const
		{//实现随机存储，效率极高 O(1) 
	       checkIndex(theIndex);
	       return element[theIndex];
        }
		int indexOf(T& x) const
		{//返回元素x第一次出现时的索引;若不存在，则返回-1 
	         for(int i=0;i<listSize;i++)
	         {
		       if(x==element[i])  return i;
	         }
	          return -1;
        }
		T& search(string str) const
		{//如果找到了对应的人(str是人的名字)，则返回元组，否则返回空值 
			for(int i=0;i<listSize;i++)
	         {
		       if(str==element[i].name)  return element[i];
	         }
	         cerr<<"未找到对应数据"<<endl;
        }
		void modify(string str)
		{//根据姓名来找到需要修改的元组 
			for(int i=0;i<listSize;i++)
	         {
		       if(str==element[i].name)
		       {
		       	  cout<<"找到该条记录!"<<endl<<"请输入新的数据（按姓名、电话号码、班级、宿舍修改）:"<<endl;
		       	  cin>>element[i].name>>element[i].tel_num>>element[i].Class>>element[i].dor_room;
		       	  return;
			   }
	         }
			 cout<<"未找到该条记录"<<endl;	
		}
		void erase(int theIndex)
		{//从表中删除索引为theIndex的元素 
	       for(int i=theIndex;i<listSize-1;i++)
	       {
		      element[i]=element[i+1];
	       }
	       //cout<<"right!"<<endl;
	       element[--listSize].~T();  //调用析构函数。？？verstehen. 单个类对象的析构，并不是动态调用 
        }
		void insert(int theIndex,const T& theElement)
		{
	       if(theIndex<0||theIndex>listSize)
	       {
		      cerr<<"请输入正确索引！"<<endl;
		      return;
		   }
	  
		   if(listSize==arrayLength)
		   {//数组空间已满 
			    T *p=new T[2*arrayLength];
			    for(int i=0;i<listSize;i++)
		       	{
	       			p[i]=element[i];
	       		}
	       		delete [] element;
	       		element=p;
	       		arrayLength*=2;
	       }
	       //cout<<"listSize is "<<listSize<<endl;
	       for(int i=listSize-1;i>=theIndex;i--)
	       {
	     	  element[i+1]=element[i];   //第二次调用插入函数错误出在这里,注意数组下标是从0开始的 
	       }
	       	  element[theIndex]=theElement;
	       	  listSize++;
	    }
		void output() const
		{//输出该线性表 
		  for(int i=0;i<listSize;i++)
		  {
			  cout<<element[i];
		  }
	    }
		void class_output() const
		{//输出该线性表 
		  cout<<"请输入想要查找的班级信息"<<endl;
		  string Class;
		  cin>>Class;
		  for(int i=0;i<listSize;i++)
		  {
			  if(element[i].Class==Class) 
			  {
			  	cout<<"以下是复合条件的数据："<<endl;
				cout<<element[i];
			  }
		  }
	    }
		//其他方法 
		int capacity() const 
		{   return arrayLength;		}
		friend ostream& operator<< (ostream& out,const Arraylist<T> &A)  //模板类的友元函数声明与实现不能分离 
    	{
        	for(int i=0;i<A.listSize;i++)
         	{   out<<A.element[i];  }
        	return out;
        }
		void save()
		{//保存信息至data.txt 
			fstream fout("data.txt");
			if(!fout) { cerr<<"save failure!"<<endl;	}
			else
			{
				for(int i=0;i<listSize;i++)
				{
					fout<<element[i].name<<" ";
					fout<<element[i].tel_num<<" ";
				    fout<<element[i].Class<<" ";
				    fout<<element[i].dor_room;
				    fout<<endl;
				}
			}
			fout.close();
		}
		protected:
			void checkIndex(int theIndex)  const
			{//确定索引的有效性，防止越界
                if(theIndex<0||theIndex>=listSize)
	            {
		          cerr<<"请检查索引的有效性！"<<endl;
	            }
            }
			 //若索引无效，则抛出异常 
			T *element;  //存储线性表元素的一维数组 
			int arrayLength;  //一维数组的容量 
			int listSize;  //线性表的元素个数 
		
};

class person
{
	public:
	string name,tel_num,Class,dor_room;
	person() { }
	person(string name1,string tel_num1,string Class1,string dor_room1)
	{
		name=name1; tel_num=tel_num1; Class=Class1; dor_room=dor_room1;
	}
	person(const person& T)
	{
		name=T.name; tel_num=T.tel_num; Class=T.Class; dor_room=T.dor_room;
	}
	~person() 
	{//这里也把string变量也自动析构了么？ 
	}
	
	friend ostream& operator<<(ostream& out,const person &A);
	bool operator ==(const person &A)
	{
		if(name==A.name)
		{
			if(tel_num==A.tel_num)
			{
				if(Class==A.Class)
				{
					if(dor_room==A.dor_room)
					  return true;
				}
			}
		 }
		 return false; 
	}	
    person& operator *()
    {
    	return *this;
	}
    person& operator=(const person& T)
    {
    	name=T.name; tel_num=T.tel_num; Class=T.Class; dor_room=T.dor_room;
	}
};

ostream& operator<<(ostream& out,const person &A)
{
	out<<A.name<<"\t"<<A.tel_num<<"\t"<<A.Class<<"\t"<<A.dor_room<<endl;
	return out;
}

int main()
{
/*	person A("ZYB","17864207200","计科17.3","B121");
	person B("洪坤姥爷","0571-110","计科17.3","B121");
	cout<<A<<B<<endl;
	
 	string name,tel_num,Class,dor_room;
	cin>>name>>tel_num>>Class>>dor_room;

     person temp(name,tel_num,Class,dor_room);
    person D(temp);  
     cout<<D;

    person *p=new person;
    (*p)=temp;   //这里就没法用复制构造函数,为什么？  人类是无法手动调用复制构造函数的 
	cout<<(*p);
*/	


/*	int n;  cout<<"请输入数据的条数n"<<endl;
	cin>>n;*/
	 int num;
     cin>>num;
	Arraylist<person> C("data.txt",num);
	
    bool k=true;
	while(k)
	{
	int flag;
	cout<<"执行插入操作请输入1"<<endl<<"执行删除操作请输入2"<<endl<<"执行编辑操作请输入3"<<endl;
	cout<<"执行查找操作请输入4"<<endl<<"执行班级搜索请输入5"<<endl; 
	cin>>flag;
	switch(flag)
	{
		case 1: {
			cout<<"请按顺序输入要插入的元组数据"<<endl;
			string name,tel_num,Class,dor_room;
	        cin>>name>>tel_num>>Class>>dor_room;
	        person A(name,tel_num,Class,dor_room);
	        cout<<"请输入要插入的位置索引(从0开始)"<<endl;
	        int pos; cin>>pos;
			C.insert(pos,A); cout<<C<<endl;
			break;
		}
		case 2: {
			cout<<"请输入要删除元组索引(从0开始)"<<endl;
			int pos; cin>>pos;
			C.erase(pos);  cout<<C<<endl;
			break;
		}
		case 3: {
			cout<<"请输入要修改的联系人姓名"<<endl;
			string name;  cin>>name;
			C.modify(name); cout<<C;
			break;
		}
		case 4: {
			cout<<"请输入要查找的联系人姓名"<<endl;
			string name;  cin>>name;
			cout<<C.search(name)<<endl;
			break;
		}
		case 5: {
			C.class_output();
			break;
		}
	}
	cout<<"如要继续操作请输入continue,否则输入任意字符"<<endl;
	string str;   cin>>str;
	if(str=="continue")  k=true;
	else k=false;
}
C.save();
	return 0;
}
