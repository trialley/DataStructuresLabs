#pragma once
#include <iostream>
#include <string>
using namespace std;

class hash{ //string hash◊®“µ∞Ê£¨÷ÿ‘ÿint£¨long 
public:
    size_t operator()(const string theKey) const{
        unsigned long hashValue = 0; 
        int length = (int) theKey.length();
        for (int i = 0; i < length; i++) hashValue = 5 * hashValue + theKey.at(i);
        return size_t(hashValue);
    }
    size_t operator()(const int theKey) const
    {return size_t(theKey);}
    size_t operator()(const long theKey) const
    {return size_t(theKey);}
};

