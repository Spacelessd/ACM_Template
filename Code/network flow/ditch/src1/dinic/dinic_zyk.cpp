#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <ctime>
#include <algorithm>
#define min(a,b)	((a)<(b)?(a):(b))
#define max(a,b)	((a)>(b)?(a):(b))
#define abs(a)	((a)<0?-(a):(a))
#define inf 214748364
#define pi 3.141592653589793
#define maxn 400011
#define maxm 2000001
using namespace std;
typedef long long ll;
int con=1,fir[maxn],next[maxm],no[maxm],t[maxm];
int n,m,bel[maxn],lim;
int dis[maxn],low[maxn],dfn[maxn],sta[maxn],stan;
int insta[maxn],path[maxn],fin,top,ret,targe;
int st[maxm],en[maxm],bn;
int q[maxm],head,tail;
int f[maxm],res;
inline void addline(int st,int en)
{
	next[++con]=fir[st],fir[st]=con;
	t[con]=en,f[con]=1;
	next[++con]=fir[en],fir[en]=con;
	t[con]=st,f[con]=0;
}
inline bool bfs()
{
	q[head=tail=0]=0;
	memset(dis,63,sizeof(dis));
	dis[0]=0;
	while(head<=tail)
	{
		int p=q[head++];
		for(int i=fir[p];i;i=next[i])
		if(f[i]&&dis[t[i]]>dis[p]+1)
		{
			dis[t[i]]=dis[p]+1;
			if(dis[t[i]]<dis[targe])
				q[++tail]=t[i];
		}
	}
	return dis[targe]<inf;
}
inline void dfs(int p)
{
	if(p==targe)
	{
		int minn=inf;
		for(int i=0;i<dis[targe];++i)
			minn=min(minn,f[path[i]]);
		for(int i=dis[targe]-1;i>=0;--i)
		{
			f[path[i]]-=minn,f[path[i]^1]+=minn;
			if(!f[path[i]])
				ret=i;
		}
		fin=1;
		return;
	}
	for(int i=fir[p];i;i=next[i])
	if(f[i]&&dis[t[i]]==dis[p]+1)
	{
		path[dis[p]]=i;
		dfs(t[i]);
		if(fin)
			if(ret==dis[p])
				fin=ret=0;else
				return;
	}
	dis[p]=-1;
}
inline void dinic()
{
	while(bfs())
	{
		fin=0;
		dfs(0);
	}
}
inline void tarjan(int p)
{
	dfn[p]=low[p]=++top;
	sta[++stan]=p,insta[p]=1;
	for(int i=fir[p];i;i=next[i])
	if(f[i]&&t[i]>=1&&t[i]<=n*2)
	{
		if(!dfn[t[i]])
			tarjan(t[i]),low[p]=min(low[p],low[t[i]]);else
		if(insta[t[i]])
			low[p]=min(low[p],dfn[t[i]]);else
			continue;
	}
	if(low[p]==dfn[p])
	{
		++bn;
		do
		{
			insta[sta[stan]]=0;
			bel[sta[stan]]=bn;
			stan--;
		}while(sta[stan+1]!=p);
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("cupid.in","r",stdin);
	freopen("cupid.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&st[i],&en[i]);
		en[i]+=n;
		addline(st[i],en[i]);
		no[i]=con;
	}
	targe=n*2+1;
	for(int i=1;i<=n;++i)
		addline(0,i),addline(i+n,targe);
	dinic();
	for(int i=1;i<=n*2;++i)
	if(!bel[i])
		tarjan(i);
	for(int i=1;i<=m;++i)
	if(bel[st[i]]!=bel[en[i]])
	{
		if(f[no[i]])
			printf("1");else
			printf("2");
	}else
		printf("0");
	printf("\n");
	return 0;
}