#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define P_max 100005
int n,K,P;ll fac[P_max],ans;
struct Int{
	ll x,y;
	Int(ll _x,ll _y):x(_x),y(_y){}
};
inline int power(ll x,int y,int P){
	ll tmp=1;
	while (y){
		if (y&1)tmp=tmp*x%P;
		x=x*x%P;y>>=1;
	}
	return tmp;
}
Int getfac(int n,int x,int y,int P){
	int nn=n/x;
	if (!nn)return Int(fac[n],0);
	Int ans=getfac(nn,x,y,P);
	ans.x=ans.x*power(fac[P],n/P,P)%P;ans.y+=nn;
	ans.x=ans.x*fac[n%P]%P;
	return ans;
}
ll Combination(int n,int m,int x,int y,int P){
	fac[0]=1;
	for (int i=1;i<=P;++i){
		if (i%x)fac[i]=fac[i-1]*i%P;
		else fac[i]=fac[i-1];
	}
	Int A=getfac(n,x,y,P),B=getfac(m,x,y,P),C=getfac(n-m,x,y,P);
	int phi=P/x*(x-1);
	A.x=A.x*power(B.x,phi-1,P)%P;A.y-=B.y;
	A.x=A.x*power(C.x,phi-1,P)%P;A.y-=C.y;
	A.x=A.x*power(x,A.y,P)%P;
	return A.x;
	
}
void merge(int &a1,int &m1,int a2,int m2){  //x%a1==m1,x%a2==m2
	int M=m1*m2;
	for (int i=0;i<M;++i)
		if (i%m1==a1&&i%m2==a2){
			a1=i;m1=M;return;
		}
}
#define M_max 25
int A[M_max],M[M_max],n1;
int exgcd(int a,int b,int &x,int &y){
	if (!b) {x=1;y=0;return a;}
	int t,tmp=exgcd(b,a%b,x,y);
	t=x;x=y;y=t-(a/b)*y;
	return tmp;
}
int Chinese_Remainder_Theorem(int A[],int M[],int n){
	int x,y,P;
	for (int i=2;i<=n;++i){
		P=M[1]*M[i];
		exgcd(M[1],M[i],x,y);
		x=(x*(A[i]-A[1])%P+P)%P;
		A[1]=(x*M[1]+A[1])%P;
		M[1]=P;
	}
	return A[1];
}
int Combination(int n,int m,int P){
	n1=0;
	for (int i=2;i*i<=P;++i)if (P%i==0){
		int m1=1,x=i,y=0;
		while (P%i==0){
			++y;m1*=i;P/=i;
		}
		int a1=Combination(n,m,x,y,m1);
		++n1;A[n1]=a1;M[n1]=m1;
	}
	if (P>1){
		int m1=P,x=P,y=1,a1=Combination(n,m,x,y,m1);
		++n1;A[n1]=a1;M[n1]=m1;
	}
	return Chinese_Remainder_Theorem(A,M,n1);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T;scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&n,&K,&P);
		int nn=n-K,start=nn/P*P;ans=start&1?-1:1;
		for (int i=start+1;i<=nn;++i)
			ans=(ans*i+(i&1?-1:1)+P)%P;
		ans=ans*Combination(n,K,P)%P;
		printf("%d\n",(int)ans);
	}
	system("pause");for (;;);
	return 0;
}


