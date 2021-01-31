#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define N 10000005
int phi[N],f[N],p[N],sum[N],len;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	for (int i=2;i<N;++i){
		if (!f[i]){
			f[i]=p[++len]=i;
			phi[i]=i-1;
		}
		for (int j=1;j<=len&&p[j]<=f[i]&&i*p[j]<N;++j){
			f[i*p[j]]=p[j];
			if (p[j]==f[i])phi[i*p[j]]=phi[i]*p[j];
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	//for (int i=1;i<N;++i)printf("%d %d\n",i,phi[i]);
	system("pause");for (;;);
	return 0;
}


