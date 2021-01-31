#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 500005
int f[N][21];
int v[N],next[N*2],e[N*2],p[N],deep[N],ll;
inline void read(int &x){
	char ch; x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}
void dfs(int x,int dep){
	int i=v[x];
	deep[x]=dep;p[x]=1;
	while (i){
		if (!p[e[i]])dfs(e[i],dep+1);
		i=next[i];
	}
}
void findlca(int x,int y){
	int i;
	p[x]=y;f[x][0]=y;
	for (i=1;i<=20;++i)
		f[x][i]=f[f[x][i-1]][i-1];
	i=v[x];
	while (i){
		if (p[e[i]]==-1)findlca(e[i],x);
		i=next[i];
	}
}
int lca(int x,int y){
	int i;
	for (i=20;i>=0;--i){
		if (deep[x]-(1<<i)>=deep[y])x=f[x][i];
		if (deep[y]-(1<<i)>=deep[x])y=f[y][i];
	}
	for (i=20;i>=0;--i){
		if (f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	if (x!=y)x=f[x][0];
	return x;
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int t1=clock();
	int n,x,y,z;
	scanf("%d",&n);
	for(int i=1;i<=n-1;++i){
		read(x);read(y);
		++ll;e[ll]=y;next[ll]=v[x];v[x]=ll;
		++ll;e[ll]=x;next[ll]=v[y];v[y]=ll;
	}
	dfs(1,1);
	memset(p,-1,sizeof(p));
	findlca(1,0);
	int Q;scanf("%d",&Q);
	for (int i=1;i<=Q;++i)
		scanf("%d%d",&x,&y),printf("%d\n",lca(x,y));
	printf("%d\n",clock()-t1);
	return 0;
}


