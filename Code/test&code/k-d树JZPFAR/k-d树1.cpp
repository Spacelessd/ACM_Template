#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define N 100010
#define K 25
#define ll long long
struct P{int x,y,p;}a[N];
struct T{int x,y,xmin,xmax,ymin,ymax,p;}f[N*4];
bool cmpx(const P &a,const P &b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool cmpy(const P &a,const P &b){return a.y<b.y||a.y==b.y&&a.x<b.x;}
void build(int t,int l,int r,bool tp){
	sort(a+l,a+r+1,tp?cmpy:cmpx);
	int mid=(l+r)>>1;
	f[t].p=a[mid].p,
	f[t].xmin=f[t].xmax=f[t].x=a[mid].x,
	f[t].ymin=f[t].ymax=f[t].y=a[mid].y;
	if(l==r)return;
	if (l<=mid-1){
		int L=t*2+1;build(L,l,mid-1,!tp);
		f[t].xmin=min(f[t].xmin,f[L].xmin);
		f[t].xmax=max(f[t].xmax,f[L].xmax);
	}
	if (mid+1<=r){
		int R=t*2+2;build(R,mid+1,r,!tp);
		f[t].ymin=min(f[t].ymin,f[R].ymin),
		f[t].ymax=max(f[t].ymax,f[R].ymax);
	}
}
inline ll dist(ll x,ll y){return x*x+y*y;}
int n,px,py,w;
pair<ll,int> A[K+1];
void upd(const pair<ll,int> a){
	if(a.first<A[w].first||A[w].first==a.first&&A[w].second<a.second)return;
	for(int i=1;i<=w;++i)
		if(A[i].first<a.first||A[i].first==a.first&&A[i].second>a.second)
			{for(int j=w;j>i;--j)A[j]=A[j-1];A[i]=a;return;}
}
void ask(int t,int l,int r,bool tp){
	if (l>r)return;
	upd(make_pair(dist(f[t].x-px,f[t].y-py),f[t].p));
	if(l==r||dist(max(f[t].xmax-px,px-f[t].xmin),max(f[t].ymax-py,py-f[t].ymin))<A[w].first)return;
	int mid=(l+r)>>1;
	(tp?(py<f[t].y||py==f[t].y&&px<f[t].x):(px<f[t].x||px==f[t].x&&py<f[t].y))?
		(ask(t*2+2,mid+1,r,!tp),ask(t*2+1,l,mid-1,!tp)):
		(ask(t*2+1,l,mid-1,!tp),ask(t*2+2,mid+1,r,!tp));
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d%d",&a[i].x,&a[i].y),a[i].p=i;
	build(1,1,n,0);
	int T;scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&px,&py,&w);
		for(int i=1;i<=w;++i)A[i]=make_pair(-1,n);
		ask(1,1,n,0),printf("%d\n",A[w].second);
	}
	//system("pause");
	return 0;
}





