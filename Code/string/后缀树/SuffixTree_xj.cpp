#include <cstdio>
#include <cstring>
#include <algorithm>
#define int64 long long
#define Sort sort
#include <ctime>

using namespace std;

const int Maxn=2510000;
const int inf=99999999;

struct Tree
{
	int s,d,trans;
	int son[28];
	
	Tree () {}
	Tree (int _s,int _d,int _trans)
	{
		s=_s;d=_d;trans=_trans;
		memset(son,0,sizeof(son));
	}
	
	int& operator [](int index)
	{
		return son[index];
	}
};

Tree tree[Maxn];
int a[Maxn];
int n,m,N,tot;
char st[Maxn];
int gr[Maxn],next[Maxn];
int fa[Maxn],q[Maxn];
int64 sub[Maxn];
bool can[Maxn];
bool leaf[Maxn];

void Init()
{
	N=0;
	for (int i=0;i<n;++i)
	{
		scanf("%s",st);
		int len=strlen(st);
		for (int j=0;j<len;++j)
		{
			a[++N]=st[j]-'a';
			gr[N]=i;
		}
		a[++N]=26;gr[N]=-1;
	}
	a[N]=27;
	next[N]=N;
	for (int i=N-1;i>=0;--i)
		if (a[i]>25) next[i]=i;
		else next[i]=next[i+1];
}

class Suffix_Tree
{
	public:
	
	int node,fir,last;
	
	int New(int s,int d,int trans)
	{
		++tot;
		tree[tot]=Tree(s,d,trans);
		return tot;
	}
	
	void Find(int &node,int fir,int en)
	{
		for (;;)
		{
			int u=tree[node][a[fir+tree[node].d]];
			if (u && tree[u].d+fir-1<=en)
				node=u;
			else break;
		}
	}
	
	void Add_New_Letter(int en,int x)
	{
		for (;fir<=en;++fir)
		{
			Find(node,fir,en-1);
			
			int v=en-fir-tree[node].d;
			if (!v)
			{
				if (last) tree[last].trans=node;
				last=0;
				if (tree[node][x]) break;
				tree[node][x]=New(en,inf,0);
				fa[tot]=node;
			}
			else
			{
				int u=tree[node][a[fir+tree[node].d]];
				if (a[tree[u].s+v]==x) break;
				New(tree[u].s,tree[node].d+v,0);
				tree[u].s+=v;
				tree[node][a[tree[tot].s]]=tot;fa[tot]=node;
				tree[tot][a[tree[u].s]]=u;fa[u]=tot;
				if (last) tree[last].trans=tot;
				last=tot;
				New(en,inf,0);
				tree[tot-1][x]=tot;fa[tot]=tot-1;
			}
			node=tree[node].trans;
		}
	}
	
	void Build()
	{
		tot=-1;
		New(0,0,0);
		node=last=0;fir=1;
		for (int i=1;i<=N;++i)
			Add_New_Letter(i,a[i]);
	}
};

int pos[Maxn],Next[Maxn];
int Tot,res;
int list[1000007];
int64 date[Maxn],sum[62];

void Add(int x,int y)
{
	Next[y]=pos[x];pos[x]=y;
}

void Hash(int64 x)
{
	int X=x % 1000007;
	for (int k=list[X];k;k=next[k])
		if (date[k]==x) return;
	date[++tot]=x;next[tot]=list[X];
	list[X]=tot;
}

void Work()
{
	sum[0]=1;
	for (int i=1;i<=60;++i) sum[i]=sum[i-1]*2;
	for (int i=0;i<=tot;++i) pos[i]=0;
	for (int i=1;i<=tot;++i) Add(fa[i],i);
	int l1=1,l2=1;
	q[1]=0;can[0]=true;
	for (;l1<=l2;++l1)
	{
		int now=q[l1];
		sub[now]=0;
		leaf[now]=true;
		if (next[tree[now].s]<=tree[now].s+tree[now].d-tree[fa[now]].d-1) 
			can[now]=false;
		for (int k=pos[now];k;k=Next[k])
		{
			int nex=k;
			q[++l2]=nex;
			fa[nex]=now;
			leaf[now]=false;
			can[nex]=can[now];
		}
	}
	tot=0;
	for (int i=0;i<1000007;++i) list[i]=0;
	for (int i=l2;i>=1;--i)
	{
		int now=q[i]; 
		int Fa=fa[now];
		if (leaf[now])
			if (gr[tree[now].s-tree[Fa].d]!=-1)
				sub[now]=sum[gr[tree[now].s-tree[Fa].d]];

		if (!now) continue;
		if (can[now] || (!can[now] && can[fa[now]] && a[tree[now].s]<26)) 
			Hash(sub[now]);
		sub[Fa]|=sub[now];
		sub[Fa]|=0;
	}

	printf("%d\n",tot);
}

int main()
{
	//freopen("keyword.in","r",stdin);
	//freopen("keyword.out","w",stdout);
	
	scanf("%d",&n);
		
	Init();
	
	(new Suffix_Tree)->Build();
	
	Work();
	
	//printf("%d\n",clock());
	
	return 0;
}


