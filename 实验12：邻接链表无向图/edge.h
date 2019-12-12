#pragma once
#include<iostream>
using namespace std;

template <class T>
class edge {
public:
    edge () {}
    edge (int v1, int v2, T weight):from(v1),to(v2),w(weight){}
    ~edge () {};

    int getFrom () const { return from; }
    int getTo () const { return to; }
    T getWeight () const { return w; }
    operator T() const { return w; } 


    friend ostream& operator<<(ostream& out, const edge<T> A) {
        out << "(" << A.from << ", " << A.to << ", " << A.w << ")";
        return out;
    }

protected:
    int from;
    int to;
    T w;
};


