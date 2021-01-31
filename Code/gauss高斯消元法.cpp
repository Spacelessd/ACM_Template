#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define M 205
#define eps (1e-5)
double A[M][M],ans[M];
int p[M];
void gauss(double a[][M],int n,int m){
	int i,j,k,empty=0;double x,y;bool bo;
	memset(p,0,sizeof(p));
	for (i=1;i<=m;++i){
		for (j=1;j<=n;++j)
			if (fabs(a[i][j])>eps){p[i]=j;break;}
		if (!p[i])continue;
		x=a[i][p[i]];
		for (k=1;k<=m;++k)
			if (k!=i&&fabs(a[k][p[i]])>eps){
				y=a[k][p[i]];
				for (j=1;j<=n+1;++j)a[k][j]=a[k][j]*x-a[i][j]*y;
			}
	}
	for (i=1;i<=m;++i){
		bo=0;
		for (j=1;j<=n;++j)if (fabs(a[i][j])>eps)bo=1;
		if (bo==0&&fabs(a[i][n+1])<=eps)++empty;
		if (bo==0&&fabs(a[i][n+1])>eps){
			printf("IMPOSSIBLE\n");
			//return;
		}
	}
	if (m-empty<n){
		printf("NOT UNIQUE\n");
		//return;
	}
	for (i=1;i<=m;++i)if (p[i])ans[p[i]]=a[i][n+1];
	for (i=1;i<=n;++i)printf("%.5f\n",ans[i]);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i){
		for (int j=1;j<=n;++j)scanf("%lf",&A[i][j]);
		scanf("%lf",&A[i][n+1]);
	}
	gauss(A,n,m);
	system("pause");for (;;);
	return 0;
}


