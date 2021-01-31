#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define ll long long
ll prime[55],p1,P,K,A;
void decompose(ll x){
	p1=0;
	for (ll i=2;i*i<=x;++i)if (x%i==0){
		prime[++p1]=i;
		while (x%i==0)x/=i;
	}
	if (x>1)prime[++p1]=x;
}
ll extend_gcd(ll a,ll b,ll &x,ll &y){
	if (!b){x=1;y=0;return a;}
	ll tmp=extend_gcd(b,a%b,y,x);y-=x*(a/b);
	return tmp;
}
ll pow(ll x,ll y){
	ll tmp=1;
	while (y){
		if (y%2)tmp=tmp*x%P;
		x=(x*x)%P;
		y/=2;
	}
	return tmp;
}
ll inv(ll x,ll p){return pow(x,p-2);}
bool isroot(ll x,ll p){
	for (int i=1;i<=p1;++i)
		if (pow(x,(p-1)/prime[i])==1)return 0;
	return 1;
}
ll FindRoot(ll p){
	decompose(p-1);
	for (ll i=2;i<p;++i)if (isroot(i,p))return i;
}
ll discrete_Log(ll a,ll p,ll g){
	map<ll,ll> M;ll Sqrt=(ll)sqrt(p)+1;
	ll v=inv(pow(g,Sqrt),p);
	ll e=1;M[1]=0;
	for (ll i=1;i<Sqrt;++i){
		e=e*g%P;if (!M.count(e))M[e]=i;
	}
	for (ll i=0;i<Sqrt;++i){
		if (M.count(a))return i*Sqrt+M[a];
		a=a*v%p;
	}
	return -1;
}
vector<ll> Solve(ll a,ll b,ll m){
	ll x,y,d=extend_gcd(a,m,x,y);
	vector<ll> tmp;
	if (b%d)return tmp;
	ll t=b/d;x%=m;if (x<0)x+=m;x=x*t%m;
	for (int i=0;i<d;++i){
		tmp.push_back(x);
		x+=m/d;x%=m;
	}
	return tmp;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%I64d%I64d%I64d",&P,&K,&A);  //x^K==A(mod P)
	if (A==0){
		printf("1\n");printf("0\n");
		return 0;
	}
	ll g=FindRoot(P);
	ll sum=discrete_Log(A,P,g);
	vector<ll> log=Solve(K,sum,P-1);
	vector<ll> ans;
	for (vector<ll>::iterator zzy=log.begin();zzy!=log.end();++zzy)
		ans.push_back(pow(g,*zzy));
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for (vector<ll>::iterator zzy=ans.begin();zzy!=ans.end();++zzy)
		printf("%I64d\n",*zzy);
	system("pause");for (;;);
	return 0;
}


