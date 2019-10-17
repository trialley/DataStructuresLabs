 /* 
 ex11
 2018-12
 */ 
#include <iostream> 

using namespace std; 


template <class T> 
struct binaryTreeNode 
{ 
    T element; 
    int leftSize;  //�����������Ľڵ���������������ε�����
    binaryTreeNode<T> *leftChild, *rightChild; 
    binaryTreeNode() 
    { 
        leftSize = 0; 
        leftChild = rightChild = NULL; 
    } 
    binaryTreeNode(const T& theElement):element(theElement) 
    { 
        leftSize = 0; 
        leftChild = rightChild = NULL; 
    } 
    binaryTreeNode(const T& theElement,const int& theLeftSize, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild):element(theElement) 
    { 
        leftSize = theLeftSize; 
        leftChild = theLeftChild; 
        rightChild = theRightChild; 
    } 
};

 
template <class E> 
class binarySearchTree 
{ 
    public: 
        binarySearchTree() 
        { 
            root = NULL; 
            treeSize = 0; 
        } 
        ~binarySearchTree() {;} 
        bool empty() const {return treeSize == 0;} 
        int size() const {return treeSize;} 
        void find(const E& theElement) const; //����
        bool find2(const E& theElement) const; 
        void insert(const E& theElement); //����
        void erase(const E& theElement); //ɾ��
        void rankfind(int rank); //�������ζ�Ӧ��Ԫ��
        E rankfind2(int rank); 
        void rankerase(int rank); //ɾ�����ζ�Ӧ��Ԫ��
    private: 
        binaryTreeNode<E> *root; //���ڵ�
        int treeSize;  //���Ľڵ���
}; 


template <class E> 
void binarySearchTree<E>::find(const E& theElement) const 
{ 
    E output = 0;  //��������ȽϽڵ������
    binaryTreeNode<E> *p = root; 
    while (p != NULL) 
    { 
        output ^= p->element; 
        if (theElement < p->element) 
            p = p->leftChild; 
        else  
            if (theElement > p->element) 
                p = p->rightChild; 
            else 
            { 
                cout << output << endl; 
                return; 
            } 
    } 
    if (p == NULL) 
        cout << 0 << endl;//û�в�ѯ��ֱ�����0 
} 
template <class E> 
bool binarySearchTree<E>::find2(const E& theElement) const 
{ 
    binaryTreeNode<E> *p = root; 
    while (p != NULL) 
    { 
        if (theElement < p->element) 
            p = p->leftChild; 
        else if (theElement > p->element) 
            p = p->rightChild; 
        else 
            return true; 
    } 
    return false;  
} 


