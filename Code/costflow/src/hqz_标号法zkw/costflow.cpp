#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define N 20005
#define M 1000005
int son[N],dis[N],v[N],cur[N];
int link[M],next[M],cap[M],opp[M],cost[M];
int n,m,ll,S,T,maxflow,mincost;
inline int min(int a,int b) {return a<b?a:b;}
void addedge(int x,int y,int z,int w)
{
	link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;cost[ll]=w;
	link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;cost[ll]=-w;
}
void init()
{
	int i,x,y,z,w;
	scanf("%d%d",&n,&m);
	memset(son,-1,sizeof(int)*(n+5));
	S=1;T=n;ll=0;mincost=maxflow=0;
	for (i=1;i<=m;++i)scanf("%d%d%d%d",&x,&y,&z,&w),addedge(x,y,z,w);
}
int aug(int x,int flow){
	int j,d;
	if (x==T){
		mincost+=flow*dis[S];
		maxflow+=flow;
		return flow;
	}
	v[x]=1;
	for (j=cur[x];j!=-1;j=next[j])
		if (cap[j]&&!v[link[j]]&&dis[x]==dis[link[j]]+cost[j])
			if (d=aug(link[j],min(flow,cap[j]))){
				cap[j]-=d;cap[opp[j]]+=d;cur[x]=j;
				return d;
			}
	cur[x]=j;return 0;
}
int modlabel(){
	int d=oo;
	for (int i=1;i<=n;++i)if (v[i])
		for (int j=son[i];j!=-1;j=next[j])
			if (cap[j]&&!v[link[j]]&&cost[j]-dis[i]+dis[link[j]]<d)
				d=cost[j]-dis[i]+dis[link[j]];
	if (d==oo)return 0;
	for (int i=1;i<=n;++i)
		if (v[i])v[i]=0,dis[i]+=d;
	return 1;
}
void findflow(){
	memset(dis,0,sizeof(int)*(n+5));
	do {
		memcpy(cur,son,sizeof(int)*(n+5));
		while (aug(S,oo))memset(v,0,sizeof(int)*(n+5));
	}while (modlabel());
}
int main()
{
	freopen("costflow.in","r",stdin);
	freopen("costflow.out","w",stdout);
	init();findflow();
	//printf("%d\n",maxflow);
	printf("%d\n",mincost);
	//system("pause");for (;;);
	return 0;
}


