#include <iostream> 
using namespace std; 
/*
散列表节点
*/ 
template <class K, class E> 
struct pairNode 
{ 
    pair<const K, E> element; 
    pairNode<K,E>* next; 
    pairNode(const pair<const K,E>& thePair):element(thePair){} 
pairNode(const   pair<const   K,E>&   thePair,   pairNode<K,E>*   
theNext):element(thePair) 
    { 
        next = theNext; 
    } 
}; 
/*
有序链表
*/ 
template <class K, class E> 
class sortedChain 
{ 
    public: 
        sortedChain()  
         //构造函数
        { 
            firstNode = NULL; 
            dSize = 0; 
        } 
        ~sortedChain(); 
             //析构函数
        bool empty() const {return dSize == 0;}     //判断是否为空
        int size() const {return dSize;}  
        //返回链表元素数量
        pair<const K,E>* find(const K&) const;      //查找
        void erase(const K&); //删除
        void insert(const pair<const K,E>&); //插入
    private: 
        pairNode<K,E>* firstNode;    //指向有序链表首节点的指针
        int dSize; 
                 //有序链表的元素数量
}; 
/*
析构函数
*/ 
template <class K, class E> 
sortedChain<K,E>::~sortedChain() 
{ 
    while (firstNode != NULL) 
    { 
        pairNode<K,E>* nextNode = firstNode->next; 
        delete firstNode; 
        firstNode = nextNode; 
    } 
} 
/*
查找
*/ 
template <class K, class E> 
pair<const K, E>* sortedChain<K,E>::find(const K& theKey) const 
{ 
    pairNode<K,E>* currentNode = firstNode; 
    while  (currentNode!=NULL&&currentNode->element.first!=theKey) 
        currentNode = currentNode->next;  //遍历链表
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;     //若匹配，则返回该元素
    return NULL; 
                      //若未查到，返回NULL 
} 
/*
插入
*/ 
template <class K, class E> 
void sortedChain<K,E>::insert(const pair<const K, E>& thePair) 
{ 
    pairNode<K,E>* currentNode = firstNode; 
    pairNode<K,E>* tp = NULL;  //p的前驱指针
    while(currentNode!=NULL&&currentNode->element.first<thePair.first) 
    {//遍历链表,插入的位置是tp的后面
        tp = currentNode; 
        currentNode = currentNode->next; 
    } 
    if(currentNode!=NULL&&currentNode->element.first== thePair.first) 
    {//值匹配，更新值
        currentNode->element.second = thePair.second; 
        cout << "Existed" << endl; 
        return; 
    } 
    pairNode<K,E>* newNode = new pairNode<K,E>(thePair, currentNode);
    if (tp == NULL)     //首节点插入
        firstNode = newNode; 
    else //中间节点插入
    { 
        tp->next = newNode; 
        newNode->next = currentNode; 
    } 
    dSize++; 
} 
/*
删除
*/ 
template <class K, class E> 
void sortedChain<K,E>::erase(const K& theKey) 
{ 
    pairNode<K,E>* currentNode = firstNode; 
    pairNode<K,E>* tp = NULL;  //p的前驱指针
    while  (currentNode!=NULL&&currentNode->element.first<theKey) 
    {//遍历链表进行搜索
        tp = currentNode; 
        currentNode = currentNode->next; 
    } 
    if (currentNode!=NULL&&currentNode->element.first==theKey)
    {//搜索到预定目标
        if (tp == NULL)  //删除首节点
            firstNode = currentNode->next; 
        else 
            tp->next = currentNode->next;  //非首节点
        delete currentNode; 
        dSize--; 
        cout << dSize << endl; 
        return; 
    } 
    else//删除失败
    { 
        cout << "Delete Failed" << endl; 
        return; 
    } 
} 
/*
链式散列表
*/ 
template <class K, class E> 
class chainHash 
{ 
    public: 
        chainHash(int theDivisor = 7);//构造函数
        ~chainHash() {delete []table;} //析构函数
        bool hempty() const {return dhSize == 0;} //判断是否为空
        int hsize() const {return dhSize;}  //返回桶的数量
        void hfind(const K&) const;  //查找
        void hinsert(const pair<const K, E>&); //插入
        void herase(const K&); //删除
    private: 
        sortedChain<K,E>* table; 
        int dhSize; 
        int dhvisor; 
}; 
/*
构造函数
*/ 
template <class K, class E> 
chainHash<K,E>::chainHash(int theDivisor) 
{ 
    dhvisor = theDivisor; 
    dhSize = 0; 
    table = new sortedChain<K,E> [dhvisor]; 
} 
/*
查找
*/ 
template <class K, class E> 
void chainHash<K,E>::hfind(const K& theKey) const 
{ 
    if (table[theKey % dhvisor].find(theKey) == NULL) 
    { 
        cout << "Not Found" << endl; 
        return; 
    } 
    cout << table[theKey %dhvisor].size() << endl; 
} 
/*
插入
*/ 
template <class K, class E> 
void chainHash<K,E>::hinsert(const pair<const K, E>& thePair) 
{ 
    int bucket = thePair.first % dhvisor; 
    //确定桶
    int bucketSize = table[bucket].size(); 
    table[bucket].insert(thePair); 
    if (table[bucket].size() > bucketSize) 
        dhSize++; 
        //若是插入新的元素，则dhSize加一
} 
/*
删除
*/ 
template <class K, class E> 
void chainHash<K,E>::herase(const K& theKey) 
{ 
    table[theKey % dhvisor].erase(theKey); 
} 
int main() 
{ 
    int D;  //除数
    int m;  //操作数
    int opt;//操作
    cin >> D; 
    cin >> m; 
    chainHash<int, int> htable(D); 
    for (int i=0; i<m; i++) 
    { 
        cin >> opt; 
        switch(opt) 
        { 
            case 0: 
                { 
                    pair<int, int> temp; 
                    cin >> temp.first; 
                    temp.second = temp.first; 
                    htable.hinsert(temp); 
                    break; 
                } 
            case 1: 
                { 
                    int temp; 
                    cin >> temp; 
                    htable.hfind(temp); 
                    break; 
                } 
            case 2: 
                { 
                    int temp; 
                    cin >> temp; 
                    htable.herase(temp); 
                    break; 
                } 
            default: 
                break; 
        } 
    } 
    return 0; 
} 
