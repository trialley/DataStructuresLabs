//#include <iostream> 
using namespace std; 
template <class T> 
class arrayList 
{ 
    protected: 
        T* Element; 
        long long int arrayLength; 
        long long int listSize; 
        void checkIndex(long long int theIndex) const;  //�������ֵ
    public: 
        arrayList(long long int initialCapacity = 1000);  //���캯��
        ~arrayList() {delete []Element;}      //��������
        arrayList(const arrayList<T>&);       //���ƹ��캯��
        bool Empty() {return listSize==0;}    //�ж��Ƿ�Ϊ��
        long long int Size() {return listSize;}         //��������Ĵ�С
        T& Get(long long int theIndex);                 //��ȡ����ֵ��ӦԪ��        
		long long int indexOf(T& theElement);           //��ȡԪ������ֵ
        void  Insert(long  long  int  theIndex,  const  T&  theElement);            //����Ԫ��
        void Erase(long long int theIndex);   //ɾ��Ԫ��
        void reSet(long long int theSize);   //��֤����Ŀռ�
        void Set(long long int theIndex, const T& theElement); //��������ֵ
        void OutputA();    //������Ա��Ԫ��
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
���ƹ��캯��
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
�������
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
��ȡ����ֵ��ӦԪ��
*/ 
template <class T> 
T& arrayList<T>::Get(long long int theIndex) 
{ 
    checkIndex(theIndex); 
    return Element[theIndex]; 
} 
/*
��ȡԪ������ֵ
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
�ı����鳤��
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
����
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
    }   //���
    if (listSize == arrayLength) 
    { 
        changeLength(Element, arrayLength, 2*arrayLength); 
        arrayLength *= 2; 
    } 
    for (long long int i=listSize-1; i>=theIndex; i--)//����λ��֮���Ԫ�غ���
        Element[i+1] = Element[i]; 
    Element[theIndex] = theElement; 
    listSize++; 
} 
/*
ɾ��Ԫ��
*/ 
template <class T> 
void arrayList<T>::Erase(long long int theIndex) 
{ 
    checkIndex(theIndex); 
    for (long long int i=theIndex; i<listSize; i++)//Ԫ��ǰ��
        Element[i-1] = Element[i]; 
    Element[--listSize].~T(); 
} 
/*
��֤����Ŀռ�
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
��������ֵ
*/ 
template <class T> 
void arrayList<T>::Set(long long int theIndex, const T& theElement) 
{ 
    if (theIndex < 0 || theIndex >= listSize) 
    { 
        cout << "wrong index" << endl; 
        cout << "index = " << theIndex << " size = " << listSize << endl; 
        return; 
    }//���
    Element[theIndex]  = theElement; 
} 
/*
������Ա��Ԫ��
*/ 
template <class T> 
void arrayList<T>::OutputA() 
{ 
    for (long long int i=0; i<listSize; i++) 
        Element[i].OutputM(); 
    cout << endl; 
} 
