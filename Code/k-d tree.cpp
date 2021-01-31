#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define N 50005
#define K 5
#define M 10
struct P{int x[K],id;}a[N];
struct T{int x[K],min[K],max[K],id;}f[N*4];
int n,k,cmp_k,p[K],s;
pair<int,int> A[M+1];
inline bool cmp(const P &a,const P &b){return a.x[cmp_k]<b.x[cmp_k];}
inline void update(int x,int son){
	for (int i=0;i<k;++i)
		f[x].min[i]=min(f[x].min[i],f[son].min[i]),
		f[x].max[i]=max(f[x].max[i],f[son].max[i]);
}
void build(int t,int l,int r,int d){
	cmp_k=d;nth_element(a+l,a+mid+1,a+r+1,cmp);
	int mid=(l+r)>>1; f[t].id=a[mid].id;
	for (int i=0;i<k;++i)f[t].min[i]=f[t].max[i]=f[t].x[i]=a[mid].x[i];
	if (l==r)return;
	if (l<=mid-1)build(t*2,l,mid-1,d+1==k?0:d+1),update(t,t*2);
	if (mid+1<=r)build(t*2+1,mid+1,r,d+1==k?0:d+1),update(t,t*2+1);
}
inline void upd(const pair<int,int> &x){
	if (A[s].first<x.first||A[s].first==x.first&&A[s].second<x.second)return;
	for (int i=1;i<=s;++i)
		if (x.first<A[i].first||x.first==A[i].first&&x.second<A[i].second)
			{for (int j=s;j>i;--j)A[j]=A[j-1];A[i]=x;return;}
}
inline int sqr(int x){return x*x;}
inline int dist(int *x1,int *x2){
	int res=0;
	for (int i=0;i<k;++i)res+=sqr(x1[i]-x2[i]);
	return res;
}
inline int dist(int *x1,int *x2,int *x3){
	int res=0;
	for (int i=0;i<k;++i)
		if (x1[i]<x2[i])res+=sqr(x2[i]-x1[i]);
		else if (x1[i]>x3[i])res+=sqr(x1[i]-x3[i]);
	return res;
}
void ask(int t,int l,int r,int d){
	if (l>r)return;
	upd(make_pair(dist(f[t].x,p),t));
	if (l==r||dist(p,f[t].min,f[t].max)>A[s].first)return;
	int mid=(l+r)>>1;
	if (p[d]<f[t].x[d])ask(t*2,l,mid-1,d+1==k?0:d+1),ask(t*2+1,mid+1,r,d+1==k?0:d+1);
	else ask(t*2+1,mid+1,r,d+1==k?0:d+1),ask(t*2,l,mid-1,d+1==k?0:d+1);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	while (scanf("%d%d",&n,&k)!=EOF){
		for (int i=1;i<=n;++i)
			for (int j=0;j<k;++j)scanf("%d",&a[i].x[j]);
		for (int i=1;i<=n;++i)a[i].id=i;
		build(1,1,n,0);
		int q;scanf("%d",&q);
		while (q--){
			for (int i=0;i<k;++i)scanf("%d",&p[i]);
			scanf("%d",&s);
			for(int i=1;i<=s;++i)A[i]=make_pair(1<<30,0);
			ask(1,1,n,0);
			printf("the closest %d points are:\n",s);
			for (int i=1;i<=s;++i)
				for (int j=0;j<k;++j)printf("%d%c",f[A[i].second].x[j],j==k-1?'\n':' ');
		}
	}
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


