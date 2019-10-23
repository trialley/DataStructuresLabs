//ʹ��ģ������ô<<��������أ� 
#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;

template<class T>
class linearlist //���������Ա� 
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
		{//�����������û��为�� 
			element=new T [initialCapacity];  //�����Ѿ���ʼ����һ�顣 
			arrayLength=initialCapacity;
			listSize=0;
			string name,tel_num,Class,dor_room;
	/*			cin>>name>>tel_num>>Class>>dor_room;
				element[1] (name,tel_num,Class,dor_room);*/
			cout<<"������"<<initialCapacity<<"������"<<"���������绰���롢�༶�����ᣩ"<<endl;
			for(int i=0;i<initialCapacity;i++)
			{
				cin>>name>>tel_num>>Class>>dor_room;
				T temp(name,tel_num,Class,dor_room);
				element[i]=temp;  //����Ӧ�õ��ø��ƹ��캯�� ,��Ƥû�����ã�������		
			}
			listSize=initialCapacity;
		}
	    Arraylist(string STR,int initialCapacity)
		{
			element=new T [initialCapacity];  //�����Ѿ���ʼ����һ�顣 
			arrayLength=initialCapacity;
			listSize=0;
			int i=0;
		    char ch[50];
			strcpy( ch,STR.c_str() );  //stringתchar 
			fstream fin;
			fin.open(ch);
			
			if(!fin) 
			{
			   cerr<<"open error!"<<endl;  return;
		    }
			while(!fin.eof())  //����ѭ��������infileΪ��
			{
				/*infile.getline(element[i++],sizeof(element[0]),'\n');
				getline��֧���ַ����ĸ���,������copy*/
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
		
		//ADT����
		bool empty() const
		{    return listSize==0;   }
		int size() const 
		{    return listSize;	   }
		T& get(int theIndex) const
		{//ʵ������洢��Ч�ʼ��� O(1) 
	       checkIndex(theIndex);
	       return element[theIndex];
        }
		int indexOf(T& x) const
		{//����Ԫ��x��һ�γ���ʱ������;�������ڣ��򷵻�-1 
	         for(int i=0;i<listSize;i++)
	         {
		       if(x==element[i])  return i;
	         }
	          return -1;
        }
		T& search(string str) const
		{//����ҵ��˶�Ӧ����(str���˵�����)���򷵻�Ԫ�飬���򷵻ؿ�ֵ 
			for(int i=0;i<listSize;i++)
	         {
		       if(str==element[i].name)  return element[i];
	         }
	         cerr<<"δ�ҵ���Ӧ����"<<endl;
        }
		void modify(string str)
		{//�����������ҵ���Ҫ�޸ĵ�Ԫ�� 
			for(int i=0;i<listSize;i++)
	         {
		       if(str==element[i].name)
		       {
		       	  cout<<"�ҵ�������¼!"<<endl<<"�������µ����ݣ����������绰���롢�༶�������޸ģ�:"<<endl;
		       	  cin>>element[i].name>>element[i].tel_num>>element[i].Class>>element[i].dor_room;
		       	  return;
			   }
	         }
			 cout<<"δ�ҵ�������¼"<<endl;	
		}
		void erase(int theIndex)
		{//�ӱ���ɾ������ΪtheIndex��Ԫ�� 
	       for(int i=theIndex;i<listSize-1;i++)
	       {
		      element[i]=element[i+1];
	       }
	       //cout<<"right!"<<endl;
	       element[--listSize].~T();  //������������������verstehen. ���������������������Ƕ�̬���� 
        }
		void insert(int theIndex,const T& theElement)
		{
	       if(theIndex<0||theIndex>listSize)
	       {
		      cerr<<"��������ȷ������"<<endl;
		      return;
		   }
	  
		   if(listSize==arrayLength)
		   {//����ռ����� 
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
	     	  element[i+1]=element[i];   //�ڶ��ε��ò��뺯�������������,ע�������±��Ǵ�0��ʼ�� 
	       }
	       	  element[theIndex]=theElement;
	       	  listSize++;
	    }
		void output() const
		{//��������Ա� 
		  for(int i=0;i<listSize;i++)
		  {
			  cout<<element[i];
		  }
	    }
		void class_output() const
		{//��������Ա� 
		  cout<<"��������Ҫ���ҵİ༶��Ϣ"<<endl;
		  string Class;
		  cin>>Class;
		  for(int i=0;i<listSize;i++)
		  {
			  if(element[i].Class==Class) 
			  {
			  	cout<<"�����Ǹ������������ݣ�"<<endl;
				cout<<element[i];
			  }
		  }
	    }
		//�������� 
		int capacity() const 
		{   return arrayLength;		}
		friend ostream& operator<< (ostream& out,const Arraylist<T> &A)  //ģ�������Ԫ����������ʵ�ֲ��ܷ��� 
    	{
        	for(int i=0;i<A.listSize;i++)
         	{   out<<A.element[i];  }
        	return out;
        }
		void save()
		{//������Ϣ��data.txt 
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
			{//ȷ����������Ч�ԣ���ֹԽ��
                if(theIndex<0||theIndex>=listSize)
	            {
		          cerr<<"������������Ч�ԣ�"<<endl;
	            }
            }
			 //��������Ч�����׳��쳣 
			T *element;  //�洢���Ա�Ԫ�ص�һά���� 
			int arrayLength;  //һά��������� 
			int listSize;  //���Ա��Ԫ�ظ��� 
		
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
	{//����Ҳ��string����Ҳ�Զ�������ô�� 
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
/*	person A("ZYB","17864207200","�ƿ�17.3","B121");
	person B("������ү","0571-110","�ƿ�17.3","B121");
	cout<<A<<B<<endl;
	
 	string name,tel_num,Class,dor_room;
	cin>>name>>tel_num>>Class>>dor_room;

     person temp(name,tel_num,Class,dor_room);
    person D(temp);  
     cout<<D;

    person *p=new person;
    (*p)=temp;   //�����û���ø��ƹ��캯��,Ϊʲô��  �������޷��ֶ����ø��ƹ��캯���� 
	cout<<(*p);
*/	


/*	int n;  cout<<"���������ݵ�����n"<<endl;
	cin>>n;*/
	 int num;
     cin>>num;
	Arraylist<person> C("data.txt",num);
	
    bool k=true;
	while(k)
	{
	int flag;
	cout<<"ִ�в������������1"<<endl<<"ִ��ɾ������������2"<<endl<<"ִ�б༭����������3"<<endl;
	cout<<"ִ�в��Ҳ���������4"<<endl<<"ִ�а༶����������5"<<endl; 
	cin>>flag;
	switch(flag)
	{
		case 1: {
			cout<<"�밴˳������Ҫ�����Ԫ������"<<endl;
			string name,tel_num,Class,dor_room;
	        cin>>name>>tel_num>>Class>>dor_room;
	        person A(name,tel_num,Class,dor_room);
	        cout<<"������Ҫ�����λ������(��0��ʼ)"<<endl;
	        int pos; cin>>pos;
			C.insert(pos,A); cout<<C<<endl;
			break;
		}
		case 2: {
			cout<<"������Ҫɾ��Ԫ������(��0��ʼ)"<<endl;
			int pos; cin>>pos;
			C.erase(pos);  cout<<C<<endl;
			break;
		}
		case 3: {
			cout<<"������Ҫ�޸ĵ���ϵ������"<<endl;
			string name;  cin>>name;
			C.modify(name); cout<<C;
			break;
		}
		case 4: {
			cout<<"������Ҫ���ҵ���ϵ������"<<endl;
			string name;  cin>>name;
			cout<<C.search(name)<<endl;
			break;
		}
		case 5: {
			C.class_output();
			break;
		}
	}
	cout<<"��Ҫ��������������continue,�������������ַ�"<<endl;
	string str;   cin>>str;
	if(str=="continue")  k=true;
	else k=false;
}
C.save();
	return 0;
}
