#include<cstdio>
#include<algorithm>
#include<ctime>
#define N 100005
int n,Q,m=0,tot=0,len=0;
int fa[N],f[N],deep[N],heavy[N],sum[N],top[N],v[N],w[N],root[N];
int son[N],next[N*2],ed[N*2];int W;
struct note{int x,id;} dis[N];
	int size[N*25],L[N*25],R[N*25];
	void build(int &t,int l,int r){
		if (!t) t=++tot; size[t]=0; int mid=(l+r)>>1;
		if (l<r) build(L[t],l,mid),build(R[t],mid+1,r);
		}
	void modify(int t,int &t1,int l,int r,int x){
		t1=++tot; int mid=(l+r)>>1;
		if (l==r){L[t1]=R[t1]=0; size[t1]=size[t]+1; return;}
		if (x<=mid) modify(L[t],L[t1],l,mid,x),R[t1]=R[t];
		else modify(R[t],R[t1],mid+1,r,x),L[t1]=L[t];
		size[t1]=size[L[t1]]+size[R[t1]];
		}
	int query(int x,int y,int z,int z1,int l,int r,int k){
		if (l==r) return l;
		int mid=(l+r)>>1,S=size[L[x]]+size[L[y]]-size[L[z]]-size[L[z1]];
		if (size[L[z]]!=size[L[z1]]+(W>=l&&W<=mid?1:0))
		printf("wawawa%d %d\n",size[L[z]],size[L[z1]]+(W>=l&&W<=mid?1:0));
		if (S>=k) return query(L[x],L[y],L[z],L[z1],l,mid,k);
		else return query(R[x],R[y],R[z],R[z1],mid+1,r,k-S);
		}
bool cmp(const note i,const note j){return i.x<j.x;}
inline void bfs()
{
	int h=0,t=1; f[1]=1; fa[1]=0;
	for (int i=1;i<=n;i++) deep[i]=0; deep[1]=1;
	while (h<t){
		int i=f[++h];
		for (int p=son[i];p;p=next[p]){
			int j=ed[p]; if (deep[j]) continue;
			deep[j]=deep[i]+1; fa[j]=i; f[++t]=j;
			}
		}
	for (int k=t;k;k--){
		int i=f[k],Max=0; sum[i]=1;
		for (int p=son[i];p;p=next[p]){
			int j=ed[p]; if (deep[j]<deep[i]) continue;
			sum[i]+=sum[j]; if (sum[j]>Max) Max=sum[j],heavy[i]=j;
			}
		}
	for (int k=1;k<=t;k++){
		int i=f[k]; if (top[i]) continue;
		for (int j=i;j;j=heavy[j]) top[j]=i;
		}
	build(root[0],1,m);
	for (int k=1;k<=t;k++) modify(root[fa[f[k]]],root[f[k]],1,m,w[f[k]]);
}
inline int lca(int x,int y)
{
	while (top[x]!=top[y])
		if (deep[top[x]]>deep[top[y]])
			if (top[x]==x) x=fa[x]; else x=top[x];
		else if (top[y]==y) y=fa[y]; else y=top[y];
	return deep[x]<deep[y]?x:y;
}
char str[10000005],*p=str;
inline void read(int &x){
	x=0;
	while(*p<'0'||*p>'9')p++;
	while(*p>='0'&&*p<='9')x=x*10+*p++-48;
}
int main()
{
	double t1=clock();
	freopen("COT.in","r",stdin);
	freopen("func_.out","w",stdout);
	fread(p,1,10000000,stdin);
	read(n),read(Q); m=0;
	for (int i=1;i<=n;i++) read(dis[i].x),dis[i].id=i;
	std::sort(dis+1,dis+n+1,cmp);
	for (int i=1;i<=n;i++){
		if (i==1 || dis[i].x!=dis[i-1].x) m++,v[m]=dis[i].x;
		w[dis[i].id]=m;
		}
	for (int i=1;i<n;i++){
		int x,y; read(x),read(y);
		ed[++len]=y; next[len]=son[x]; son[x]=len;
		ed[++len]=x; next[len]=son[y]; son[y]=len;
		}
	bfs();
	while (Q--){
		int x,y,z,z1,k;		
		read(x); read(y); read(k); z=lca(x,y); z1=fa[z]; W=w[z];
		printf("",v[query(root[x],root[y],root[z],root[z1],1,m,k)]);
		}
	printf("%lf\n",clock()-t1);
	return 0;
}


