#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1005
#define ll long long
#define L 60
ll a[N];int g[L],n;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%I64d",&a[i]);
	sort(a+1,a+1+n);reverse(a+1,a+1+n);
	for (int i=0;i<L;++i)g[i]=0;
	ll ans=0;
	for (int i=1;i<=n;++i){
		ll old=a[i];
		for (int j=L-1;j>=0;--j)
			if (g[j]&&a[i]&1LL<<j)a[i]^=a[g[j]];
		if (!a[i]){ans+=old;continue;}
		for (int j=L-1;j>=0;--j)
			if (a[i]&1LL<<j){g[j]=i;break;}
	}
	printf("%I64d\n",ans);
	system("pause");for (;;);
	return 0;
}


