#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define ll long long
ll exp(ll x,ll y,ll z){  //x^y mod z
	ll ans=1,tmp=x;
	while (y){
		if (y&1LL)ans=ans*tmp%z;
		tmp=tmp*tmp%z;y>>=1LL;
	}
	return ans;
}
bool Judge(ll x){
	#define Sp 4
	static const ll a[Sp]={2,3,5,7};
	if (x==1)return 0;
	//for (ll i=2;i<=(ll)sqrt(x);++i)
	//	if (!x%i)return 0;
	for (int i=0;i<Sp;++i)
		if (a[i]<x&&exp(a[i],x-1,x)!=1)return 0;
	return 1;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;ll x;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%I64d",&x);
		if (Judge(x))printf("YES\n");
			else printf("NO\n");
	}
	system("pause");for (;;);
	return 0;
}


