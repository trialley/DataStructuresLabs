// abstract class dic
// abstract data type specification for dic data structure
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef dic_
#define dic_

using namespace std;

template<class K, class E>
class dic
{
public:
    virtual ~dic() {}
    virtual bool empty() const = 0;
    // return true iff dic is empty
    virtual int size() const = 0;
    // return number of pairs in dic
    virtual pair<const K, E> *find(const K &) const = 0;
    // return pointer to matching pair
    virtual void erase(const K &) = 0;
    // remove matching pair
    virtual void insert(const pair<const K, E> &) = 0;
    // insert a (key, value) pair into the dic
};
#endif

