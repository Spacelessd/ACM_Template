#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 500005
#define D 20
int f[N][D+1],v[N],next[N],e[N],w[N],p[N],deep[N],ll;
inline void read(int &x){
	char ch; x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}
void dfs(int x,int cost,int dep){
	deep[x]=dep;p[x]=1;
	for (int i=v[x];i;i=next[i]){
		if (!p[e[i]])dfs(e[i],w[i],dep+1);
	}
}
void findlca(int x,int y){
	p[x]=y;f[x][0]=y;
	for (int i=1;i<=D;++i)
		f[x][i]=f[f[x][i-1]][i-1];
	for (int i=v[x];i;i=next[i])
		if (p[e[i]]==-1)findlca(e[i],x);
}
int lca(int x,int y){
	for (int i=D;i>=0;--i){
		if (deep[x]-(1<<i)>=deep[y])x=f[x][i];
		if (deep[y]-(1<<i)>=deep[x])y=f[y][i];
	}
	for (int i=D;i>=0;--i)
		if (f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	if (x!=y)x=f[x][0];
	return x;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,x,y,z;scanf("%d",&n);
	for(int i=1;i<=n-1;++i){
		read(x);read(y);read(z);
		++ll;e[ll]=y;w[ll]=z;next[ll]=v[x];v[x]=ll;
		++ll;e[ll]=x;w[ll]=z;next[ll]=v[y];v[y]=ll;
	}
	dfs(1,0,1);
	memset(p,-1,sizeof(p));
	findlca(1,0);
	system("pause");for (;;);
	return 0;
}


