#include <cstdio>
#include <cstring>
#include <algorithm>
#define Sort sort

using namespace std;

const int Maxn=101000;
const int gap=200;
const int Dep=20;

struct Tnode
{
	int l,r;
};

struct Pnode
{
	int x,y,z1,z2,id;
};

Tnode dfn[Maxn];
Pnode p[Maxn];
int a[Maxn],b[Maxn];
int pos[Maxn];
int date[Maxn],next[Maxn];
int ans[Maxn];
bool visit[Maxn];
int cnt[Maxn];
int fa[Dep][Maxn],dep[Maxn];
int n,m,nn,res,tot,num,Lca;

bool Cmp(Pnode A,Pnode B)
{
	return A.z1<B.z1 || (A.z1==B.z1 && A.z2<B.z2);
}

void Add(int x,int y)
{
	++tot;
	date[tot]=y;next[tot]=pos[x];pos[x]=tot;
}

void Init()
{
	scanf("%d%d",&n,&m);
	
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	Sort(b+1,b+n+1);
	nn=unique(b+1,b+n+1)-(b+1);
	for (int i=1;i<=n;++i)
		a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
		
	memset(pos,0,sizeof(pos));
	tot=0;
	for (int i=1;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Add(x,y);Add(y,x);
	}
}

void Dfs(int x)
{
	visit[x]=true;
	dfn[x].l=++tot;
	for (int k=pos[x];k;k=next[k])
		if (!visit[date[k]])
		{
			dep[date[k]]=dep[x]+1;fa[0][date[k]]=x;
			Dfs(date[k]);
		}
	dfn[x].r=++tot;
}

int Get_Lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=num;i>=0;--i)
		if (dep[fa[i][x]]>=dep[y]) x=fa[i][x];
	if (x==y) return x;
	for (int i=num;i>=0;--i)
		if (fa[i][x]!=fa[i][y]) 
		{
			x=fa[i][x];y=fa[i][y];
		}
	return fa[0][x];
}

void Prepare()
{
	memset(visit,false,sizeof(visit));
	dep[0]=-1;dep[1]=0;tot=-1;
	Dfs(1);
	
	for (int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if (dfn[x].l>dfn[y].l) swap(x,y);
		p[i].x=x;p[i].y=y;
		p[i].z1=dfn[x].l/gap;p[i].z2=dfn[y].l;
		p[i].id=i;
	}
	Sort(p+1,p+m+1,Cmp);
	
	num=0;
	for (int s=1;s*2<=n;s*=2,++num);
	for (int k=1;k<=num;++k)
		for (int i=1;i<=n;++i)
			fa[k][i]=fa[k-1][fa[k-1][i]];
}

bool con(int x,int y)
{
	return dfn[x].l<=dfn[y].l && dfn[x].r>=dfn[y].r;
}

void Insert(int u)
{
	if (!visit[u])
	{
		visit[u]=true;
		res+=((++cnt[a[u]])==1);
	}
}

void Delete(int u)
{
	if (visit[u])
	{
		visit[u]=false;
		res-=((--cnt[a[u]])==0);
	}
}

void Modify(int u,int x,int y)
{
	if (con(Lca,u) && (con(u,x) || con(u,y))) Insert(u);
	else Delete(u);
}

void Go(int s,int t,int x,int y)
{
	int lca=Get_Lca(s,t);
	for (;s!=lca;s=fa[0][s]) Modify(s,x,y);
	for (;t!=lca;t=fa[0][t]) Modify(t,x,y);
	Modify(lca,x,y);
}

void Work()
{
	memset(visit,false,sizeof(visit));
	memset(cnt,0,sizeof(cnt));
	res=1;visit[1]=true;cnt[a[1]]=1;
	int L=1,R=1;
	for (int i=1;i<=m;++i)
	{
		int x=p[i].x,y=p[i].y;
		Lca=Get_Lca(x,y);
		Go(L,x,x,y);Go(R,y,x,y);
		L=x;R=y;ans[p[i].id]=res;
	}
	
	for (int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
}

int main()
{
	//freopen("x.in","r",stdin);
	//freopen("x.out","w",stdout);
	
	Init();
	
	Prepare();
	
	Work();
	
	return 0;
}


