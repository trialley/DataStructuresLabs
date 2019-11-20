#include<iostream>
using namespace std;
class Age
{
  public:
       Age(){i=0;};
       
	   Age& operator++()
       {
          cout<<this<<endl;
		  ++i;
		  this->show();
          return *this;
       }
       
	   const Age operator++(int)
       {
          cout<<this<<endl;
		  Age tmp = *this;
		  (*this).i=(*this).i+1; 
		  this->show();
          return tmp;
       }
       
	   void show(){cout<<i<<endl;};
    private:
       int i;
};
int main()
{
   Age a;
   cout<<&a<<endl;
   (++a)++;
   a.show();
   return 0;
}