template <class E> 
void binarySearchTree<E>::insert(const E& theElement) 
{ 
    if (find2(theElement)) 
    { 
        cout << 0 << endl; 
        return; 
    }   //����һ��
    E output = 0;  //��������ȽϽڵ������
    binaryTreeNode<E> *p = root; 
    binaryTreeNode<E> *pp = NULL; 
    while (p != NULL) //ֵ�����ڣ��ҵ���ȷ�Ĳ���λ��
    { 
        output ^= p->element; //��p�ڵ��ֵ���������
        pp = p; 
        if (theElement < p->element) 
        { 
            p->leftSize++; 
            p = p->leftChild; 
        } 
        else 
            if (theElement > p->element) 
                p = p->rightChild; 
    } 
    binaryTreeNode<E> *newNode = new binaryTreeNode<E>(theElement); 
    if (root != NULL) //������ֵ��������Ϊ�գ���pp����
        if (theElement < pp->element) 
            pp->leftChild = newNode; 
        else 
            pp->rightChild = newNode; 
    else //��Ϊ�գ���Ϊ���ڵ�
        root = newNode; 
    cout << output << endl; 
    treeSize++; 
}

 
template <class E> 
void binarySearchTree<E>::erase(const E& theElement) 
{ 
    if (!find2(theElement)) 
    { 
        cout << 0 << endl; 
        return; 
    } 
    E output = 0; 
    binaryTreeNode<E> *p = root; 
    binaryTreeNode<E> *pp = NULL; 
    output ^= p->element; 
    while (p != NULL && p->element != theElement)  //�ҵ���ӦԪ��
    { 
        pp = p; 
        if (theElement < p->element) 
        { 
            p->leftSize--; 
            p = p->leftChild; 
        } 
        else 
            p = p->rightChild; 
        output ^= p->element; 
    } 
    if (p->leftChild != NULL && p->rightChild != NULL) //ͬʱ�����������Һ���
    {   //��p����������Ѱ����Сֵ
        binaryTreeNode<E> *s = p->rightChild; 
        binaryTreeNode<E> *ps = p; //s�ĸ��ڵ�
        while (s->leftChild != NULL) 
        { 
            ps = s; 
            s->leftSize--; 
            s = s->leftChild; 
        } 
        //����СԪ���ƶ�p 
        binaryTreeNode<E> *q = new binaryTreeNode<E> (s->element, p->leftSize, p->leftChild, p->rightChild); 
        if (pp == NULL) 
            root = q; 
        else if (p == pp->leftChild) 
            pp->leftChild = q; 
        else 
            pp->rightChild = q; 
        if (ps == p) 
            pp = q; 
        else  
            pp = ps; 
        delete p; 
        p = s; 
    } 
    binaryTreeNode<E> *c; 
    if (p->rightChild != NULL) 
        c = p->rightChild; 
    else 
        c = p->leftChild; 
    if (p == root) 
        root = c; 
    else 
    { 
        if (p == pp->leftChild) 
            pp->leftChild = c; 
        else 
            pp->rightChild = c; 
    } 
    treeSize--; 
    delete p; 
    cout << output << endl; 
} 


template <class E> 
void binarySearchTree<E>::rankfind(int rank) 
{ 
    if (rank < 1 || rank > treeSize) 
    { 
        cout << 0 << endl; 
        return; 
    }                //�����rank��ֱ���˳�
    int output = 0; 
    binaryTreeNode<E> *p = root; 
    while (p != NULL) 
    { 
        output ^= p->element; 
        if (rank < p->leftSize+1) 
            p = p->leftChild; 
        else 
            if (rank > p->leftSize+1) 
            { 
                rank -= (p->leftSize+1); 
                p = p->rightChild; 
            } 
            else 
            { 
                cout << output << endl; 
                return; 
            } 
    } 
    if (p == NULL) 
        cout << 0 << endl; 
    return; 
} 
/*
���ҵ���Ӧ��Ԫ��ֵ�����ڰ����ε�ɾ��
*/ 
template <class E> 
E binarySearchTree<E>::rankfind2(int rank) 
{ 
    if (rank < 1 || rank > treeSize) 
        return 0; 
    binaryTreeNode<E> *p = root; 
    while (p != NULL) 
    { 
        if (rank == p->leftSize+1) 
            return p->element; 
        else if (rank > p->leftSize+1) 
        { 
            rank -= (p->leftSize+1); 
            p = p->rightChild; 
        } 
        else if (rank < p->leftSize+1) 
            p =  p->leftChild; 
    } 
    return 0; //û�в�ѯ��
} 
template <class E> 
void binarySearchTree<E>::rankerase(int rank) 
{ 
    if (rank > treeSize || rank < 1) 
        cout << 0 << endl; 
    erase(rankfind2(rank)); //�Ȳ���Ԫ���ٵ���ɾ������
} 
int main() 
{ 
    binarySearchTree<int> bsTree; 
    int num; 
    cin >> num; 
    int choice; 
    int input; 
    for (int i=0; i<num; i++) 
    { 
        cin >> choice; 
        switch(choice) 
        { 
            case 0: 
                cin >> input; 
                bsTree.insert(input); 
                break; 
            case 1: 
                cin >> input; 
                bsTree.find(input); 
                break; 
            case 2: 
                cin >> input; 
                bsTree.erase(input); 
                break; 
            case 3: 
                cin >> input; 
                bsTree.rankfind(input); 
                break; 
            case 4: 
                cin >> input; 
                bsTree.rankerase(input); 
                break; 
            default: 
                break; 
        } 
    } 
    return 0; 
} 
