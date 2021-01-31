#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 105
#define N maxn*maxn
int a[maxn][maxn],l[N],r[N],d[N],u[N],c[N],s[maxn],head[maxn],n,m,ans;
inline int getid(int x,int y){return x*n+y;}
void remove(int x){
	for (int i=d[x];i!=x;i=d[i])
		l[r[i]]=l[i],r[l[i]]=r[i];
}
void resume(int x){
	for (int i=u[x];i!=x;i=u[i])
		l[r[i]]=i,r[l[i]]=i;
}
bool hash[maxn];
int h(){
	for (int i=1;i<=m;++i)hash[i]=0;
	int ans=0;
	for (int i=r[0];i;i=r[i])if (!hash[i]){
		++ans;hash[i]=1;
		for (int j=d[i];j!=i;j=d[j])
			for (int k=r[j];k!=j;k=r[k])hash[c[k]]=1;
	}
	return ans;
}
void dfs(int dep){
	if (dep+h()>=ans)return;
	if(r[0]==0){
		if (dep<ans)ans=dep;
		return;
	}
	int x=0,min=1<<30;
	for (int i=r[0];i;i=r[i])
		if (s[i]<min)min=s[i],x=i;
	for (int i=d[x];i!=x;i=d[i]){
		remove(i);
		for (int j=r[i];j!=i;j=r[j])remove(j);
		dfs(dep+1);
		for (int j=l[i];j!=i;j=l[j])resume(j);
		resume(i);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	memset(a,0,sizeof(a));
	scanf("%d%d",&m,&n);
	for (int i=1;i<=n;++i){
		int x,y;scanf("%d",&x);
		for (int j=1;j<=x;++j){
			scanf("%d",&y);a[i][y]=1;
		}
	}
	for (int i=0;i<=m;++i)head[i]=i;
	for (int i=1;i<=m;++i)r[head[i]]=head[i+1];
	for (int i=1;i<=m;++i)l[head[i]]=head[i-1];
	r[head[0]]=head[1];l[head[1]]=head[0];
	l[head[0]]=head[m];r[head[m]]=head[0];
	for (int i=1;i<=n;++i){
		int pre=0,first=0;
		for (int j=1;j<=m;++j)if (a[i][j]){
			if (pre)l[getid(i,j)]=getid(i,pre),r[getid(i,pre)]=getid(i,j);
			pre=j;if (!first)first=j;
		}
		if (first){
			l[getid(i,first)]=getid(i,pre);r[getid(i,pre)]=getid(i,first);
		}
	}
	for (int j=1;j<=m;++j){
		int pre=0,first=0;
		for (int i=1;i<=n;++i)if (a[i][j]){
			if (pre)u[getid(i,j)]=getid(pre,j),d[getid(pre,j)]=getid(i,j);
			pre=i;if (!first)first=i;
		}
		if (pre){
			u[getid(first,j)]=head[j];d[head[j]]=getid(first,j);
			u[head[j]]=getid(pre,j);d[getid(pre,j)]=head[j];
		}
	}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)if (a[i][j])c[getid(i,j)]=head[j];
	memset(s,0,sizeof(s));
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)if (a[i][j])++s[j];
	ans=1<<30;dfs(0);
	if (ans==1<<30)printf("-1\n");
	else printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


