#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define CH getchar()
#define N 100005
struct Query{int z,L,R,mid,k,cnt;} q[N];
struct note{int x,id;} dis[N];
int n,Q,tot=0,len=0;
int fa[N],f[N],deep[N],heavy[N],sum[N],high[N];
int a[N],c[N],stack[N],l[N],r[N],v[N],w[N];
int son[N],next[N*3],ed[N*3],data[N*3];
bool vst[N],b[N];
bool cmp(const note i,const note j){return i.x<j.x;}
void add(int x,int v){for (;x<=tot;x+=x&-x) c[x]+=v;}
int get(int x){int ans=0; for (;x;x-=x&-x) ans+=c[x]; return ans;}
void read(int &x)
{
	x=0; char ch; bool y=0;
	for (ch=CH;ch<'0' || ch>'9';ch=CH) if (ch=='-') y=1;
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH);
	if (y) x=-x;
}
void dfs()
{
	int top=1,now=0; stack[1]=1;
	memset(vst,0,sizeof(vst));
	while (top){
		int x=stack[top];
		if (vst[x]) {r[x]=++now,a[now]=-w[x]; top--; continue;}
		vst[x]=1; l[x]=++now; a[now]=w[x];
		for (int p=son[x];p;p=next[p]){
			int j=ed[p]; if (vst[j]) continue;
			stack[++top]=j;
			}
		}
//	for (int i=1;i<=n;i++) printf("%d %d\n",l[i],r[i]); for(;;);
}
void bfs()
{
	int h=0,t=1; f[1]=1; fa[1]=0;
	memset(deep,0,sizeof(deep)); deep[1]=1;
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
	memset(b,0,sizeof(b));
	for (int k=1;k<=t;k++){
		int i=f[k]; if (b[i]) continue;
		for (int j=i;j;j=heavy[j]) high[j]=i,b[j]=1;
		}
//	for (int i=1;i<=n;i++)
//		printf("%d %d %d %d %d\n",i,fa[i],deep[i],heavy[i],high[i]);
}
int lca(int x,int y)
{
	while (high[x]!=high[y])
//		printf("%d %d\n",x,y);
		if (deep[high[x]]>deep[high[y]])
			if (high[x]==x) x=fa[x]; else x=high[x];
		else if (high[y]==y) y=fa[y]; else y=high[y];
	return deep[x]<deep[y]?x:y;
}
void addedge(int x,int y,int z)
{
//	printf("addedge %d %d %d\n",x,y,z);
	ed[++len]=y; data[len]=z; next[len]=son[x]; son[x]=len;
}
void work()
{
	for (int i=1;i<=n*2;i++){
		if (a[i]>0) add(a[i],1); else add(-a[i],-1);
		for (int p=son[i];p;p=next[p])
			q[ed[p]].cnt+=data[p]*get(q[ed[p]].mid);
		}
}
int main()
{
	read(n),read(Q);
	for (int i=1;i<=n;i++) read(dis[i].x),dis[i].id=i;
	std::sort(dis+1,dis+n+1,cmp);
	for (int i=1;i<=n;i++){
		if (i==1 || dis[i].x!=dis[i-1].x) tot++,v[tot]=dis[i].x;
		w[dis[i].id]=tot;
		}
//	for (int i=1;i<=n;i++) printf("%d ",w[i]); printf("\n");
//	for (int i=1;i<=tot;i++) printf("%d ",v[i]); printf("\n");
	for (int i=1;i<n;i++){
		int x,y; read(x),read(y);
		ed[++len]=y; next[len]=son[x]; son[x]=len;
		ed[++len]=x; next[len]=son[y]; son[y]=len;
		}
	bfs(); dfs(); memset(q,0,sizeof(q));
	memset(son,0,sizeof(son)); len=0;
	for (int i=1;i<=Q;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&q[i].k);
		q[i].z=lca(x,y); q[i].L=1; q[i].R=tot;
//		printf("!%d %d %d\n",x,y,q[i].z);
		addedge(l[x],i,1); addedge(l[y],i,1);
		addedge(l[q[i].z],i,-2);
		}
//	for (int i=1;i<=n+n;i++) printf("%d ",a[i]); printf("\n");
//	for (int i=1;i<=n;i++) printf("%d %d  ",l[i],r[i]); printf("\n");
	while (q[1].L<q[1].R){
		for (int i=1;i<=Q;i++)
			q[i].mid=(q[i].L+q[i].R)/2,q[i].cnt=0;
		work();
		for (int i=1;i<=Q;i++){
			if (w[q[i].z]<=q[i].mid) q[i].cnt++;
			if (q[i].cnt>=q[i].k) q[i].R=q[i].mid;
			else q[i].L=q[i].mid+1;
			}
		}
	for (int i=1;i<=Q;i++) printf("%d\n",v[q[i].R]);
	return 0;
}
