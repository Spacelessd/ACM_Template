#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 500005
int f[N],son[N],next[N*2],ed[N*2],deep[N],fa[N],sum[N],heavy[N],top[N];
bool b[N];
int n,i,x,y,z,l=0,len;
inline void read(int &x){
	char ch; x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}
void dfs(int x,int dep,int y){
	deep[x]=dep; fa[x]=y; sum[x]=1; int m=0,q=0; f[++len]=x;
	for (int p=son[x];p;p=next[p]){
		int j=ed[p]; if (j==fa[x]) continue; dfs(j,dep+1,x);
		sum[x]+=sum[j]; if (sum[j]>m) m=sum[j],q=j;
	}
	heavy[x]=q;
}
int lca(int x,int y){
	while (top[x]!=top[y]){
		if (deep[top[x]]<deep[top[y]]){int t=x;x=y;y=t;}
		if (top[x]==x) x=fa[x];
		else x=top[x];
	}
	if (deep[x]<deep[y]) return x;
	else return y;
}
int main()
{
	int t1=clock();
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<n;++i){
		read(x); read(y);
		++l; ed[l]=y; next[l]=son[x]; son[x]=l;
		++l; ed[l]=x; next[l]=son[y]; son[y]=l;
	}
	dfs(1,0,-1);
	for (int k=1;k<=n;k++){
		int i=f[k]; if (b[i]) continue;	
		for (int j=i;j;j=heavy[j]) top[j]=i,b[j]=1;
	}
	int Q;scanf("%d",&Q);
	for (int i=1;i<=Q;++i)
		scanf("%d%d",&x,&y),printf("%d\n",lca(x,y));
	printf("%d\n",clock()-t1);
	return 0;
}


