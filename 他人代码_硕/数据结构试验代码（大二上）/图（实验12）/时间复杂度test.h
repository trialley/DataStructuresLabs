//以下两种写法是一样的，因为第二层循环不是满的，所以时间复杂度是O(N^2) 
		while( S[dest]!=true )
		{/*下面找一个不在顶点集S中的u且L[u]标号最小，可以借助一下线性表吗？*/	 
			int u;
			for(u=1;u<=n;u++)
			{
				if( S[u]==false && L[u]==Minium(L,S,n) )  //这里找一个不在顶点集S且标号最小的点，复杂度可以降到O(1)吗？ 
				{                                        //按我的写法复杂度好像是O(n^3)，可以通过把两个循环判断条件糅合来降低复杂度嘛？ 
				    S[u]=true;  //把u加入顶点集S中
				    for(int v=1;v<=n;v++)
				    {//对每一个不属于S的顶点v 
				    	if( S[v]==false && L[u]+a[u][v]<L[v] )
				    	{
				    		L[v]=L[u]+a[u][v];
				    		predecessor[v]=u;   //顶点v的前驱是u 
						}   
					}
					break;  //跳到最外层的while循环 
			    }
			}
		}
		
		while( S[dest]!=true )
		{/*下面找一个不在顶点集S中的u且L[u]标号最小，可以借助一下线性表吗？*/	 
			int u,tag;
			for(u=1;u<=n;u++)
			{
				if( S[u]==false && L[u]==Minium(L,S,n) )  //这里找一个不在顶点集S且标号最小的点，复杂度可以降到O(1)吗？ 
				{                                        //按我的写法复杂度好像是O(n^3)，可以通过把两个循环判断条件糅合来降低复杂度嘛？ 
				    S[u]=true;  //把u加入顶点集S中 
				    tag=u;
				    break;
			    } 
			}
			
			for(int v=1;v<=n;v++)
			{//对每一个不属于S的顶点v 
				if( S[v]==false && L[tag]+a[tag][v]<L[v] )
				{
				    L[v]=L[tag]+a[tag][v];
				    predecessor[v]=tag;   //顶点v的前驱是u 
				}   
			}
		}
