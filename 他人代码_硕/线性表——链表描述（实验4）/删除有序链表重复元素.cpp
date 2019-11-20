#include<iostream>
using namespace std;
//删除一个有序链表中的重复节点 
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
	ChainNode *headNode=new ChainNode;    //设置额外的首节点，省的讨论 
	preNode=headNode;
	
	while(preNode->next!=NULL)
	{
		ChainNode *curNode=preNode->next;
		while(preNode->val!=curNode->val && curNode!=NULL)
		{
			curNode=curNode->next;
		}
		
		if(curNode==NULL)  //遍历完一次链表,prenode后移一位 
		{
			preNode=preNode->next;
		}
		else
		{//找到了重复的元素，删除后面的 
		    preNode->next=curNode->next;
		    delete curNode;
		}
    }
	return firstNode;
	
}
