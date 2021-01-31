#include<algorithm>
#include<assert.h>
#include<bitset>
#include<complex>
#include<ctype.h>
#include<deque>
#include<functional>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<limits>
#include<list>
#include<map>
#include<math.h>
#include<numeric>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdarg.h>
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<time.h>
#include<utility>
#include<vector>
//#include<memory.h>
//#include<rope.h>
//#include<ext/rope>
//#include <hash_map>
//#include <hash_set>
//#include<windows.h>
using namespace std;
//using namespace __gnu_cxx;
#define rep(i,n) for (int i=1;i<=n;++i)
#define For(i,l,r) for(int i=l;i<=r;++i)
#define foreach(i,x) for(typeof((x).begin()) i=(x).begin();i!=(x).end();++i)
#define DO(n) while(n--)
#define DO_C(n) int n_=n;while(n_--)
#define INS(A,P,B) A.insert(A.begin()+P,B)
#define ERS(A,P) A.erase(A.begin()+P)
#define CTN(A,x) (A.find(x)!=A.end())
#define SORT(x) sort(all(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))
#define CPY(A,B) memcpy(A,B,sizeof(B))
#define all(x) x.begin(),x.end()
#define SZ(x) ((int)(x.size()))
#define DREP(x) sort(all(x));x.erase(unique(x.begin(),x.end()),x.end())
#define INDEX(arr,index) (lower_bound(arr.begin(),arr.end(),index)-arr.begin())
#define MP(A,B) make_pair(A,B)
#define Debug(x) cout<<#x<<"="<<x<<endl
#define debug(args...) {dbg,args; cerr<<endl;}
#define dline cerr<<endl
#define mp make_pair
#define pb push_back
#define RT return
#define FF first
#define SS second
#define tri(a,b,c) make_pair((a),make_pair((b),(c)))
#define XX first
#define YY second.first
#define ZZ second.second
#define Scan(x) scanf("%d",&x)
#ifdef _WIN32
	#define Scanl(x) scanf("%I64d",x)
#else
	#define Scanl(x) scanf("%lld",x)
