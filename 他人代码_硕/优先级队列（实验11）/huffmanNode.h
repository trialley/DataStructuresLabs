#pragma once
#include<iostream>
#include"小根堆.h"
#include"二叉树.h"
using namespace std;

template<class T>
class huffmanNode
{
	public:
		operator T()
		{
			return weight;
		}	
		bool operator >(huffmanNode<T> A)
		{
			if(A.weight<this->weight) return true;
			else return false; 
		}
		bool operator >=(huffmanNode<T> A)
		{
			if(A.weight<=this->weight) return true;
			else return false; 
		}		
		linkedBinaryTree<int> * tree;
		T weight;
};

template<class T>
linkedBinaryTree<int>* huffman(T weight[],int n)
{//用权weight[1:n]生成huffman树，n>=1 
 //创建一组单节点
   huffmanNode<int> *hNode=new huffmanNode<T> [n+1];
   linkedBinaryTree<int> ET;  //空树
   for(int i=1;i<=n;i++)
   {
   	  hNode[i].weight=weight[i];
   	  hNode[i].tree=new linkedBinaryTree<int>;
   	  hNode[i].tree->makeTree(i,ET,ET);   //i是tree中的element值，相当于节点标号 
   }
 //让单节点构成一个小根堆(根据权重weight来确定相对位置)
   minHeap< huffmanNode<T> > heap;
   heap.initialize(hNode,n);
 
 //不断从小根堆中取出两个最轻的树合并后再插入堆，直到只剩下一颗树 
   huffmanNode<T> w,x,y;
   linkedBinaryTree<int> *t;
   for(int i=1;i<n;i++)
   {
   	  x=heap.top();  heap.pop();
   	  y=heap.top();  heap.pop();
   	  
   	  t=new linkedBinaryTree<int>;
   	  //cout<<"中间元素是："<<x.tree->root_element()<<endl;
   	  t->makeTree(x.weight+y.weight, *(x.tree) , *(y.tree) );  //让huffman节点中树的根元素值等于其子树的权重值，与书上不一样 
   	  w.weight=x.weight+y.weight;
   	  w.tree=t;
   	  heap.push(w);
   	  delete x.tree; delete y.tree;
   }
 //跳出循环时heap中只剩一颗树 
   return heap.top().tree;
}




