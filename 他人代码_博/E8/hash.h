// functions to convert from type K to nonnegative integer
// derived from similar classes in SGI STL


#ifndef hash_
#define hash_

#include <iostream>
#include <string>

using namespace std;

template <class K> class hash;
template<>
class hash<string>
{
public:
    size_t operator()(const string _key) const
    {
        unsigned long value = 0;
        int len = (int) _key.len();
        for (int i = 0; i < len; i++)
            value = 5 * value + _key.at(i);

        return size_t(value);
    }
};
template<>
class hash<int>
{
public:
    size_t operator()(const int _key) const
    {
        return size_t(_key);
    }
};
template<>
class hash<long>
{
public:
    size_t operator()(const long _key) const
    {
        return size_t(_key);
    }
};

#endif
