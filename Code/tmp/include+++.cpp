#include<algorithm>
#include<assert.h>
#include<bitset>
#include<complex>
#include<ctype.h>
#include<deque>
#include<functional>
#include<iomanip>
#include<iostream>
#include<limits.h>
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
//#include<windows.h>
using namespace std;
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
#define maX(a,b) ((a)>(b)?(a):(b))
#define miN(a,b) ((a)<(b)?(a):(b))
#define abS(x) ((x)<0?-(x):(x))
#define Display(A,n,m){ \
	rep(i,n){ \
        rep(j,m)cout<<A[i][j]<<" "; \
		cout<<endl; \
	} \
}
#pragma comment(linker,"/STACK:36777216")
#pragma GCC optimize ("O2")
#define Ruby system("ruby main.rb")
#define Haskell system("runghc main.hs")
#define Python system("py main.py")
#define Pascal system("fpc main.pas")
const int inf=~0U>>1;
const int MOD=1000000007;
const long long linf=(long long)1e18;
const double eps=1e-6,PI=4*atan(1);
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
template <class T>T Min(const T &a,const T &b){return a<b?a:b;}
template <class T>T Max(const T &a,const T &b){return a>b?a:b;}
template<class T> inline void checkMin(T &a,const T b){if (b<a)a=b;}
template<class T> inline void checkMax(T &a,const T b){if (b>a)a=b;}
template<class T,class C> inline void checkMin(T &a,const T b,C c){if (c(b,a))a=b;}
template<class T,class C> inline void checkMax(T &a,const T b,C c){if (c(a,b))a=b;}
template<class T> inline T Min(const T &a,const T &b,const T &c){return min(min(a,b),c);}
template<class T> inline T Max(const T &a,const T &b,const T &c){return max(max(a,b),c);}
template<class T> inline T Min(const T &a,const T &b,const T &c,const T &d){return min(min(a,b),min(c,d));}
template<class T> inline T Max(const T &a,const T &b,const T &c,const T &d){return max(max(a,b),max(c,d));}
template<class T> inline T SQR(const T &a){return a*a;}
template<class T> inline T cub(const T &a){return a*a*a;}
inline int Ceil(int x,int y){return (x-1)/y+1;}
inline bool _1(int x,int i){return x&1<<i;}
inline bool _1(ll x,int i){return x&1LL<<i;}
inline ll _1(int i){return 1LL<<i;}
template<class T> inline T low_bit(T x){return x&-x;}
template<class T> inline T high_bit(T x) {
	T p=low_bit(x); while (p!=x)x-=p,p=low_bit(x); return p;
}
template<class T> inline T cover_bit(T x){
	T p=1; while (p<x)p<<=1;return p;
}
inline int count_bits(int x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
inline int count_bits(ll x){
	x=(x&0x5555555555555555LL)+((x&0xaaaaaaaaaaaaaaaaLL)>>1);
	x=(x&0x3333333333333333LL)+((x&0xccccccccccccccccLL)>>2);
	x=(x&0x0f0f0f0f0f0f0f0fLL)+((x&0xf0f0f0f0f0f0f0f0LL)>>4);
	x=(x&0x00ff00ff00ff00ffLL)+((x&0xff00ff00ff00ff00LL)>>8);
	x=(x&0x0000ffff0000ffffLL)+((x&0xffff0000ffff0000LL)>>16);
	x=(x&0x00000000ffffffffLL)+((x&0xffffffff00000000LL)>>32);
	return x;
}
int reverse_bits(int x){
	x=((x>>1)&0x55555555)|((x<<1)&0xaaaaaaaa);
	x=((x>>2)&0x33333333)|((x<<2)&0xcccccccc);
	x=((x>>4)&0x0f0f0f0f)|((x<<4)&0xf0f0f0f0);
	x=((x>>8)&0x00ff00ff)|((x<<8)&0xff00ff00);
	x=((x>>16)&0x0000ffff)|((x<<16)&0xffff0000);
	return x;
}
ll reverse_bits(ll x){
	x=((x>>1)&0x5555555555555555LL)|((x<<1)&0xaaaaaaaaaaaaaaaaLL);
	x=((x>>2)&0x3333333333333333LL)|((x<<2)&0xccccccccccccccccLL);
	x=((x>>4)&0x0f0f0f0f0f0f0f0fLL)|((x<<4)&0xf0f0f0f0f0f0f0f0LL);
	x=((x>>8)&0x00ff00ff00ff00ffLL)|((x<<8)&0xff00ff00ff00ff00LL);
	x=((x>>16)&0x0000ffff0000ffffLL)|((x<<16)&0xffff0000ffff0000LL);
	x=((x>>32)&0x00000000ffffffffLL)|((x<<32)&0xffffffff00000000LL);
	return x;
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
template<class T> inline T gcd(T x,T y){return !y?x:gcd(y,x%y);}
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}
inline int rand32(){return (bool(rand()&1)<<30)|(rand()<<15)+rand();}
inline int random32(int l,int r){return rand32()%(r-l+1)+l;}
inline int random(int l,int r){return rand()%(r-l+1)+l;}
struct point{
	static const double eps=1e-10;
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator +(const point &b)const{return point(x+b.x,y+b.y);}
	point operator -(const point &b)const{return point(x-b.x,y-b.y);}
	double operator *(const point &b)const{return x*b.x+y*b.y;}  //dot
	double operator ^(const point &b)const{return x*b.y-b.x*y;}  //cha
	point operator *(double d)const{return point(x*d,y*d);}
	friend point operator *(double d,const point &x){return point(x.x*d,x.y*d);}
	point operator /(double d)const{return point(x/d,y/d);}
	friend point operator /(double d,const point &x){return point(x.x/d,x.y/d);}
	point operator -()const{return point(-x,-y);}
	bool operator ==(const point &b)const{return fabs(x-b.x)<eps&&fabs(y-b.y)<eps;}
	bool operator !=(const point &b)const{return !(*this==b);}
};
struct point3D{
	double x,y,z;
	point3D(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
	friend point3D operator +(const point3D &x,const point3D &b){return point3D(x.x+b.x,x.y+b.y,x.z+b.z);}
	friend point3D operator -(const point3D &x,const point3D &b){return point3D(x.x-b.x,x.y-b.y,x.z-b.z);}
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
inline int sgn(double x){return fabs(x)<eps?0:(x<0?-1:1);}
inline double dist(const point &x,const point &y){return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));}
inline double cross(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
inline double dot(double x1,double y1,double x2,double y2){return x1*x2-y1*y2;}
double (*cha)(double,double,double,double)=cross;
inline point3D cross(const point3D &x,const point3D &y){return point3D(x.y*y.z-y.y*x.z,x.z*y.x-y.z*x.x,x.x*y.y-y.x*x.y);}
inline double dot(const point3D &x,const point3D &y){return x.x*y.x+x.y*y.y+x.z*y.z;}
inline double vlen(const point3D &x){return sqrt(x.x*x.x+x.y*x.y+x.z*x.z);}
inline double area(const point3D &a,const point3D &b,const point3D &c){return vlen(cross(b-a,c-a));}
inline double volume(const point3D &a,const point3D &b,const point3D &c,const point3D &d){return dot(cross(b-a,c-a),d-a);}
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
	double fi,cosfi,norm;
	double sx=p1.x-o.x,sy=p1.y-o.y,ex=p2.x-o.x,ey=p2.y-o.y;
	cosfi=sx*ex+sy*ey;
	norm=(sx*sx+ey*ey)*(ex*ex+ey*ey);
	cosfi/=sqrt(norm);
	if (cosfi>=1.0)return 0;
	if (cosfi<=-1.0)return -PI;
	fi=acos(cosfi);
	if (cha(sx,sy,ex,ey)>0)return fi;
		else return -fi;
}
inline int direction(const point &p1,const point &p2,const point &p3){return sgn((p3-p1)^(p2-p1));}
inline int cross(const line &a,const line &b){
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
	angle+=2*M_PI;
	return angle-floor(angle/(2.0*M_PI))*2.0*M_PI;
}
inline double angle(const circle &O,const point &x){  //极角 
	double angle=asin(x.y-O.y);
	if (x.x-O.x<0)angle=M_PI-angle;
	return angle;
}
inline point to_point(const circle &O,double angle){
	return point(O.x+O.r*cos(angle),O.y+O.r*sin(angle));
}
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
			if (y>0){out('.'); for (size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
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


