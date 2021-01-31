#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
#include<algorithm>
using namespace std;
int dhh;
#define N 100010
#define K 25
#define ll long long
struct P{int x,y,p;}a[N];
struct T{int x,y,xmin,xmax,ymin,ymax,p;}f[N*4];
bool cmpx(const P &a,const P &b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool cmpy(const P &a,const P &b){return a.y<b.y||a.y==b.y&&a.x<b.x;}
inline void update(int x,int son){
	f[x].xmin=min(f[x].xmin,f[son].xmin);
	f[x].xmax=max(f[x].xmax,f[son].xmax);
	f[x].ymin=min(f[x].ymin,f[son].ymin),
	f[x].ymax=max(f[x].ymax,f[son].ymax);
}
void build(int t,int l,int r,bool tp){
	sort(a+l,a+r+1,tp?cmpy:cmpx);
	int mid=(l+r)>>1;
	f[t].p=a[mid].p,
	f[t].xmin=f[t].xmax=f[t].x=a[mid].x,
	f[t].ymin=f[t].ymax=f[t].y=a[mid].y;
	if(l==r)return;
	if (l<=mid-1){
		int L=t*2+1;build(L,l,mid-1,!tp);update(t,L);
	}
	if (mid+1<=r){
		int R=t*2+2;build(R,mid+1,r,!tp);update(t,R);
	}
}
inline ll dist(ll x,ll y){return x*x+y*y;}
int n,px,py,w;
//bool cmp(pair<ll,int> a,pair<ll,int> b){
	//return a.first<b.first||a.second
priority_queue<pair<ll,int> > Q;
void upd(const pair<ll,int> a){
	if(Q.top().first>a.first||Q.top().first==a.first&&Q.top().second<a.second)return;
	Q.pop();Q.push(a);
}
void ask(int t,int l,int r,bool tp){
	if (l>r)return;
	upd(make_pair(dist(f[t].x-px,f[t].y-py),f[t].p));
	if(l==r||dist(max(f[t].xmax-px,px-f[t].xmin),max(f[t].ymax-py,py-f[t].ymin))<Q.top().first)return;
	int mid=(l+r)>>1;
	(tp?(py<f[t].y||py==f[t].y&&px<f[t].x):(px<f[t].x||px==f[t].x&&py<f[t].y))?
		(ask(t*2+2,mid+1,r,!tp),ask(t*2+1,l,mid-1,!tp)):
		(ask(t*2+1,l,mid-1,!tp),ask(t*2+2,mid+1,r,!tp));
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d%d",&a[i].x,&a[i].y),a[i].p=i;
	build(1,1,n,0);//return 0;
	int T;scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&px,&py,&w);
		for(int i=1;i<=w;++i)Q.push(make_pair(-1,n));
		ask(1,1,n,0);printf("%d\n",Q.top().second);
		for (int i=1;i<=w;++i)Q.pop();
	}
	//printf("%d\n",dhh);
	//system("pause");for (;;);
	return 0;
}





