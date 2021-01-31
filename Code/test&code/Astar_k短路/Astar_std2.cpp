#include <iostream>
#include <queue>
using namespace std;
const int N=1010;
struct edge
{
	int to,w,nxt;
}e[N*N],ef[N*N];
int p[N],pf[N],q[N],n,m,s,t,k;
bool vis[N];
int h[N],g[N],tm[N];
struct astar
{
	int w,d,i;
	astar(int ww,int dd,int ii){w=ww,d=dd,i=ii;}
	friend bool operator<(astar a1,astar a2){return a1.w>a2.w;}
};
int main()
{
	scanf("%d%d",&n,&m);
	int i,j=0,x,y,w;
	memset(p,-1,sizeof(p));
	memset(pf,-1,sizeof(pf));
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&w);
		e[j].to=y;e[j].w=w;e[j].nxt=p[x];p[x]=j;
		ef[j].to=x;ef[j].w=w;ef[j].nxt=pf[y];pf[y]=j++;
	}
	scanf("%d%d%d",&s,&t,&k);
	memset(vis,0,sizeof(vis));
	int tl=-1,hd=-1;
	q[++tl]=t;
	for(i=1;i<=n;i++)
		h[i]=1<<29;
	h[t]=0;
	while(hd!=tl)
	{
		int u=q[hd=(hd+1)%N];
		vis[u]=false;
		for(int x=pf[u];x!=-1;x=ef[x].nxt)
		{
			int v=ef[x].to,w=ef[x].w;
			if(h[v]>h[u]+w)
			{
				h[v]=h[u]+w;
				if(!vis[v])
					vis[q[tl=(tl+1)%N]=v]=true;
			}
		}
	}
	if(s==t)
		k++;
	memset(tm,0,sizeof(tm));
	priority_queue<astar>pq;
	pq.push(astar(h[s],0,s));
	int ans=-1;
	while(!pq.empty())
	{
		int u=pq.top().i,d=pq.top().d,w=pq.top().w;
		pq.pop();
		tm[u]++;
		if(tm[u]>k)
			continue;
		if(tm[t]==k)
		{
			ans=w;
			break;
		}
		for(int x=p[u];x!=-1;x=e[x].nxt)
		{
			int v=e[x].to,ww=e[x].w;
			pq.push(astar(d+ww+h[v],d+ww,v));
		}
	}
	printf("%d\n",ans);
	return 0;
}

 
