#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
class Int{
	#define BASE 100000000
	public:
	typedef long long value;
	void New(size_t l){
		if (a!=NULL)delete[] a;a=new value[len];
	}
	void clear(){New(1);len=1;a[0]=0;sign=1;}
	Int():a(NULL),base(BASE){clear();}
	Int(value x):a(NULL),base(BASE){clear();*this=x;}
	~Int(){delete[] a;}
	Int& operator =(const Int &A){
		New(A.len);len=A.len;memcpy(a,A.a,sizeof(value)*len);
		base=A.base;sign=A.sign;return *this;
	}
	friend Int operator -(Int A){
		A.sign=1-A.sign;return A;
	}
	friend Int operator +(Int A,Int B){
		if (A.sign!=B.sign){B.sign=1-B.sign;return A-B;}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		Int res;res.set_base(A.base);res.sign=A.sign;
		size_t len=A.len>B.len?A.len:B.len;res.New(len+1);
		memset(res.a,0,(len+1)*sizeof(value));
		for (int i=0;i<len;++i){
			if (i<=A.len)res.a[i]+=A.a[i];
			if (i<=B.len)res.a[i]+=B.a[i];
		}
		for (int i=0;i<len;++i)
			while (res.a[i]>=res.base)++res.a[i+1],res.a[i]-=res.base;
		if (res.a[len])res.len=len+1;else res.len=len;
		return res;
	}
	friend Int operator -(Int A,Int B){
		if (A.sign!=B.sign){B.sign=1-B.sign;return A+B;}
		if (A.base!=B.base)
			if (A.base>B.base)B.set_base(A.base);
			else A.set_base(B.base);
		if (small(A,B))swap(A,B),A.sign=1-A.sign;
		Int res;res.set_base(A.base);res.sign=A.sign;
		size_t len=A.len>B.len?A.len:B.len;res.New(len);
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
		Int res;res.set_base(A.base);res.sign=(A.sign==B.sign);
		size_t len=A.len+B.len;res.New(len);
		memset(res.a,0,len*sizeof(value));
		for (int i=0;i<A.len;++i)
			for (int j=0;j<B.len;++j){
				res.a[i+j]+=A.a[i]*B.a[j];
				res.a[i+j+1]+=res.a[i+j]/res.base;
				res.a[i+j]%=res.base;
			}
		while (len>1&&!res.a[len-1])--len;res.len=len;
		return res;
	}
	friend pair<Int,Int> divide(Int A,Int B){
		size_t len=A.len;Int C,D;C.set_base(A.base);D.set_base(A.base);
		for (int i=len-1;i>=0;--i){
			C.a[i]=0;D=D*D.base;D.a[0]=A.a[i];
			int l=0,r=A.base-1,mid;
			while (l<r){
				mid=(l+r+1)>>1;
				if (B*mid<=D)l=mid;
					else r=mid-1;
			}
			C.a[i]=l;D-=B*l;
		}
		while (len>1&&!C.a[len-1])--len;C.len=len;
		return make_pair(C,D);
	}
	Int operator /(value x){
		value d=0;Int res;
		for (int i=len;i;--i){
			d=d*base+a[i];
			res.a[i]=d/x;d%=x;
		}
		res.len=len;
		while (res.len>1&&!res.a[res.len-1])--res.len;
		return res;
	}
	Int operator %(value x){
		value d=0;
		for (int i=len;i;--i)d=(d*base+a[i])%x;
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
	Int operator /(Int &B){return divide(*this,B).first;}
	Int operator %(Int &B){return divide(*this,B).second;}
	Int &operator +=(Int &B){*this=*this+B;return *this;}
	Int &operator -=(Int &B){*this=*this-B;return *this;}
	Int &operator *=(Int &B){*this=*this*B;return *this;}
	Int operator /=(Int &B){*this=*this/B;return *this;}
	Int operator %=(Int &B){*this=*this%B;return *this;}
	Int &operator ++(){Int T;T=1;*this=*this+T;return *this;}
	Int &operator --(){Int T;T=1;*this=*this-T;return *this;}
	Int operator ++(int){Int T,res=*this;T=1;*this=*this+T;return res;}
	Int operator --(int){Int T,res=*this;T=1;*this=*this-T;return res;}
	Int operator +(value x){Int T;T=x;return *this+T;}
	Int operator -(value x){Int T;T=x;return *this-T;}
	Int operator *(value x){Int T;T=x;return *this*T;}
	//Int operator /(value x){Int T;T=x;return *this/T;}
	//Int operator %(value x){Int T;T=x;return *this%T;}
	Int operator *=(value x){*this=*this*x;return *this;}
	Int operator +=(value x){*this=*this+x;return *this;}
	Int operator -=(value x){*this=*this-x;return *this;}
	Int operator /=(value x){*this=*this/x;return *this;}
	Int operator %=(value x){*this=*this%x;return *this;}
	bool operator ==(value x){Int T;T=x;return *this==T;}
	bool operator !=(value x){Int T;T=x;return *this!=T;}
	bool operator <=(value x){Int T;T=x;return *this<=T;}
	bool operator >=(value x){Int T;T=x;return *this>=T;}
	bool operator <(value x){Int T;T=x;return *this<T;}
	bool operator >(value x){Int T;T=x;return *this>T;}
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
	size_t to_arr(char *c){
		char *c1=c;
		for (int i=0;i<len-1;++i){
			
		}
		return c1-c;
	}
	void from_arr(char *c){
		
	}
	void set_base(int _base){
		int l=0,i;for (i=base;i>=10;++l,i/=10);
		char *c=new char[len*l];
		to_arr(c);for (base=1,i=1;i<=_l;++i,base*=10);
		from_arr(c);
		delete[] c;
	}
	void set_basel(int _l){
		int l=0,i;for (i=base;i>=10;++l,i/=10);
		char *c=new char[len*l];
		to_arr(c);for (base=1,i=1;i<=_l;++i,base*=10);
		from_arr(c);
		delete[] c;
	}
	void print(){
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
	value *a,base;size_t len;bool sign;  //0="-"
	#undef BASE
}a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	a.println();
	system("pause");
	return 0;
}


