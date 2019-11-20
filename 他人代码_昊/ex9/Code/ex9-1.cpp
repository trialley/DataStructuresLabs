#include <iostream> 
#include <string> 
using namespace std; 
/*
二叉树结点
*/ 
template <class E> 
struct binaryTreeNode      
{ 
    E element;       //节点元素
    binaryTreeNode<E>* leftChild;   //左儿子
    binaryTreeNode<E>* rightChild;  //右儿子
    binaryTreeNode() {rightChild = leftChild = NULL;} 
    binaryTreeNode(const E& theElement):element(theElement) {rightChild = leftChild = NULL;} 
    binaryTreeNode(const E& theElement, binaryTreeNode<E>* theLeftChild, binaryTreeNode<E>* theRightChild):element(theElement) 
    { 
        rightChild = theRightChild; 
        leftChild = theLeftChild; 
    } 
}; 
/*
链表节点
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
链表型队列
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
二叉树
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
        void makeTree(int n); //建树
        void leverOrder(); //层次遍历
        void pheight(); //输出节点作为根节点的子树的高度
        void pcount(); 
           //输出节点作为根节点的子树的节点数
    protected: 
        binaryTreeNode<E>* root;   //二叉树的根节点
        int treeSize;  //树的节点的个数
        int* hei;  //记录每个节点作为根节点的子树的高度
        int* cou; //记录每个节点作为根节点的子树的节点个数
        int height(binaryTreeNode<E>*);//计算某个节点作为根节点的子树的高度
        int count(binaryTreeNode<E>*); //计算某个节点作为根节点的子树的节点个数
}; 
/*
建树过程
*/ 
template <class E> 
void linkedBinaryTree<E>::makeTree(int n) 
{ 
    treeSize = n; 
    hei = new int[treeSize]; //定义hei数组
    cou = new int[treeSize]; //定义cou数组
    for(int i=0; i<treeSize; i++) 
    { 
        hei[i] = 0; 
        cou[i] = 0; 
    } 
    int theLeftChild; //定义左孩子
    int theRightChild; //定义右孩子
    binaryTreeNode<E>* childs[n];    //创建一个树结点数组保存树中的其他节点
    for (int i=0; i<n; i++)    //为每个节点赋值
        childs[i] = new binaryTreeNode<E>(i+1); 
        //节点元素的赋值，为下标值加一
    root = childs[0]; 
    for (int i=0; i<n; i++) 
    { 
        cin >> theLeftChild; 
        cin >> theRightChild; 
        if (theLeftChild != -1) 
            childs[i]->leftChild = childs[theLeftChild-1];  //左孩子节点的建立
        else 
            childs[i]->leftChild = NULL; 
        if (theRightChild != -1) 
            childs[i]->rightChild = childs[theRightChild-1];//右孩子节点的建立
        else 
            childs[i]->rightChild = NULL; 
    } 
} 
/*
层次遍历
*/ 
template <class E> 
void linkedBinaryTree<E>::leverOrder() 
{ 
    chainQueue<binaryTreeNode<E>*> q; //记录节点
    binaryTreeNode<E>* t = root; 
    while(t != NULL) 
    { 
        cout << t->element << " "; 
        if (t->leftChild != NULL) //入队左孩子
            q.push(t->leftChild); 
        if (t->rightChild != NULL) //入队右孩子
            q.push(t->rightChild); 
        try {t = q.front();} 
        catch (string error) {break;} 
        q.pop(); 
    } 
    cout << endl; 
} 
/*
计算高度
*/ 
template <class E> 
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t) 
{ 
    if (t == NULL) 
        return 0; 
    int hl = height(t->leftChild); //左子树高度
    int hr = height(t->rightChild); //右子树高度
    if (hl>hr) //取其中较大值
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
计算节点数
*/ 
template <class E> 
int linkedBinaryTree<E>::count(binaryTreeNode<E>* t) 
{ 
    if (t == NULL) 
        return 0; 
    int cl = count(t->leftChild);   //左子树节点数
    int cr = count(t->rightChild); //右子树节点数
    cou[t->element-1] = cl + cr + 1; //左子树节点数加右子树节点数加一
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
    int n;  //二叉树节点数量
    cin >> n; 
    linkedBinaryTree<int> b; 
    b.makeTree(n); 
    b.leverOrder(); 
    b.pcount(); 
    b.pheight(); 
    cout << endl; 
    return 0; 
} 
