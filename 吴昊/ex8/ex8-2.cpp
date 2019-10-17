#include <iostream> 
using namespace std; 
/*
ɢ�б�ڵ�
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
��������
*/ 
template <class K, class E> 
class sortedChain 
{ 
    public: 
        sortedChain()  
         //���캯��
        { 
            firstNode = NULL; 
            dSize = 0; 
        } 
        ~sortedChain(); 
             //��������
        bool empty() const {return dSize == 0;}     //�ж��Ƿ�Ϊ��
        int size() const {return dSize;}  
        //��������Ԫ������
        pair<const K,E>* find(const K&) const;      //����
        void erase(const K&); //ɾ��
        void insert(const pair<const K,E>&); //����
    private: 
        pairNode<K,E>* firstNode;    //ָ�����������׽ڵ��ָ��
        int dSize; 
                 //���������Ԫ������
}; 
/*
��������
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
����
*/ 
template <class K, class E> 
pair<const K, E>* sortedChain<K,E>::find(const K& theKey) const 
{ 
    pairNode<K,E>* currentNode = firstNode; 
    while  (currentNode!=NULL&&currentNode->element.first!=theKey) 
        currentNode = currentNode->next;  //��������
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;     //��ƥ�䣬�򷵻ظ�Ԫ��
    return NULL; 
                      //��δ�鵽������NULL 
} 
/*
����
*/ 
template <class K, class E> 
void sortedChain<K,E>::insert(const pair<const K, E>& thePair) 
{ 
    pairNode<K,E>* currentNode = firstNode; 
    pairNode<K,E>* tp = NULL;  //p��ǰ��ָ��
    while(currentNode!=NULL&&currentNode->element.first<thePair.first) 
    {//��������,�����λ����tp�ĺ���
        tp = currentNode; 
        currentNode = currentNode->next; 
    } 
    if(currentNode!=NULL&&currentNode->element.first== thePair.first) 
    {//ֵƥ�䣬����ֵ
        currentNode->element.second = thePair.second; 
        cout << "Existed" << endl; 
        return; 
    } 
    pairNode<K,E>* newNode = new pairNode<K,E>(thePair, currentNode);
    if (tp == NULL)     //�׽ڵ����
        firstNode = newNode; 
    else //�м�ڵ����
    { 
        tp->next = newNode; 
        newNode->next = currentNode; 
    } 
    dSize++; 
} 
/*
ɾ��
*/ 
template <class K, class E> 
void sortedChain<K,E>::erase(const K& theKey) 
{ 
    pairNode<K,E>* currentNode = firstNode; 
    pairNode<K,E>* tp = NULL;  //p��ǰ��ָ��
    while  (currentNode!=NULL&&currentNode->element.first<theKey) 
    {//���������������
        tp = currentNode; 
        currentNode = currentNode->next; 
    } 
    if (currentNode!=NULL&&currentNode->element.first==theKey)
    {//������Ԥ��Ŀ��
        if (tp == NULL)  //ɾ���׽ڵ�
            firstNode = currentNode->next; 
        else 
            tp->next = currentNode->next;  //���׽ڵ�
        delete currentNode; 
        dSize--; 
        cout << dSize << endl; 
        return; 
    } 
    else//ɾ��ʧ��
    { 
        cout << "Delete Failed" << endl; 
        return; 
    } 
} 
/*
��ʽɢ�б�
*/ 
template <class K, class E> 
class chainHash 
{ 
    public: 
        chainHash(int theDivisor = 7);//���캯��
        ~chainHash() {delete []table;} //��������
        bool hempty() const {return dhSize == 0;} //�ж��Ƿ�Ϊ��
        int hsize() const {return dhSize;}  //����Ͱ������
        void hfind(const K&) const;  //����
        void hinsert(const pair<const K, E>&); //����
        void herase(const K&); //ɾ��
    private: 
        sortedChain<K,E>* table; 
        int dhSize; 
        int dhvisor; 
}; 
/*
���캯��
*/ 
template <class K, class E> 
chainHash<K,E>::chainHash(int theDivisor) 
{ 
    dhvisor = theDivisor; 
    dhSize = 0; 
    table = new sortedChain<K,E> [dhvisor]; 
} 
/*
����
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
����
*/ 
template <class K, class E> 
void chainHash<K,E>::hinsert(const pair<const K, E>& thePair) 
{ 
    int bucket = thePair.first % dhvisor; 
    //ȷ��Ͱ
    int bucketSize = table[bucket].size(); 
    table[bucket].insert(thePair); 
    if (table[bucket].size() > bucketSize) 
        dhSize++; 
        //���ǲ����µ�Ԫ�أ���dhSize��һ
} 
/*
ɾ��
*/ 
template <class K, class E> 
void chainHash<K,E>::herase(const K& theKey) 
{ 
    table[theKey % dhvisor].erase(theKey); 
} 
int main() 
{ 
    int D;  //����
    int m;  //������
    int opt;//����
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
