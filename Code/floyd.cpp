#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1005
int f[N][N];
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int S,T,n,m;scanf("%d%d",&n,&m);S=1;T=n;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)f[i][j]=1<<29;
	for (int i=1;i<=m;++i){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		if (z<f[x][y])f[x][y]=z;
		if (z<f[y][x])f[y][x]=z;
	}
	for (int i=1;i<=n;++i)f[i][i]=0;
	for (int k=1;k<=n;++k)
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
				if (f[i][k]+f[k][j]<f[i][j])f[i][j]=f[i][k]+f[k][j];
	printf("%d\n",f[S][T]);
	system("pause");for (;;);
	return 0;
}


