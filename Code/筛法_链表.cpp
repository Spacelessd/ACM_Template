#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 30000005
int f[N],l[N],r[N],prime[N],n,p1,sum;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	int t1=clock();
	for (int i=1;i<=n;++i)f[i]=0,l[i]=i-1,r[i]=i+1;
	int sq=(int)sqrt(n);
	for (int i=2;i<=sq;i=r[i]){
		int j=n/i,k;
		while (f[j])j=l[j];
		for (;j>=i;j=l[j]){
			k=i*j;f[k]=i;++sum;
			r[l[k]]=r[k];l[r[k]]=l[k];
		}
	}
	for (int i=2;i<=n;++i)if (!f[i]){
		prime[++p1]=i;
		//printf("%d\n",i);
	}
	printf("sum=%d\n",sum);
	printf("prime=%d\n",p1);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


