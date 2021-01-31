#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1000005
int a[N],b[N],c[N],h,t;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,ans=0;scanf("%d",&n);h=1;t=0;
	for (int i=1;i<=n;++i){
		scanf("%d%d",&a[i],&b[i]);
		while (h<=t&&b[i]<a[c[h]])++h;
		if (h<=t)ans=max(ans,i-c[h]+1);
		int x=i;while (h<=t&&a[i]>a[c[t]])x=c[t--];
		a[x]=a[i];c[++t]=x;
	}
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


