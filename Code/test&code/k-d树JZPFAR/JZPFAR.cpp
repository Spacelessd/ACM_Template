#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 100010
struct P{int x,y,p;}a[N];
struct T{int x,y,xmi,xma,ymi,yma,p;}f[N*4];
bool cmpx(const P&a,const P&b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool cmpy(const P&a,const P&b){return a.y<b.y||a.y==b.y&&a.x<b.x;}
void blt(int p,int l,int r,bool tp)
{
	sort(a+l,a+r,tp?cmpy:cmpx);
	int mid=(l+r)/2;
	f[p].p=a[mid].p,
	f[p].xmi=f[p].xma=f[p].x=a[mid].x,f[p].ymi=f[p].yma=f[p].y=a[mid].y;
	if(l==r-1)return;
	blt(p*2+1,l,mid,!tp),blt(p*2+2,mid,r,!tp),
	f[p].xmi=min(f[p*2+1].xmi,f[p*2+2].xmi),
	f[p].xma=max(f[p*2+1].xma,f[p*2+2].xma),
	f[p].ymi=min(f[p*2+1].ymi,f[p*2+2].ymi),
	f[p].yma=max(f[p*2+1].yma,f[p*2+2].yma);
}
typedef pair<ll,int> PLI;
#define mp make_pair
#define fi first
#define se second
int n,px,py,w,v[N],T;PLI A[22];
ll dis(int x,int y){return (ll)x*x+(ll)y*y;}
void upd(const PLI a)
{
	if(a.fi<A[w-1].fi)return;
	for(int i=0;i<w;i++)
		if(A[i].fi<a.fi||A[i].fi==a.fi&&A[i].se>a.se)
			{for(int j=w-1;j>i;j--)A[j]=A[j-1];A[i]=a;return;}
}
void ask(int p,int l,int r,bool tp)
{
	if(v[f[p].p]!=T)v[f[p].p]=T,upd(mp(dis(f[p].x-px,f[p].y-py),f[p].p));
	if(l==r-1||dis(max(f[p].xma-px,px-f[p].xmi),max(f[p].yma-py,py-f[p].ymi))<A[w-1].fi)return;
	int mid=(l+r)/2;
	(tp?(py<f[p].y||py==f[p].y&&px<f[p].x):(px<f[p].x||px==f[p].x&&py<f[p].y))?
		(ask(p*2+2,mid,r,!tp),ask(p*2+1,l,mid,!tp)):
		(ask(p*2+1,l,mid,!tp),ask(p*2+2,mid,r,!tp));
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d%d",&a[i].x,&a[i].y),a[i].p=i;
	blt(0,0,n,0);
	int _;scanf("%d",&_);
	while(_--)
	{
		T++,scanf("%d%d%d",&px,&py,&w);
		for(int i=0;i<w;i++)A[i]=mp(-1,n);
		ask(0,0,n,0),printf("%d\n",A[w-1].se+1);
	}
	system("pause");
	return 0;
}


