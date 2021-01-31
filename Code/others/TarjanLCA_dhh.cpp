#include<cstdio>
#include<cstdlib>
#include<cstring>
#define CH getchar()
#define N 300005
int g[N],f[N],d[N],fa[N],now[N],s[N],c[N],a[N];
bool vst[N];
struct Edge{
	int son[N],next[N*2],ed[N*2],l;
	void pre(){memset(son,0,sizeof(son)); l=0;}
	void add(int x,int y){
		ed[++l]=y; next[l]=son[x]; son[x]=l;
		ed[++l]=x; next[l]=son[y]; son[y]=l;
	}
}e,q;
int get(int x)
{
	if (g[x]==x) return x;
	return g[x]=get(g[x]);
}
void dfs()
{
	int x=1;
	while (x){
		if (now[x]){
			int p=now[x]; now[x]=e.next[p]; int j=e.ed[p];
			if (d[j]>d[x]) x=j; continue;
		}
		for (int p=q.son[x];p;p=q.next[p]){
			int j=q.ed[p],g;
			if (vst[j]) g=get(j),s[g]--,s[fa[g]]--;
		}
		vst[x]=1; g[x]=g[fa[x]]; x=fa[x];
	}
}
void bfs()
{
	int h=0,t=1; f[1]=1;
	memset(d,255,sizeof(d)); d[1]=0;
	while (h<t){
		int i=f[++h];
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.ed[p]; if (d[j]!=-1) continue;
			d[j]=d[i]+1; f[++t]=j; fa[j]=i;
		}
	}
}
void work(int n)
{
	for (int k=n;k;k--){
		int i=f[k]; c[i]+=s[i]; c[fa[i]]+=c[i];
	}
}
void read(int &x)
{
	x=0; char ch;
	for (ch=CH;ch<'0' || ch>'9';ch=CH);
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,x,y; read(n); q.pre(); e.pre();
	for (int i=1;i<=n;i++) read(a[i]);
	for (int i=1;i<n;i++) q.add(a[i],a[i+1]);
	for (int i=1;i<n;i++) read(x),read(y),e.add(x,y);
	for (int i=1;i<=n;i++) g[i]=i;
	bfs(); memcpy(now,e.son,sizeof(now)); dfs();
	for (int i=1;i<n;i++) s[a[i]]++,s[fa[a[i+1]]]++;
	work(n); for (int i=1;i<=n;i++) printf("%d\n",c[i]);
	return 0;
}


