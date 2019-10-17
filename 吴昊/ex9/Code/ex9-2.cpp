#include <iostream> 
using namespace std; 
template <class E> 
struct binaryTreeNode     //�������ڵ�
{ 
    E element;       //�ڵ�Ԫ��
    binaryTreeNode<E>* leftChild;   //�����
    binaryTreeNode<E>* rightChild;  //�Ҷ���
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
        binaryTreeNode<E>* root;   //�������ĸ��ڵ�
        int treeSize;  //���Ľڵ�ĸ���
}; 
template <class E> 
void linkedBinaryTree<E>::transPost (E* pre, E* in, int theSize) 
{ 
    if (theSize == 0)   //������Ϊ�㣬ֱ�ӷ��ؿ�ָ��
    { 
        return; 
    } 
    binaryTreeNode<E>* newNode = new binaryTreeNode<E>; 
    newNode->element = *pre;    //��λ��ǰ��ĸ��ڵ�
    int index = 0; 
    for (; index<theSize; index++) 
    { 
        if (in[index] == *pre)    //ǰ������ĵ�һ��Ԫ�ؿ϶��Ǹ��ڵ㣬��λ������������е�λ��
        break; 
    } 
    transPost(pre+1,in,index);  //�������϶���������ڵ�����
    transPost(pre+index+1,in+index+1,theSize-(index+1));  //�������϶���������ڵ���ұ�
    cout << newNode->element << " "; 
    delete newNode; 
} 
int main() 
{ 
    int n;  //�������ڵ�����
    cin >> n; 
    int pre[n];   //�洢ǰ�����������
    int in[n]; //�洢�������������
    for(int i=0; i<n; i++) 
        cin >> pre[i]; 
    for(int i=0; i<n; i++) 
        cin >> in[i]; 
    linkedBinaryTree<int> test; 
    test.transPost(pre,in,n); 
    return 0; 
} 
