#include<iostream>
using namespace std;


class BTNode
{
	public:
		char element;  //节点中的元素 
		BTNode *left,*right;  //左右子树 
};


BTNode *createBT(char *post,char *in,int n)
{//post:存放后序序列  in:存放中序序列  n:（子）树的元素数量 
	BTNode *next_root;
	char *p,cur_root;  //cur_root是根节点值 
	int mid;  //根节点在中序序列中的索引（从0开始）
	if(n<=0)  
	    return NULL;
	cur_root=*(post+n-1);
	next_root=new BTNode;
	next_root->element=cur_root;
	
	for(p=in;p<in+n;p++)
	{//指针运算 
		if( (*p) == cur_root )
		   break;
	}
	mid=p-in;   //mid等于几就代表它前面有几个元素。即左子树的元素数 
	next_root->left=createBT(post,in,mid);            //递归构造左子树 
	next_root->right=createBT(post+mid,p+1,n-mid-1); //递归构造右子树 
	
	return next_root;
}

BTNode *CreateBT(char *pre,char *in,int n)
{
    if(n<=0)
	   return NULL;
	BTNode *b=new BTNode;
	char root=(*pre);  //前序序列中第一位是根节点的元素值 
	b->element=root;
	char *p;
	int mid;   
	
	for(p=in;p<in+n;p++)
	{//取得root在中序序列中的位置 （指针） 
		if( (*p)== root ) 
		  break;
	}
	mid=p-in;    //mid等于几就代表它前面有几个元素。即左子树的元素数
	b->left=CreateBT(pre+1,in,mid);
	b->right=CreateBT(pre+1+mid,p+1,n-mid-1);
	
	return b;
}
