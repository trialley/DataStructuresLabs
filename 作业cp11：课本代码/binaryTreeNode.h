#ifndef binaryTreeNode_
#define binaryTreeNode_

using namespace std;

template <class T>
struct binaryTreeNode
{
   T element;
   binaryTreeNode<T> *left,   // left subtree
                     *right;  // right subtree

   binaryTreeNode() {left = right = NULL;}
   binaryTreeNode(const T& theElement):element(theElement)
   {
      left = right = NULL;
   }
   binaryTreeNode(const T& theElement,
                  binaryTreeNode *theLeftChild,
                  binaryTreeNode *theRightChild)
                  :element(theElement)
   {
      left = theLeftChild;
      right = theRightChild;
   }
};

#endif
