#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 15
#define eps 1e-10
double g[N][N];
double det(double c[N][N],int n){
	static double a[N][N];double ans=1;int sign=0;
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)a[i][j]=c[i][j];
	for (int i=0;i<n;++i){
		if (fabs(a[i][i])<eps){
			int j;for (j=i+1;j<n;++j)if (fabs(a[j][i])>eps)break;
			if (j==n)return 0;
			for (int k=i;k<n;++k){double tmp=a[i][k];a[i][k]=a[j][k];a[j][k]=tmp;}
			sign^=1;
		}
		ans*=a[i][i];
		for (int k=i+1;k<n;++k)a[i][k]/=a[i][i];
		for (int j=i+1;j<n;++j)
			for (int k=i+1;k<n;++k)a[j][k]-=a[j][i]*a[i][k];
	}
	return sign?-ans:ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T,x,y,n,m;scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)g[i][j]=0;
		for (int i=1;i<=m;++i)scanf("%d%d",&x,&y),g[x-1][y-1]=g[y-1][x-1]=-1;
		for (int i=0;i<n;++i){
			int d=0;
			for (int j=0;j<n;++j)d-=g[i][j];
			g[i][i]=d;
		}
		printf("%.0lf\n",det(g,n-1));
	}
	system("pause");for (;;);
	return 0;
}


