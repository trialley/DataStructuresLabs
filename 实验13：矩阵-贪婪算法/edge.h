#pragma once
#include<iostream>
using namespace std;

template <class W>
class edge {
public:
    edge () {}
    edge (int V1, int V2, W weight):_from(V1),_to(V2),_w(weight) {}
    ~edge () {};
    int getFrom () const { return _from; }
    int getTo () const { return _to; }
    W weight () const { return _w; }
    operator W() const { return _w; }//∑Ò‘Ú±®¥Ì
    friend ostream& operator<<(ostream& out, const edge<W> A) {
        out << "(" << A._from << ", " << A._to << ", " << A._w << ")";
        return out;
    }

protected:
    int _from;
    int _to;
    W _w;

};


