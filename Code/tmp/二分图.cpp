#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int maxn=1005;
int n,ans;
int g[maxn][maxn],y[maxn],link[maxn];
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
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	memset(link,0,sizeof(link));
	for (int i=1;i<=n;++i){
		memset(y,0,sizeof(y));
		if (find(i))++ans;
	}
	printf("%d\n",ans);
	system("pause");
	return 0;
}




