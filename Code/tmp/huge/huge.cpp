#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
struct huge{
	#define N_huge 105
	#define base 100000000
	typedef long long value;
	value a[N_huge];int len;
	void clear(){len=1;a[len]=0;}
	huge(){clear();}
	huge operator =(huge b){
		len=b.len;for (int i=1;i<=len;++i)a[i]=b.a[i];
	}
	huge operator +(huge b){
		int L=len>b.len?len:b.len;huge tmp;
		for (int i=1;i<=L+1;++i)tmp.a[i]=0;
		for (int i=1;i<=L;++i){
			if (i>len)tmp.a[i]+=b.a[i];
			else if (i>b.len)tmp.a[i]+=a[i];
			else {
				tmp.a[i]+=a[i]+b.a[i];
				if (tmp.a[i]>=base){
					tmp.a[i]-=base;++tmp.a[i+1];
				}
			}
		}
		if (tmp.a[L+1])tmp.len=L+1;
			else tmp.len=L;
		return tmp;
	}
	huge operator -(huge b){
		int L=len>b.len?len:b.len;huge tmp;
		for (int i=1;i<=L+1;++i)tmp.a[i]=0;
		for (int i=1;i<=L;++i){
			if (i>b.len)b.a[i]=0;
			tmp.a[i]+=a[i]-b.a[i];
			if (tmp.a[i]<0){
				tmp.a[i]+=base;--tmp.a[i+1];
			}
		}
		while (L>1&&!tmp.a[L])--L;
		tmp.len=L;
		return tmp;
	}
	huge operator *(huge b){
		int L=len+b.len;huge tmp;
		for (int i=1;i<=L;++i)tmp.a[i]=0;
		for (int i=1;i<=len;++i)
			for (int j=1;j<=b.len;++j){
				tmp.a[i+j-1]+=a[i]*b.a[j];
				if (tmp.a[i+j-1]>=base){
					tmp.a[i+j]+=tmp.a[i+j-1]/base;
					tmp.a[i+j-1]%=base;
				}
			}
		tmp.len=len+b.len;
		while (tmp.len>1&&!tmp.a[tmp.len])--tmp.len;
		return tmp;
	}
	pair<huge,huge> divide(huge a,huge b){
		int L=a.len;huge c,d;
		for (int i=L;i;--i){
			c.a[i]=0;d=d*base;d.a[1]=a.a[i];
			//while (d>=b){d-=b;++c.a[i];}
			int l=0,r=base-1,mid;
			while (l<r){
				mid=(l+r+1)>>1;
				if (b*mid<=d)l=mid;
					else r=mid-1;
			}
			c.a[i]=l;d-=b*l;
		}
		while (L>1&&!c.a[L])--L;c.len=L;
		return make_pair(c,d);
	}
	huge nie(huge a,huge b){  //fast divide
		int L=a.len;huge c,d;
		for (int i=L;i;--i){
			c.a[i]=0;d=d*base;d.a[1]=a.a[i];
			//while (d>=b){d-=b;++c.a[i];}
			int l=0,r=base-1,mid;
			while (l<r){
				mid=(l+r+1)>>1;
				if (b*mid<=d)l=mid;
					else r=mid-1;
			}
			c.a[i]=l;d-=b*l;
		}
		while (L>1&&!c.a[L])--L;c.len=L;
		return c;
	}
	huge operator /(huge b){return divide(*this,b).first;}
	huge operator %(huge b){return divide(*this,b).second;}
	huge &operator +=(huge b){*this=*this+b;return *this;}
	huge &operator -=(huge b){*this=*this-b;return *this;}
	huge &operator *=(huge b){*this=*this*b;return *this;}
	huge &operator ++(){huge T;T=1;*this=*this+T;return *this;}
	huge &operator --(){huge T;T=1;*this=*this-T;return *this;}
	huge &operator ++(int){huge T;T=1;*this=*this+T;return *this;}
	huge operator +(value x){huge T;T=x;return *this+T;}
	huge operator -(value x){huge T;T=x;return *this-T;}
	huge operator *(value x){huge T;T=x;return *this*T;}
	huge operator /(value x){huge T;T=x;return *this/T;}
	huge operator %(value x){huge T;T=x;return *this%T;}
	huge operator *=(value x){*this=*this*x;return *this;}
	huge operator +=(value x){*this=*this+x;return *this;}
	huge operator -=(value x){*this=*this-x;return *this;}
	huge operator /=(value x){*this=*this/x;return *this;}
	huge operator %=(value x){*this=*this%x;return *this;}
	void operator =(value x){
		len=0;
		while (x)a[++len]=x%base,x/=base;
		if (!len)a[++len]=0;
	}
	bool operator <(huge b){
		if (len<b.len)return 1;
		if (len>b.len)return 0;
		for (int i=len;i;--i){
			if (a[i]<b.a[i])return 1;
			if (a[i]>b.a[i])return 0;
		}
		return 0;
	}
	bool operator ==(huge b){
		if (len!=b.len)return 0;
		for (int i=len;i;--i)
			if (a[i]!=b.a[i])return 0;
		return 1;
	}
	bool operator >(huge b){return !(*this<b);}
	bool operator <=(huge b){return (*this<b)||(*this==b);}
	bool operator >=(huge b){return (*this>b)||(*this==b);}
	void print(){
		printf("%d",(int)a[len]);
		for (int i=len-1;i;--i){
			for (int j=base/10;j>=10;j/=10){
				if (a[i]<j)printf("0");
					else break;
			}
			printf("%d",(int)a[i]);
		}
		printf("\n");
	}
};
int main(){
	huge a,b,c;
	//a=123;b=456;
	/*c=a+b;c.print();
	c=b-a;c.print();
	c=a*b;c.print();*/
	//c=b/a;c.print();
	a=1213;b=4566789;
	//a=10;b=123;
	c=b/a;c.print();
	c=b%a;c.print();
	system("pause");
	return 0;
}


