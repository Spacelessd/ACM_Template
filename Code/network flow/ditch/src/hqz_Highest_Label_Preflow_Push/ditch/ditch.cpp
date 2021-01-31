/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
const int maxn=20010;
const int maxm=1000010;
int h[maxn],sumh[maxn*2],e[maxn],son[maxn],cur[maxn],
PRE[maxn],NEXT[maxn],L[maxn*2];
int *Pre=PRE+1,*Next=NEXT+1;
int link[maxm],next[maxm],cap[maxm],opp[maxm];
int q[maxn];
int n,m,ll,S,T,newh,level;
inline int min(int a,int b) {return a<b?a:b;}
void addedge(int x,int y,int z)
{
	link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
	link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
inline void ins(int x){
	int y=h[x];
	Next[x]=L[y];Pre[L[y]]=x;
	Pre[x]=-1;L[y]=x;
}
inline void del(int x){
	Pre[Next[x]]=Pre[x];Next[Pre[x]]=Next[x];
	if (Pre[x]==-1)L[h[x]]=Next[x];
}
void build(){
	int x,y,i,l=1,r=1;
	for (i=1;i<=n;i++)h[i]=n*2;
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
	for (i=1;i<=n;++i)++sumh[h[i]];
}
void push(int x,int y){
	int tmp=min(e[x],cap[y]),ed=link[y];
	if (tmp){
		if (!e[ed])ins(ed);
		cap[y]-=tmp;cap[opp[y]]+=tmp;
		e[x]-=tmp;e[ed]+=tmp;
	}
}
void preflow(){
	e[S]=oo;for (int i=son[S];i!=-1;i=next[i])push(S,i);e[S]-=oo;
}
void relabel(int x){
	int i,minh=oo,pl,hh=h[x];
	for (i=son[x];i!=-1;i=next[i])
		if (cap[i]&&h[link[i]]<minh)minh=h[link[i]],pl=i;
	cur[x]=pl;sumh[hh]--;
	del(x);h[x]=++minh;
	sumh[minh]++;ins(x);
	if (!sumh[hh]&&hh<=n-1)
		for (i=1;i<=n;i++)
			if (i!=S&&h[i]>hh&&h[i]<n+1){
				del(i);sumh[h[i]]--;
				h[i]=n+1;ins(i);
			}
	if (h[x]<=n&&h[x]>level)newh=h[x];
}
void discharge(int x){
	while (e[x]){
		for (int p=cur[x];p!=-1;p=next[p])
			if (cap[p]&&h[x]==h[link[p]]+1){
				push(x,p);
				if (!e[x])break;
			}
		if (e[x])relabel(x);
	}
}
void init(){
	int i,x,y,z;
	scanf("%d%d",&m,&n);
	memset(son,-1,sizeof(int)*(n+5));
	memset(e,0,sizeof(int)*(n+5));
	S=1;T=n;ll=0;h[S]=n;
	for (i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),addedge(x,y,z);
}
void HLPP(){
	memcpy(cur,son,sizeof(int)*(n+5));
	build();preflow();
	int i,j;level=n;newh=0;
	memset(L,-1,sizeof(int)*(n*2+5));
	for (i=1;i<=n;i++)if (i!=S&&e[i]) ins(i);
	while (level){
		i=L[level];
		while (i!=-1){
			discharge(i);
			if (newh){level=newh+1;newh=0;break;}
			if (h[i]>n)i=L[level];
				else {del(i);i=Next[i];}
		}
		--level;
	}
}
int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	init();
	HLPP();
	printf("%d\n",e[T]);
	//system("pause");
	//for(;;);
	return 0;
}


