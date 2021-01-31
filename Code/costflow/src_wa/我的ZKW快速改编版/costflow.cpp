#include <cstdio>
#include <cstring>
using namespace std;
const int BIG = 999999999;
const int MAXN = 1505;

int n, m;            //顶点数，边数
int cost;            //算出的最小费用
int dist[MAXN];        //最短路径
int c[MAXN][MAXN];    //边权矩阵
int u[MAXN][MAXN];    //残留网络
bool visit[MAXN];    //标志数组

inline int min(int a, int b)
{
	return a < b ? a : b;
}
int aug(int i,int augco)    //增广
{
        int j, delta;
        if(i == n)        //到达汇点
        {
            cost += dist[1] * augco;
            return augco;
        }
        visit[i] = true;
        for(j = 1; j <= n; j++)        //枚举邻接点
            if (!visit[j] && u[i][j] && dist[j] + c[i][j] == dist[i])
            {
                delta = min(augco, u[i][j]);
                delta = aug(j, delta);
                if (delta > 0)
                {
                    u[i][j] -= delta;
                    u[j][i] += delta;
                    return delta;
                }
            }
        return 0;
}

bool modlabel()        //修改标号
{
        int d = BIG, delta, i, j;
        for(i = 1; i <= n; i++)
            if(visit[i])
                for(j = 1; j <= n; j++)
                    if(!visit[j] && u[i][j])
                    {
                       delta = c[i][j] - dist[i] + dist[j];
                       if (delta < d)
                            d = delta;
                    }
        if(d == BIG) 
            return false;
        for(i = 1; i <= n; i++)
            if(visit[i])
                dist[i] += d;
        return true;
}

int main()
{
        freopen("costflow.in","r",stdin);
        freopen("costflow.out","w",stdout);
        int s,t,c0,u0;
        scanf("%d %d",&n,&m);
        memset(u, 0, sizeof(u));
        while(m--)
        {
                scanf("%d %d %d %d",&s,&t,&u0,&c0);
                c[s][t] = c0;
                c[t][s] = -c0;
                u[s][t] = u0;
                u[t][s]=0;
        }
        do {
            
            do {
                memset(visit, 0, sizeof(visit));
            }while(aug(1, BIG));
        }while(modlabel());
        printf("%d\n",cost);
        return 0;
}
