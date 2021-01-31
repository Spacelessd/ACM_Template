#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
struct Edge{
	int link[N*2],next[N*2],cost[N*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
int n,m,ans;
int a[N],p[N];
void dfs(int dep,int anc,int x){
	if (x!=anc&&a[x]+a[anc]>dep)++ans;
	p[x]=1;
	for (int i=e.son[x];i;i=e.next[i])
		if (!p[e.link[i]])
			dfs(dep+e.cost[i],anc,e.link[i]);
}
/*
void dfs(int x){
	p[x]=1;
	for (int i=e.son[x];i;i=e.next[i])
		if (!p[e.link[i]])
			dfs(e.link[i]);
}
*/
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y,z;
	scanf("%d",&n);e.clear();
	for (int i=1;i<=n;++i)scanf("%d",&a[i]);
	for (int i=1;i<n;++i){
		scanf("%d%d%d",&x,&y,&z);
		e.addedge(x,y,z);e.addedge(y,x,z);
	}
	for (int i=1;i<=n;++i){
		memset(p,0,sizeof(p));
		dfs(0,i,i);
	}
	ans/=2;
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


