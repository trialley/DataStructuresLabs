/*adjacencyWDigraph�����ƶ�ջģ��*/
void rDfs(int v) 
{//ʹ��ջģ��ݹ� 
	arrayStack<int> s(10);
	reach[v]=label;
	s.push(v);
	
	while(!s.empty()) //��ջ����ʱ 
	{
		int w=s.top();
		s.pop();
				
		for(int j=1;j<=n;j++)  //����һ������ĵ�w�������ڽӵ� 
		{
			if( a[w][j]!=noEdge) 
			{
				if(  reach[j]!=label ) //�������һ��δ��ǵĵ�j 
				{  reach[j]=label;  s.push(j);	} 
				else{//j�ѱ������wû�������ڽӵ���
					  if()  s.pop(); 
				}
			}
		}
	}
}

/*adjacencyWDigraph�ĵ�������ջģ��*/ 
void rDfs(int v) 
{//ʹ��ջģ��ݹ� 
	arrayStack<int> s(10);
	reach[v]=label;
	s.push(v);
	
	while(!s.empty()) //��ջ����ʱ 
	{
		int w=s.top();
		s.pop();
		myIterator *iv=iterator(w);		
		while( ( u=iv->next() )!=0 )  //����һ������ĵ�w�������ڽӵ� 
		{
			if(  reach[u]!=label ) //�������һ��δ��ǵĵ�j 
			{  reach[u]=label;  s.push(u);	} 
			else{//j�ѱ������wû�������ڽӵ���
				   if(iv->next()==0)  s.pop(); 
			    }
		}
	}
}


