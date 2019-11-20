#ifndef myExceptions_
#define myExceptions_
#include <string>
using namespace std;

class illegalValue {
public:
    illegalValue(string s)
        {cout<<s<<endl;}
    illegalValue(){}; 
};

class matrixIndexOutOfBounds {
public:
    matrixIndexOutOfBounds(string s)
        {cout<<s<<endl;}
    matrixIndexOutOfBounds(){}; 
};

class matrixSizeMismatch {
public:
    matrixSizeMismatch(string s)
        {cout<<s<<endl;}
    matrixSizeMismatch(){}
};

class stackEmpty{
public:
    stackEmpty(string s)
        {cout<<s<<endl;}
    stackEmpty(){};
};

class queueEmpty{
public:
    queueEmpty(string s)
        {cout<<s<<endl;}
    queueEmpty(){}
};

class hashTableFull{
public:
    hashTableFull(string s)
        {cout<<s<<endl;}
    hashTableFull(){}
};

class undefinedEdgeWeight{
public:
    undefinedEdgeWeight(string s)
        {cout<<s<<endl;}
    undefinedEdgeWeight(){}
        
};

class undefinedMethod{
public:
    undefinedMethod(string s)
        {cout<<s<<endl;}
    undefinedMethod(){}
};
#endif
