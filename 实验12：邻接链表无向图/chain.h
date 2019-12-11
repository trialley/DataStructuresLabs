#include <iostream>
using namespace std;
#define until(re) while(!(re))

template <class T>
struct node {
    T data;
    node<T>* next;

    node () {}
    node (const T& datai) :data (datai), next (nullptr) {}
    node (const T& datai, node<T>* nexti) :data (datai), next (nexti) {}
};
template<class T>
class chain {
public:
    typedef enum err { chain_index_out_of_range }err;
    chain ();
    chain (const chain<T>&);
    ~chain ();

    bool empty () const { return _list_size == 0; }
    int size () const { return _list_size; }
    T& getByIndex (int indexi) const;
    int getIndexByData (const T& datai) const;
    void eraseByIndex (int indexi);
    void insert (const T& weighti);
    void output (ostream& out) const;
    node<T>* getfirst () {
        return _head;
    }
    T* eraseByData (int theVertex);
protected:
    void _checkIndex (int indexi) const;
    node<T>* _head;
    int _list_size;
};

template<class T>
chain<T>::chain () :_head (nullptr), _list_size (0) {}

template<class T>
chain<T>::chain (const chain<T>& theList) {
    _list_size = theList._list_size;

    if (_list_size == 0) {
        _head = nullptr;
        return;
    }

    node<T>* sorce_node = theList._head;

    _head = new node<T> (sorce_node->data);

    sorce_node = sorce_node->next;
    node<T>* target_node = _head;

    until (sorce_node == nullptr) {
        target_node->next = new node<T> (sorce_node->data);
        target_node = target_node->next;
        sorce_node = sorce_node->next;
    }
    target_node->next = nullptr;
}

template<class T>
chain<T>::~chain () {
    until (_head == nullptr) {
        node<T>* next_node = _head->next;
        delete _head;
        _head = next_node;
    }
}

template<class T>
void chain<T>::_checkIndex (int indexi) const {
    if (indexi < 0 || indexi >= _list_size)
        throw chain_index_out_of_range;
}

template<class T>
T& chain<T>::getByIndex (int indexi) const {
    _checkIndex (indexi);

    node<T>* current_node = _head;
    for (int i = 0; i < indexi; i++)
        current_node = current_node->next;

    return current_node->data;
}

template<class T>
int chain<T>::getIndexByData (const T& datai) const {
    node<T>* current_node = _head;
    int index = 0;
    until (current_node == nullptr || current_node->data == datai) {
        current_node = current_node->next;
        index++;
    }

    if (current_node == nullptr) {
        return -1;
    } else {
        return index;
    }
}
template<class T>
T* chain<T>::eraseByData (int theVertex) {
    node<T>* current = _head, * trail = nullptr;

    until (current == nullptr || current->data == theVertex) {
        trail = current;
        current = current->next;
    }
    if (current == nullptr) {
        return nullptr;
    }

    T* datai = &current->data;

    if (trail != nullptr) {
        trail->next = current->next;
    } else {
        _head = current->next;
    }

    delete current;
    _list_size--;
    return datai;
}
template<class T>
void chain<T>::eraseByIndex (int indexi) {
    _checkIndex (indexi);

    node<T>* deleteNode;
    if (indexi == 0) {
        deleteNode = _head;
        _head = _head->next;
    } else {
        node<T>* p = _head;
        for (int i = 0; i < indexi - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next;
    }
    _list_size--;
    delete deleteNode;
}
template<class T>
void chain<T>::insert (const T& weighti) {
    int a = this->getIndexByData (weighti);
    if (a == -1) {
        node<int>* p = _head, * q = _head;
        if (_head == nullptr || weighti <= _head->data)
            _head = new node<T> (weighti, _head);
        else {
            while (weighti > p->data) {
                q = p;
                p = p->next;
                if (p == nullptr)
                    break;
            }
            p = new node<T> (weighti, q->next);
            q->next = p;
        }
    }
}


template<class T>
void chain<T>::output (ostream& out) const {
    for (node<T>* current_node = _head; current_node != nullptr; current_node = current_node->next)
        out << current_node->data << "  ";
    out << endl;
}