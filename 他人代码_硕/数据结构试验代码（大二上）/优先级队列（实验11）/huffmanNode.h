#pragma once
#include<iostream>
#include"С����.h"
#include"������.h"
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
{//��Ȩweight[1:n]����huffman����n>=1 
 //����һ�鵥�ڵ�
   huffmanNode<int> *hNode=new huffmanNode<T> [n+1];
   linkedBinaryTree<int> ET;  //����
   for(int i=1;i<=n;i++)
   {
   	  hNode[i].weight=weight[i];
   	  hNode[i].tree=new linkedBinaryTree<int>;
   	  hNode[i].tree->makeTree(i,ET,ET);   //i��tree�е�elementֵ���൱�ڽڵ��� 
   }
 //�õ��ڵ㹹��һ��С����(����Ȩ��weight��ȷ�����λ��)
   minHeap< huffmanNode<T> > heap;
   heap.initialize(hNode,n);
 
 //���ϴ�С������ȡ��������������ϲ����ٲ���ѣ�ֱ��ֻʣ��һ���� 
   huffmanNode<T> w,x,y;
   linkedBinaryTree<int> *t;
   for(int i=1;i<n;i++)
   {
   	  x=heap.top();  heap.pop();
   	  y=heap.top();  heap.pop();
   	  
   	  t=new linkedBinaryTree<int>;
   	  //cout<<"�м�Ԫ���ǣ�"<<x.tree->root_element()<<endl;
   	  t->makeTree(x.weight+y.weight, *(x.tree) , *(y.tree) );  //��huffman�ڵ������ĸ�Ԫ��ֵ������������Ȩ��ֵ�������ϲ�һ�� 
   	  w.weight=x.weight+y.weight;
   	  w.tree=t;
   	  heap.push(w);
   	  delete x.tree; delete y.tree;
   }
 //����ѭ��ʱheap��ֻʣһ���� 
   return heap.top().tree;
}




