#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 205
#define ll long long
int a[N][N],n,P;
int det(int a[N][N],int n){
	if (P==1)return 0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)a[i][j]%=P;
	int ans=1;
	for (int i=1;i<=n;++i){
		for (int j=i+1;j<=n;++j)while (a[j][i]){
			int t=a[i][i]/a[j][i];
			for (int k=i;k<=n;++k)
				a[i][k]=((ll)a[j][k]*-t+a[i][k])%P;
			for (int k=i;k<=n;++k)
				{int tmp=a[i][k];a[i][k]=a[j][k];a[j][k]=tmp;}
			ans=-ans;
		}
		if (a[i][i]==0)return 0;
		ans=(ll)ans*a[i][i]%P;
	}
	return ((ll)ans+P)%P;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&P);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)scanf("%d",&a[i][j]);
	printf("%d\n",det(a,n));
	system("pause");for (;;);
	return 0;
}


