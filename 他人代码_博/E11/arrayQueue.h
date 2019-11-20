
#pragma once
#include<iostream>
#include<cstdlib> 
#include<algorithm>
template<class T>
class arrayQueue
{
	public:
		arrayQueue(int initialCapacity = 10)
		{//11?足o‘那y 
			if(initialCapacity<0) std::cerr<<"?車芍D3∟?豕㊣?D?∩車車迆0㏒?"<<std::endl;
			else{
				Queue=new T[initialCapacity];
				arrayLength=initialCapacity;
				qFront=qBack=0;     //?a角?那?∩車Queue[1]?a那?2?豕??a?? 
			}
		}
        ~arrayQueue() {delete [] Queue;}
        bool empty() const
        {
        	if(qFront==qBack) return true;
        	else return false;
		}
        int size() const
        {
        	return (arrayLength+qBack-qFront)%arrayLength;
		}
        T& front()
        {
        	if(empty()!=true)
			  return Queue[(qFront+1)%arrayLength];
			else
			  {  std::cerr<<"?車芍D?a??"<<std::endl; exit(1);  }
		}
        T& back()
        {
        	if(empty()!=true)
        	  return Queue[qBack];
        	else
		      {  std::cerr<<"?車芍D?a??"<<std::endl; exit(1);  }
		}
        T pop()
        {//∩車?車那℅谷?3y?a?? 
        	T *p=&front(); //?a角?辰??-?D??芍??車芍D那?﹞??a?? 
        	T temp=(*p);
        	qFront=(qFront+1)%arrayLength;
        	(*p).~T();  //??11那℅?a??o???2??邦㊣赤那?int米?谷?3y...㏒??赤那??T﹞“???∩米?3?那??‘辰??～米?℅∩足?
			return temp; 
		}
        void push(const T& ele)
        {//∩車?車?2足赤?車?a?? 
        	if( (qBack+1)%arrayLength==qFront )
        	{//?車芍D???迆㏒??車㊣?那y℅谷3∟?豕 
        		T *newQueue=new T[2*arrayLength];
        		int start=(qFront+1)%arrayLength;
        		if(start==0||start==1)
        		{//?∩D?3谷?﹞ 
        			std::copy(Queue+start,Queue+qBack+1,newQueue);
				}
				else
				{//D?3谷芍??﹞ 
					std::copy(Queue+start,Queue+arrayLength,newQueue); 
					//?∩??米迆2??(start,?車芍D????㏒?D??車芍D?e米?㏒? 
					std::copy(Queue,Queue+qBack+1,newQueue+(arrayLength-start));
					//?∩??米迆1??㏒“?-?車芍D那℅??㏒?qback,D??車芍D米迆arraylength-start??????㏒? 
				}
				qFront=(arrayLength)*2-1;
			    qBack=arrayLength-1-1;   //??D?谷豕??那℅?2車?㊣那 
				arrayLength=arrayLength*2;
				delete [] Queue;
				Queue=newQueue;
			}
			//～??a??2?豕??車芍D米??22?
			qBack=(qBack+1)%arrayLength;
			Queue[qBack]=ele;
			
		}
		void output()
		{
			for(int i=qFront;i<qBack;i++)
			   std::cout<<Queue[i];
			std::cout<<std::endl;   
		} 
	private:
		int qFront;  //?車芍D?D米迆辰????a??米??～辰????∩?a 
		int qBack;   //?車芍D℅?o車辰????a??米????? 
		int arrayLength;  //?車芍D米?豕Y芍? 
		T *Queue;	 //?車芍D?a?? 
};
