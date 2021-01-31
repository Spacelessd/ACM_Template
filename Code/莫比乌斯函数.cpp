#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define N 100005
int mu[N],f[N],p[N],sum[N],len;
//求1<=i<=x,1<=j<=y,gcd(i,j)==d的对数
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	mu[1]=1;
	for (int i=2;i<N;++i){
		if (!f[i]){
			f[i]=p[++len]=i;
			mu[i]=-1;
		}
		for (int j=1;j<=len&&p[j]<=f[i]&&i*p[j]<N;++j){
			f[i*p[j]]=p[j];
			if (p[j]==f[i])mu[i*p[j]]=0;
			else mu[i*p[j]]=-mu[i];
		}
	}
	for (int i=1;i<N;++i)sum[i]=sum[i-1]+mu[i];
	//for (int i=1;i<=n;++i)printf("%d %d %d\n",i,mu[i],sum[i]);
	int T;scanf("%d",&T);
	while (T--){
		int x,y,d;scanf("%d%d%d",&x,&y,&d);
		x/=d;y/=d;if (x>y){int tmp=x;x=y;y=tmp;}
		int ans=0;
		for (int l=1;l<=x;++l){
			int r=min(x/(x/l),y/(y/l));
			ans+=(sum[r]-sum[l-1])*(x/l)*(y/l);
			l=r;
		}
		printf("%d\n",ans);
	}
	system("pause");for (;;);
	return 0;
}