#endif
#define Scanf(x) scanf("%lf",&x)
#define Scans(x) scanf("%s",x)
#define eprintf(...) {fprintf(stderr,__VA_ARGS__),fflush(stderr);}
#define maX(a,b) ((a)>(b)?(a):(b))
#define miN(a,b) ((a)<(b)?(a):(b))
#define abS(x) ((x)<0?-(x):(x))
#define Display(A,n,m){ \
	rep(i,n){ \
        rep(j,m)cout<<A[i][j]<<" "; \
		cout<<endl; \
	} \
}
//#define if(_) if(!(_))
#pragma comment(linker,"/STACK:36777216")
#pragma GCC optimize ("O2")
#define Ruby system("ruby main.rb")
#define Haskell system("runghc main.hs")
#define Python system("py main.py")
#define Pascal system("fpc main.pas")
const int inf=~0U>>1;
const int MOD=1000000007;
const long long linf=(long long)1e18;
const double eps=1e-6,PI=atan(1.0)*4;
typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double DB;
typedef long double ld;
typedef pair<int,int> PII;
typedef pair<int,bool> PIB;
typedef pair<int,pair<int,int> > tri;
typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<string> VS;
typedef vector<ll> VL;
typedef vector<double> VD;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef vector<VII> VVII;
typedef vector<int>::iterator vit;
typedef set<int> SI;
typedef set<string> SS;
typedef set<ll> SL;
typedef set<double> SD;
typedef set<PII> SII;
typedef set<int>::iterator sit;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef map<ll,int> MLI;
typedef map<double,int> MDI;
typedef map<int,bool> MIB;
typedef map<string,bool> MSB;
typedef map<ll,bool> MLB;
typedef map<double,bool> MDB;
typedef map<int,int>::iterator mit;
typedef map<PII,int> MPIII;
typedef map<PII,bool> MPIIB;
typedef istringstream ISS;
typedef ostringstream OSS;
template<class T> string tostr(const T &x){
	OSS out;out<<x;return out.str();
}
struct debugger{
	template<typename T>
	debugger& operator ,(const T &x){
		cerr<<x<<endl;
		return *this;
	}
}dbg;
template<class T> inline void CLR(priority_queue<T,vector<T>,less<T> > &Q){
	while (!Q.empty())Q.pop();
}
template<class T> inline void CLR(priority_queue<T,vector<T>,greater<T> > &Q){
	while (!Q.empty())Q.pop();
}
template<class T> inline void CLR(T &A){A.clear();}
template<class T> inline void SRT(T &A){sort(all(A));}
void showVi(const vector<int> &A){
	for (vector<int>::const_iterator i=A.begin();i!=A.end();++i)cout<<*i<<" ";cout<<endl;
}
void showArray(int *A,int n){
	for (int i=1;i<=n;++i)cout<<A[i]<<" ";cout<<endl;
}
int **Make2DArray(int n,int m){
	int **p=new int*[n],*a=new int[n*m];
	for (int i=0;i<n;++i)p[i]=a+m*i;
	return p;
}
template <class T> inline T Min(const T &a,const T &b){return a<b?a:b;}
template <class T> inline T Max(const T &a,const T &b){return a>b?a:b;}
template <class T> inline void Swap(T &a,T &b){T tmp=a;a=b;b=tmp;}
inline int max_fast(int x,int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min_fast(int x,int y){int m=(y-x)>>31;return y&m|x&~m;}
template<class T> inline void checkMin(T &a,const T b){if (b<a)a=b;}
template<class T> inline void checkMax(T &a,const T b){if (b>a)a=b;}
template<class T,class C> inline void checkMin(T &a,const T b,C c){if (c(b,a))a=b;}
template<class T,class C> inline void checkMax(T &a,const T b,C c){if (c(a,b))a=b;}
template<class T> inline T Min(const T &a,const T &b,const T &c){return min(min(a,b),c);}
template<class T> inline T Max(const T &a,const T &b,const T &c){return max(max(a,b),c);}
template<class T> inline T Min(const T &a,const T &b,const T &c,const T &d){return min(min(a,b),min(c,d));}
template<class T> inline T Max(const T &a,const T &b,const T &c,const T &d){return max(max(a,b),max(c,d));}
template<class T> inline T sqr(const T &a){return a*a;}
template<class T> inline T cub(const T &a){return a*a*a;}
inline int Ceil(int x,int y){return (x-1)/y+1;}
inline bool _1(int x,int i){return x&1<<i;}
inline bool _1(ll x,int i){return x&1LL<<i;}
inline ll _1(int i){return 1LL<<i;}
template<class T> inline T low_bit(T x){return x&-x;}
template<class T> inline T high_bit(T x){
	T p=low_bit(x); while (p!=x)x-=p,p=low_bit(x); return p;
}
template<class T> inline T cover_bit(T x){
	T p=1; while (p<x)p<<=1;return p;
}
//__builtin_popcount() __builtin_clz() __builtin_ctz()
inline int count_bits(uint x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
inline int count_bits(ull x){
	x=(x&0x5555555555555555LL)+((x&0xaaaaaaaaaaaaaaaaLL)>>1);
	x=(x&0x3333333333333333LL)+((x&0xccccccccccccccccLL)>>2);
	x=(x&0x0f0f0f0f0f0f0f0fLL)+((x&0xf0f0f0f0f0f0f0f0LL)>>4);
	x=(x&0x00ff00ff00ff00ffLL)+((x&0xff00ff00ff00ff00LL)>>8);
	x=(x&0x0000ffff0000ffffLL)+((x&0xffff0000ffff0000LL)>>16);
	x=(x&0x00000000ffffffffLL)+((x&0xffffffff00000000LL)>>32);
	return x;
}
inline int reverse_bits(uint x){
	x=((x>>1)&0x55555555)|((x<<1)&0xaaaaaaaa);
	x=((x>>2)&0x33333333)|((x<<2)&0xcccccccc);
	x=((x>>4)&0x0f0f0f0f)|((x<<4)&0xf0f0f0f0);
	x=((x>>8)&0x00ff00ff)|((x<<8)&0xff00ff00);
	x=((x>>16)&0x0000ffff)|((x<<16)&0xffff0000);
	return x;
}
inline ll reverse_bits(ull x){
	x=((x>>1)&0x5555555555555555LL)|((x<<1)&0xaaaaaaaaaaaaaaaaLL);
	x=((x>>2)&0x3333333333333333LL)|((x<<2)&0xccccccccccccccccLL);
	x=((x>>4)&0x0f0f0f0f0f0f0f0fLL)|((x<<4)&0xf0f0f0f0f0f0f0f0LL);
	x=((x>>8)&0x00ff00ff00ff00ffLL)|((x<<8)&0xff00ff00ff00ff00LL);
	x=((x>>16)&0x0000ffff0000ffffLL)|((x<<16)&0xffff0000ffff0000LL);
	x=((x>>32)&0x00000000ffffffffLL)|((x<<32)&0xffffffff00000000LL);
	return x;
}
ll C(int n,int m){
	if (n>m)return 0;
	ll res=1;
	for (int i=1;i<=n;++i)res=res*(m-i+1)/i;
	return res;
}
inline void INC(int &a,int b){a+=b;if (a>=MOD)a-=MOD;}
inline int SUM(int a,int b){a+=b;if (a>=MOD)a-=MOD;return a;}
inline void DEC(int &a,int b){a-=b;if (a<0)a+=MOD;}
inline int DFF(int a,int b){a-=b;if (a<0)a+=MOD;return a;}
inline void MUL(int &a,int b){a=(ll)a*b%MOD;}
inline int SUM(int a,int b,int c){return SUM(SUM(a,b),c);}
inline int SUM(int a,int b,int c,int d){return SUM(SUM(a,b),SUM(c,d));}
inline int pow(int x,int y){
	int res=1;
	for (;y;y>>=1){
		if (y&1)MUL(res,x);MUL(x,x);
	}
	return res;
}
inline ll mul32(ll x,ll y){
	ll res=0;x%=MOD;y%=MOD;
	while (y){if (y&1)res+=x;x=(x<<1)%MOD;y>>=1;}
	return res;
}
template<class T> inline T gcd(T x,T y){return !y?x:gcd(y,x%y);}
template<class T> inline T lcm(T x,T y){return x*(y/gcd(x,y));}
template<class T> T extend_gcd(T a,T b,T &x,T &y){
	if (!b){x=1;y=0;return a;}
	T res=exgcd(b,a%b,y,x);y-=x*(a/b);
	return res;
}
template<class T> pair<vector<T>,int> factor(T x){
	pair<vector<T>,int> res;
	for (T i=2;i*i<=x;++i)if (x%i==0){
		int cnt=0;while (x%i==0)x/=i,++cnt;res.push(make_pair(i,cnt));
	}
	if (x>1)res.push(make_pair(x,1));
	return res;
}
template<class T> T phi(T x){
	pair<vector<T>,int> tmp=factor(x);
	for (int i=0;i<tmp.size();++i)x=x/tmp[i].first*(tmp[i].first-1);return x;
}
inline ll exp(ll x,ll y,ll z){  //x^y mod z
	ll ans=1;
	while (y){
		if (y&1)ans=ans*x%z;
		x=x*x%z;y>>=1;
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
inline ll inv(ll x,ll p,ll P){return exp(x,p-2,P);}
int get_prime(int p[],int n){
	int len=0,*f=new int[n+1];
	memset(f+1,0,sizeof(int)*n);
	for (int i=2;i<=n;++i){
		if (!f[i])f[i]=p[++len]=i;
		for (int j=1;j<=len&&p[j]<=f[i]&&i*p[j]<=n;++j)
			f[i*p[j]]=p[j];
	}
	delete[] f;return len;
}
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}
inline int rand32(){return (bool(rand()&1)<<30)+(rand()<<15)+rand();}
inline int random32(int l,int r){return rand32()%(r-l+1)+l;}
inline int random(int l,int r){return rand()%(r-l+1)+l;}
template<class T>
struct CMP{
	bool operator ()(const T &x,const T &y){
		return x<y;
	}
};
/*template<int stack_size,class T>
void Calldfs(T *p,int a){
	int *Stack=new int[stack_size],bak;
	__asm__ __volatile__
	(
		"mov %%esp,%0\n"
		"mov %1,%%esp\n"
		:"=g"(bak)
		:"g"(Stack+stack_size-1)
		:
	);
	(*p)(a);
	__asm__ __volatile__
	(
		"mov %0,%%esp\n"
		:
		:"g"(bak)
		:
	);
	delete[] Stack;
}*/
struct Timer{
	int t;
	Timer(){init();}
	void init(){t=clock();}
	int time(){return clock()-t;}
	void print(){printf("time=%d\n",time());}
};
template<int _N,int _M>
struct Edge{
	int link[_M],next[_M],son[_N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
template<int _N,int _M>
struct Edge_c{
	int link[_M*2],next[_M*2],cost[_M*2],son[_N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
template<int N>
struct DisjointSet{
	int f[N],rank[N];
	void init(int n){for (int i=1;i<=n;++i)f[i]=i,rank[i]=0;}
	int find(int x){
		if (f[x]==x)return x;
		else return f[x]=find(f[x]);
	}
	void link(int x,int y){f[find(x)]=find(y);}
	void _link(int x,int y){
		int f1=find(x),f2=find(y);
		if (f1==f2)return;
		if (rank[f1]>rank[f2])f[f2]=f1;
			else if (rank[f1]<rank[f2])f[f1]=f2;
				else f[f2]=f1,++rank[f1];
	}
};
namespace Matrix{
	const ll P=1000000007;size_t size;
	template<size_t Size>
	struct matrix{
		ll key[Size][Size];
		void clear(){memset(key,0,sizeof(key));}
		void print(int n){
			for (int i=0;i<size;++i)
				for (int j=0;j<size;++j)
					printf("%d%c",(int)key[i][j],j+1==size?'\n':' ');
		}
		int det(){
			if (P==1)return 0;
			for (int i=0;i<size;++i)
				for (int j=0;j<size;++j)key[i][j]%=P;
			int ans=1;
			for (int i=0;i<size;++i){
				for (int j=i+1;j<size;++j)while (key[j][i]){
					int t=key[i][i]/key[j][i];
					for (int k=i;k<size;++k)
						key[i][k]=((ll)key[j][k]*-t+key[i][k])%P;
					for (int k=i;k<size;++k)
						{int tmp=key[i][k];key[i][k]=key[j][k];key[j][k]=tmp;}
					ans=-ans;
				}
				if (key[i][i]==0)return 0;
				ans=(ll)ans*key[i][i]%P;
			}
			return ((ll)ans+P)%P;
		}
	};
	template<size_t Size>
	const matrix<Size>& operator +(const matrix<Size> &a,const matrix<Size> &b){
		static matrix<Size> T;T.clear();
		for (int i=0;i<size;++i)
			for (int j=0;j<size;++j)T.key[i][j]=(a.key[i][j]+b.key[i][j])%P;
		return T;
	}
	template<size_t Size>
	const matrix<Size>& operator *(const matrix<Size> &a,const matrix<Size> &b){
		static matrix<Size> T;T.clear();
		for (int k=0;k<size;++k)
			for (int i=0;i<size;++i)
				for (int j=0;j<size;++j)
					T.key[i][j]+=a.key[i][k]*b.key[k][j];
		for (int i=0;i<size;++i)
			for (int j=0;j<size;++j)T.key[i][j]=T.key[i][j]%P;
		return T;
	}
	template<size_t Size>
	matrix<Size> pow(const matrix<Size> &x,int y){
		static matrix<Size> res,tmp;tmp=x;
		memset(res.key,0,sizeof(res.key));
		for (int i=0;i<Size;++i)res.key[i][i]=1;
		while (y){
			if (y&1)res=res*tmp;
			tmp=tmp*tmp;y>>=1;
		}
		return res;
	}
};
using Matrix::matrix;
struct fraction{
	ll a,b;
	void simplify(){
		ll g=abs(gcd(a,b));a/=g;b/=g;
		if (b<0)a=-a,b=-b;
	}
	fraction(ll _a=0,ll _b=1):a(_a),b(_b){simplify();}
	void set(ll _a,ll _b){a=_a;b=_b;simplify();}
	void getvalue(ll &_a,ll &_b)const{_a=a;_b=b;}
	friend bool operator ==(const fraction &x,const fraction &y){return x.a==y.a&&x.b==y.b;}
	friend bool operator !=(const fraction &x,const fraction &y){return !(x==y);}
	friend fraction operator +(const fraction &x,const fraction &y){
		return fraction(x.a*y.b+x.b*y.a,x.b*y.b);
	}
	friend fraction operator -(const fraction &x,const fraction &y){
		return fraction(x.a*y.b-x.b*y.a,x.b*y.b);
	}
	friend fraction operator *(const fraction &x,const fraction &y){
		return fraction(x.a*y.a,x.b*y.b);
	}
	friend fraction operator /(const fraction &x,const fraction &y){
		return fraction(x.a*y.b,x.b*y.a);
	}
};
struct point{
	static const double eps=1e-10;
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator +(const point &p)const{return point(x+p.x,y+p.y);}
	point operator -(const point &p)const{return point(x-p.x,y-p.y);}
	double operator *(const point &p)const{return x*p.x+y*p.y;}  //dot
	double operator ^(const point &p)const{return x*p.y-p.x*y;}  //cha
	point operator *(double d)const{return point(x*d,y*d);}
	friend point operator *(double d,const point &x){return point(x.x*d,x.y*d);}
	point operator /(double d)const{return point(x/d,y/d);}
	friend point operator /(double d,const point &x){return point(x.x/d,x.y/d);}
	point operator -()const{return point(-x,-y);}
	bool operator <(const point &p)const{return x<p.x||x==p.x&&y<p.y;}
	bool operator ==(const point &p)const{return fabs(x-p.x)<eps&&fabs(y-p.y)<eps;}
	bool operator !=(const point &p)const{return !(*this==p);}
	point& operator +=(const point &p){x+=p.x;y+=p.y;return *this;}
	point& operator -=(const point &p){x-=p.x;y-=p.y;return *this;}
	point& operator *=(double d){x*=d;y*=d;return *this;}
	point& operator /=(double d){x/=d;y/=d;return *this;}
	double len()const{return sqrt(x*x+y*y);}
	double atan(){return atan2(y,x);}
	point rotate(double angle){
		return point(x*cos(angle)-y*sin(angle),y*cos(angle)+x*sin(angle));
	}
	istream& operator >>(istream &in){return in>>x>>y;}
	ostream& operator <<(ostream &out){return out<<"("<<x<<","<<y<<")";}
};
struct point3D{
	double x,y,z;
	point3D(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
	friend point3D operator +(const point3D &x,const point3D &y){return point3D(x.x+y.x,x.y+y.y,x.z+y.z);}
	friend point3D operator -(const point3D &x,const point3D &y){return point3D(x.x-y.x,x.y-y.y,x.z-y.z);}
	double operator *(const point3D &p)const{return x*p.x+y*p.y+z*p.z;}
	friend point3D operator ^(const point3D &x,const point3D &y){return point3D(x.y*y.z-y.y*x.z,x.z*y.x-y.z*x.x,x.x*y.y-y.x*x.y);}
	point3D operator *(double d)const{return point3D(x*d,y*d,z*d);}
	point3D operator /(double d)const{return point3D(x/d,y/d,z/d);}
	point3D operator -()const{return point3D(-x,-y,-z);}
	bool operator ==(const point3D &p)const{return fabs(x-p.x)<eps&&fabs(y-p.y)<eps&&fabs(z-p.z)<eps;}
	bool operator !=(const point3D &p)const{return !(*this==p);}
	point3D& operator +=(const point3D &p){x+=p.x;y+=p.y;z+=p.z;return *this;}
	point3D& operator -=(const point3D &p){x-=p.x;y-=p.y;z-=p.z;return *this;}
	point3D& operator *=(double d){x*=d;y*=d;z*=d;return *this;}
	point3D& operator /=(double d){x/=d;y/=d;z/=d;return *this;}
	double len()const{return sqrt(x*x+y*y+z*z);}
	istream& operator >>(istream &in){return in>>x>>y>>z;}
	ostream& operator <<(ostream &out){return out<<"("<<x<<","<<y<<","<<z<<")";}
};
struct circle{
	double x,y,r;
	circle(double _x=0,double _y=0,double _r=0):x(_x),y(_y),r(_r){}
};
struct line{
	point x,y;
	line(){}
	line(const point &_x,const point &_y):x(_x),y(_y){}
};
struct plane{  //Ax+By+C>=0
	double A,B,C,angle;
	plane(double _A=0,double _B=0,double _C=0,double _angle=0):A(_A),B(_B),C(_C),angle(_angle){}
	void rev(){A=-A;B=-B;C=-C;}
	inline friend bool operator <(const plane &x,const plane &y){return x.angle+eps<y.angle;}
};
inline int sgn(double x){return fabs(x)<eps?0:(x<0?-1:1);}
inline double dist(const point &x,const point &y){return (x-y).len();}
inline double cross(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
inline double dot(double x1,double y1,double x2,double y2){return x1*x2-y1*y2;}
double (*cha)(double,double,double,double)=cross;
inline double area(const point3D &a,const point3D &b,const point3D &c){return ((b-a)^(c-a)).len();}
inline double volume(const point3D &a,const point3D &b,const point3D &c,const point3D &d){return ((b-a)^(c-a))*(d-a);}
inline point rotate(const point &x,double angle){  //向量转角度
	return point(x.x*cos(angle)-x.y*sin(angle),x.y*cos(angle)+x.x*sin(angle));
}
inline int on_segment(const point &p,const line &l){
	if (min(l.x.x,l.y.x)-eps<=p.x&&max(l.x.x,l.y.x)+eps>=p.x&&
	min(l.x.y,l.y.y)-eps<=p.y&&max(l.x.y,l.y.y)+eps>=p.y)return 1;
	else return 0;
}
inline int online(const point &p,const line &l){
	return sgn((p-l.x)*(l.y-l.x))==0
		&&sgn((p.x-l.x.x)*(p.x-l.y.x))<1
		&&sgn((p.y-l.x.y)*(p.y-l.y.y))<1;
}
inline double angle(const point &o,const point &p1,const point &p2){
	double sx=p1.x-o.x,sy=p1.y-o.y,ex=p2.x-o.x,ey=p2.y-o.y;
	double fi,cosfi=sx*ex+sy*ey,norm=(sx*sx+ey*ey)*(ex*ex+ey*ey); cosfi/=sqrt(norm);
	if (cosfi>=1.0)return 0; if (cosfi<=-1.0)return -PI; fi=acos(cosfi);
	if (cha(sx,sy,ex,ey)>0)return fi; else return -fi;
}
inline int direction(const point &p1,const point &p2,const point &p3){return sgn((p3-p1)^(p2-p1));}
inline bool cross(const line &a,const line &b){
	const point &p1=a.x,&p2=a.y,&p3=b.x,&p4=b.y;
	int d1=direction(p3,p4,p1),
		d2=direction(p3,p4,p2),
		d3=direction(p1,p2,p3),
		d4=direction(p1,p2,p4);
	if (d1*d2==-1&&d3*d4==-1)return 1;
	else if (d1==0&&on_segment(p1,b))return 1;
	else if (d2==0&&on_segment(p2,b))return 1;
	else if (d3==0&&on_segment(p3,a))return 1;
	else if (d4==0&&on_segment(p4,a))return 1;
	else return 0;
}
inline pair<point,point> cross_circle(const circle &O,const point &x){  //与圆的切点
	double d1=dist(point(O.x,O.y),x),d2=sqrt(d1*d1-O.r*O.r),angle=asin(O.r/d1);
	point delta=point(O.x,O.y)-x,x1=x+rotate(delta,-angle)*(d2/d1),x2=x+rotate(delta,angle)*(d2/d1);
	return make_pair(x1,x2);
}
inline double new_angle(double angle){  //angle%360
	angle+=2*PI;return angle-floor(angle/(2.0*PI))*2.0*PI;
}
inline double angle(const circle &O,const point &x){  //极角 
	double angle=asin(x.y-O.y);
	if (x.x-O.x<0)angle=PI-angle;
	return angle;
}
inline point to_point(const circle &O,double angle){
	return point(O.x+O.r*cos(angle),O.y+O.r*sin(angle));
}
inline point3D cross(const plane &x,const plane &y){
	point3D p;p.x=x.B*y.C-x.C*y.B; p.y=x.C*y.A-x.A*y.C; p.z=x.A*y.B-x.B*y.A;
	if (fabs(p.z)>eps)p.x/=p.z,p.y/=p.z,p.z=1;
	return p;
}
inline bool stayout(const point3D &p,const plane &l){
	return l.A*p.x+l.B*p.y+l.C*p.z<-eps?1:0;
}
inline plane make_line(double x1,double y1,double x2,double y2){  //left plane
	plane l;double z1=1,z2=1;
	l.A=y1*z2-y2*z1;l.B=z1*x2-z2*x1;l.C=x1*y2-x2*y1;l.angle=atan2(y2-y1,x2-x1);
	if (stayout(point3D(x1+y1-y2,y1+x2-x1,1),l))l.rev();return l;
}
struct polygon{
	vector<point> a;
	typedef vector<point>::iterator vit;
	double area(){
		double res=0;
		for (vit i=a.begin(),next;i!=a.end();++i){
			next=i;++next; if (next==a.end())next=a.begin(); res+=(*i)*(*next);
		}
		return fabs(res/2);
	}
	bool inside(const point &p){
		bool in=0;
		for (vit i=a.begin(),next;i!=a.end();++i){
			next=i;++next; if (next==a.end())next=a.begin();
			if (cross(line(*i,*next),line(p,point(0,1e10))))in^=1;
		}
		return in;
	}
	void add(const point &p){a.push_back(p);}
	vector<point> ConvuxHull(){
		vector<point> res,A=a;int *c=new int[a.size()],top=0;
		sort(A.begin(),A.end());
		for (int i=0;i<a.size();++i){
			while (top>1&&cha(a[i].x-a[c[top]].x,a[i].y-a[c[top]].y,a[c[top]].x-a[c[top-1]].x,a[c[top]].y-a[c[top-1]].y)>eps)--top;
			c[++top]=i;
		}
		for (int i=a.size()-2;i>=0;--i){
			while (top>1&&cha(a[i].x-a[c[top]].x,a[i].y-a[c[top]].y,a[c[top]].x-a[c[top-1]].x,a[c[top]].y-a[c[top-1]].y)>eps)--top;
			c[++top]=i;
		}
		for (int i=1;i<=top;++i)res.push_back(a[c[i]]);
		return res;
	}
};
template<size_t N>
void radix_sort(int A[N],int l,int r){  //a[i]>=0
	#define base 65535
	#define W 16
	A+=l-1;r-=l-1;l=1;
	int *B=new int[N],*s=new int[base+1],*a=A,*b=B,x=0;
	for (int i1=1;i1<=2;++i1){
		memset(s,0,sizeof(s));
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>x&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;x+=W;
	}
	if (a!=A)memcpy(A+1,a+1,sizeof(int)*r);
	delete[] B;delete[] s;
	#undef W
	#undef base
}
template<class T>
struct Vector{
	typedef T* it;
	it Mem,End,MemEnd;
	void Grow(){
		int s=MemEnd-Mem;it NewMem=new T[s*2];
		memcpy(NewMem,Mem,sizeof(T)*s);delete[] Mem;
		Mem=NewMem;End=Mem+s;MemEnd=Mem+s*2;
	}
	void Shrink(){
		int s=MemEnd-Mem,l=End-Mem;it NewMem=new T[s>>1];
		memcpy(NewMem,Mem,sizeof(T)*(s>>1));delete[] Mem;
		Mem=NewMem;End=Mem+l;MemEnd=Mem+(s>>1);
	}
	Vector(){Mem=new T[1];End=Mem;MemEnd=Mem+1;}
	void push_back(const T &x){
		if (End==MemEnd)Grow();*(End++)=x;
	}
	void pop_back(){
		--End;if (End-Mem<(MemEnd-Mem)>>2)Shrink();
	}
	it begin(){return Mem;}
	it end(){return End;}
	int size(){return End-Mem;}
	int capacity(){return MemEnd-Mem;}
	void resize(int _size){while (size()<_size)Grow();End=Mem+_size;}
	void clear(){End=Mem;}
	T& operator [](int id){return Mem[id];}
};
struct heap{
	typedef int value;
	Vector<value> a;int len;
	heap(){len=0;a.clear();a.push_back(0);}
	void up(int x){
		int i=x;value j;
		while (i>1&&a[i]<a[i>>1]){
			j=a[i];a[i]=a[i>>1];a[i>>1]=j;i>>=1;
		}
	}
	void down(int x){
		int i=x,j;value k;
		while (i<<1<=len){
			j=i; if (a[i<<1]<a[i])j=i<<1;
			if ((i<<1)+1<=len&&a[(i<<1)+1]<a[j])j=(i<<1)+1;
			if (j==i)break;
			k=a[i];a[i]=a[j];a[j]=k; i=j;
		}
	}
	void build(int *tmp,int n){
		len=n;a.resize(n+1);
		for (int i=n;i;--i)a[i]=tmp[i];
		for (int i=n>>1;i;--i)down(i);
	}
	void insert(value x){++len;a.push_back(x);up(len);}
	bool empty(){return len==0;}
	value top(){return a[1];}
	void pop(){a[1]=a[len--];a.pop_back();down(1);}
	void clear(){len=0;a.clear();a.push_back(0);}
};
template<size_t N,size_t M>
struct graph{
	#define new_arr(arr) arr=new int[n+5]
	#define oo (1<<29)
	int link[M],cost[M],next[M],son[N],*cap,*opp,*st,l;
	void add(int x,int y,int z=0){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
	void clear(){l=0;memset(son,-1,sizeof(son));}
	void set(int _n){n=_n;clear();}
	graph():n(0),cap(NULL),opp(NULL){}
	graph(int _n):n(_n),cap(NULL),opp(NULL){clear();}
	void addedge(int x,int y){add(x,y);}
	void addedge2(int x,int y){add(x,y);add(y,x);}
	void addedge(int x,int y,int z){add(x,y,z);}
	void addedge2(int x,int y,int z){add(x,y,z);add(y,x,z);}
	void addedge_f(int x,int y,int z){
		if (!cap)cap=new int[M],opp=new int[M];
		link[++l]=y;next[l]=son[x];son[x]=l;cap[l]=z;opp[l]=l+1;
		link[++l]=x;next[l]=son[y];son[y]=l;cap[l]=0;opp[l]=l-1;
	}
	void addedge_c(int x,int y,int z,int c){
		if (!cap)cap=new int[M],opp=new int[M];if (!st)st=new int[M];
		link[++l]=y;st[l]=x;next[l]=son[x];son[x]=l;cap[l]=z;cost[l]=c;opp[l]=l+1;
		link[++l]=x;st[l]=y;next[l]=son[y];son[y]=l;cap[l]=0;cost[l]=-c;opp[l]=l-1;
	}
	int *inq,*q,*d,*f,*pre,n,S,T;
	void spfa(int S,int *d){
		int h=0,t=1;new_arr(inq);new_arr(q);
		for (int i=0;i<=n;++i)d[i]=oo;
		for (int i=0;i<=n;++i)inq[i]=0;
		d[S]=0;q[1]=S;inq[S]=1;
		while (h!=t){
			h=h<n?h+1:1;int i=q[h];inq[i]=0;
			for (int p=son[i];p!=-1;p=next[p]){
				int j=link[p];
				if (d[i]+cost[p]<d[j]){
					d[j]=d[i]+cost[p];
					if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
				}
			}
		}
		delete[] inq;delete[] q;
	}
	struct d_node{
		int d,x;
		d_node(int _d,int _x){d=_d;x=_x;}
		bool operator <(const d_node &y)const{return d>y.d;}
	};
	void dijkstra(int S,int *dis){
		priority_queue<d_node> Q;
		bool *visit=new bool[n+5];
		for (int i=0;i<=n;++i)visit[i]=0,dis[i]=oo;
		Q.push(d_node(0,S));
		while (!Q.empty()){
			int d=Q.top().d,x=Q.top().x;visit[x]=1;dis[x]=d;
			for (int p=son[x];p!=-1;p=next[p])
				Q.push(d_node(d+cost[p],link[p]));
			while (!Q.empty()&&visit[Q.top().x])Q.pop();
		}
		delete[] visit;
	}
	int *dfn,*low,*stack,*instack,*num,top,D,now;
	void tarjan_f(int x){
		dfn[x]=low[x]=++D;stack[++top]=x;instack[x]=1;
		for (int p=son[x];p!=-1;p=next[p]){
			int j=link[p];
			if (!dfn[j]) tarjan_f(j),low[x]=min(low[x],low[j]);
			else if (instack[j]) low[x]=min(low[x],dfn[j]);
		}
		if (low[x]==dfn[x]){
			int k;++now;
			do k=stack[top--],instack[k]=0,num[k]=now; while (k!=x);
		}
	}
	void tarjan(int *_num){
		new_arr(dfn);new_arr(low);new_arr(stack);new_arr(instack);
		memset(dfn,0,sizeof(int)*(n+5));D=0;top=0;now=0;num=_num;
		for (int i=1;i<=n;++i)if (!dfn[i])tarjan(i);
		delete[] dfn;delete[] low;delete[] stack;delete[] instack;
	}
	int toposort(int *q){
		int *in;new_arr(in);
		int h=0,t=0;
		for (int i=1;i<=n;++i)in[i]=0;
		for (int i=1;i<=n;++i)
			for (int p=son[i];p!=-1;p=next[p])++in[link[p]];
		for (int i=1;i<=n;++i)if (!in[i])q[++t]=i;
		while (h<t){
			int i=q[++h];
			for (int p=son[i];p!=-1;p=next[p]){
				int j=link[p]; --in[j];
				if (!in[j])q[++t]=j;
			}
		}
		delete[] in;return t;
	}
	int find(int x){
		if (f[x]==x)return x;
		else return f[x]=find(f[x]);
	}
	struct k_edge{
		int x,y,z,id;
		bool operator <(const k_edge &y)const{return z<y.z;}
	};
	int kruskal(){
		k_edge *e=new k_edge[l+5];new_arr(f);
		int m=0,ans=0,num=0;
		for (int i=1;i<=n;++i)
			for (int p=son[i];p!=-1;p=next[p])
				e[++m].x=i,e[m].y=link[p],e[m].z=cost[p],e[m].id=m;
		std::sort(e+1,e+1+m);
		for (int i=1;i<=n;++i)f[i]=i;
		for (int i=1;i<=m;++i){
			int f1=find(e[i].x),f2=find(e[i].y);
			if (f1!=f2)f[f1]=f2,ans+=e[i].z,++num;
		}
		delete[] e;delete[] f;
		if (num==n-1)return ans;else return oo;
	}
	bool build(){
		int x,y,l=1,r=1;
		memset(d,-1,sizeof(int)*(n+5));
		q[1]=S;d[S]=0;
		while (l<=r){
			x=q[l++];
			for (int i=son[x];i!=-1;i=next[i]){
				y=link[i];
				if (cap[i]&&d[y]==-1){
					d[y]=d[x]+1;q[++r]=y;
					if (y==T)return 1;
				}
			}
		}
		return 0;
	}
	int find(int now,int flow){
		int ret,y,w=0;
		if (now==T)return flow;
		for (int i=son[now];i!=-1&&w<flow;i=next[i]){
			y=link[i];
			if (cap[i]&&d[y]==d[now]+1&&(ret=find(y,min(flow-w,cap[i]))))
				cap[i]-=ret,cap[opp[i]]+=ret,w+=ret;
		}
		if (!w)d[now]=-1;
		return w;
	}
	int maxflow(int _S,int _T){  //dinic
		int ans=0;new_arr(d);new_arr(q);S=_S;T=_T;
		while (build()) while (1){
			int flow=find(S,oo);
			if (!flow)break;
			ans+=flow;
		}
		delete[] d;delete[] q;
		return ans;
	}
	int spfa_c(){
		int h=0,t=1,i,j,p;
		for (int i=0;i<=n;++i)d[i]=oo;
		for (int i=0;i<=n;++i)inq[i]=0;
		d[S]=0;q[1]=S;inq[S]=1;
		while (h!=t){
			h=h<n?h+1:1;i=q[h];inq[i]=0;
			for (p=son[i];p!=-1;p=next[p]){
				j=link[p];
				if (d[i]+cost[p]<d[j]&&cap[p]){
					d[j]=d[i]+cost[p];pre[j]=p;
					if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
				}
			}
		}
		return d[T]<oo?1:0;
	}
	void update(int &maxflow,int &mincost){
		int p,flow=oo;
		for (p=T;p!=S;p=st[p]){
			p=pre[p];if (cap[p]<flow)flow=cap[p];
		}
		maxflow+=flow;
		for (p=T;p!=S;p=st[p]){
			p=pre[p];mincost+=cost[p]*flow;
			cap[p]-=flow;cap[opp[p]]+=flow;
		}
	}
	pair<int,int> costflow(int _S,int _T){
		int maxflow,mincost;S=_S;T=_T;new_arr(d);new_arr(q);new_arr(inq);new_arr(pre);
		maxflow=mincost=0;while (spfa_c())update(maxflow,mincost);
		delete[] d;delete[] q;delete[] inq;delete[] pre;
		return make_pair(maxflow,mincost);
	}
	template<int _N,int _M>
	void floyd(int (&a)[_N][_M]){
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)a[i][j]=oo;
		for (int i=1;i<=n;++i)a[i][i]=0;
		for (int x=1;x<=n;++x)
			for (int p=son[x],y=link[p];p!=-1;p=next[p],y=link[p])
				a[x][y]=min(a[x][y],cost[p]);
		for (int k=1;k<=n;++k)
			for (int i=1;i<=n;++i)
				for (int j=1;j<=n;++j)
					a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	}
	template<int _N,int _M>
	void Johnson(int (&a)[_N][_M]){
		if (n<1)return;
		int *_cost=new int[l];new_arr(d);spfa(1,d);
		memcpy(_cost,cost,sizeof(int)*l);
		for (int x=1;x<=n;++x)
			for (int p=son[x],y=link[p];p!=-1;p=next[p],y=link[p])
				cost[p]+=d[x]-d[y];
		for (int i=1;i<=n;++i){
			dijkstra(i,a[i]);
			for (int j=1;j<=n;++j)a[i][j]+=d[j]-d[i];
		}
		memcpy(cost,_cost,sizeof(int)*l);
		delete[] d;delete[] _cost;
	}
	#undef oo
	#undef new_arr
};
template<int S>
struct BitSet{
	#define W 5
	#define mask 31
	#define get_size(n) ((n)<1?0:((n)+mask)>>W)
	typedef unsigned int uint;
	uint a[get_size(S)];int size;
	void clear(){memset(a,0,sizeof(uint)*size);}
	BitSet():size(get_size(S)){clear();}
	BitSet(uint x):size(get_size(S)){clear();a[0]=x;}
	BitSet(const BitSet<S> &x):size(get_size(S)){*this=x;}
	void set(int x,int y){
		if (y<0||y>1){printf("error!\n");return;}
		int X=x>>W,Y=x&mask;
		if (y)a[X]|=1<<Y;else a[X]&=~(1<<Y);
	}
	uint find(uint x){uint X=x>>W,Y=x&mask;return (a[X]>>Y)&1u;}
	uint operator [](uint x){return find(x);}
	BitSet& operator =(const BitSet &y){
		memcpy(a,y.a,sizeof(uint)*size);
		//uint *startA=a,*startB=y.a,*endA=a+size;
		//while (startA!=endA)*startA++=*startB++;
		//for (int i=0;i<size;++i)a[i]=y.a[i];
		return *this;
	}
	BitSet<S> operator |(const BitSet<S> &y){
		BitSet<S> res;
		for (int i=0;i<size;++i)res.a[i]=a[i]|y.a[i];
		return res;
	}
	BitSet<S> operator &(const BitSet<S> &y){
		BitSet<S> res;
		for (int i=0;i<size;++i)res.a[i]=a[i]&y.a[i];
		return res;
	}
	BitSet<S> operator ^(const BitSet<S> &y){
		BitSet<S> res;
		for (int i=0;i<size;++i)res.a[i]=a[i]^y.a[i];
		return res;
	}
	BitSet<S> operator ~(){
		return BitSet<S>(*this).flip();
		/*BitSet<S> res;
		uint *startA=a,*startB=res.a,*endA=a+size;
		while (startA!=endA)*startB++=~*startA++;
		//for (int i=0;i<size;++i)res.a[i]=~a[i];
		return res;*/
	}
	BitSet<S>& operator =(const char *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!='0'&&s[i]!='1')break;
			int X=i>>W,Y=i&mask;
			if (s[i]=='1')a[X]|=1<<Y;
		}
		return *this;
	}
	BitSet<S>& operator =(const int *s){
		memset(a,0,sizeof(uint)*size);
		for (int i=0;i<S;++i){
			if (s[i]!=0&&s[i]!=1)break;
			int X=i>>W,Y=i&mask;
			if (s[i]==1)a[X]|=1<<Y;
		}
		return *this;
	}
	BitSet<S> operator <<(uint x){}
	BitSet<S> operator >>(uint x){}
	BitSet<S>& operator |=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA)*startA++|=*startB++;
		//for (int i=0;i<size;++i)a[i]|=y.a[i];
		return *this;
	}
	BitSet<S>& operator &=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA)*startA++&=*startB++;
		//for (int i=0;i<size;++i)a[i]&=y.a[i];
		return *this;
	}
	BitSet<S>& operator ^=(const BitSet<S> &y){
		uint *startA=a;const uint *startB=y.a,*endA=a+size;
		while (startA!=endA)*startA++^=*startB++;
		//for (int i=0;i<size;++i)a[i]^=y.a[i];
		return *this;
	}
	operator bool(){return count()>0;}
	BitSet<S>& flip(){
		for (uint *start=a,*end=a+size;start!=end;*start=~*start++);
		return *this;
	}
	//void flip(){*this=~*this;}
	void flip(int x){a[x>>W]^=1<<(x&mask);}
	uint popcount(uint x)const{
		x=(x&0x55555555)+((x>>1)&0x55555555);
		x=(x&0x33333333)+((x>>2)&0x33333333);
		x=(x&0x0F0F0F0F)+((x>>4)&0x0F0F0F0F);
		x=(x&0x00FF00FF)+((x>>8)&0x00FF00FF);
		x=(x&0x0000FFFF)+((x>>16)&0x0000FFFF);
		return x;
	}
	int count(){
		int res=0;
		if (S&mask)a[size-1]&=(1<<(S&mask))-1;
		for (int i=0;i<size;++i)res+=popcount(a[i]);
		return res;
	}
	void reset(){
		memset(a,0,sizeof(uint)*size);
		//for (int i=0;i<size;++i)a[i]=0;
	}
	uint to_uint(){
		if (S&mask)a[size-1]&=(1<<(S&mask))-1;
		return a[0];
	}
	void print(){
		for (int i=0;i<size;++i)
			for (int j=0;j<=mask&&(i<<W)+j+1<=S;++j)printf("%d",(a[i]>>j)&1);
		printf("\n");
	}
	#undef mask
	#undef W
	#undef get_size
};
template<class Tkey> inline size_t Gethash(const Tkey &x){return x;}
template<class Tkey,class Tvalue,size_t (*gethash)(const Tkey&)=Gethash>
struct Hash{
	Tkey *key; Tvalue *value;
	int *v,*next,len,P,size;
	void build(int Len=9,int p=11){  //len个数  hashsize=p
		P=p;len=0;size=Len;++Len; key=new Tkey[Len];
		v=new int[p];memset(v,0,sizeof(int)*p);
		value=new Tvalue[Len];memset(value,0,sizeof(Tvalue)*Len);
		next=new int[Len];memset(next,0,sizeof(int)*Len);
	}
	Hash(int Len=0,int p=11){if (Len==0)return;build(Len,p);}
	void clear(){len=0;memset(v,0,sizeof(int)*P);}
	void insert(const Tkey &x,const Tvalue &y=0){
		size_t x1=gethash(x)%P;
		key[++len]=x;value[len]=y;
		next[len]=v[x1];v[x1]=len;
	}
	void del(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (int i=v[x1],pre=0;i;pre=i,i=next[i])
			if (key[i]==x)
				if (pre==0)v[x1]=next[i];
				else next[pre]=next[i];
	}
	Tvalue find(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (int i=v[x1];i;i=next[i])
			if (key[i]==x)return value[i];
		return -1;
	}
	Tvalue& find_r(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (int i=v[x1];i;i=next[i])
			if (key[i]==x)return value[i];
		Tvalue *null=NULL;return *null;
	}
	void inc(const Tkey &x,const Tvalue &y=1){
		size_t x1=gethash(x)%P;
		for (int i=v[x1];i;i=next[i])
			if (key[i]==x){value[i]+=y;return;}
	}
	Tvalue& operator [](const Tkey &x){
		Tvalue& tmp=find_r(x);
		if (&tmp==0)insert(x);return find_r(x);
	}
	Tvalue id(const Tkey &x){return find(x);}
};
class Int{
	#define BASE 1000000000
	public:
	typedef long long value;
	void New(size_t l){
		if (a!=NULL)delete[] a;a=new value[l];
		len=1;a[0]=0;sign=1;
	}
	Int():a(NULL),base(BASE){New(1);}
	Int(value x):a(NULL),base(BASE){New(1);*this=x;}
	Int(const Int &B):a(NULL),base(BASE){New(1);*this=B;}
	~Int(){delete[] a;}
	Int& operator =(value x){
		size_t l=1;for (value x1=max(x,-x);x1>=base;++l,x1/=base);New(l);
		if (x<0)x=-x,sign=0;else sign=1;
		len=0;while (x)a[len++]=x%base,x/=base;
		if (!len)a[len++]=0;
		return *this;
	}
	Int& operator =(const Int &A){
		New(A.len);len=A.len;memcpy(a,A.a,sizeof(value)*len);
		base=A.base;sign=A.sign;return *this;
	}
	friend Int operator -(Int A){A.sign=1-A.sign;return A;}
	bool operator !(){if (len==1&&a[0]==0)return 1;else return 0;}
	friend Int operator +(Int A,Int B){
		if (A.sign!=B.sign){B.sign=1-B.sign;return A-B;}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		Int res;res.set_base(A.base); int len=A.len>B.len?A.len:B.len;
		res.New(len+1);res.sign=A.sign;
		memset(res.a,0,(len+1)*sizeof(value));
		for (int i=0;i<len;++i){
			if (i<A.len)res.a[i]+=A.a[i];
			if (i<B.len)res.a[i]+=B.a[i];
		}
		for (int i=0;i<len;++i)
			if (res.a[i]>=res.base)++res.a[i+1],res.a[i]-=res.base;
		if (res.a[len])res.len=len+1;else res.len=len;
		return res;
	}
	friend Int operator -(Int A,Int B){
		if (A.sign!=B.sign){B.sign=1-B.sign;return A+B;}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (small(A,B))swap(A,B),A.sign=1-A.sign;
		Int res;res.set_base(A.base); int len=A.len>B.len?A.len:B.len;
		res.New(len);res.sign=A.sign;
		memset(res.a,0,len*sizeof(value));
		for (int i=0;i<len;++i){
			if (i>=B.len)res.a[i]+=A.a[i];
			else res.a[i]+=A.a[i]-B.a[i];
			if (res.a[i]<0)res.a[i]+=res.base,--res.a[i+1];
		}
		while (len>1&&!res.a[len-1])--len;res.len=len;
		return res;
	}
	friend Int operator *(Int A,Int B){
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		Int res;res.set_base(A.base); int len=A.len+B.len;
		res.New(len);res.sign=(A.sign==B.sign);
		memset(res.a,0,len*sizeof(value));
		for (int i=0;i<A.len;++i)
			for (int j=0;j<B.len;++j){
				res.a[i+j]+=A.a[i]*B.a[j];
				res.a[i+j+1]+=res.a[i+j]/res.base;
				res.a[i+j]%=res.base;
			}
		/*
		for (int i=0;i<A.len;++i)
			for (int j=0;j<B.len;++j)res.a[i+j]+=A.a[i]*B.a[j];
		for (int i=0;i<len-1;++i)res.a[i+1]+=res.a[i]/res.base,res.a[i]%=res.base;
		*/
		while (len>1&&!res.a[len-1])--len;res.len=len;
		return res;
	}
	friend pair<Int,Int> divide(Int A,Int B){
		if (!B){puts("error:div zero!");for (;;);}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (small(A,B))return make_pair(Int(0),A);
		Int C,D;C.set_base(A.base);D.set_base(A.base);C.New(A.len);C.len=A.len;
		for (int i=A.len-1;i>=0;--i){
			C.a[i]=0;D=D*D.base;D.a[0]=A.a[i];
			int l=0,r=A.base-1,mid;
			while (l<r){
				mid=(l+r+1)>>1;
				if (small(B*mid,D+1))l=mid;
					else r=mid-1;
			}
			C.a[i]=l;D=D-B*l;
		}
		C.sign=(A.sign==B.sign);D.sign=A.sign;
		while (C.len>1&&!C.a[C.len-1])--C.len;
		return make_pair(C,D);
	}
	Int operator /(value x){
		if (!x){puts("error:div zero!");for (;;);}
		value d=0;Int res;res.set_base(base);res.New(len);res.len=len;
		if (x<0)x=-x,res.sign=(sign==0);
		else res.sign=(sign==1);
		for (int i=len-1;i>=0;--i)
			d=d*base+a[i],res.a[i]=d/x,d%=x;
		while (res.len>1&&!res.a[res.len-1])--res.len;
		return res;
	}
	Int operator %(value x){
		value d=0;if (x<0)x=-x;
		for (int i=len-1;i>=0;--i)d=(d*base+a[i])%x;
		return d;
	}
	friend Int abs(Int A){A.sign=1;return A;}
	friend bool small(Int A,Int B){
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (A.len!=B.len)return A.len<B.len;
		for (int i=A.len-1;i>=0;--i)
			if (A.a[i]!=B.a[i])return A.a[i]<B.a[i];
		return 0;
	}
	friend bool operator <(Int A,Int B){
		if (A.sign!=B.sign)return A.sign<B.sign;
		return small(A,B);
	}
	friend bool operator ==(Int A,Int B){
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (A.sign!=B.sign||A.len!=B.len)return 0;
		for (int i=0;i<A.len;++i)if (A.a[i]!=B.a[i])return 0;
		return 1;
	}
	friend bool operator !=(Int A,Int B){return !(A==B);}
	friend bool operator >(Int A,Int B){return !(A<B||A==B);}
	friend bool operator <=(Int A,Int B){return A<B||A==B;}
	friend bool operator >=(Int A,Int B){return A>B||A==B;}
	Int operator /(Int B){return divide(*this,B).first;}
	Int operator %(Int B){return divide(*this,B).second;}
	Int& operator +=(Int B){*this=*this+B;return *this;}
	Int& operator -=(Int B){*this=*this-B;return *this;}
	Int& operator *=(Int B){*this=*this*B;return *this;}
	Int& operator /=(Int B){*this=*this/B;return *this;}
	Int& operator %=(Int B){*this=*this%B;return *this;}
	Int& operator ++(){*this=*this+1;return *this;}
	Int& operator --(){*this=*this-1;return *this;}
	Int operator ++(int){Int res(*this);*this=*this+1;return res;}
	Int operator --(int){Int res(*this);*this=*this-1;return res;}
	Int operator +(value x){return *this+Int(x);}
	Int operator -(value x){return *this-Int(x);}
	Int operator *(value x){return *this*Int(x);}
	//Int operator /(value x){Int T;T=x;return *this/T;}
	//Int operator %(value x){Int T;T=x;return *this%T;}
	Int& operator *=(value x){*this=*this*x;return *this;}
	Int& operator +=(value x){*this=*this+x;return *this;}
	Int& operator -=(value x){*this=*this-x;return *this;}
	Int& operator /=(value x){*this=*this/x;return *this;}
	Int& operator %=(value x){*this=*this%x;return *this;}
	bool operator ==(value x){return *this==Int(x);}
	bool operator !=(value x){return *this!=Int(x);}
	bool operator <=(value x){return *this<=Int(x);}
	bool operator >=(value x){return *this>=Int(x);}
	bool operator <(value x){return *this<Int(x);}
	bool operator >(value x){return *this>Int(x);}
	void to_arr(char *c){
		char *c1=c;
		for (int i=0;i<len-1;++i)
			for (value x=a[i],b=base/10;b>=1;b/=10)*c1++='0'+x%10,x/=10;
		for (value x=a[len-1];x>0;x/=10)*c1++='0'+x%10;
		if (len==1&&a[len]==0)*c1++='0';
		if (sign==0)*c1++='-';*c1=0;reverse(c,c1);
	}
	void from_arr(char *c){
		size_t base_l=get_basel(),b=1;int cl=strlen(c);value x=0;
		New((cl+base_l-1)/base_l);len=0;
		if (*c=='-')sign=0,++c,--cl;else sign=1;
		while (--cl>=0){
			x+=(c[cl]-'0')*b;b*=10;if (b==base)a[len++]=x,x=0,b=1;
		}
		if (!len||x)a[len++]=x;
		while (len>1&&!a[len-1])--len;
	}
	void set_base(int _base){
		if (base==_base)return;
		char *c=new char[len*get_basel()];
		to_arr(c);base=_base;from_arr(c);
		delete[] c;
	}
	void set_basel(int _l){
		size_t _base=1;while (_l--)_base*=10;set_base(_base);
	}
	void read(){
		vector<char> s;char ch;
		scanf(" %c",&ch);if (ch=='-')s.push_back('-'),ch=getchar();
		for (;ch>='0'&&ch<='9';ch=getchar())s.push_back(ch);
		char *c=new char[s.size()+1];
		for (int i=0;i<s.size();++i)c[i]=s[i];c[s.size()]=0;
		from_arr(c);delete[] c;
	}
	void print(){
		if (!sign)putchar('-');
		printf("%d",int(a[len-1]));
		for (int i=len-2;i>=0;--i){
			for (int j=base/10;j>=10;j/=10)
				if (a[i]<j)putchar('0');
					else break;
			printf("%d",(int)a[i]);
		}
	}
	void println(){print();putchar('\n');}
	private:
	value *a,base;int len;bool sign;  //0="-"
	size_t get_basel(){
		size_t res=0;for (int b=base/10;b>=1;b/=10,++res);
		return res;
	}
	#undef BASE
};
namespace fastIO{
	#define BUF_SIZE 100000
	#define OUT_SIZE 100000
	#define ll long long
	//fread->read
	bool IOerror=0;
	inline char nc(){
		static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
		if (p1==pend){
			p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
			if (pend==p1){IOerror=1;return -1;}
			//{printf("IO error!\n");system("pause");for (;;);exit(0);}
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void read(int &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	inline void read(ll &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (ch=='.'){
			double tmp=1; ch=nc();
			for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
		}
		if (sign)x=-x;
	}
	inline void read(char *s){
		char ch=nc();
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
		*s=0;
	}
	inline void read(char &c){
		for (c=nc();blank(c);c=nc());
		if (IOerror){c=-1;return;}
	}
	//getchar->read
	inline void read1(int &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (bo)x=-x;
	}
	inline void read1(ll &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (bo)x=-x;
	}
	inline void read1(double &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (ch=='.'){
			double tmp=1;
			for (ch=getchar();ch>='0'&&ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
		}
		if (bo)x=-x;
	}
	inline void read1(char *s){
		char ch=getchar();
		for (;blank(ch);ch=getchar());
		for (;!blank(ch);ch=getchar())*s++=ch;
		*s=0;
	}
	inline void read1(char &c){for (c=getchar();blank(c);c=getchar());}
	//scanf->read
	inline void read2(int &x){scanf("%d",&x);}
	inline void read2(ll &x){
		#ifdef _WIN32
			scanf("%I64d",&x);
		#else
		#ifdef __linux
			scanf("%lld",&x);
		#else
			puts("error:can't recognize the system!");
		#endif
		#endif
	}
	inline void read2(double &x){scanf("%lf",&x);}
	inline void read2(char *s){scanf("%s",s);}
	inline void read2(char &c){scanf(" %c",&c);}
	inline void readln2(char *s){gets(s);}
	//fwrite->write
	struct Ostream_fwrite{
		char *buf,*p1,*pend;
		Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
		void out(char ch){
			if (p1==pend){
				fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
			}
			*p1++=ch;
		}
		void print(int x){
			static char s[15],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1);
		}
		void println(int x){
			static char s[15],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1); out('\n');
		}
		void print(ll x){
			static char s[25],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1);
		}
		void println(ll x){
			static char s[25],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1); out('\n');
		}
		void print(double x,int y){
			static ll mul[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,
				1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
				100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL};
			if (x<-1e-12)out('-'),x=-x;x*=mul[y];
			ll x1=(ll)floor(x); if (x-floor(x)>=0.5)++x1;
			ll x2=x1/mul[y],x3=x1-x2*mul[y]; print(x2);
			if (y>0){out('.'); for (int i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
		}
		void println(double x,int y){print(x,y);out('\n');}
		void print(char *s){while (*s)out(*s++);}
		void println(char *s){while (*s)out(*s++);out('\n');}
		void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
		~Ostream_fwrite(){flush();}
	}Ostream;
	inline void print(int x){Ostream.print(x);}
	inline void println(int x){Ostream.println(x);}
	inline void print(char x){Ostream.out(x);}
	inline void println(char x){Ostream.out(x);Ostream.out('\n');}
	inline void print(ll x){Ostream.print(x);}
	inline void println(ll x){Ostream.println(x);}
	inline void print(double x,int y){Ostream.print(x,y);}
	inline void println(double x,int y){Ostream.println(x,y);}
	inline void print(char *s){Ostream.print(s);}
	inline void println(char *s){Ostream.println(s);}
	inline void println(){Ostream.out('\n');}
	inline void flush(){Ostream.flush();}
	//puts->write
	char Out[OUT_SIZE],*o=Out;
	inline void print1(int x){
		static char buf[15];
		char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
		while(x)*p1++=x%10+'0',x/=10;
		while(p1--!=buf)*o++=*p1;
	}
	inline void println1(int x){print1(x);*o++='\n';}
	inline void print1(ll x){
		static char buf[25];
		char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
		while(x)*p1++=x%10+'0',x/=10;
		while(p1--!=buf)*o++=*p1;
	}
	inline void println1(ll x){print1(x);*o++='\n';}
	inline void print1(char c){*o++=c;}
	inline void println1(char c){*o++=c;*o++='\n';}
	inline void print1(char *s){while (*s)*o++=*s++;}
	inline void println1(char *s){print1(s);*o++='\n';}
	inline void println1(){*o++='\n';}
	inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
	struct puts_write{
		~puts_write(){flush1();}
	}_puts;
	inline void print2(int x){printf("%d",x);}
	inline void println2(int x){printf("%d\n",x);}
	inline void print2(char x){printf("%c",x);}
	inline void println2(char x){printf("%c\n",x);}
	inline void print2(ll x){
		#ifdef _WIN32
			printf("%I64d",x);
		#else
		#ifdef __linux
			printf("%lld",x);
		#else
			puts("error:can't recognize the system!");
		#endif
		#endif
	}
	inline void println2(ll x){print2(x);printf("\n");}
	inline void println2(){printf("\n");}
	#undef ll
	#undef OUT_SIZE
	#undef BUF_SIZE
};
using namespace fastIO;
#define J (")
string name="", in=".in", out=".out";
const int N=100005;
int main()
{
	//freopen((name+in).c_str(),"r",stdin);
	//freopen((name+out).c_str(),"w",stdout);
#ifndef ONLINE_JUDGE
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
#endif
	
	system("pause");for (;;);
	return 0;
}


