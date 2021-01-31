#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=200005;
struct Edge{
	int link[N*2],next[N*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e,_e;
int n,ans,w[N],anc[N],visit[N],f[N],father[N];
char zzy[105];
int tot;
char Xwj[10000005],*xwj=Xwj;
inline void read(int &x){
	int bo=0;x=0;
	while(*xwj<'0'||*xwj>'9')if (*xwj++=='-')bo=1;
	while(*xwj>='0'&&*xwj<='9')x=x*10+*xwj++-'0';
	if (bo)x=-x;
}
inline void read(char *s){
	int len=0;
	while(*xwj<'A'||*xwj>'z')xwj++;
	while(*xwj>='A'&&*xwj<='z')s[len++]=*xwj++;
	s[len]=0;
}
int stack[N],s1;
void build(int l,int r,int &x){
	if (l==r){--tot;x=stack[l];return;}
	int mid=(l+r)>>1;
	int L=++tot;build(l,mid,L);
	int R=++tot;build(mid+1,r,R);
	e.addedge(x,L);
	e.addedge(x,R);
}
void _dfs(int x,int fa){
	visit[x]=1;
	for (int p=_e.son[x];p;p=_e.next[p])if (!visit[_e.link[p]])
		_dfs(_e.link[p],x);
	s1=0;
	for (int p=_e.son[x];p;p=_e.next[p]){
		int y=_e.link[p];
		if (y!=fa)stack[++s1]=y;
	}
	if (s1==1)e.addedge(x,stack[1]);
	int _tot=tot;
	if (s1>1)build(1,s1,x);
	for (int i=_tot+1;i<=tot;++i)anc[i]=x;
}
void dfs(int x,int fa){
	father[x]=fa;f[x]=w[x]>0?w[x]:0;visit[x]=1;
	for (int p=e.son[x];p;p=e.next[p])if (!visit[e.link[p]]){
		dfs(e.link[p],x);
		if (f[e.link[p]]+w[x]>f[x])f[x]=f[e.link[p]]+w[x];
	}
}
struct node{
	int l,r,sum;
	node(int _l,int _r,int _sum):l(_l),r(_r),sum(_sum){}
	node(){}
};
node a[N*4];
void change(int t,int l,int r,int x,int y){
	if (l==r){
		a[t].l=a[t].r=(y>0?y:0);
		a[t].sum=y;
		return;
	}
	int mid=(l+r)>>1;
	if (x<=mid)change(t*2,l,mid,x,y);
		else change(t*2+1,mid+1,r,x,y);
	a[t].sum=a[t*2].sum+a[t*2+1].sum;
	a[t].l=max(a[t*2].l,a[t*2].sum+a[t*2+1].l);
	a[t].r=max(a[t*2+1].r,a[t*2+1].sum+a[t*2].r);
}
node QueryL(int t,int l,int r,int x){
	if (l==r){return node(0,w[l],a[t].sum);}
	int mid=(l+r)>>1;node tmp,result;
	if (x<=mid)return QueryL(t*2,l,mid,x);
	else {
		tmp=QueryL(t*2+1,mid+1,r,x);
		result.sum=a[t*2].sum+tmp.sum;
		result.r=max(tmp.r,tmp.sum+a[t*2].r);
		return result;
	}
}
node QueryR(int t,int l,int r,int x){
	if (l==r){return node(w[l],0,a[t].sum);}
	int mid=(l+r)>>1;node tmp,result;
	if (x<=mid){
		tmp=QueryR(t*2,l,mid,x);
		result.sum=a[t*2+1].sum+tmp.sum;
		result.l=max(tmp.l,tmp.sum+a[t*2+1].l);
		return result;
	}
	else return QueryR(t*2+1,mid+1,r,x);
}
void print(int t,int l,int r){
	printf("%d %d %d %d %d\n",l,r,a[t].l,a[t].r,a[t].sum);
	if (l==r)return;
	int mid=(l+r)>>1;
	print(t*2,l,mid);
	print(t*2+1,mid+1,r);
}
void workB(){
	int x,y;
	read(n);
	for (int i=1;i<=n;++i)read(w[i]),change(1,1,n,i,w[i]);
	for (int i=1;i<n;++i)read(x),read(y);
	//print(1,1,n);
	while (1){
		read(zzy);
		if (zzy[0]=='D')break;
		if (zzy[0]=='C'){
			read(x);read(y);
			w[x]=y;
			change(1,1,n,x,y);
		}
		if (zzy[0]=='Q'){
			read(x);
			ans=w[x];
			ans=max(ans,QueryL(1,1,n,x).r);
			ans=max(ans,QueryR(1,1,n,x).l);
			printf("%d\n",ans);
		}
	}
	//system("pause");for (;;);
	exit(0);
}
void Uncompress()
{
	int N, M, L, now, A, B, Q, tmp, i;
	char type = getc(stdin);
	scanf("%d%d%d", &N, &M, &L);
	scanf("%d%d%d%d", &now, &A, &B, &Q);
	sprintf(xwj, "%c %d\n", type, N);
	while (*xwj)++xwj;
	for (i = 1; i <= N; i ++)
	{
		now = (now * A + B) % Q, tmp = now % 10000;
		now = (now * A + B) % Q;
		if (now * 2 < Q) tmp *= -1;
		if (i < N)
			sprintf(xwj, "%d ", tmp);
		else
			sprintf(xwj, "%d\n", tmp);
		while (*xwj)++xwj;
	}
	for (i = 1; i < N; i ++)
	{
		now = (now * A + B) % Q;
		tmp = (i < L) ? i : L;
		sprintf(xwj, "%d %d\n", i - now % tmp, i + 1);
		while (*xwj)++xwj;
	}
	for (i = 1; i < M; i ++)
	{
		now = (now * A + B) % Q;
		if (now * 3 < Q)
		{
			now = (now * A + B) % Q;
			sprintf(xwj, "Query %d\n", now % N + 1);
			while (*xwj)++xwj;
		}
		else
		{
			now = (now * A + B) % Q, tmp = now % 10000;
			now = (now * A + B) % Q;
			if (now * 2 < Q) tmp *= -1;
			now = (now * A + B) % Q;
			sprintf(xwj, "Change %d %d\n", now % N + 1, tmp);
			while (*xwj)++xwj;
		}
	}
	sprintf(xwj, "Done\n");
	while (*xwj)++xwj;
	xwj=Xwj;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	Uncompress();
	char kind;kind=*xwj++;
	if (kind=='B')workB();
	int x,y;read(n);
	for (int i=1;i<=n;++i)read(w[i]);
	for (int i=1;i<n;++i)
		read(x),read(y),_e.addedge(x,y),_e.addedge(y,x);
	for (int i=1;i<=n;++i)visit[i]=0;
	tot=n;
	_dfs(1,0);
	for (int i=1;i<=n;++i)visit[i]=0;
	dfs(1,0);
	while (1){
		read(zzy);
		if (zzy[0]=='D')break;
		if (zzy[0]=='C'){
			read(x);read(y);
			w[x]=y;
			for (;x!=0;x=father[x]){
				f[x]=w[x]>0?w[x]:0;
				for (int p=e.son[x];p;p=e.next[p])if (e.link[p]!=father[x]){
					if (f[e.link[p]]+w[x]>f[x])f[x]=f[e.link[p]]+w[x];
				}
			}
		}
		if (zzy[0]=='Q'){
			int x;read(x);
			int ans=w[x],now=0,pre=0,bo=0;
			for (;x!=0;pre=x,x=father[x]){
				if (x>n){
					if (!bo)now+=w[anc[x]],bo=1;
				}
				else {
					if (!bo)now+=w[x];
					else bo=0;
				}
				for (int p=e.son[x];p;p=e.next[p]){
					int y=e.link[p];
					if (y!=father[x]&&y!=pre){
						if (now+f[y]>ans)ans=now+f[y];
					}
				}
				if (now>ans)ans=now;
			}
			printf("%d\n",ans);
		}
	}
	system("pause");for (;;);
	return 0;
}


