#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
const unsigned int M=2013265921;
const int alpha=137,beta=749463956;
extern "C"{
static void calc(int *b,int n,int w0){
	int nn=(1<<n);
	int *buf=new int[nn];
	buf[0]=1;
	for (int i=1;i<nn;i++)buf[i]=(long long)buf[i-1]*w0%M;
	for (int i=0;i<n;i++){
		int hn=(1<<i),dn=hn<<1;
		for (int j=0;j<nn;j+=dn){
			for (int k=j;k<j+hn;k++){
				int t;
				asm volatile ("#specialmark\n");
				t=(int)(((long long)buf[(k-j)<<(n-1-i)]*b[k+hn])%M);
				asm volatile ("#endspmark\n");
				b[k+hn]=b[k]-t;
				if (b[k+hn]<0)b[k+hn]+=M;
				b[k]+=t;
				if ((unsigned int)b[k]>=M)b[k]-=M;
			}
		}
	}
	delete []buf;
	asm volatile ("#spmark2\n");
}
}
struct v2{
	double x,y;
};
void bitrev_v2(v2 *a,int n){
	int nn=(1<<n),u=0;
	for (int i=0;i<nn;i++){
		if (i<u)swap(a[i],a[u]);
		for (int j=nn>>1;;j>>=1){
			if (u&j)u^=j;
			else{
				u|=j;
				break;
			}
		}
	}
}
void fft_v2(v2 *a,int n){
	bitrev_v2(a,n);
	static v2 alpha[24];
	alpha[0].x=1;alpha[0].y=0;
	alpha[1].x=-1;alpha[1].y=0;
	alpha[2].x=0;alpha[2].y=1;
	for (int i=3;i<=n;i++){
		//cos2a=2cos^a-1
		//cosa=sqrt(((cos2a)+1)/2)
		alpha[i].x=sqrt((double)((alpha[i-1].x+1)*0.5));
		alpha[i].y=sqrt((double)(1.0-alpha[i].x*alpha[i].x));
	}
	int nn=1<<n;
	v2 *buf=new v2[nn];
	buf[0].x=1;buf[0].y=0;
	for (int i=0;i<n;i++){
		for (int j=(1<<i)-1;j>=0;j--)
			buf[j+j]=buf[j];
		for (int j=1;j<(1<<(i+1));j+=2){
			buf[j].x=buf[j-1].x*alpha[i+1].x-buf[j-1].y*alpha[i+1].y;
			buf[j].y=buf[j-1].y*alpha[i+1].x+buf[j-1].x*alpha[i+1].y;
		}
		for (int j=0;j<nn;j+=(1<<(i+1))){
			for (int k=j,l=j+(1<<i);k<(j+(1<<i));k++,l++){
				v2 t;
				t.x=a[l].x*buf[k-j].x-a[l].y*buf[k-j].y;
				t.y=a[l].x*buf[k-j].y+a[l].y*buf[k-j].x;
				a[l].x=a[k].x-t.x;
				a[l].y=a[k].y-t.y;
				a[k].x+=t.x;
				a[k].y+=t.y;
			}
		}
	}
	delete []buf;
}
void ifft_v2(v2 *a,int n){
	bitrev_v2(a,n);
	static v2 alpha[24];
	alpha[0].x=1;alpha[0].y=0;
	alpha[1].x=-1;alpha[1].y=0;
	alpha[2].x=0;alpha[2].y=1;
	for (int i=3;i<=n;i++){
		//cos2a=2cos^a-1
		//cosa=sqrt(((cos2a)+1)/2)
		alpha[i].x=sqrt((double)((alpha[i-1].x+1)*0.5));
		alpha[i].y=sqrt((double)(1.0-alpha[i].x*alpha[i].x));
	}
	int nn=1<<n;
	v2 *buf=new v2[nn];
	buf[0].x=1;buf[0].y=0;
	for (int i=0;i<n;i++){
		for (int j=(1<<i)-1;j>=0;j--)
			buf[j+j]=buf[j];
		for (int j=1;j<(1<<(i+1));j+=2){
			buf[j].x=buf[j-1].x*alpha[i+1].x-buf[j-1].y*alpha[i+1].y;
			buf[j].y=buf[j-1].y*alpha[i+1].x+buf[j-1].x*alpha[i+1].y;
		}
		for (int j=0;j<nn;j+=(1<<(i+1))){
			for (int k=j,l=j+(1<<i);k<(j+(1<<i));k++,l++){
				v2 t;
				t.x=a[l].x*buf[k-j].x+a[l].y*buf[k-j].y;
				t.y=-a[l].x*buf[k-j].y+a[l].y*buf[k-j].x;
				a[l].x=a[k].x-t.x;
				a[l].y=a[k].y-t.y;
				a[k].x+=t.x;
				a[k].y+=t.y;
			}
		}
	}
	delete []buf;
	for (int i=0;i<nn;i++)a[i].x/=nn,a[i].y/=nn;
}
void bitrev(int *b,int n){
	int j=0;
	for (int i=0;i<(1<<n);i++){
		if (i<j){
			int t=b[i];b[i]=b[j];b[j]=t;
		}
		int k=1<<(n-1);
		while (j&k){
			j-=k;
			k>>=1;
		}
		j|=k;
	}
}
int Pow(int a,int b){
	int c=1;
	while (b){
		if (b&1)c=(int)((long long)c*a%M);
		a=(int)((long long)a*a%M);
		b>>=1;
	}
	return c;
}
void fft(int *b,int n){
	bitrev(b,n);
	calc(b,n,Pow(alpha,1<<(27-n)));
}
void ifft(int *b,int n){
	bitrev(b,n);
	calc(b,n,Pow(beta,1<<(27-n)));
	int theta=Pow(1<<n,M-2);
	for (int i=0;i<(1<<n);i++)
		b[i]=(int)((long long)b[i]*theta%M);
}
struct bigint{
	typedef int basetype;
	struct sigpair{
		basetype *b;
		int n;
		sigpair(){}
		sigpair(basetype *_b,int _n):b(_b),n(_n){}
	};
	static void arrmultiv2(sigpair a,sigpair b,sigpair c){
		int n=0,nn;
		int an=(a.n+1)>>1,bn=(b.n+1)>>1;
		while ((1<<n)<an+bn)n++;
		nn=(1<<n);
		fprintf(stderr,"arrmultiv2 %d %d nn=%d\n",a.n,b.n,nn);
		v2* b1=new v2[nn];
		for (int i=0;i<an;i++){
			b1[i].x=a.b[i+i];
			if (i+i+1<a.n)b1[i].x+=a.b[i+i+1]*10;
			b1[i].y=0.0;
		}
		for (int i=an;i<nn;i++)b1[i].x=b1[i].y=0.0;
		fft_v2(b1,n);
		v2 *b2;
		if (b.b!=a.b){
			b2=new v2[nn];
			for (int i=0;i<bn;i++){
				b2[i].x=b.b[i+i];
				if (i+i+1<b.n)b2[i].x+=b.b[i+i+1]*10;
				b2[i].y=0.0;
			}
			for (int i=bn;i<nn;i++)b2[i].x=b2[i].y=0.0;
			fft_v2(b2,n);
		}else b2=b1;
		for (int i=0;i<nn;i++){
			double t=b1[i].x*b2[i].x-b1[i].y*b2[i].y;
			b1[i].y=b1[i].y*b2[i].x+b1[i].x*b2[i].y;
			b1[i].x=t;
		}
		if (b2!=b1)delete []b2;
		ifft_v2(b1,n);
		int z=0;
		long long s=0;
		for (int i=0;i<c.n;i++){
			if ((i&1)==0){
				if ((i>>1)<nn)s+=(long long)(b1[i>>1].x+0.5);
				z=s%100;
				s/=100;
			}
			c.b[i]=z%10;z/=10;
		}
		delete []b1;
	}
	static void arrmulti(sigpair a,sigpair b,sigpair c){
		int n=0,nn;
		if (a.n+b.n<=(1<<22)){
			arrmultiv2(a,b,c);
			return;
		}
		while ((1<<n)<a.n+b.n)n++;
		nn=(1<<n);
		fprintf(stderr,"arrmulti %d %d nn=%d\n",a.n,b.n,nn);
		int *b1=new int[nn];
		for (int i=0;i<a.n;i++)b1[i]=a.b[i];
		for (int i=a.n;i<nn;i++)b1[i]=0;
		fft(b1,n);
		int *b2=new int[nn];
		for (int i=0;i<b.n;i++)b2[i]=b.b[i];
		for (int i=b.n;i<nn;i++)b2[i]=0;
		fft(b2,n);
		for (int i=0;i<nn;i++)b1[i]=(long long)b1[i]*b2[i]%M;
		delete []b2;
		ifft(b1,n);
		unsigned int s=0;
		for (int i=0;i<c.n;i++){
			if (i<nn)s+=b1[i];
			c.b[i]=s%10;
			s/=10;
		}
		delete []b1;
	}
	static void arradd(sigpair a,sigpair b,sigpair c){
		int s=0;
		for (int i=0;i<c.n;i++){
			if (i<a.n)s+=a.b[i];
			if (i<b.n)s+=b.b[i];
			if (s>=10)c.b[i]=s-10,s=1;
			else c.b[i]=s,s=0;
		}
	}
	static void arrsubtract(sigpair a,sigpair b,sigpair c){
		int s=0;
		for (int i=0;i<c.n;i++){
			if (i<a.n)s+=a.b[i];
			if (i<b.n)s-=b.b[i];
			if (s<0)c.b[i]=s+10,s=-1;
			else c.b[i]=s,s=0;
		}
	}
	static bool greater(sigpair a,sigpair b){
		for (int i=a.n-1;i>=b.n;i--)if (a.b[i])return 1;
		for (int i=b.n-1;i>=a.n;i--)if (b.b[i])return 0;
		for (int i=min(a.n,b.n)-1;i>=0;i--){
			if (a.b[i]>b.b[i])return 1;
			if (a.b[i]<b.b[i])return 0;
		}
		return 0;
	}
	static void arrmulti(sigpair a,int b){
		int s=0;
		for (int i=0;i<a.n;i++){
			s+=b*a.b[i];
			a.b[i]=s%10;
			s/=10;
		}
	}
	vector<basetype> digits;
	char op;
	void setto(int a){
		digits.clear();
		if (a>=0)op=0;
		else op=1,a=-a;
		do{
			digits.push_back(a%10);
			a/=10;
		}while (a);
	}
	bigint(){setto(0);}
	bigint(int a){setto(a);}
	bigint(char *a){
		op=0;
		if ((*a)=='+' || (*a)=='-'){
			if ((*a)=='-')op=1;
			a++;
		}
		int l;
		for (l=0;a[l];l++);
		for (int i=0;i<l;i++)digits.push_back(a[l-1-i]-'0');
	}
	bigint(const bigint &a){
		op=a.op;
		digits=a.digits;
	}
	bool iszero() const{
		return digits.size()==0 || (digits.size()==1 && digits[0]==0);
	}
	bool negative() const{
		return op && !iszero();
	}
	void print() const{
		if (negative())putchar('-');
		for (int i=digits.size()-1;i>=0;i--)
			printf("%d",digits[i]);
	}
	void println() const{print();puts("");}
	static void elz(vector<basetype> &d){
		while (d.size()>1 && *(d.rbegin())==0)
			d.erase(--d.end());
	}
	static void add(vector<basetype> &a,const vector<basetype> &b){
		int n=b.size();
		while ((int)a.size()<=n)
			a.push_back(0);
		arradd(sigpair(&(a[0]),a.size()),
				sigpair((basetype*)&(b[0]),b.size()),
				sigpair(&(a[0]),a.size()));
		elz(a);
	}
	static void subtract(vector<basetype> &a,const vector<basetype> &b){
		arrsubtract(sigpair(&(a[0]),a.size()),
				sigpair((basetype*)&(b[0]),b.size()),
				sigpair(&(a[0]),a.size()));
		elz(a);
	}
	static void subtract2(vector<basetype> &a,const vector<basetype> &b){
		while (a.size()<b.size())a.push_back(0);
		arrsubtract(sigpair((basetype*)&(b[0]),b.size()),
			sigpair(&(a[0]),a.size()),
			sigpair(&(a[0]),a.size()));
		elz(a);
	}
	static bool greater(const vector<basetype> &a,const vector<basetype> &b){
		return greater(sigpair((basetype*)&(a[0]),a.size()),
				sigpair((basetype*)&(b[0]),b.size()));
	}
	bigint& operator+=(const bigint &b){
		if (op==0){
			if (b.op==0)add(digits,b.digits);
			else{
				if (greater(digits,b.digits))
					subtract(digits,b.digits);
				else{
					subtract2(digits,b.digits);
					op=1;
				}
			}
		}else{
			if (b.op==0){
				if (greater(digits,b.digits))
					subtract(digits,b.digits);
				else{
					subtract2(digits,b.digits);
					op=0;
				}
			}else add(digits,b.digits);
		}
		return *this;
	}
	bigint& operator-=(const bigint &b){
		if (op==0){
			if (b.op==1)add(digits,b.digits);
			else{
				if (greater(digits,b.digits))
					subtract(digits,b.digits);
				else{
					subtract2(digits,b.digits);
					op=1;
				}
			}
		}else{
			if (b.op==1){
				if (greater(digits,b.digits))
					subtract(digits,b.digits);
				else{
					subtract2(digits,b.digits);
					op=0;
				}
			}else add(digits,b.digits);
		}
		return *this;
	}
	static void multi(vector<basetype> &a,const vector<basetype> &b){
		int n=a.size()+b.size();
		basetype *buf=new basetype[n];
		arrmulti(sigpair(&(a[0]),a.size()),
				sigpair((basetype*)&(b[0]),b.size()),
				sigpair(buf,n));
		for (int i=0;i<n;i++){
			if (i<(int)a.size())a[i]=buf[i];
			else a.push_back(buf[i]);
		}
		delete []buf;
		elz(a);
	}
	bigint& operator*=(const bigint &b){
		multi(digits,b.digits);
		op^=b.op;
		return *this;
	}
	bigint& operator*=(int b){
		if (b<0)op^=1,b=-b;
		for (int i=b;i;i/=10)digits.push_back(0);
		arrmulti(sigpair(&(digits[0]),digits.size()),b);
		elz(digits);
		return *this;
	}
	bigint& operator>>=(int a){
		if ((int)digits.size()<=a)setto(0);
		else{
			digits.erase(digits.begin(),digits.begin()+a);
		}
		return *this;
	}
	bigint& operator<<=(int a){
		for (int i=0;i<a;i++)digits.push_back(0);
		for (int i=digits.size()-1;i>=a;i--)
			digits[i]=digits[i-a];
		for (int i=0;i<a;i++)digits[i]=0;
		return *this;
	}
	bigint& operator/=(int a){
		if (a<0)op^=1,a=-a;
		int s=0;
		for (int i=digits.size()-1;i>=0;i--){
			s=s*10+digits[i];
			digits[i]=s/a;
			s%=a;
		}
		elz(digits);
		return *this;
	}
	int toInt() const{
		int s=0;
		for (int i=digits.size()-1;i>=0;i--)s=s*10+digits[i];
		if (op)s=-s;
		return s;
	}
};
int getDiv(const bigint &a,const bigint &b){
	if (a.digits.size()<b.digits.size())return 0;
	if (b.digits.size()<4){
		return a.toInt()/b.toInt();
	}
	int u=0;
	for (int i=0;i<4;i++)u=u*10+b.digits[b.digits.size()-1-i];
	int v=0;
	for (int i=0;i<4+(int)a.digits.size()-(int)b.digits.size();i++)
		v=v*10+a.digits[a.digits.size()-1-i];
	return (a.op==1?-1:1)*v/u;
}
bool absGreater(const bigint &a,const bigint &b){
	return bigint::greater(a.digits,b.digits);
}
pair<bigint,bigint> DivMod(const bigint &x,const bigint &y){
	if (x.digits.size()<y.digits.size())return make_pair(bigint(0),x);
	if (y.digits.size()<4){
		int s=0,k=y.toInt();
		bigint b(x);
		for (int i=b.digits.size()-1;i>=0;i--){
			s=s*10+b.digits[i];
			b.digits[i]=s/k;
			s%=k;
		}
		bigint::elz(b.digits);
		return make_pair(b,bigint(s));
	}
	int tt=0;
	for (int i=0;i<4;i++)tt=tt*10+y.digits[y.digits.size()-1-i];
	bigint a(tt),b(10000000/tt);
	int n=4;
	bigint c(a);
	c*=b;
	c-=bigint(10000000);
	c.op^=1;
	while (n-1+(int)y.digits.size()<(int)x.digits.size()){
		printf("n=%d\n",n);
		bigint t;
		t.digits.clear();
		for (int i=n-1;i>=0;i--){
			int j=y.digits.size()-1-n-i;
			if (j>=0)t.digits.push_back(y.digits[j]);
			else t.digits.push_back(0);
		}
		bigint tmp(b);
		tmp*=t;
		c<<=n;
		c-=tmp;
		tmp=b;
		tmp*=c;
		tmp>>=2*n-1;
		b<<=n;
		b+=tmp;
		a<<=n;
		a+=t;
		tmp*=a;
		c<<=n;
		c-=tmp;
		while (absGreater(c,a)){
			int e=getDiv(c,a);
			tmp=a;
			tmp*=e;
			c-=tmp;
			b+=bigint(e);
		}
		n+=n;
	}
	b*=x;
	b>>=n-1+y.digits.size();
	a=b;a*=y;
	c=x;c-=a;
	while (absGreater(c,y)){
		int e=getDiv(c,y);
		b+=bigint(e);
		a=y;a*=e;
		c-=a;
	}
	if (c.negative()){
		c+=y;
		b-=bigint(1);
	}
	return make_pair(b,c);
}
int demo_divide(int ds){
	bigint a,b;
	srand(2133);
	a.digits.clear();
	for (int i=0;i<ds;i++)a.digits.push_back(rand()%9+1);
	b.digits.clear();
	for (int i=0;i<ds/2;i++)b.digits.push_back(rand()%9+1);
	int t1=clock();
	pair<bigint,bigint> c=DivMod(a,b);
	printf("%d\n",(int)clock()-t1);
	printf("%d %d %d %d\n",a.digits.size(),b.digits.size(),c.first.digits.size(),(int)(absGreater(c.second,b)));
	getchar();
	t1=clock();
	bigint t(b);t*=c.first;
	printf("%d\n",(int)clock()-t1);
	t+=c.second;t-=a;
	t.println();
	getchar();
	a.println();
	b.println();
	c.first.println();
	c.second.println();
	return 0;
}
int demo_multiply(int ds){
	bigint a,b;
	srand(2133);
	a.digits.clear();
	for (int i=0;i<ds;i++)a.digits.push_back(rand()%9+1);
	b.digits.clear();
	for (int i=0;i<ds;i++)b.digits.push_back(rand()%9+1);
	bigint c(a);
	int t1=clock();
	c*=b;
	printf("%d\n",(int)clock()-t1);
	printf("%d %d %d\n",a.digits.size(),b.digits.size(),c.digits.size());
	getchar();
	a.println();
	b.println();
	c.println();
	return 0;
}
int demo_sqrt2(int mx){
	bigint y("14142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727350138462309122970249248360");
	int n=y.digits.size();
	while (n<mx){
		//y'=1.5y*10^n-25y^3/10^n
		bigint u(y);
		u*=u;u*=y;
		u*=25;u>>=n;
		y<<=n-1;y*=15;
		y-=u;
		n+=n;
	}
	fprintf(stderr,"%d\n",(int)clock());
	for (int i=0;i<mx;i++)
		printf("%d",(int)(y.digits[y.digits.size()-1-i]));
	puts("");
	return 0;
}
int main(){
	demo_sqrt2(1000000);
	return 0;
}


