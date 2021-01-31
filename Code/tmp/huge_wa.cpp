#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct huge{
	typedef long long value;
	#define Maxn_huge 205
	#define base 10000
	value *a;
	static value tmp[Maxn_huge+10];
	int len,Mlen;
	void clear(int n=5){
		Mlen=n++;a=new value[n];
		len=1;a[len]=0;
	}
	huge(int n=5){clear(n);}
	huge operator +(huge &b){
	int L=len>b.len?len:b.len,TL,i;
	memset(tmp,0,sizeof(value)*(L+2));
	for (i=1;i<=L;++i){
		if (i>len)tmp[i]+=b.a[i];
		else if (i>b.len)tmp[i]+=a[i];
			else {
				tmp[i]+=a[i]+b.a[i];
				if (tmp[i]>=base){
				   tmp[i]-=base;++tmp[i+1];
				}
			}
		}
		if (tmp[i+1])TL=L+1;
			else TL=L;
		huge T(Mlen);memcpy(T.a,tmp,sizeof(value)*(TL+1));
		T.len=TL;return T;
	}
	huge operator *(huge &b){
		int L=len+b.len,TL,i,j;
		memset(tmp,0,sizeof(value)*(L+2));
		for (i=1;i<=len;++i)
			for (j=1;j<=b.len;++j){
				tmp[i]+=a[i]*b.a[j];
				if (tmp[i]>=base){
					tmp[i+1]+=tmp[i]/base;
					tmp[i]%=base;
				}
			}
		TL=len+b.len;
		while (TL>1&&!tmp[TL])--TL;
		huge T(Mlen);memcpy(T.a,tmp,sizeof(value)*(TL+1));
		T.len=TL;return T;
	}
	huge &operator +=(huge &b){
		*this=*this+b;
		return *this;
	}
	huge &operator ++(){
		huge T(1);T=1;
		*this=*this+T;
		return *this;
	}
	void operator ++(int){
		huge T(1);T=1;
		*this=*this+T;
	}
	huge operator +(value x){
		huge T(20);T=x;
		return *this+T;
	}
	huge operator *(value x){
		huge T(20);T=x;
		return *this*T;
	}
	void operator =(value x){
		len=0;
		while (x)a[++len]=x%base,x/=base;
		if (!len)a[++len]=0;
	}
	/*void operator =(char s[]){
		int L=strlen(s);
		len=0;
		while (x)a[++len]=x%base,x/=base;
		if (!len)a[++len]=0;
	}*/
	bool operator <(huge &b){
		if (len<b.len)return 1;
		if (len>b.len)return 0;
		for (int i=len;i;--i){
			if (a[i]<b.a[i])return 1;
			if (a[i]>b.a[i])return 0;
		}
		return 0;
	}
	bool operator ==(huge &b){
		if (len!=b.len)return 0;
		for (int i=len;i;--i)
			if (a[i]!=b.a[i])return 0;
		return 1;
	}
	bool operator <=(huge &b){
		return (*this<b)||(*this==b);
	}
	bool operator >(huge &b){
		return !(*this<b);
	}
	void print(){
		if (len)printf("%d",(int)a[len]);
		for (int i=len-1;i;--i){
			for (int j=base/10;j>9;j/=10){
				if (a[i]<j)printf("0");
					else break;
			}
			printf("%d",(int)a[i]);
		}
		printf("\n");
	}
};huge::value huge::tmp[Maxn_huge+10];
int main(){
	huge a,b;
	a=1052350002;a.print();
	++a;a=a+5;
	a.print();
	a=a*3;
	a.print();
	b=123;
	printf("%d\n",a<b);
	system("pause");
}

