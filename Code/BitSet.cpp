#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<bitset>
using namespace std;
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
const int maxn=100000;
#define func(A,B,n){ \
	int t1,x=rand()*rand()%maxn; \
	t1=clock(); \
	for (int i=1;i<=n;++i)~A; \
	printf("~ time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n;++i)A|=B; \
	printf("| time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n;++i)A&=B; \
	printf("& time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n;++i)A^=B; \
	printf("^ time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n<<4;++i)A=B; \
	printf("= time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n;++i)A=~B; \
	printf("=~ time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n<<4;++i)A.reset(); \
	printf("reset time=%d\n",clock()-t1); \
	t1=clock(); \
	for (int i=1;i<=n;++i)A.flip(); \
	printf("flip time=%d\n",clock()-t1); \
	for (int i=1;i<=n<<5;++i)A[x]; \
	printf("[x] time=%d\n",clock()-t1); \
	printf("\n"); \
}
#define func1(A,B,n){ \
	int t1,x=rand()*rand()%maxn; \
	t1=clock(); \
	for (int i=1;i<=n<<4;++i)A=B; \
	printf("= time=%d\n",clock()-t1); \
}
#define func2(A,B,n){ \
	int t1,x=rand()*rand()%maxn; \
	t1=clock(); \
	for (int i=1;i<=n;++i)~A; \
	printf("~ time=%d\n",clock()-t1); \
}
void test(){
	static bitset<maxn> A,B;
	static BitSet<maxn> a,b;
	func(A,B,32000);
	func(a,b,32000);
	/*t1=clock();
	for (int i=1;i<=300000;++i)a.reset();
	printf("rp time=%d\n",clock()-t1);*/
}
#define N 50
BitSet<N> A,B,C(0xffff-1);
void test1(){
	A.set(1,1);A.set(4,1);A.set(40,1);A.print();
	B="0111";B.print();
	A|=B;A.print();
	A&=B;A.print();
	A=~A;A.print();
	printf("cnt=%d\n",A.count());
	A.flip();A.print();
	for (int i=0;i<5;++i)printf("%d\n",A[i]);
	C.print();
	if (C)printf("test ok\n");
	BitSet<N> D;D=C;D.flip();D.print();
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//test1();
	test();
	system("pause");for (;;);
	return 0;
}
/*
~ time=390
| time=422
& time=437
^ time=422
= time=375
=~ time=453
reset time=344
flip time=328
[x] time=360

~ time=390
| time=328
& time=313
^ time=312
= time=391
=~ time=437
reset time=344
flip time=328
[x] time=344
*/


