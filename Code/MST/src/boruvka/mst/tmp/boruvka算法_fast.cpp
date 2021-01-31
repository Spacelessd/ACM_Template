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
int id[N];
#define maxn 1005
int a[maxn][maxn],d[maxn];
inline void update(int x,int &y){if (x<y)y=x;}
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
		int s=0;
		for (int i=1;i<=n;++i)if (f[i]==i)++s;
		printf("s=%d\n",s);
		if (s<maxn){
			ll ans1=0;int id1=0;
			for (int i=1;i<=n;++i)if (f[i]==i)id[f[i]]=++id1;
			for (int i=1;i<=n;++i)id[i]=id[f[i]];//printf("%d\n",id[i]);
			n=s;
			for (int i=1;i<=n;++i)
				for (int j=1;j<=n;++j)a[i][j]=(1LL<<31)-1;
			//printf("wei\n");
			for (int i=1;i<=m;++i)
				update(e[i].w,a[id[e[i].x]][id[e[i].y]]);
			for (int i=1;i<=n;++i)
				for (int j=1;j<=n;++j)update(a[i][j],a[j][i]);
			for (int i=1;i<=n;++i)a[i][i]=(1LL<<31)-1;
			const int oo=(1LL<<31)-1;
			for (int i=1;i<=n;++i)d[i]=a[1][i];
			d[1]=-oo;
			for (int i1=1;i1<n;++i1){
				int min=oo,id;
				for (int i=1;i<=n;++i)
					if (d[i]!=-oo&&min>d[i])min=d[i],id=i;
				ans1+=d[id];d[id]=-oo;
				for (int i=1;i<=n;++i)
					if (a[id][i]<d[i])d[i]=a[id][i];
			}
			ans+=ans1;
			break;
		}
		if (!has)break;
	}
	printf("%d\n",zzy);
	return ans;
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
char str[70000005],*p=str;
inline void read1(int &x){
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
	//fread(str,1,70000000,stdin);
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


