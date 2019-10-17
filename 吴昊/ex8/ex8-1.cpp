#include <iostream> 
#include <string> 
using namespace std; 


template <class K, class E> 
class hashTable 
{ 
    public: 
        hashTable(int theDivisor = 11);  //构造函数
        ~hashTable() {delete [] table;}  //析构函数
        bool empty() const {return dSize == 0;}  //判断是否为空
        int size() const {return dSize;}         //返回散列表的元素数量
        void find(const K&) const;               //查找
        void insert(const pair<const K, E>&);    //插入
        void erase(const K&);                    //删除
    private: 
        int search(const K&) const;              //根据关键字搜索
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
    int home = theKey % divisor;  //设置起始桶
    int i = home;                 //从起始桶开始
    do 
    { 
        if (table[i] == NULL || table[i]->first == theKey)  //为空或结果匹配
            return i;          //返回检索索引
        i = (i + 1) % divisor; //否则跳转至下一个元素
    } 
    while (i != home); 
    return i;   //若再次碰到j==i则说明表满
} 




template<class K, class E> 
void hashTable<K,E>::find(const K& theKey) const 
{ 
    int index = search(theKey);     //通过查询函数找到theKey对应的数组元素下标
    if (table[index] == NULL || table[index]->first != theKey)//判断对应的数组元素是否符合要求
    {//不符合要求就输出-1 
        cout << "-1" << endl; 
        return; 
    } 
    cout << index << endl;   //符合要求输出元素下标
    return; 
} 


/*
插入
*/ 
template<class K, class E> 
void hashTable<K,E>::insert(const pair<const K, E>& thePair) 
{ 
    int index = search(thePair.first);  //搜索散列表，查找匹配数对
    if (table[index] == NULL) 
    { 
        table[index] = new pair<const K, E> (thePair); 
        dSize++; 
        cout << index << endl;   //输出插入的元素下标
    } 
    else 
    { 
        if (table[index]->first == thePair.first) 
        { 
            table[index]->second  =  thePair.second;    //覆写相同关键字的数对
            cout << "Existed" << endl;    //已经存在，输出Existed 
        } 
        else 
        { 
            cout << "It's a full table" << endl; 
            string errorFull = "It's a full table"; 
            throw errorFull;  //表已满
        } 
    } 
} 




/*
删除
*/ 
template<class K, class E> 
void hashTable<K,E>::erase(const K& theKey) 
{ 
    int index = search(theKey); 
    int home = index;   //确定开始的位置
    int count = 0; 
        //删除过程中移动的元素数量
    if (table[index] == NULL) 
    { 
        cout << "Not Found" << endl; 
        return; 
    } 
    else 
    { 
        table[index] = NULL; 
        int emptyindex = index;   //现有散列表删除之后的空值索引
        do 
        { 
            index = (index + 1) % divisor; 
            if (table[index] != NULL)   //索引值对应元素不为空
            { 
                if(index != search(table[index]->first))   //索引值素不为应在的位置
                { 
                    table[emptyindex]=new pair<const K,E>(*table[index]);//插入到前一个空值的位置
                    table[index] = NULL;  //将转移的值设为空
                    emptyindex = index;   //更新空值索引
                    count++; //记录移动元素的数量            
                } 
            } 
        } 
        while (index != home); 
        cout << count << endl;   //输出删除中移动的元素数量
        return; 
    } 
} 
int main() 
{ 
    int D;  //除数
    int m;  //操作数
    int opt;//操作
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
