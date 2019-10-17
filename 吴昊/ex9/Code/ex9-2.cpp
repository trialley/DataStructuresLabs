#include <iostream> 
using namespace std; 
template <class E> 
struct binaryTreeNode     //二叉树节点
{ 
    E element;       //节点元素
    binaryTreeNode<E>* leftChild;   //左儿子
    binaryTreeNode<E>* rightChild;  //右儿子
    binaryTreeNode() 
    { 
        rightChild = leftChild = NULL; 
    } 
    binaryTreeNode(const E& theElement):element(theElement) 
    { 
        rightChild = leftChild = NULL; 
    } 
    binaryTreeNode(const E& theElement, binaryTreeNode<E>* theLeftChild, binaryTreeNode<E>* theRightChild):element(theElement) 
    { 
        rightChild = theRightChild; 
        leftChild = theLeftChild; 
    } 
};
 
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
        void transPost(E* pre, E* in, int theSize); 
    private: 
        binaryTreeNode<E>* root;   //二叉树的根节点
        int treeSize;  //数的节点的个数
}; 
template <class E> 
void linkedBinaryTree<E>::transPost (E* pre, E* in, int theSize) 
{ 
    if (theSize == 0)   //若长度为零，直接返回空指针
    { 
        return; 
    } 
    binaryTreeNode<E>* newNode = new binaryTreeNode<E>; 
    newNode->element = *pre;    //定位到前序的根节点
    int index = 0; 
    for (; index<theSize; index++) 
    { 
        if (in[index] == *pre)    //前序遍历的第一个元素肯定是根节点，定位其在中序遍历中的位置
        break; 
    } 
    transPost(pre+1,in,index);  //左子树肯定在中序根节点的左边
    transPost(pre+index+1,in+index+1,theSize-(index+1));  //右子树肯定在中序根节点的右边
    cout << newNode->element << " "; 
    delete newNode; 
} 
int main() 
{ 
    int n;  //二叉树节点数量
    cin >> n; 
    int pre[n];   //存储前序遍历的数组
    int in[n]; //存储中序遍历的数组
    for(int i=0; i<n; i++) 
        cin >> pre[i]; 
    for(int i=0; i<n; i++) 
        cin >> in[i]; 
    linkedBinaryTree<int> test; 
    test.transPost(pre,in,n); 
    return 0; 
} 
