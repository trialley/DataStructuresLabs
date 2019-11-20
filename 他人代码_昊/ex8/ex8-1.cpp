#include <iostream> 
#include <string> 
using namespace std; 


template <class K, class E> 
class hashTable 
{ 
    public: 
        hashTable(int theDivisor = 11);  //���캯��
        ~hashTable() {delete [] table;}  //��������
        bool empty() const {return dSize == 0;}  //�ж��Ƿ�Ϊ��
        int size() const {return dSize;}         //����ɢ�б��Ԫ������
        void find(const K&) const;               //����
        void insert(const pair<const K, E>&);    //����
        void erase(const K&);                    //ɾ��
    private: 
        int search(const K&) const;              //���ݹؼ�������
        pair<const K, E>** table; 
        int dSize; 
        int divisor; 
}; 



template <class K, class E> 
hashTable<K,E>::hashTable (int theDivisor) 
{ 
    divisor = theDivisor; 
    dSize = 0; 
    table = new pair<const K, E>* [divisor]; 
    for (int i=0; i<divisor; i++) 
        table[i] = NULL; 
} 



template <class K, class E> 
int hashTable<K,E>::search (const K& theKey) const 
{ 
    int home = theKey % divisor;  //������ʼͰ
    int i = home;                 //����ʼͰ��ʼ
    do 
    { 
        if (table[i] == NULL || table[i]->first == theKey)  //Ϊ�ջ���ƥ��
            return i;          //���ؼ�������
        i = (i + 1) % divisor; //������ת����һ��Ԫ��
    } 
    while (i != home); 
    return i;   //���ٴ�����j==i��˵������
} 




template<class K, class E> 
void hashTable<K,E>::find(const K& theKey) const 
{ 
    int index = search(theKey);     //ͨ����ѯ�����ҵ�theKey��Ӧ������Ԫ���±�
    if (table[index] == NULL || table[index]->first != theKey)//�ж϶�Ӧ������Ԫ���Ƿ����Ҫ��
    {//������Ҫ������-1 
        cout << "-1" << endl; 
        return; 
    } 
    cout << index << endl;   //����Ҫ�����Ԫ���±�
    return; 
} 


/*
����
*/ 
template<class K, class E> 
void hashTable<K,E>::insert(const pair<const K, E>& thePair) 
{ 
    int index = search(thePair.first);  //����ɢ�б�����ƥ������
    if (table[index] == NULL) 
    { 
        table[index] = new pair<const K, E> (thePair); 
        dSize++; 
        cout << index << endl;   //��������Ԫ���±�
    } 
    else 
    { 
        if (table[index]->first == thePair.first) 
        { 
            table[index]->second  =  thePair.second;    //��д��ͬ�ؼ��ֵ�����
            cout << "Existed" << endl;    //�Ѿ����ڣ����Existed 
        } 
        else 
        { 
            cout << "It's a full table" << endl; 
            string errorFull = "It's a full table"; 
            throw errorFull;  //������
        } 
    } 
} 




/*
ɾ��
*/ 
template<class K, class E> 
void hashTable<K,E>::erase(const K& theKey) 
{ 
    int index = search(theKey); 
    int home = index;   //ȷ����ʼ��λ��
    int count = 0; 
        //ɾ���������ƶ���Ԫ������
    if (table[index] == NULL) 
    { 
        cout << "Not Found" << endl; 
        return; 
    } 
    else 
    { 
        table[index] = NULL; 
        int emptyindex = index;   //����ɢ�б�ɾ��֮��Ŀ�ֵ����
        do 
        { 
            index = (index + 1) % divisor; 
            if (table[index] != NULL)   //����ֵ��ӦԪ�ز�Ϊ��
            { 
                if(index != search(table[index]->first))   //����ֵ�ز�ΪӦ�ڵ�λ��
                { 
                    table[emptyindex]=new pair<const K,E>(*table[index]);//���뵽ǰһ����ֵ��λ��
                    table[index] = NULL;  //��ת�Ƶ�ֵ��Ϊ��
                    emptyindex = index;   //���¿�ֵ����
                    count++; //��¼�ƶ�Ԫ�ص�����            
                } 
            } 
        } 
        while (index != home); 
        cout << count << endl;   //���ɾ�����ƶ���Ԫ������
        return; 
    } 
} 
int main() 
{ 
    int D;  //����
    int m;  //������
    int opt;//����
    cin >> D; 
    cin >> m; 
    hashTable<int, int> htable(D); 
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
                    htable.insert(temp); 
                    break; 
                } 
            case 1: 
                { 
                    int temp; 
                    cin >> temp; 
                    htable.find(temp); 
                    break; 
                } 
            case 2: 
                { 
                    int temp; 
                    cin >> temp; 
                    htable.erase(temp); 
                    break; 
                } 
            default: 
                break; 
        } 
    } 
} 
