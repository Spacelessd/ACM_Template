#include <stdio.h>
#include <math.h>
#include <time.h>
#define MMax 300000
#define NMax 20020
using namespace std;
#define OPT(_) (epool+(((_)-epool)^1))
struct edge{
	int e,f;
	edge *next;
}epool[MMax+MMax],*etop;
edge *E[NMax];
int N;
int RelabelToFront(){
	static int h[NMax],e[NMax],pre[NMax],next[NMax];
	static edge *cur[NMax];
	int head,u;
	for (int i=1;i<N-1;i++){
		h[i]=0;e[i]=0;pre[i]=i-1;next[i]=i+1;
		cur[i]=E[i];
	}
	h[0]=N;h[N-1]=0;e[N-1]=e[0]=0;u=head=1;
	for (edge *p=E[0];p;p=p->next){
		e[p->e]+=p->f;OPT(p)->f+=p->f;p->f=0;
	}
	while (u<N-1){
		int oh=h[u];
		while (e[u]){
			for (;cur[u] && e[u];cur[u]=cur[u]->next)if (h[cur[u]->e]==h[u]-1 && cur[u]->f){
				int t=cur[u]->f;if (t>e[u])t=e[u];
				cur[u]->f-=t;OPT(cur[u])->f+=t;e[u]-=t;e[cur[u]->e]+=t;
			}
			if (e[u]){
				h[u]=N+N;
				for (edge *p=E[u];p;p=p->next)if (p->f && h[u]>h[p->e]+1)
					h[u]=h[p->e]+1;
				cur[u]=E[u];
			}
		}
		if (h[u]>oh){
			if (head!=u){
				if (next[u]<N-1)pre[next[u]]=pre[u];
				if (pre[u]>0)next[pre[u]]=next[u];
				next[u]=head;pre[u]=0;pre[head]=u;
				head=u;
			}
		}
		u=next[u];
	}
	return e[N-1];
}
int level[NMax];
int mkLevel(){
	for (int i=(level[0]=0)+1;i<N;i++)level[i]=-1;
	static int Q[NMax],bot;
	Q[(bot=1)-1]=0;
	for (int top=0;top<bot;top++){int x=Q[top];
		for (edge *p=E[x];p;p=p->next)if (level[p->e]==-1 && p->f)
			level[Q[bot++]=p->e]=level[x]+1;
	}
	return level[N-1]!=-1;
}
int extend(int a,int b){
	int r=0,t;
	if (a==N-1)return b;
	for (edge *p=E[a];p && r<b;p=p->next)if (p->f && level[p->e]==level[a]+1){
		t=p->f;if (t>b-r)t=b-r;t=extend(p->e,t);
		r+=t;p->f-=t;OPT(p)->f+=t;
	}
	if (!r)level[a]=-1;
	return r;
}
int Dinic(){int ret=0,t;
	while (mkLevel())while ((t=extend(0,1000000000)))ret+=t;
	return ret;
}
int SAP(){
	static int d[NMax],g[NMax+1],Q[NMax];
	static edge *c[NMax],*pre[NMax];
	int ret=0,x=0,bot;
	for (int i=0;i<N;i++)c[i]=E[i],d[i]=g[i]=0;
	pre[g[N]=0]=NULL;
	Q[(bot=1)-1]=N-1;
	for (int i=0;i<bot;i++)for (edge *p=E[Q[i]];p;p=p->next)
		if (OPT(p)->f && p->e!=N-1 && d[p->e]==0)d[Q[bot++]=p->e]=d[Q[i]]+1;
	for (int i=0;i<N;i++)g[d[i]]++;
	while (d[0]<N){
		while (c[x] && (!c[x]->f || d[c[x]->e]+1!=d[x]))c[x]=c[x]->next;
		if (c[x]){
			pre[c[x]->e]=OPT(c[x]);
			x=c[x]->e;
			if (x==N-1){
				int t=~0u>>1;
				for (edge *p=pre[N-1];p;p=pre[p->e])if (t>OPT(p)->f)t=OPT(p)->f;
				for (edge *p=pre[N-1];p;p=pre[p->e])
					p->f+=t,OPT(p)->f-=t;
				ret+=t;
				x=0;
			}
		}else{
			int od=d[x];
			g[d[x]]--;
			d[x]=N;
			for (edge *p=c[x]=E[x];p;p=p->next)if (p->f && d[x]>d[p->e]+1)d[x]=d[p->e]+1;
			g[d[x]]++;
			if (x)x=pre[x]->e;
			if (!g[od])break;
		}
	}
	return ret;
}
void addedge(int u,int v,int a,int b){
	etop->e=v;etop->f=a;etop->next=E[u];E[u]=etop;etop++;
	etop->e=u;etop->f=b;etop->next=E[v];E[v]=etop;etop++;
}
int &ran(){
	static int x=1234567;
	x+=(x<<4)+1;
	x&=(~0u>>1);
	return x;
}
void build(int n,int m){
	etop=epool;
	int a,b,c;
	N=n+2;
	for (int i=0;i<N;i++)E[i]=NULL;
	ran()=1365789;
	for (int i=1;i<=n;i++){
		//scanf("%d %d",&a,&b);
		a=ran()%10000+1;b=ran()%10000+1;
		addedge(0,i,a,0);
		addedge(i,N-1,b,0);
	}
	for (int i=0;i<m;i++){
		//scanf("%d %d %d",&a,&b,&c);
		a=ran()%n+1;
		do b=ran()%n+1; while (a==b);
		c=ran()%10000+1;
		addedge(a,b,c,c);
	}
}
int main()
{
	etop=epool;
	int n,m;
	scanf("%d %d",&n,&m);
	build(n,m);
	int t1=clock();
	printf("%d ",Dinic());
	printf("time=%d\n",(int)clock()-t1);
	build(n,m);
	t1=clock();
	printf("%d ",SAP());
	printf("time=%d\n",(int)clock()-t1);
	build(n,m);
	t1=clock();
	printf("%d ",RelabelToFront());
	printf("time=%d\n",(int)clock()-t1);
	getchar();getchar();
	return 0;
}
