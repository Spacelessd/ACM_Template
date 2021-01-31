#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1005
#define P 105
int a[N][N*2],inv[P],n,p,first=1;
int power(int x,int y){
	int tmp=1;
	while (y){
		if (y&1)tmp=tmp*x%p;
		y>>=1;x=x*x%p;
	}
	return tmp;
}
bool gauss(){
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)a[i][n+j]=0;
	for (int i=1;i<=n;++i)a[i][n+i]=1;
	for (int i=1;i<=n;++i){
		if (!a[i][i])for (int j=i+1;j<=n;++j)if (a[j][i])
			for (int k=i;k<=n+n;++k)swap(a[i][k],a[j][k]);
		if (!a[i][i]){printf("singular\n");return 0;}
		int x=a[i][i];
		for (int k=i;k<=n+n;++k)a[i][k]=a[i][k]*inv[x]%p;
		for (int j=i+1;j<=n;++j){
			x=a[j][i];
			for (int k=i;k<=n+n;++k){
				a[j][k]=(a[j][k]-a[i][k]*x)%p;
				if (a[j][k]<0)a[j][k]+=p;
			}
		}
	}
	for (int i=n;i;--i)
		for (int j=i-1;j;--j){
			int x=a[j][i];
			for (int k=i;k<=n+n;++k){
				a[j][k]=(a[j][k]-a[i][k]*x)%p;
				if (a[j][k]<0)a[j][k]+=p;
			}
		}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)printf("%d%c",a[i][n+j],j==n?'\n':' ');
	return 1;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//p is prime
	while (scanf("%d%d",&n,&p),n||p){
		if (first)first=0;else printf("\n");
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)scanf("%d",&a[i][j]);
		for (int i=0;i<p;++i)inv[i]=power(i,p-2);
		gauss();
	}
	system("pause");for (;;);
	return 0;
}


