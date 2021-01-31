#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
#define ll long long
ll gcd(ll x,ll y){
	if (y==0)return x;
	return gcd(y,x%y);
}
ll rho(ll n){
	ll i,k,x1,x2,y,d;
	srand(time(0));
	i=1;x1=(((ll)rand()<<(ll)40)+((ll)rand()<<(ll)32)
		+((ll)rand()<<(ll)16)+(ll)rand())%(n-1);
	y=x1;k=2;
	while (1){
		++i;
		if (i>100)return n;
		x2=(x1*x1-1)%n;
		d=gcd(n+y-x2,n);
		if (d!=1&&d!=n){
			cout<<d<<"\n";
			n/=d;
			if (n==1)return n;
		}
		if (i==k){
			y=x2;k*=2;
		}
		x1=x2;
	}
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin>>n;
	while (n!=1){
		n=rho(n);
		//printf("n=%d\n",n);
	}
	system("pause");
	return 0;
}


