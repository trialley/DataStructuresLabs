//Author ZhangJunshuo
//Using zjslib.h
//zjslib.h for details please contact me.
#include<iostream>
using namespace std;
#include<cstddef>
#include<string.h>
/////////////////////////////////////////////////////////////////////////////

template<class K, class E>
class dic
{
public:
    virtual ~dic() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual pair<const K, E> *find(const K &) const = 0;
    virtual int erase(const K &) = 0;
    virtual int insert(const pair<const K, E> &) = 0;
};

template<class K, class E>
class chaindic : public dic<K, E>
{
private:
	struct pairnode //再次重申，pairnode本身不是模板类，但是定义pair时必须注明模板类型，这是因为pair成员element所要求的！
	{
	public:
	    pair<const K, E> element;   //节点内容一律是element
	    pairnode *next;         //next表示这是个单向链结构
	public: //分隔字段和方法
	    pairnode(const pair<const K, E> &_pair)
	    :element(_pair)
		{

		}
	    pairnode(const pair<const K, E> &_pair, pairnode *_next)
	    :element(_pair)
	    {
	    	//element = _pair;    //非静态const成员 'first'，不能使用默认赋值运算符!
	        next = _next;
	    }
	};
protected:
    pairnode *head;   //链表头结点一律是head
    int listsize;   //链表结构一律用listsize，表实际用量；数组结构一律是arrlen和listsize，arrlen表容量，listsize表实际用量.
public:
    chaindic()
    {
        head = NULL;
        listsize = 0;
    }
    ~chaindic()
	{
	    while (head != NULL)
	    {
	        pairnode *nextnode = head->next;
	        delete head;
	        head = nextnode;
	    }
	}
    bool empty() const
    {
        return listsize == 0;
    }
    int size() const
    {
        return listsize;
    }
    pair<const K, E> *find(const K &_key) const
	{
	    pairnode *currentNode = head;
	    while (currentNode != NULL && currentNode->element.first != _key)
	        currentNode = currentNode->next;
	    if (currentNode != NULL && currentNode->element.first == _key)
	        return &currentNode->element;
	    return NULL;
	}
	int locate(const K &_key) const
	{
	    pairnode *currentNode = head;
	    while (currentNode != NULL && currentNode->element.first != _key)
	    	currentNode = currentNode->next;
	    if (currentNode != NULL && currentNode->element.first == _key)
	        return 0;
	    return -1;
	}
	int erase(const K &_key)
	{
	    pairnode* p = head;
	    pairnode* theone_who_following_p = NULL;
	    while (p != NULL && p->element.first < _key)
	    {
	        theone_who_following_p = p;
	        p = p->next;
	    }
	    if (p != NULL && p->element.first == _key)
	    {
	        if (theone_who_following_p == NULL) head = p->next;
	        else theone_who_following_p->next = p->next;
	        delete p;
	        listsize--;
	        return 0;   //正常删除，返回0；
	    }
	    return -1;  //删除失败，返回-1；
	}
    int insert(const pair<const K, E> &_pair)  //普通插入，如果关键字已经存在则输出提示并放弃插入.
	{
	    pairnode* p = head;
	    pairnode* theone_who_following_p = NULL;
	    while (p != NULL && p->element.first < _pair.first)
	    {
	        theone_who_following_p = p;
	        p = p->next;
	    }
	    if (p != NULL && p->element.first == _pair.first)
			return -1;
	    pairnode *newNode = new pairnode(_pair, p);
	    if (theone_who_following_p == NULL) head = newNode;
	    else theone_who_following_p->next = newNode;
	    listsize++;
	    return 0;
	}
	void forced_insert(const pair<const K, E> &_pair)   //强制插入，覆写式.
	{
	    pairnode* p = head;
	    pairnode* theone_who_following_p = NULL;
	    while (p != NULL && p->element.first < _pair.first)
	    {
	        theone_who_following_p = p;
	        p = p->next;
	    }
	    if (p != NULL && p->element.first == _pair.first)
	    {
	        p->element.second = _pair.second;
	        return;
	    }
	    pairnode *newNode = new pairnode(_pair, p);
	    if (theone_who_following_p == NULL) head = newNode;
	    else theone_who_following_p->next = newNode;
	    listsize++;
	    return;
	}
    void output(ostream &out) const
	{
	    for (pairnode *currentNode = head;
	            currentNode != NULL;
	            currentNode = currentNode->next)
	        out << currentNode->element.first << " "
	            << currentNode->element.second << "  ";
	}
};

