#include<iostream>
using namespace std;
//ɾ��һ�����������е��ظ��ڵ� 
/*
*/
struct ChainNode {
    int val;
    ChainNode next = null;

    ChainNode(int val) {
        this.val = val;
    }
};

ChainNode deleteDuplication(ChainNode *firstNode)
{
	if(firstNode==NULL)
	   return NULL;
	ChainNode *preNode,*curNode=firstNode;
	ChainNode *headNode=new ChainNode;    //���ö�����׽ڵ㣬ʡ������ 
	preNode=headNode;
	
	while(preNode->next!=NULL)
	{
		ChainNode *curNode=preNode->next;
		while(preNode->val!=curNode->val && curNode!=NULL)
		{
			curNode=curNode->next;
		}
		
		if(curNode==NULL)  //������һ������,prenode����һλ 
		{
			preNode=preNode->next;
		}
		else
		{//�ҵ����ظ���Ԫ�أ�ɾ������� 
		    preNode->next=curNode->next;
		    delete curNode;
		}
    }
	return firstNode;
	
}
