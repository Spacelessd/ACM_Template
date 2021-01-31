#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
const int maxn=20010;
const int maxm=1000010;
int h[maxn],sumh[maxn],e[maxn],son[maxn],cur[maxn],inq[maxn],a[maxn],q[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
int n,m,ll,S,T,hh,tt,l,r;
inline int min(int a,int b) {return a<b?a:b;}
void build()
{
	int x,y,i;l=1,r=1;
	memset(h,7,sizeof(int)*(n+5));
	q[1]=T;h[T]=0;
	while (l<=r){
		x=q[l++];
		for (i=son[x];i!=-1;i=next[i]){
			y=link[i];
			if (cap[opp[i]]&&h[x]+1<h[y]){
				h[y]=h[x]+1;q[++r]=y;
			}
		}
	}
	h[S]=n;
	memset(sumh,0,sizeof(int)*(n+5));
	for (i=1;i<=n;i++)if (h[i]<n*2)sumh[h[i]]++;
}
void addedge(int x,int y,int z)
{
	link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
	link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
void push(int x,int y){
	int tmp=min(e[x],cap[y]),ed=link[y];
	cap[y]-=tmp;cap[opp[y]]+=tmp;
	e[x]-=tmp;e[ed]+=tmp;
	if (!inq[ed])tt=tt<n?tt+1:1,a[tt]=ed,inq[ed]=1;
}
void preflow(){
	hh=0;tt=0;inq[S]=inq[T]=1;
	e[S]=oo;for (int i=son[S];i!=-1;i=next[i])push(S,i);e[S]-=oo;
}
void relabel(int x){
	int i,minh=oo,pl;
	for (i=son[x];i!=-1;i=next[i])
		if (cap[i]&&h[link[i]]<minh)minh=h[link[i]],pl=i;
	cur[x]=pl;
	sumh[h[x]]--;
	if (!sumh[h[x]]&&h[x]<=n-1){
		for (i=1;i<=n;++i)
			if (i!=S&&h[i]>h[x]&&h[i]<n+1){
				sumh[h[i]]--;
				h[i]=n+1;
			}
		h[x]=n+1;return;
	}
	h[x]=minh+1;
	sumh[h[x]]++;
}
void init()
{
	int i,x,y,z;
	scanf("%d%d",&m,&n);
	memset(son,-1,sizeof(int)*(n+5));
	memset(h,0,sizeof(int)*(n+5));
	memset(sumh,0,sizeof(int)*(n+5));
	memset(e,0,sizeof(int)*(n+5));
	S=1;T=n;ll=0;h[S]=n;
	for (i=1;i<=m;++i)scanf("%d%d%d",&x,&y,&z),addedge(x,y,z);
	memcpy(cur,son,sizeof(int)*(n+5));
}
int main()
{
	//freopen("ditch.in","r",stdin);
	//freopen("ditch.out","w",stdout);
	init();build();
	preflow();
	int x,p,j;
	while (hh!=tt){
		hh=hh<n?hh+1:1;x=a[hh];inq[x]=0;
		if (h[x]>=n)continue;
		for (p=cur[x];p!=-1;p=next[p]){
			j=link[p];
			if (h[x]==h[j]+1&&cap[p]){
				push(x,p);cur[x]=p;
				if (!e[x])break;
			}
		}
		if (e[x]){
			relabel(x);
			tt=tt<n?tt+1:1,a[tt]=x,inq[x]=1;
		}
	}
	printf("%d\n",e[T]);
	//system("pause");
}



