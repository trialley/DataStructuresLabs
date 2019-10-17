#include <iostream> 
#include <string> 
using namespace std; 
/*
���������
*/ 
template <class E> 
struct binaryTreeNode      
{ 
    E element;       //�ڵ�Ԫ��
    binaryTreeNode<E>* leftChild;   //�����
    binaryTreeNode<E>* rightChild;  //�Ҷ���
    binaryTreeNode() {rightChild = leftChild = NULL;} 
    binaryTreeNode(const E& theElement):element(theElement) {rightChild = leftChild = NULL;} 
    binaryTreeNode(const E& theElement, binaryTreeNode<E>* theLeftChild, binaryTreeNode<E>* theRightChild):element(theElement) 
    { 
        rightChild = theRightChild; 
        leftChild = theLeftChild; 
    } 
}; 
/*
����ڵ�
*/ 
template <class T> 
struct chainNode 
{ 
    T element; 
    chainNode<T>* next; 
    chainNode(){} 
    chainNode(const T& theElement) 
    { 
        element = theElement; 
        next = NULL; 
    } 
    chainNode(const T& theElement, chainNode<T>* theNext) 
    { 
        element = theElement; 
        next = theNext; 
    } 
}; 
/*
�����Ͷ���
*/ 
template <class T> 
class chainQueue 
{ 
    public: 
        chainQueue() 
        { 
            queueFront = NULL; 
            queueSize = 0; 
        } 
        ~chainQueue() 
        { 
            while (queueFront != NULL) 
            { 
                chainNode<T>* nextNode = queueFront->next; 
                delete queueFront; 
                queueFront = nextNode; 
            } 
        } 
        bool empty() const {return queueSize == 0;} 
        int size() const {return queueSize;} 
        T& front() 
        { 
            if (queueSize == 0) 
            { 
                string error = "Empty queue"; 
                throw error; 
            } 
            return queueFront->element; 
        } 
        T& back() 
        { 
            if (queueSize == 0) 
            { 
                string error = "Empty queue"; 
                throw error; 
            } 
            return queueBack->element; 
        } 
        void pop() 
        { 
            if (queueSize == 0) 
            { 
                string error = "Empty queue"; 
                throw error; 
            } 
            chainNode<T>* nextNode = queueFront->next; 
            delete queueFront; 
            queueFront = nextNode; 
            queueSize--; 
        } 
        void push(const T& theElement) 
        { 
            chainNode<T>* newNode = new chainNode<T>(theElement); 
            if (queueSize == 0) 
                queueFront = newNode; 
            else 
                queueBack->next = newNode; 
            queueBack = newNode; 
            queueSize++; 
        } 
    private: 
        chainNode<T>* queueFront; 
        chainNode<T>* queueBack; 
        int queueSize; 
}; 
/*
������
*/ 
template <class E> 
class linkedBinaryTree 
{ 
    public: 
        linkedBinaryTree() 
        { 
            root = NULL; 
            treeSize = 0; 
        } 
        ~linkedBinaryTree(){;} 
        int size() const {return treeSize;} 
        void makeTree(int n); //����
        void leverOrder(); //��α���
        void pheight(); //����ڵ���Ϊ���ڵ�������ĸ߶�
        void pcount(); 
           //����ڵ���Ϊ���ڵ�������Ľڵ���
    protected: 
        binaryTreeNode<E>* root;   //�������ĸ��ڵ�
        int treeSize;  //���Ľڵ�ĸ���
        int* hei;  //��¼ÿ���ڵ���Ϊ���ڵ�������ĸ߶�
        int* cou; //��¼ÿ���ڵ���Ϊ���ڵ�������Ľڵ����
        int height(binaryTreeNode<E>*);//����ĳ���ڵ���Ϊ���ڵ�������ĸ߶�
        int count(binaryTreeNode<E>*); //����ĳ���ڵ���Ϊ���ڵ�������Ľڵ����
}; 
/*
��������
*/ 
template <class E> 
void linkedBinaryTree<E>::makeTree(int n) 
{ 
    treeSize = n; 
    hei = new int[treeSize]; //����hei����
    cou = new int[treeSize]; //����cou����
    for(int i=0; i<treeSize; i++) 
    { 
        hei[i] = 0; 
        cou[i] = 0; 
    } 
    int theLeftChild; //��������
    int theRightChild; //�����Һ���
    binaryTreeNode<E>* childs[n];    //����һ����������鱣�����е������ڵ�
    for (int i=0; i<n; i++)    //Ϊÿ���ڵ㸳ֵ
        childs[i] = new binaryTreeNode<E>(i+1); 
        //�ڵ�Ԫ�صĸ�ֵ��Ϊ�±�ֵ��һ
    root = childs[0]; 
    for (int i=0; i<n; i++) 
    { 
        cin >> theLeftChild; 
        cin >> theRightChild; 
        if (theLeftChild != -1) 
            childs[i]->leftChild = childs[theLeftChild-1];  //���ӽڵ�Ľ���
        else 
            childs[i]->leftChild = NULL; 
        if (theRightChild != -1) 
            childs[i]->rightChild = childs[theRightChild-1];//�Һ��ӽڵ�Ľ���
        else 
            childs[i]->rightChild = NULL; 
    } 
} 
/*
��α���
*/ 
template <class E> 
void linkedBinaryTree<E>::leverOrder() 
{ 
    chainQueue<binaryTreeNode<E>*> q; //��¼�ڵ�
    binaryTreeNode<E>* t = root; 
    while(t != NULL) 
    { 
        cout << t->element << " "; 
        if (t->leftChild != NULL) //�������
            q.push(t->leftChild); 
        if (t->rightChild != NULL) //����Һ���
            q.push(t->rightChild); 
        try {t = q.front();} 
        catch (string error) {break;} 
        q.pop(); 
    } 
    cout << endl; 
} 
/*
����߶�
*/ 
template <class E> 
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t) 
{ 
    if (t == NULL) 
        return 0; 
    int hl = height(t->leftChild); //�������߶�
    int hr = height(t->rightChild); //�������߶�
    if (hl>hr) //ȡ���нϴ�ֵ
    { 
        hei[t->element-1] = hl+1; 
        return ++hl; 
    } 
    else 
    { 
        hei[t->element-1] = hr+1; 
        return ++hr; 
    } 
} 
template <class E> 
void linkedBinaryTree<E>::pheight() 
{ 
    height(root); 
    for (int i=0; i<treeSize; i++) 
        cout << hei[i] << " "; 
    cout << endl; 
} 
/*
����ڵ���
*/ 
template <class E> 
int linkedBinaryTree<E>::count(binaryTreeNode<E>* t) 
{ 
    if (t == NULL) 
        return 0; 
    int cl = count(t->leftChild);   //�������ڵ���
    int cr = count(t->rightChild); //�������ڵ���
    cou[t->element-1] = cl + cr + 1; //�������ڵ������������ڵ�����һ
    return cl + cr + 1; 
} 
template <class E> 
void linkedBinaryTree<E>::pcount() 
{ 
    count(root); 
    for (int i=0; i<treeSize; i++) 
        cout << cou[i] << " "; 
    cout << endl; 
} 
int main() 
{ 
    int n;  //�������ڵ�����
    cin >> n; 
    linkedBinaryTree<int> b; 
    b.makeTree(n); 
    b.leverOrder(); 
    b.pcount(); 
    b.pheight(); 
    cout << endl; 
    return 0; 
} 
