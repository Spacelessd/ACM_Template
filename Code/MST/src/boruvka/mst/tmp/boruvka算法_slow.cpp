#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1000005
#define M 5000005
#define ll long long
typedef int value;
int f[N],g[N],w[N],n,m;
struct edge{
	int x,y;value w;
}e[M];
int find(int x){
	if (f[x]==x)return x;
	else return f[x]=find(f[x]);
}
inline void link(int x,int y){f[find(x)]=find(y);}
ll boruvka(int n,int m){
	ll ans=0;
	for (int i=1;i<=n;++i)f[i]=i;
	while (1){
		bool has=0;
		for (int i=1;i<=n;++i)g[i]=i,w[i]=(ll)(1LL<<31)-1;
		for (int i=1;i<=m;++i){
			int x=find(e[i].x),y=find(e[i].y);value ww=e[i].w;
			if (x==y)continue;
			if (ww<w[x])w[x]=ww,g[x]=y;
			if (ww<w[y])w[y]=ww,g[y]=x;
		}
		for (int i=1;i<=n;++i){
			int x=find(i),y=find(g[x]);
			if (x!=y){
				has=1;ans+=w[x];link(x,y);
			}
		}
		if (!has)break;
	}
	return ans;
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	read(n);read(m);
	for (int i=1;i<=m;++i)
		read(e[i].x),read(e[i].y),read(e[i].w);
	ll ans=boruvka(n,m);
	printf("%I64d\n",ans);
	system("pause");for (;;);
	return 0;
}


