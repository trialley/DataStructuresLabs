#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class K> class hash;

template<>
class hash<string>
{//从一个string类型转换为一个size_t类型的非负整数 
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
{//从int转size_t 
   public:
      size_t operator()(const int theKey) const
      {return size_t(theKey);}
};


