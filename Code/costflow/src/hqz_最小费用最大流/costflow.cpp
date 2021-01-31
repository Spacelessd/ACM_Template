#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 20005
#define M 100005
#define oo (1<<29)
int son[N],q[N],d[N],pre[N],inq[N];
int link[M],st[M],next[M],cap[M],opp[M],cost[M];
int n,m,S,T,ll,maxflow,mincost;
void addedge(int x,int y,int z,int c){
	link[++ll]=y;st[ll]=x;next[ll]=son[x];son[x]=ll;cap[ll]=z;cost[ll]=c;opp[ll]=ll+1;
	link[++ll]=x;st[ll]=y;next[ll]=son[y];son[y]=ll;cap[ll]=0;cost[ll]=-c;opp[ll]=ll-1;
}
int spfa(int s){
	int h=0,t=1,i,j,p;
	for (int i=0;i<=n;++i)d[i]=oo;
	for (int i=0;i<=n;++i)inq[i]=0;
	d[S]=0;q[1]=S;inq[S]=1;
	while (h!=t){
		h=h<n?h+1:1;i=q[h];inq[i]=0;
		for (p=son[i];p!=-1;p=next[p]){
			j=link[p];
			if (d[i]+cost[p]<d[j]&&cap[p]){
				d[j]=d[i]+cost[p];pre[j]=p;
				if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
			}
		}
	}
	return d[T]<oo?1:0;
}
void update(){
	int p,flow=oo;
	for (p=T;p!=S;p=st[p]){
		p=pre[p];if (cap[p]<flow)flow=cap[p];
	}
	maxflow+=flow;
	for (p=T;p!=S;p=st[p]){
		p=pre[p];mincost+=cost[p]*flow;
		cap[p]-=flow;cap[opp[p]]+=flow;
	}
}
int main()
{
	freopen("costflow.in","r",stdin);
	freopen("costflow.out","w",stdout);
	int nn,x,y,z,w;ll=0;scanf("%d%d",&nn,&m);
	n=nn;S=1;T=n;memset(son,-1,sizeof(int)*(n+1));
	for (int i=1;i<=m;++i){
		scanf("%d%d%d%d",&x,&y,&z,&w);
		addedge(x,y,z,w);
	}
	maxflow=mincost=0;while (spfa(S))update();
	//printf("%d\n",maxflow);
	printf("%d\n",mincost);
	//system("pause");for(;;);
	return 0;
}


