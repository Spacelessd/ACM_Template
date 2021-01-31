#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1005
int a[N][N],d[N];
int prim(int n){
	const int oo=1<<30;int ans=0;
	for (int i=1;i<=n;++i)d[i]=a[1][i];
	d[1]=-oo;
	for (int i1=1;i1<n;++i1){
		int min=oo,id;
		for (int i=1;i<=n;++i)
			if (d[i]!=-oo&&min>d[i])min=d[i],id=i;
		ans+=d[id];d[id]=-oo;
		for (int i=1;i<=n;++i)
			if (a[id][i]<d[i])d[i]=a[id][i];
	}
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;scanf("%d",&n);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)scanf("%d",&a[i][j]);
	int ans=prim(n);
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


