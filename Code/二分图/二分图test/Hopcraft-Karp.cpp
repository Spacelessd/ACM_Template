#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
#define M 400005
struct edge{int v,next;}w[M];
int V[N],distx[N],disty[N],queue[N],link[N],ling[N];
int n,ll,ans;
bool build(){
	int tail=0,u,v;bool yes=0;
	memset(distx,0,sizeof(distx));
	memset(disty,0,sizeof(disty));
	for (int i=1;i<=n;++i) if (!ling[i])queue[++tail]=i;
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
	memset(link,0,sizeof(link));
	memset(ling,0,sizeof(ling));
	ans=0;
	while (build())
		for (int i=1;i<=n;++i)
			if (!ling[i])ans+=find(i);
}
inline void addedge(int x,int y){
	w[++ll].v=y;w[ll].next=V[x];V[x]=ll;
}
void init(){
	int u,v,n1,n2,m;
	scanf("%d%d%d",&n1,&n2,&m);n=n1>n2?n1:n2;
	ll=0;memset(V,0,sizeof(V));
	for (int i=1;i<=m;++i){
		scanf("%d%d",&u,&v);addedge(u,v);
	}
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	init();Hopcroft_Karp();
	printf("%d\n",ans);
	//system("pause");for (;;);
	return 0;
}


