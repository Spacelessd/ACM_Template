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
ll a[N],c[N];
bool can(ll c[],int n,ll x){
	const int L=60;
	static int a[L][N],p[L];
	memset(a,0,sizeof(a));
	memset(p,0,sizeof(p));
	for (int i=0;i<L;++i)
		for (int j=1;j<=n;++j)a[i][j]=(c[j]&1LL<<i)?1:0;
	for (int i=0;i<L;++i)a[i][n+1]=(x&1LL<<i)?1:0;
	for (int i=0;i<L;++i){
		for (int j=1;j<=n;++j)if (a[i][j]){p[i]=j;break;}
		if (!p[i])continue;
		for (int j=0;j<L;++j)if (j!=i&&a[j][p[i]]){
			for (int k=1;k<=n+1;++k)a[j][k]^=a[i][k];
		}
	}
	for (int i=0;i<L;++i){
		bool bo=0;
		for (int j=1;j<=n;++j)if (a[i][j])bo=1;
		if (!bo&&a[i][n+1])return 0;
	}
	return 1;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	ll ans=0;int n;cin>>n;
	for (int i=1;i<=n;++i)cin>>a[i],ans+=a[i];
	sort(a+1,a+1+n);reverse(a+1,a+1+n);
	int c1=0;
	for (int i=1;i<=n;++i)
		if (!can(c,c1,a[i])){c[++c1]=a[i];ans-=a[i];}
	cout<<ans<<endl;
	system("pause");for (;;);
	return 0;
}


