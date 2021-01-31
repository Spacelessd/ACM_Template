#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define CH getchar()
#define oo (1<<30)
#define N 100005
//#define read(x) scanf("%d",&x)
int n,size,deep[N],fa[N],top[N],num[N],w[N],q[N],m[N],c[N],X[N],Y[N];
inline int max(int a,int b){return a>b?a:b;}
inline void swap(int &x,int &y){int t=x;x=y;y=t;}
inline void read(int &x)
{
	x=0; char c; bool y=0;
	for (c=CH;c<'0' | c>'9';c=CH) if (c=='-') y=1;
	for (;c>='0' && c<='9';x=x*10+c-48,c=CH);
	if (y) x=-x;
}
struct Edge{
	int ed[N*2],next[N*2],data[N*2],son[N],l;
	inline void clear(){l=0; memset(son,0,sizeof(son));}
	inline void addedge(int x,int y,int z){
		ed[++l]=y; data[l]=z; next[l]=son[x]; son[x]=l;
		}
}a,e;
void build(int x,int y,int D)
{
	deep[x]=D; fa[x]=y;
	if (!top[x]) top[x]=x,num[x]=1; int now=top[x];
	for (int p=a.son[x];p;p=a.next[p]){
		int j=a.ed[p]; if (j==y) continue;
		if (num[now]<size) e.addedge(x,j,0),num[now]++,top[j]=now;
		c[j]=a.data[p]; build(j,x,D+1);
		}
}
void dfs(int x,int M)
{
	m[x]=M=max(M,c[x]);
	for (int p=e.son[x];p;p=e.next[p]) dfs(e.ed[p],M);
}
void Qmax(int x,int y)
{
	int M=-oo;
	while (x!=y){
		if (deep[x]<deep[y]) swap(x,y);
		if (top[x]==top[y]) M=max(M,c[x]),x=fa[x];
		else{
			if (deep[top[x]]<deep[top[y]]) swap(x,y);
			M=max(M,m[x]),x=fa[top[x]];		
			}
		}
	printf("%d\n",M);
}
void Change(int x,int y)
{
	c[x]=y; if (top[x]==x) dfs(x,-oo);
	else dfs(x,m[fa[x]]);
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int test,x,y,z; read(test);
	while (test--){
		memset(top,0,sizeof(top));
		
		read(n); size=(int)sqrt(1.0*n)+1; a.clear(); e.clear(); 
		for (int i=1;i<n;i++){
			read(x); read(y); read(z); X[i]=x,Y[i]=y;
			a.addedge(x,y,z); a.addedge(y,x,z);
			}
		
		build(1,0,0);
		for (int i=1;i<=n;i++) if (top[i]==i) dfs(i,-oo);
		
		for (int i=1;i<n;i++) if (deep[X[i]]>deep[Y[i]]) w[i]=X[i]; else w[i]=Y[i];
		
		for(;;){
			//char str[15]; scanf("%s",str); char ch=str[0];
			char ch=getchar();
			if (ch=='D') break; read(x); read(y);
			if (ch=='Q') Qmax(x,y); else Change(w[x],y);
			}
		}
	return 0;
}
