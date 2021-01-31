#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 3005
int g[N][N],y[N],link[N],n,ans;
bool find(int v){
	for (int i=1;i<=n;++i)
		if (g[v][i]&&!y[i]){
			y[i]=1;
			if (!link[i]||find(link[i])){
				link[i]=v;return 1;
			}
		}
	return 0;
}
int main()
{
	int m,n1,n2,xx,yy;
	freopen("1.in","r",stdin);
	freopen("7.out","w",stdout);
	scanf("%d%d%d",&n1,&n2,&m);
	n=n1>n2?n1:n2;
	for (int i=1;i<=m;++i)
		scanf("%d%d",&xx,&yy),g[xx][yy]=1;
	memset(link,0,sizeof(link));
	for (int i=1;i<=n;++i){
		memset(y,0,sizeof(y));
		if (find(i))++ans;
	}
	printf("%d\n",ans);
	//system("pause");for (;;);
	return 0;
}


