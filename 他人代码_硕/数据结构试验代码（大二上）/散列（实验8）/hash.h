#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class K> class hash;

template<>
class hash<string>
{//��һ��string����ת��Ϊһ��size_t���͵ķǸ����� 
   public:
      size_t operator()(const string theKey) const
      {
         unsigned long hashValue = 0; 
         int length = (int) theKey.length();
         for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);
    
         return size_t(hashValue);
      }
};

template<>
class hash<int>
{//��intתsize_t 
   public:
      size_t operator()(const int theKey) const
      {return size_t(theKey);}
};


