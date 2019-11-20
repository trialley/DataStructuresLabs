// hash table using sorted chains and division
// implements all dic methods

#ifndef hashchaindic_
#define hashchaindic_



#include <iostream>
#include "hash.h"  // mapping functions from K to nonnegative integer


using namespace std;
//hashchaindic relies on dic and chaindic !!!
//do not change their location in zjslib !
template<class K, class E>
class hashchaindic : public dic<K, E>
{
protected:
    chaindic<K, E> *table;		//this is a array of chaindic!
    hash<K> hash;              	
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
        return table[hash(_key) % divisor].find(_key);
    }
    void insert(const pair<const K, E> &_pair)
    {
        int targetbucket = (int) hash(_pair.first) % divisor;
        int bucketsize = table[targetbucket].size();
        table[targetbucket].insert(_pair);
        if (table[targetbucket].size() > bucketsize)
            num_element++;
    }
    void erase(const K &_key)
    {
        table[hash(_key) % divisor].erase(_key);
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


// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, const hashchaindic<K, E> &x)
{
    x.output(out);
    return out;
}

#endif
