#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define ll long long
ll exp(ll x,ll y,ll z){  //x^y mod z
	ll ans=1,tmp=x;
	while (y){
		if (y&1)ans=ans*tmp%z;
		tmp=tmp*tmp%z;y>>=1;
	}
	return ans;
}
bool witness(ll x,ll n){
	ll tmp=n-1;
	while (!(tmp&1))tmp>>=1;
	ll x0,x1=exp(x,tmp,n);
	while (tmp!=n-1){
		x0=x1;x1=x0*x0%n;
		if (x1==1&&x0!=1&&x0!=n-1)return 1;
		tmp<<=1;
	}
	if (x1!=1)return 1;
		else return 0;
}
bool Judge(ll x){
	#define Sp 4
	if (x==1)return 0;
	for (int i=0;i<Sp;++i){
		ll tmp=((rand()<<16)+rand())%(x-1)+1;
		if (witness(tmp,x))return 0;
	}
	return 1;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	int a,b,T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&a,&b);
		for (int i=a;i<=b;++i){
			if (Judge(i))printf("%d\n",i);
		}
		if (T)printf("\n");
	}
	system("pause");for (;;);
	return 0;
}


