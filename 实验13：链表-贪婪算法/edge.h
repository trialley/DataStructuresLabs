#pragma once
#include<iostream>
using namespace std;

template <class T>
class edge {
public:
    edge () {}
    edge (int V1, int V2, T weight) {
        v1 = V1;  v2 = V2;  w = weight;
    }
    ~edge () {};
    int vertex1 () const { return v1; }
    int vertex2 () const { return v2; }
    T weight () const { return w; }
    operator T() const { return w; }  //ÒşÊ½×ª»»£¬we'll see. 
    friend ostream& operator<<(ostream& out, const edge<T> A) {
        out << "(" << A.v1 << ", " << A.v2 << ", " << A.w << ")";
        return out;
    }

protected:
    int v1;
    int v2;
    T w;

};


