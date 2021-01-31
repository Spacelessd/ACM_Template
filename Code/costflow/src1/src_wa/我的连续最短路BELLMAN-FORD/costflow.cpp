/*
网络中最小费用最大流:
输入格式：：
第1行：2个空格分开的整数N，M。N是节点数，M是边数。N≤500，M≤N^2/2 
第2..M+1行：每行4个空格分开的整数A，B，C，D，表示了一条有向边A-B，边的容量为C，费用为D 
输出格式：
第1行：1个整数，表示从源点1到汇点N的最小费用最大流

参数含义:     n代表网络中的总节点数，编号1～n
              net[][]代表残留网络
              cost[][]代表代价矩阵
              path[]保存增广路径
              dist[]源点到各点的最短路
算法:初始最小费用和最大流均为，寻找单位费用最短路
在最短路中求出最大流，即为增广路，再修改剩余网络，直到无可增广路为止
返回值:
              最小费用，最大流量
思考：
bellman_ford()可以换为SPFA，速度可能会更快
图用邻接表，可能会更快
当前算法，在BZOJ1292的10组数据中，最慢的要8秒多一点

Task1 [204MS] right
Task2 [281MS] right
Task3 [469MS] right
Task4 [954MS] right
Task5 [1531MS] right
Task6 [2375MS] right
Task7 [3219MS] right
Task8 [4766MS] right
Task9 [6687MS] right
Task10 [8703MS] right

Accepted  10/10
All right task [29189MS]

*/
#include <iostream>
using namespace std;
const int NMAX = 512;
int net[NMAX][NMAX], cost[NMAX][NMAX];
int path[NMAX], dist[NMAX];
int n, m, ans, s, t;	//s:源点, t:汇点
void init()
{
    int i, j, k, c, d;
    scanf("%d%d", &n, &m);
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
          cost[i][j] = INT_MAX;
        cost[i][i] = 0;
    }
    for (i=1; i<=m; i++)
    {
        scanf("%d%d%d%d", &j, &k, &c, &d);
        net[j][k] = c;
        cost[j][k] = d;
    }
	s = 1;    t = n;
}
bool bellman_ford()	//求从源点s到汇点n的最短路
{
    int i,j;
     memset(path,-1,sizeof(path));
     fill(dist, dist+NMAX, INT_MAX);
     dist[s] = 0;

    bool flag = true;		//标志能否松弛
    while(flag) 
	{
        flag = false;
        for(i=1;i<=n;i++) 
		{
            if(dist[i] == INT_MAX)  continue ;
            
            for(j=1;j<=n;j++) 
			{
			    //如果有残留容量，且可松弛
                if(net[i][j] > 0 && dist[j] > dist[i]+cost[i][j] ) 
				{
                     flag = true;
                     dist[j] = dist[i]+cost[i][j];	//更新j的距离
                     path[j] = i;					//更新j的前趋
                }
            }
        }
    }
    return dist[t] != INT_MAX;		//返回汇点n是否还可达
}

int min_cost_max_flow()
{
    int mincost = 0, maxflow = 0;
    while( bellman_ford() )			//当存在从s到t的最短路（增广路）
	{
        int now = t;
        int neck = INT_MAX;
        while(now != s) 			//查找最短路径上的最小残留容量
		{
            int pre = path[now];
            neck = min(neck, net[pre][now]);
            now = pre;
        }
        maxflow += neck;			//更新最大流
        now = t;
        while(now != s) 			//增广
		{
            int pre = path[now];
             net[pre][now] -= neck;					//会不会减成负数？不会！
             net[now][pre] += neck;					//反向流
             cost[now][pre] = - cost[pre][now];		//更新反向边的代价
             mincost += cost[pre][now] * neck;		//更新最小代价
             now = pre;
        }
    }
    return mincost;
}
int main()
{
    freopen("costflow.in","r",stdin);
    freopen("costflow.out","w",stdout);
    init();
    ans = min_cost_max_flow();
    printf("%d\n",ans);
    return 0;
}
