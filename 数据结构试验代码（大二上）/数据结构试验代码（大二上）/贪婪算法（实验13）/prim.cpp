#define N 10            // �������ڵ�����ʵ���м����Ǽ���
#define MAXDIST 100        // �����룬��ʾ�����ڵ�䲻�ɴ�, Ϊ�����뷽�����ó�100��ʵ�ʿ���INT_MAX

// Ϊ�˼��㷽�㴫��ľ��������ָ������ĸ�ʽ��n�ǽڵ���
int Prim(int (*map)[N], int n)
{
    int i, j;
    int minDist, minIndex, totalWeight;
    int *visited, *parent, *dist;    // �ֱ𱣴�ڵ���Ѵ��־�����ڵ㣬�����ľ���

    // ����ռ䲢����
    visited = (int *)malloc(n * sizeof(int));
    parent = (int *)malloc(n * sizeof(int));
    dist = (int *)malloc(n * sizeof(int));

    memset(visited, 0, n * sizeof(int));
    memset(parent, 0, n * sizeof(int));
    memset(dist, 0, n * sizeof(int));

    // ��ʼ�������ýڵ�0Ϊ���ڵ�
    visited[0] = 1;
    totalWeight = 0;

    // ��ʼ��δ��ڵ㵽���ľ���
    for (i = 1; i < n; ++i)
    {
        parent[i] = 0;
        dist[i] = map[0][i];    //dist[0]=0;
    }

    printf("\nEdge\tWeight\n");

    // n - 1��ѭ���ҳ�n - 1����
    for (i = 0; i < n - 1; ++i)
    {
        minDist = MAXDIST;
        minIndex = i;

        // �ҳ�����������С�Ľڵ�
        for (j = 1; j < n; ++j)
        {
            if (visited[j] == 0 && dist[j] < minDist)
            {
                minDist = dist[j];
                minIndex = j;
            }
        }

        if (minIndex == i)        // ���нڵ㵽���ľ��붼ΪMAXDIST��˵��������ͨͼ������
        {
            printf("This is not a connected graph!\n");
            return MAXDIST;
        }

        // ��ǲ�����ҵ��Ľڵ�ͱ�
        visited[minIndex] = 1;
        totalWeight += minDist;
        printf("%d-->%d\t%3d\n", parent[minIndex], minIndex, map[parent[minIndex]][minIndex]);

        // ����ʣ��ڵ㵽���ľ���
        for (j = 1; j < n; ++j)
        {
            if (visited[j] == 0 && map[j][minIndex] < dist[j])
            {
                parent[j] = minIndex;
                dist[j] = map[j][minIndex];
            }
        }
    }

    printf("\nTotal Weight: %d\n\n", totalWeight);

    return totalWeight;
}

 int main()
 {
      int map[N][N];
      int i, j;
      int n, tmp;
 
     printf("Num of nodes: ");
      scanf("%d", &n);
  
     printf("Distance matrix (lower triangular) : ");
     for (i = 1; i < n; ++i)
     {
         map[i][i] = 0;
 
         for (j = 0; j < i; ++j)
        {
             scanf("%d", &tmp);
             map[i][j] = tmp;
             map[j][i] = tmp;
         }
     }
 
     Prim(map, n);
 
     return 0;
 }
 
 
