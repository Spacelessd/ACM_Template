#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
#define ll long long
ll f[N],v[N],inv[N];int n,P;
inline int pow(int x,int y){//x^y mod p
	ll tmp=1,t=x;
	while (y){
		if (y&1)tmp=tmp*t%P;
		t=t*t%P;y>>=1;
	}
	return (int)tmp;
}
int calc_phi(int P){
	static int c[105];int phi=P,c1=0;
	for (int i=2;i*i<=P;++i)
		if (P%i==0){
			c[++c1]=i;while (P%i==0)P/=i;
		}
	if (P!=1)c[++c1]=P;
	for (int i=1;i<=c1;++i)phi=phi/c[i]*(c[i]-1);
	return phi;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//要求P为质数
	scanf("%d%d",&n,&P);if (n>P-1)n=P-1;
	//solution 1
	f[0]=1;for (int i=1;i<=n;++i)f[i]=f[i-1]*i%P;
	int phi=calc_phi(P);v[n]=pow(f[n],phi-1);
	for (int i=n-1;i;--i)v[i]=v[i+1]*(i+1)%P;
	for (int i=1;i<=n;++i)inv[i]=v[i]*f[i-1]%P;
	for (int i=1;i<=n;++i)printf("%d %I64d\n",i,inv[i]);printf("--------\n");
	//solution 2
	inv[1]=1;
	for (int i=2;i<=n;++i)inv[i]=inv[P%i]*(P-P/i)%P;
	for (int i=1;i<=n;++i)printf("%d %I64d\n",i,inv[i]);printf("--------\n");
	system("pause");for (;;); 
	return 0;
}


