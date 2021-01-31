#include <cstdio>
#include <string.h>
#define NMax 2000
#define MMax 100000
#define OPT(_) (epool+(((_)-epool)^1))
using namespace std;
struct edge{
	int e,c,f;
	edge *next;
}epool[MMax+MMax],*etop;
int N,ret;
edge *E[NMax];
int dist[NMax];
char vi[NMax];
int dfs(int a,int m){
	if (a==N-1)return m;
	vi[a]=1;
	int l=m;
	for (edge *p=E[a];p && l;p=p->next)if (p->f && !vi[p->e] && dist[p->e]==dist[a]+p->c){
		int t=dfs(p->e,l>p->f?p->f:l);
		ret+=t*p->c,p->f-=t,OPT(p)->f+=t,l-=t;
	}
	return m-l;
}
int extend(){
	static int queue[NMax+1];
	static char inq[NMax];
	static edge *fa[NMax];
	for (int i=0;i<N;i++)dist[i]=1000000000,inq[i]=0;
	dist[queue[0]=0]=0;inq[0]=1;fa[0]=NULL;
	int head=0,bot=1/*,alpha=1000000000*/;
	while (head!=bot){int x=queue[head];head=(head==NMax?0:head+1);
		inq[x]=0;
		for (edge *p=E[x];p;p=p->next)if (p->f && dist[p->e]>dist[x]+p->c){
			dist[p->e]=dist[x]+p->c;fa[p->e]=OPT(p);
			if (!inq[p->e])inq[queue[bot]=p->e]=1,bot=(bot==NMax?0:bot+1);
		}
	}
	if (dist[N-1]==1000000000)return 0;
	//for (edge *p=fa[N-1];p;p=fa[p->e])if (alpha>OPT(p)->f)alpha=OPT(p)->f;
	//for (edge *p=fa[N-1];p;p=fa[p->e])p->f+=alpha,OPT(p)->f-=alpha,ret+=OPT(p)->c*alpha;
	do memset(vi,0,N*sizeof(vi[0]));
	while (dfs(0,1000000000));
	return 1;
}
int main()
{
	etop=epool;
	int M;
	scanf("%d %d",&N,&M);
	for (int i=0;i<N;i++)E[i]=NULL;
	for (int i=0;i<M;i++){
		int x,y,u,c;
		scanf("%d%d%d%d",&x,&y,&u,&c);x--;y--;
		etop->e=y;etop->c=c;etop->f=u;etop->next=E[x];E[x]=etop++;
		etop->e=x;etop->c=-c;etop->f=0;etop->next=E[y];E[y]=etop++;
	}
	ret=0;
	while (extend());
	printf("%d\n",ret);
	return 0;
}

