#include<stdio.h>
#include<stdlib.h>
int pos[50000];
int n;
int locationInMid(int mid[],int ms,int me,int root)
{
	int i;
	for(i=ms; i<=me; ++i)
	{
		if(mid[i]==root)
			return i;
	}
	return -1;
}
void postOrder(int pre[],int ps,int pe,int mid[],int ms,int me)
{
	int root=0,cl=0,cr=0;
	pos[--n]=pre[ps];
	root=locationInMid(mid,ms,me,pre[ps]);
	else
	{
		left=root-ms;
		right=me-root;
		if(right>0)
			postOrder(pre,ps+right+1,pe,mid,root+1,me);
		if(left>0)
			postOrder(pre,ps+1,ps+left,mid,ms,root-1);
	}
	return ;
}
int  main()
{
	int pre[50000];
	int mid[50000];
	int i,t;

	scanf("%d",&n);
	t=n;
	for(i=0; i<n; ++i)
		scanf("%d",&pre[i]);
	for(i=0; i<n; ++i)
		scanf("%d",&mid[i]);
		
	postOrder(pre,0,n-1,mid,0,n-1);

	for(i=0; i<t; ++i)
		printf("%d ",pos[i]);
	printf("\n");
	
	return 0;
}
