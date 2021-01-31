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
	int zzy=0;
	while (1){
		bool has=0;
		for (int i=1;i<=n;++i)g[i]=i,w[i]=(ll)(1LL<<31)-1;
		for (int i=1;i<=m;++i){
			int x=f[e[i].x],y=f[e[i].y];
			if (x==y)continue;
			value ww=e[i].w;
			if (ww<w[x])w[x]=ww,g[x]=y;
			if (ww<w[y])w[y]=ww,g[y]=x;
		}
		for (int i=1;i<=n;++i){
			int x=find(i),y=find(g[x]);
			if (x!=y){
				has=1;ans+=w[x];link(x,y);
			}
		}
		for (int i=1;i<=n;++i)find(i);
		++zzy;zzy+=m;
		if (!has)break;
	}
	printf("%d\n",zzy);
	return ans;
}
inline void read1(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
char str[70000005],*p=str;
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
int zzy[N];
int main()
{
	freopen("road9.in","r",stdin);
	//freopen("1.out","w",stdout);
	fread(str,1,70000000,stdin);
	int t1=clock();
	read(n);read(m);
	for (int i=1;i<=n;++i)read(zzy[i]);
	for (int i=1;i<=m;++i)
		read(e[i].x),read(e[i].y),read(e[i].w),e[i].w-=zzy[e[i].x]+zzy[e[i].y];
	printf("time=%d\n",clock()-t1);
	ll ans=boruvka(n,m);
	printf("%I64d\n",ans);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


