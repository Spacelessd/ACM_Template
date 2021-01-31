#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 8
#define ll long long
int c[N],c1,P,phi;
inline ll exp(ll x,int y,int P){
	ll tmp=1;
	while (y){
		if (y&1)tmp=tmp*x%P;
		x=x*x%P;
		y>>=1;
	}
	return tmp;
}
struct node{
	int num[N];ll mul;
	node(){for (int i=1;i<=c1;++i)num[i]=0;mul=1;}
	int to_int(){
		ll tmp=mul;
		for (int i=1;i<=c1;++i)tmp=tmp*exp(c[i],num[i],P)%P;
		return tmp%P;
	}
	void print(){
		printf("%d\n",to_int());
	}
	friend node operator *(const node &x,int y){
		node tmp=x;
		int num[N];for (int i=1;i<=c1;++i)num[i]=0;
		for (int i=1;i<=c1;++i)
			while (y%c[i]==0)++num[i],y/=c[i];
		for (int i=1;i<=c1;++i)tmp.num[i]+=num[i];
		tmp.mul=tmp.mul*y%P;
		return tmp;
	}
	friend node operator /(const node &x,int y){
		node tmp=x;
		int num[N];for (int i=1;i<=c1;++i)num[i]=0;
		for (int i=1;i<=c1;++i)
			while (y%c[i]==0)++num[i],y/=c[i];
		for (int i=1;i<=c1;++i)tmp.num[i]-=num[i];
		tmp.mul=tmp.mul*exp(y,phi-1,P)%P;
		return tmp;
	}
};
int main()
{
	int t1=clock();
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T,n,K;scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&n,&K,&P);
		int _P=P;c1=0;
		for (int i=2;i*i<=_P;++i)if (_P%i==0){
			++c1;c[c1]=i;
			while (_P%i==0)_P/=i;
		}
		if (_P>1)c[++c1]=_P;
		phi=P;
		for (int i=1;i<=c1;++i)phi=phi/c[i]*(c[i]-1);
		node tmp;ll ans=0,mul;
		for (int i=K+1;i<=n;++i)tmp=tmp*i;
		if ((n-K)&1)mul=-1;else mul=1;
		for (int i=1;i<=n-K;++i)tmp=tmp/i;
		for (int i=n-K;i>=2;--i){
			ans=(ans+mul*tmp.to_int())%P;
			tmp=tmp*i;mul=-mul;
		}
		if (n-K==0)ans=1;
		if (n-K==1)ans=0;
		ans=(ans+P)%P;
		printf("%d\n",(int)ans);
	}
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


