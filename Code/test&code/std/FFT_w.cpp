#include <iostream>
#include <cstring>
#include <cstdio>
typedef long long ll;
#define swap(x,y) { ll temp=x;x=y;y=temp; }
#define max(x,y) ((x)>(y)?(x):(y))

using namespace std;

const ll N=1048576,P=2013265921,Root=440564289;
char num1[N+1],num2[N+1];
ll a[N],b[N],c[N];
int n,len1,len2;

ll pow(ll a,ll n) {
	ll res=1;
	while (n) {
		if (n&1) res=res*a%P;
		a=a*a%P; n>>=1;
	}
	return res;
}
void calc(ll a[],ll wt) {
	for (ll m=2;m<=n;m<<=1)
		for (ll k=0,w0=pow(wt,n/m);k<n;k+=m)
			for (ll j=0,w=1;j*2<m;++j) {
				ll u=a[k+j], t=a[k+j+(m>>1)]*w%P;
				a[k+j]=(u+t)%P; a[k+j+(m>>1)]=(u-t)%P; w=w*w0%P;
			}
}
void bitrc(ll a[]) {
	ll m=0;
	while ((1<<m)<n) ++m;
	for (ll i=0;i<n;++i) {
		int x=i,y=0;
		for (int j=0;j<m;++j) y=(y<<1)+(x&1), x>>=1;
		if (i<y) swap(a[i],a[y]);
	}
}
void FFT(ll a[]) {
	bitrc(a);
	calc(a,pow(Root,(1<<27)/n));
	for (int i=0;i<n;++i) a[i]=(a[i]%P+P)%P;
}
void IFFT(ll a[]) {
	bitrc(a);
	calc(a,pow(Root,(1<<27)/n*(n-1)));
	ll t=pow(n,P-2);
	for (int i=0;i<n;++i) a[i]=(a[i]*t%P+P)%P;
}
void solve() {
	FFT(a); FFT(b);
	for (int i=0;i<n;++i) a[i]=a[i]*b[i]%P;
	IFFT(a);
	for (int i=0;i<n;++i) a[i+1]+=a[i]/100LL, a[i]%=100LL;
	--n; while (!a[n]) --n;
}

int main() {
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	int T;
	scanf("%d",&T);
	while (T--){
	//gets(num1); gets(num2);
	scanf("%s%s",&num1,&num2);
	len1=strlen(num1); len2=strlen(num2);
	ll temp=max(len1,len2)/2,len;
		for (n=1;n<=temp;n<<=1);n*=2;
	for (int i=0;i<=n;++i)a[i]=b[i]=0;
	{	
		for (int i=0;i<len1;++i) a[(len1-1-i)/2]=a[(len1-1-i)/2]*10+num1[i]-'0';
		for (int i=0;i<len2;++i) b[(len2-1-i)/2]=b[(len2-1-i)/2]*10+num2[i]-'0';
	}
	//printf("nie%d\n",(int)n);
	solve();
	printf("%I64d",a[n]);
	for (int i=n-1;i>=0;--i) {
		if (a[i]<10) printf("0");
		printf("%I64d",a[i]);
	}
	printf("\n");
	}
	system("pause");
}


