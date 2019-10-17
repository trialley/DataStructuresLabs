//#include <iostream> 
using namespace std; 
template <class T> 
class arrayList 
{ 
    protected: 
        T* Element; 
        long long int arrayLength; 
        long long int listSize; 
        void checkIndex(long long int theIndex) const;  //检查索引值
    public: 
        arrayList(long long int initialCapacity = 1000);  //构造函数
        ~arrayList() {delete []Element;}      //析构函数
        arrayList(const arrayList<T>&);       //复制构造函数
        bool Empty() {return listSize==0;}    //判断是否为空
        long long int Size() {return listSize;}         //返回数组的大小
        T& Get(long long int theIndex);                 //获取索引值对应元素        
		long long int indexOf(T& theElement);           //获取元素索引值
        void  Insert(long  long  int  theIndex,  const  T&  theElement);            //插入元素
        void Erase(long long int theIndex);   //删除元素
        void reSet(long long int theSize);   //保证充足的空间
        void Set(long long int theIndex, const T& theElement); //重设索引值
        void OutputA();    //输出线性表的元素
}; 

template <class T> 
arrayList<T>::arrayList(long long int initialCapacity) 
{ 
    if (initialCapacity < 1) 
    { 
        cout << "wrong capacity" << endl; 
        return; 
    } 
    arrayLength = initialCapacity; 
    Element = new T[arrayLength]; 
    listSize = 0; 
} 
/*
复制构造函数
*/ 
template <class T> 
arrayList<T>::arrayList(const arrayList<T>& theList) 
{ 
    arrayLength = theList.arrayLength; 
    listSize = theList.listSize; 
    Element = new T[arrayLength]; 
    for (long long int i=0; i<listSize; i++) 
        Element[i] = theList.Element[i]; 
} 
/*
检查索引
*/ 
template <class T> 
void arrayList<T>::checkIndex(long long int theIndex) const 
{ 
    if(theIndex<0 || theIndex>=listSize) 
    { 
        cout << "error Index" << endl; 
        return; 
    } 
} 
/*
获取索引值对应元素
*/ 
template <class T> 
T& arrayList<T>::Get(long long int theIndex) 
{ 
    checkIndex(theIndex); 
    return Element[theIndex]; 
} 
/*
获取元素索引值
*/ 
template <class T> 
long long int arrayList<T>::indexOf(T& theElement) 
{ 
    for(long long int i=0; i<listSize; i++) 
        if(Element[i] == theElement) 
            return i; 
    return -1; 
} 
/*
改变数组长度
*/ 
template <class T> 
void  changeLength(T*&a,  long  long  int  oldLength,  long  long  int  
newLength) 
{ 
    if (newLength < 0) 
    { 
        cout << "error: wrong capacity" << endl; 
        return; 
    } 
    T* temp = new T[newLength]; 
    long long int number = min(oldLength,newLength); 
    for (long long int i=0; i<number; i++) 
        temp[i] = a[i]; 
    delete []a; 
    a = temp; 
} 
/*
插入
*/ 
template <class T> 
void   arrayList<T>::Insert(long   long   int   theIndex,   const   T&   
theElement) 
{ 
    if (theIndex<0 || theIndex>listSize) 
    { 
        cout << "wrong index" << endl; 
        cout << "index = " << theIndex << " size = " << listSize << endl; 
        return; 
    }   //检查
    if (listSize == arrayLength) 
    { 
        changeLength(Element, arrayLength, 2*arrayLength); 
        arrayLength *= 2; 
    } 
    for (long long int i=listSize-1; i>=theIndex; i--)//插入位置之后的元素后移
        Element[i+1] = Element[i]; 
    Element[theIndex] = theElement; 
    listSize++; 
} 
/*
删除元素
*/ 
template <class T> 
void arrayList<T>::Erase(long long int theIndex) 
{ 
    checkIndex(theIndex); 
    for (long long int i=theIndex; i<listSize; i++)//元素前移
        Element[i-1] = Element[i]; 
    Element[--listSize].~T(); 
} 
/*
保证充足的空间
*/ 
template <class T> 
void arrayList<T>::reSet(long long int theSize) 
{ 
    if (theSize < 0) 
    { 
        cout << "wrong capacity" << endl; 
        return; 
    } 
    if (theSize > arrayLength) 
    { 
        delete []Element; 
        Element = new T[theSize]; 
        arrayLength = theSize; 
    } 
    listSize = theSize; 
} 
/*
重设索引值
*/ 
template <class T> 
void arrayList<T>::Set(long long int theIndex, const T& theElement) 
{ 
    if (theIndex < 0 || theIndex >= listSize) 
    { 
        cout << "wrong index" << endl; 
        cout << "index = " << theIndex << " size = " << listSize << endl; 
        return; 
    }//检查
    Element[theIndex]  = theElement; 
} 
/*
输出线性表的元素
*/ 
template <class T> 
void arrayList<T>::OutputA() 
{ 
    for (long long int i=0; i<listSize; i++) 
        Element[i].OutputM(); 
    cout << endl; 
} 
