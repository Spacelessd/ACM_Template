#include<cstdio>
#include<algorithm>
#define CH getchar()
using namespace std;
typedef int node[100005];
typedef int edge[200005];
typedef int tree[4000005];
int N,q,x,y,z,tot,Len,k,Num,i,s,Ans;
int fa[100005][20];
node a,p,b,in,out,Q,son,f,d,g,c;
edge ed,next,u,root;
tree Tree,L,R;
int cmp(const int i,const int j)
{
	return b[i]<b[j];
}
void read(int &x)
{
	char ch;x=0;
	bool y=0;
	for(ch=CH;ch<'0'||ch>'9';ch=CH)
		if(ch=='-') y=1;
	for(;ch>='0'&&ch<='9';x=x*10+ch-48,ch=CH);
}
void Addedge(int i,int j)
{
	ed[++tot]=j,next[tot]=son[i],son[i]=tot;
}
void dfs()
{
	int l,i,j,k;
	Q[1]=in[1]=f[1]=u[1]=l=Len=1;
	g[1]=-1;
	for(;l;)
	{
		i=Q[l];
		for(j=son[i];j&&f[ed[j]];j=next[j]);
		son[i]=next[j];
		if(!j)
		{
			out[i]=++Len,u[Len]=i+N;
			--l;
		}
		else
		{
			for(k=0;(1<<k)<=l;k++) fa[ed[j]][k]=Q[l+1-(1<<k)];
			d[ed[j]]=d[i]+1,g[ed[j]]=k-1;
			in[ed[j]]=++Len,u[Len]=ed[j];
			f[ed[j]]=1,Q[++l]=ed[j];
		}
	}
}
int Lca(int x,int y)
{
	int j;
	if(d[x]>d[y])
		for(j=g[x];j>=0;j--)
			if(j<=g[x]&&d[fa[x][j]]>=d[y])
				x=fa[x][j];
	if(d[y]>d[x])
		for(j=g[y];j>=0;j--)
			if(j<=g[y]&&d[fa[y][j]]>=d[x])
				y=fa[y][j];
	if(x==y) return x;
	for(j=g[x];j>=0;j--)
		if(fa[x][j]!=fa[y][j])
			x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}
void Build(int t,int l,int r)
{
	int mid=(l+r)/2;
	if(l==r) return;
	L[t]=++Num,R[t]=++Num;
	Build(L[t],l,mid),Build(R[t],mid+1,r);
}
void Modify(int b,int t,int l,int r,int x,int y)
{
	int mid=(l+r)/2;
	if(l==r)
	{
		Tree[b]+=y;
		return;
	}
	if(x<=mid)
	{
		if(!L[b]||L[b]==L[t])
		{
			L[b]=++Num;
			Tree[L[b]]=Tree[L[t]];
		}
		if(!R[b]) R[b]=R[t];
		Modify(L[b],L[t],l,mid,x,y);
	}
	else
	{
		if(!L[b]) L[b]=L[t];
		if(!R[b]||R[b]==R[t])
		{
			R[b]=++Num;
			Tree[R[b]]=Tree[R[t]];
		}
		Modify(R[b],R[t],mid+1,r,x,y);
	}
	Tree[b]=Tree[L[b]]+Tree[R[b]];
}
int Query(int tp,int tz,int tx,int ty,int l,int r,int Last)
{
	int mid=(l+r)/2,tmp;
	if(l==r) return c[l];
	tmp=Last+Tree[L[tx]]+Tree[L[ty]]-Tree[L[tz]]-Tree[L[tp]];
	if(tmp>=k) return Query(L[tp],L[tz],L[tx],L[ty],l,mid,Last);
	else return Query(R[tp],R[tz],R[tx],R[ty],mid+1,r,tmp);
}
int main()
{
	read(N),read(q);
	for(i=1;i<=N;++i) read(b[i]);
	for(i=1;i<N;++i)
	{
		read(x),read(y);
		Addedge(x,y),Addedge(y,x);
	}
	dfs();
	for(i=1;i<=N;++i) p[i]=i;
	sort(p+1,p+N+1,cmp);
	for(i=1;i<=N;++i)
	{
		if(i==1||b[p[i]]!=b[p[i-1]]) ++s;
		a[p[i]]=s,c[s]=b[p[i]];
	}
	root[0]=++Num;
	Build(root[0],1,s);
	for(i=1;i<=Len;++i)
	{
		root[i]=++Num;
		if(u[i]<=N) Modify(root[i],root[i-1],1,s,a[u[i]],1);
		else Modify(root[i],root[i-1],1,s,a[u[i]-N],-1);
	}
	for(;q--;)
	{
		read(x),read(y),read(k);
		z=Lca(x,y);
		Ans=Query(root[in[z]-1],root[in[z]],root[in[x]],root[in[y]],1,s,0);
		printf("%d\n",Ans);
	}
	return 0;
}

