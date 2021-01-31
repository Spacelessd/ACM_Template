#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define oo (1<<30)
#define N 50005
#define M 180005
int a[N],l[N],r[N],p[N],visit[N],f[N],ans[M];
struct Edge{
	int link[N*2],next[N*2],son[N],l;
	void clear(int n){l=0;memset(son,0,sizeof(int)*(n+1));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
struct EdgeQ{
	int link[M*2],next[M*2],id[M*2],son[N],l;
	void addedge(int x,int y,int z){
		link[++l]=y;id[l]=z;next[l]=son[x];son[x]=l;
	}
}Q;
int find(int x){
	if (f[x]==x)return x;
	else return f[x]=find(f[x]);
}
void TarjanLCA(int x){
	visit[x]=1;
	for (int p=e.son[x];p;p=e.next[p]){
		int y=e.link[p];
		if (!visit[y])TarjanLCA(y),f[find(y)]=x;
	}
	visit[x]=2;
	for (int p=Q.son[x];p;p=Q.next[p])
		if (visit[Q.link[p]]==2)ans[Q.id[p]]=a[find(Q.link[p])];
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,x,y,root;scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)scanf("%d",&a[i]);
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),Q.addedge(x,y,i),Q.addedge(y,x,i);
	//min
	a[0]=-oo;r[0]=0;
	memset(l,0,sizeof(int)*(n+1));
	memset(r,0,sizeof(int)*(n+1));
	for (int i=1;i<=n;++i){
		int j=i-1;
		while (a[j]>=a[i])j=p[j];
		l[i]=r[j];p[r[j]]=i;r[j]=i;p[i]=j;
	}
	for (root=1;p[root];root=p[root]);
	e.clear(n);
	for (int i=1;i<=n;++i){
		if (l[i])e.addedge(i,l[i]);
		if (r[i])e.addedge(i,r[i]);
	}
	for (int i=1;i<=n;++i)f[i]=i;
	memset(visit,0,sizeof(int)*(n+1));
	TarjanLCA(root);
	for (int i=1;i<=m;++i)printf("%d\n",ans[i]);
	system("pause");for (;;);
	return 0;
}


