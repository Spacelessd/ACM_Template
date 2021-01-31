#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#define N 100005
int n,Q,tot=0,len=0,flag=1;
int fa[N],f[N],deep[N],heavy[N],sum[N],high[N];
int a[N*2],c[N],stack[N],l[N],r[N],v[N],w[N];
int son[N*2],next[N*3],ed[N*3],data[N*3];
bool vst[N],b[N];
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
}
int lca(int x,int y)
{
	while (high[x]!=high[y])
		if (deep[high[x]]>deep[high[y]])
			if (high[x]==x) x=fa[x]; else x=high[x];
		else if (high[y]==y) y=fa[y]; else y=high[y];
	return deep[x]<deep[y]?x:y;
}
int main()
{
	freopen("COT.in","w",stdout);
	srand(time(0));
	int n=100000,m=100000,l=0; printf("%d %d\n",n,m);
	for (int i=1;i<=n;i++) printf("%d ",rand()+1); printf("\n");
	for (int i=2;i<=n;i++){
		int x=rand()%(i-1)+1,y=i;
		printf("%d %d\n",x,y);
		ed[++l]=y; next[l]=son[x]; son[x]=l;
		ed[++l]=x; next[l]=son[y]; son[y]=l;		
		}
	bfs();
	for (int i=1;i<=m;i++){
		int x=rand()%n+1,y=rand()%n+1,k,z=lca(x,y);
		k=rand()%(deep[x]+deep[y]-2*deep[z]+1)+1;
		printf("%d %d %d\n",x,y,k);
		}
	return 0;
}
