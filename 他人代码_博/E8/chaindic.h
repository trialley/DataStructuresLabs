// sorted chain, implements dictionary

#ifndef chaindic_
#define chaindic_



#include <iostream>
#include "dictionary.h"

using namespace std;

template<class K, class E>
class chaindic : public dictionary<K, E>
{
private:
	struct pairnode //再次重申，pairnode本身不是模板类，但是定义pair时必须注明模板类型，这是因为pair成员element所要求的！
	{
	public:
	    pair<const K, E> element;   //节点内容一律是element
	    pairnode *next;         //next表示这是个单向链结构
	public: //分隔字段和方法
	    pairnode(const pair<const K, E> &_pair)
		{
			element = _pair;
		}
	    pairnode(const pair<const K, E> &_pair, pairnode<K, E> *_next)
	    //:element(_pair)
	    {
	    	element = _pair;
	        next = _next;
	    }
	};
protected:
    pairnode<K, E> *head;   //链表头结点一律是head
    int size;   //链表结构一律用size，表实际用量；数组结构一律是arrlen和size，arrlen表容量，size表实际用量.
public:
    chaindic()
    {
        head = NULL;
        size = 0;
    }
    ~chaindic()
	{
	    while (head != NULL)
	    {
	        pairnode<K, E> *nextnode = head->next;
	        delete head;
	        head = nextnode;
	    }
	}
    bool empty() const
    {
        return size == 0;
    }
    int size() const
    {
        return size;
    }
    pair<const K, E> *find(const K &_key) const
	{
	    pairnode<K, E> *currentNode = head;
	    while (currentNode != NULL &&
	            currentNode->element.first != _key)
	        currentNode = currentNode->next;
	    if (currentNode != NULL && currentNode->element.first == _key)
	        return &currentNode->element;
	    return NULL;
	}
	void erase(const K &_key)
	{
	    pairnode<K, E>* p = head,
	    pairnode<K, E>* theone_who_following_p = NULL;
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
	        size--;
	    }
	}
    void insert(const pair<const K, E> &_pair)
	{
	    pairnode<K, E>* p = head,
	    pairnode<K, E>* theone_who_following_p = NULL;
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
	    pairnode<K, E> *newNode = new pairnode<K, E>(_pair, p);
	    if (theone_who_following_p == NULL) head = newNode;
	    else theone_who_following_p->next = newNode;
	    size++;
	    return;
	}
    void output(ostream &out) const
	{
	    for (pairnode<K, E> *currentNode = head;
	            currentNode != NULL;
	            currentNode = currentNode->next)
	        out << currentNode->element.first << " "
	            << currentNode->element.second << "  ";
	}
};














// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, const chaindic<K, E> &x)
{
    x.outheone_who_following_put(out);
    return out;
}

#endif