template <typename K> class zjshash;
template<>
class zjshash<string>
{
public:
    size_t operator()(const string _key) const
    {
        unsigned long value = 0;
        int len = (int) _key.length();
        for (int i = 0; i < len; i++)
            value = 5 * value + _key.at(i);
       	return size_t(value);
	}
};
template<>
class zjshash<int>
{
public:
    size_t operator()(const int _key) const
	{
    	return size_t(_key);
	}
};
template<>
class zjshash<long>
{
public:
    size_t operator()(const long _key) const
    {
        return size_t(_key);
    }
};

//hashchaindic relies on dic and chaindic !!!
//do not change their location in zjslib !
template<typename K, typename E>
class hashchaindic : public dic<K, E>
{
private:

protected:
    chaindic<K, E> *table;		//this is a array of chaindic!
    zjshash<K> _hash;
    int num_element;            // number of all elements in this table
    int divisor;
public:
    hashchaindic(int _divisor = 11)
    {
        divisor = _divisor;
        num_element = 0;
        table = new chaindic<K, E> [divisor];
    }
    ~hashchaindic()
    {
        delete [] table;
    }
    bool empty() const
    {
        return num_element == 0;
    }
    int size() const
    {
        return num_element;
    }
    pair<const K, E> *find(const K &_key) const
    {
        return table[_hash(_key) % divisor].find(_key);
    }
    int locate(const K &_key)
    {
    	int num_bucket = _hash(_key) % divisor;
    	int successornot = table[num_bucket].locate(_key);
    	if(successornot==-1) return -1;   //if no key in this bucket return -1.
    	else return table[num_bucket].size();
    }
    int insert(const pair<const K, E> &_pair)
    {
        int targetbucket = (int) _hash(_pair.first) % divisor;
        int bucketsize = table[targetbucket].size();
        int successornot = table[targetbucket].insert(_pair);
        if(successornot == -1) return -1;
        if (table[targetbucket].size() > bucketsize)
            num_element++;
		return targetbucket;
    }
    int erase(const K &_key)
    {
    	int targetbucket = (int) _hash(_key) % divisor;
        int successornot = table[targetbucket].erase(_key);
        if(successornot == -1) return -1;
        return table[targetbucket].size();
    }
    void output(ostream &out) const
    {
        for (int i = 0; i < divisor; i++)
            if (table[i].size() == 0)
                cout << "NULL" << endl;
            else
                cout << table[i] << endl;
    }
};

/////////////////////////////////////////////////////////////////////////////

int main(){
//	chaindic<int,char> zjs;
//	hashchaindic<int,char> zjs2;
	int D = 0;
	int m = 0;
	cin >> D >> m;
	hashchaindic<int,int> test(D);
	for(int i=0;i<m;i++)
	{
		int opt = 0;
		int x = 0;
		cin >> opt >> x;
		pair<int,int> tempx(x,0);
		switch(opt)
		{
			case 0:
			{
				int num_bucket = test.insert(tempx);
				if(num_bucket==-1) cout << "Existed" << endl;
				//else cout << num_bucket << endl;
				break;
			}
			case 1:
			{
				int num_bucket = test.locate(x);
				if(num_bucket==-1) cout << "Not Found" << endl;
				else cout << num_bucket << endl;

				break;
			}
			case 2:
			{
				int num_bucket = test.erase(x);
				if(num_bucket==-1) cout << "Delete Failed" << endl;
				else cout << num_bucket << endl;
				break;
			}
		}
	}
	return 0;
}

