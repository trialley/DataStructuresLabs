#include<iostream>
using namespace std;


class BTNode
{
	public:
		char element;  //�ڵ��е�Ԫ�� 
		BTNode *left,*right;  //�������� 
};


BTNode *createBT(char *post,char *in,int n)
{//post:��ź�������  in:�����������  n:���ӣ�����Ԫ������ 
	BTNode *next_root;
	char *p,cur_root;  //cur_root�Ǹ��ڵ�ֵ 
	int mid;  //���ڵ������������е���������0��ʼ��
	if(n<=0)  
	    return NULL;
	cur_root=*(post+n-1);
	next_root=new BTNode;
	next_root->element=cur_root;
	
	for(p=in;p<in+n;p++)
	{//ָ������ 
		if( (*p) == cur_root )
		   break;
	}
	mid=p-in;   //mid���ڼ��ʹ�����ǰ���м���Ԫ�ء�����������Ԫ���� 
	next_root->left=createBT(post,in,mid);            //�ݹ鹹�������� 
	next_root->right=createBT(post+mid,p+1,n-mid-1); //�ݹ鹹�������� 
	
	return next_root;
}

BTNode *CreateBT(char *pre,char *in,int n)
{
    if(n<=0)
	   return NULL;
	BTNode *b=new BTNode;
	char root=(*pre);  //ǰ�������е�һλ�Ǹ��ڵ��Ԫ��ֵ 
	b->element=root;
	char *p;
	int mid;   
	
	for(p=in;p<in+n;p++)
	{//ȡ��root�����������е�λ�� ��ָ�룩 
		if( (*p)== root ) 
		  break;
	}
	mid=p-in;    //mid���ڼ��ʹ�����ǰ���м���Ԫ�ء�����������Ԫ����
	b->left=CreateBT(pre+1,in,mid);
	b->right=CreateBT(pre+1+mid,p+1,n-mid-1);
	
	return b;
}
