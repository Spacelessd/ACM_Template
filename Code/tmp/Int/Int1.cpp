#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
class Int{
	//#define BASE 1000000000
	#define BASE 10
	public:
	typedef long long value;
	void New(size_t l){
		if (a!=NULL)delete[] a;a=new value[len];
		len=1;a[0]=0;sign=1;
	}
	Int():a(NULL),base(BASE){New(1);}
	Int(value x):a(NULL),base(BASE){New(1);*this=x;}
	Int(const Int &B):a(NULL),base(BASE){New(1);*this=B;}
	~Int(){delete[] a;}
	Int& operator =(value x){
		if (x<0)x=-x,sign=0;else sign=1;
		size_t l=1;for (value x1=x;x>=base;++l,x/=base);New(l);
		while (x)a[len++]=x%base,x/=base;
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
		Int res;res.set_base(A.base);res.sign=A.sign;
		size_t len=A.len>B.len?A.len:B.len;res.New(len+1);
		memset(res.a,0,(len+1)*sizeof(value));
		for (int i=0;i<len;++i){
			if (i<=A.len)res.a[i]+=A.a[i];
			if (i<=B.len)res.a[i]+=B.a[i];
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
		Int C,D;C.set_base(A.base);D.set_base(A.base);C.New(A.len);
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
		for (int i=len-1;i>=0;--i){
			d=d*base+a[i];res.a[i]=d/x;d%=x;
		}
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
	Int operator ++(int){Int res=*this;*this=*this+1;return res;}
	Int operator --(int){Int res=*this;*this=*this-1;return res;}
	Int operator +(value x){Int T;T=x;return *this+T;}
	Int operator -(value x){Int T;T=x;return *this-T;}
	Int operator *(value x){Int T;T=x;return *this*T;}
	//Int operator /(value x){Int T;T=x;return *this/T;}
	//Int operator %(value x){Int T;T=x;return *this%T;}
	Int& operator *=(value x){*this=*this*x;return *this;}
	Int& operator +=(value x){*this=*this+x;return *this;}
	Int& operator -=(value x){*this=*this-x;return *this;}
	Int& operator /=(value x){*this=*this/x;return *this;}
	Int& operator %=(value x){*this=*this%x;return *this;}
	bool operator ==(value x){Int T;T=x;return *this==T;}
	bool operator !=(value x){Int T;T=x;return *this!=T;}
	bool operator <=(value x){Int T;T=x;return *this<=T;}
	bool operator >=(value x){Int T;T=x;return *this>=T;}
	bool operator <(value x){Int T;T=x;return *this<T;}
	bool operator >(value x){Int T;T=x;return *this>T;}
	void to_arr(char *c){
		char *c1=c;
		for (int i=0;i<len-1;++i){
			value x=a[i];
			for (int b=base/10;b>=1;b/=10)*c1++='0'+x%10,x/=10;
		}
		for (value x=a[len-1];x>0;x/=10)*c1++='0'+x%10;
		if (len==1&&a[len]==0)*c1++='0';
		if (sign==0)*c1++='-';*c1=0;
		reverse(c,c1);
	}
	void from_arr(char *c){
		size_t base_l=get_basel(),b=1,cl=strlen(c);value x=0;
		New((cl+base_l-1)/base_l);set_base(BASE);len=0;
		if (*c=='-')sign=0,++c;else sign=1;
		while (--cl>=0){
			x+=(c[cl]-'0')*b;b*=10;if (b==base)a[++len]=x,x=0,b=1;
		}
		if (!len||x)a[len++]=x;
	}
	void set_base(int _base){
		char *c=new char[len*get_basel()];
		to_arr(c);base=_base;from_arr(c);
		delete[] c;
	}
	void set_basel(int _l){
		size_t l=0,_base=1;while (_l)_base*=10;
		set_base(_base);
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
	value *a,base;size_t len;bool sign;  //0="-"
	size_t get_basel(){
		size_t res=0;for (int b=base/10;b>=1;b/=10,++res);
		return res;
	}
	#undef BASE
};
Int a,b,c;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//b=1;c=2;
	//a=b+c;
	//a.println();
	system("pause");
	return 0;
}


