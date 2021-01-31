/*
PROG:NOI2008 志愿者招募employee
ALGO:minimum cost maximum flow(实现采用类似SAP的算法)
STAT:AC(total test time 0.72s)
MEMO:本题的关键在构图，怎样做以及为什么要这样做参看CMYK的解题报告。另一个关键是实现，如果
     直接套用SPFA求最小费用流，则通常只能过8组数据。采用类似SAP的算法，可以完美AC。
	 算法思想如下（BY ZKW）：
	 定义d[i]为点i的距离标号, c[i][j]为边edge(i,j)的权
	 任何一个最短路算法保证，算法结束时对任意边edge(i,j)满足:
            d[i] <= d[j] + c[i][j]	         （条件1）
	 且对于每个i，至少存在一个j使得等号成立  （条件2）
     换句话说，任何一个满足以上两个条件的算法都可以叫做最短路，而不仅仅是SPFA、Dijkstra.
	 算法结束后，恰在最短路上的边满足d[i]=d[j]+c[i][j]
     
	 在最小费用流的计算中，我们每次沿d[i]=d[j]+c[i][j]的路径增广后都不会破坏条件1，
	 但是可能破坏了条件2。(这个论断是不是需要假设初始的d[i]是很大的？)
	 不满足条件2的后果是什么呢？使我们找不到每条边都满足d[i]=d[j]+c[i][j]的新的增广路。
	 如果采用使用Dijkstra，SPFA等等算法计算最小费用流，
	 只好每次增广后重新计算新的满足条件2的距离标号。这无疑是一种浪费！
	 我们可以采用类似SAP计算最大流的思想，在始终满足条件1的距离标号上不断修改，
	 直到可以继续增广（满足条件2）。 
     根据最后一次寻找增广路不成功的DFS，找到
	 t = min{d[j]+c[i][j]-d[i]} (visit[i]==true && visit[j]==false && cap[i][j]>0)
	 然后所有访问过的点(visit[i]==true)的距离标号d[i]增加t
	 可以证明，这样不会破坏性质1，而且至少有一条新的边进入了d[i]=d[j]+c[i][j]的子图
	 
	 算法的步骤就是初始标号设为0 ，不断增广，如果不能增广，修改标号继续增广，
	 直到彻底不能增广：源点的标号已经被加到了+∞。 
     
	 另：在最大流SAP用DFS找增广路的过程中，有两种处理办法：
	 (1)找到一条增广路，立即退出DFS过程，更新流量
	 (2)找到一条增广路，不退出，累加当前路径的可增广量，再从当前点继续找新的增广路
	 对于最大流问题，当前第(2)种方法的速度更快，但编码复杂度高些
	 对于最小费用流问题，由于距离标号受c[i][j]影响大，一般一次增广S-T之间的最短路只有一条
	 所以用(1)的方法处理就已经非常快了
	 这一点是我的认识，对吗？

LAST MODI：2009/5/31 

*/
#include <iostream>
using namespace std;
const int MAXN = 1248;
const int BIG  = 99999999;
struct node {
  int v, w, c;     		//v:adj vetex, c:capacity, w:cost
  node *next, *back;
};
node *g[MAXN];			//ajacent list to store the flow network
int n, m, cost;
int S, T;				//S: source node, T: sink node
int dist[MAXN];			//dist: shortest distance
bool visit[MAXN];

inline void addedge(int u, int v, int w, int c = BIG)
{
  node nu = {v, w, c, g[u], NULL}, nv = {u, -w, 0, g[v], NULL};
  g[u] = new node(nu);
  g[v] = new node(nv);
  g[u]->back = g[v];
  g[v]->back = g[u];
}
void init()
{
  int i, j, k, t;
  freopen("employee.in","r",stdin);
  freopen("employee.out","w",stdout);
  scanf("%d%d", &n, &m);
  n++;
  for (i=1; i<n; i++)
  {
    scanf("%d", &t);
	addedge(n+1, i, 0, t);
	addedge(i+1, 0, 0, t);
  }
  for (i=1; i<=m; i++)
  {
    scanf("%d%d%d", &j, &k, &t);
	addedge(j, k+1, t);
  }
  for (i=1; i<n; i++)
    addedge(i+1, i, 0);
  S = n+1;    T = 0;
}

int aug(int i, int lim)   //recursively find the shortest augmenting path
{
  node *p;
  int d, nlim;
  if (i==T)					//找到汇点
  {
    cost += dist[S] * lim;	//累加本次增广的费用代价
	return lim;				//返回增广容量
  }
  visit[i] = true;
  for (p = g[i]; p != NULL; p = p->next)
    if ( !visit[p->v] && (p->c > 0) && (p->w + dist[p->v] == dist[i])) //can go to p->v
	{
	   nlim = lim < p->c ? lim : p->c;		//新的可增广容量
	   d = aug(p->v, nlim);					//沿路径递归
	   if (d > 0)							//如果可达汇点，则找到一条可增广路
	   {
	     p->c -= d;							//更新容量
	     p->back->c += d;
	     return d;
	   }
	}
  return 0;		  //can not find a augmenting path
}

bool modlabel()		//修改距离标号
{
  int d = BIG, t, i;
  node *p;
  for (i = 0; i<= n+1; i++)
    if (visit[i])
	  for (p = g[i]; p ; p = p->next)
	    if (!visit[p->v] && p->c > 0)
		{
		  t = dist[p->v] + p->w - dist[i];
		  if (t < d) d = t;
		}
  if (d == BIG) return false;
  for (i=0; i<= n+1; i++)
    if (visit[i])
	  dist[i] += d;
  return true;
}

int main()
{
  init();
  do {
    do
	  memset(visit, 0, sizeof(visit));
	while(aug(S, BIG));
  }while(modlabel());
  printf("%d\n", cost);
  return 0;
}


