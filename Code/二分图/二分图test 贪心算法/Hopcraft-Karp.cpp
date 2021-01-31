#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 100005
#define maxm 400005
struct edge{
	int v,next;
};
edge w[maxm];
int	V[maxn],distx[maxn],disty[maxn],queue[maxn],link[maxn],ling[maxn];
int	M,N,ll=0,ans;
bool build(){
	int tail=0,u,v;bool yes=0;
	memset(distx,0,sizeof(distx));
	memset(disty,0,sizeof(disty));
	for (int i=1;i<=N;++i) if (!ling[i]) queue[++tail]=i;
	for (int head=1;head<=tail;++head){
		u=queue[head];
		for (int i=V[u];i;i=w[i].next){
			if (disty[v=w[i].v]) continue;
			disty[v]=distx[u]+1;
			if (!link[v])yes=1;
				else distx[queue[++tail]=link[v]]=disty[v]+1;
		}
	}
	return yes;
}
bool find(int u){
	for (int i=V[u];i;i=w[i].next){
		int v=w[i].v;
		if (disty[v]!=distx[u]+1||!disty[v]) continue;
		disty[v]=0;
		if (!link[v]||find(link[v])){
			link[v]=u;ling[u]=v;
			return 1;
		}
	}
	return 0;
}
void Hopcroft_Karp(){
	ans=0;ll=0;
	memset(link,0,sizeof(link));
	memset(ling,0,sizeof(ling));
	while (build())
		for (int i=1;i<=N;++i)
			if (!ling[i]) ans+=find(i);
}
void addedge(int x,int y){
	w[++ll].v=y;w[ll].next=V[x];V[x]=ll;
}
void init(){
	int u,v,N1,N2;
	scanf("%d%d%d",&N1,&N2,&M);
	if (N1>N)N=N1;
	if (N2>N)N=N2;
	for (int i=1;i<=M;++i){
		scanf("%d%d",&u,&v);addedge(u,v);
	}
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	init();Hopcroft_Karp();
	printf("%d\n",ans);
	return 0;
}




