#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 500010
int f[N][21];
int v[N],next[N],e[N],w[N],p[N],deep[N];
int n,i,x,y,z,ll;
inline void read(int &x){
	char ch; x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}
void dfs(int x,int cost,int dep){
	int i=v[x];
	deep[x]=dep;p[x]=1;
	while (i){
		if (!p[e[i]])dfs(e[i],w[i],dep+1);
		i=next[i];
	}
}
void findlca(int x,int y){
	int i,tmp;
	p[x]=y;
	f[x][0]=y;
	for (i=1;i<=20;++i){
		tmp=f[f[x][i-1]][i-1];
		if (tmp==-1)tmp=0;
		f[x][i]=tmp;
	}
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
    scanf("%d",&n);
	for(i=1;i<=n-1;++i){
		read(x);read(y);read(z);
		++ll;e[ll]=y;w[ll]=z;next[ll]=v[x];v[x]=ll;
		++ll;e[ll]=x;w[ll]=z;next[ll]=v[y];v[y]=ll;
	}
    dfs(1,0,1);
    memset(p,-1,sizeof(p));
    findlca(1,0);
    return 0;
}





