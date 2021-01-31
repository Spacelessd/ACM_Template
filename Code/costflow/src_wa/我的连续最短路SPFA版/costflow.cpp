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
求最短路换为SPFA，速度更快! SPFA如果用邻接矩阵，会不会更快？
在BZOJ1292的10组数据中，最慢的要4秒多一点

Task1 [187MS] right
Task2 [250MS] right
Task3 [344MS] right
Task4 [547MS] right
Task5 [844MS] right
Task6 [1281MS] right
Task7 [1750MS] right
Task8 [2594MS] right
Task9 [3375MS] right
Task10 [4672MS] right

Accepted  10/10
All right task [15844MS]

*/
#include <iostream>
using namespace std;
const int NMAX = 512;
const int BIG = 99999999;
int net[NMAX][NMAX], cost[NMAX][NMAX];
int path[NMAX], dist[NMAX];
int n, m, ans, s, t;	//s:源点, t:汇点
int q[NMAX*1024];		//SPFA要的队列
bool visit[NMAX];		//SPFA要的标志数组
void init()
{
    int i, j, k, c, d;
    scanf("%d%d", &n, &m);
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
          cost[i][j] = BIG;
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
bool SPFA()
{
	int i, j, f=0, r=1;
	memset(path, -1, sizeof(path));
	memset(visit, 0, sizeof(visit));
	fill(dist, dist+NMAX, BIG);
	dist[s] = 0;
	q[r] = s;
	visit[s] = true;
	while (f < r)
	{
		f++;
		i = q[f];	visit[i] = false;
		for (j=1; j<=n; j++)
			if (net[i][j] > 0 && dist[j] > dist[i] + cost[i][j])
			{
				if (!visit[j])
				{
					r++;
					q[r] = j;
					visit[j] = true;
				}
				dist[j] = dist[i] + cost[i][j];
				path[j] = i;
			}
	}
	return dist[t] != BIG;
}

int min_cost_max_flow()
{
    int mincost = 0, maxflow = 0;
    while( SPFA() )			//当存在从s到t的最短路（增广路）
	{
        int now = t;
        int neck = BIG;
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
